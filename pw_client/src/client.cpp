#include "client.hpp"

namespace pw
{

void Client::registry_ev_(
  void * data, uint32_t id, uint32_t permissions, const char * type, uint32_t version,
  const struct spa_dict * props)
{
  (void)permissions;
  (void)version;
  (void)props;
  if (!data || !type) {
    return;
  }

  Client * instance = static_cast<Client *>(data);
  if (instance->client_ != nullptr) {
    return;
  }

  if (strcmp(type, PW_TYPE_INTERFACE_Client) == 0) {
    instance->client_ =
      static_cast<pw_client *>(pw_registry_bind(
        instance->registry_, id, type, PW_VERSION_CLIENT,
        0));
    pw_client_add_listener(
      instance->client_, &instance->client_listener_,
      &instance->client_events_, instance);
  }
}

void Client::client_ev_(void * data, const struct pw_client_info * info)
{
  if (!data || !info) {
    return;
  }

  Client * instance = static_cast<Client *>(data);
  const struct spa_dict_item * item;

  printf("client %s: id:%u\n", instance->get_name().c_str(), info->id);
  printf("\tprops:\n");
  spa_dict_for_each(item, info->props) printf("\t\t%s: \"%s\"\n", item->key, item->value);
}

static void terminate(void * userdata, int signal_number)
{
  if (!userdata) {
    return;
  }

  Client * instance = static_cast<Client *>(userdata);
  instance->on_terminate(signal_number);
}

Client::Client(const std::string & name)
: connected_(false), name_(name), mutex_(nullptr)
{
  pw_init(nullptr, nullptr);
  loop_ = pw_thread_loop_new(name_.c_str(), nullptr);
  mutex_.update(loop_);

  const std::lock_guard<LoopMutex> lock(mutex_);

  // TODO: test.. these hooks is used only if pw_thread_loop_wait called
  pw_loop_add_signal(pw_thread_loop_get_loop(loop_), SIGINT, terminate, this);
  pw_loop_add_signal(pw_thread_loop_get_loop(loop_), SIGTERM, terminate, this);

  context_ = pw_context_new(pw_thread_loop_get_loop(loop_), nullptr, 0);

  pw_thread_loop_start(loop_);
}

Client::~Client()
{
  if (connected_) {
    disconnect();
  }

  pw_thread_loop_stop(loop_);
  pw_context_destroy(context_);
  pw_thread_loop_destroy(loop_);

  pw_deinit();
}

bool Client::connect()
{
  const std::lock_guard<LoopMutex> lock(mutex_);
  core_ = pw_context_connect(context_, nullptr, 0);
  if (!core_) {
    return false;
  }

  connected_ = true;
  registry_ = pw_core_get_registry(core_, PW_VERSION_REGISTRY, 0);
  pw_registry_add_listener(registry_, &registry_listener_, &registry_events_, this);
  return true;
}

void Client::disconnect()
{
  const std::lock_guard<LoopMutex> lock(mutex_);
  if (!core_) {
    return;
  }

  if (client_) {
    pw_proxy_destroy((struct pw_proxy *)client_);
  }

  if (registry_) {
    pw_proxy_destroy((struct pw_proxy *)registry_);
  }

  pw_core_disconnect(core_);
  connected_ = false;
}

void Client::on_terminate([[maybe_unused]] int signo)
{
  pw_thread_loop_signal(loop_, false);
}

}  // namespace pw
