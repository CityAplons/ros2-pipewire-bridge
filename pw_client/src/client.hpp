#pragma once

#include "utils/pw_lock.hpp"

#include <pipewire/pipewire.h>

#include <cstdint>
#include <string>

namespace pw
{

class Client
{
private:
  bool connected_;
  const std::string name_;

  struct pw_thread_loop * loop_ = nullptr;
  struct pw_context * context_ = nullptr;
  struct pw_core * core_ = nullptr;

  struct pw_registry * registry_ = nullptr;
  struct spa_hook registry_listener_;

  struct pw_client * client_ = nullptr;
  struct spa_hook client_listener_;

  // static void registry_remove_ev_(void *data, uint32_t id);
  static void registry_ev_(
    void * data, uint32_t id, uint32_t permissions, const char * type, uint32_t version,
    const struct spa_dict * props);
  const struct pw_registry_events registry_events_ = {
    PW_VERSION_REGISTRY_EVENTS,  // .version
    registry_ev_,                // .global
    nullptr,                     // .global_remove
  };

  static void client_ev_(void * data, const struct pw_client_info * info);
  // static void client_permissions_ev_(void *data, uint32_t index,
  //                                    uint32_t n_permissions,
  //                                    const struct pw_permission
  //                                    *permissions);
  const struct pw_client_events client_events_ = {
    PW_VERSION_CLIENT_EVENTS,  // .version
    client_ev_,                // .info
    nullptr                    // .permissions
  };

  LoopMutex mutex_;

public:
  Client(const std::string & name);
  Client()
  : Client("ros2_generic_client")
  {
  }
  virtual ~Client();

  Client(Client & other) = delete;
  Client(Client && other)
  : loop_{other.loop_}
    , context_{other.context_}
    , core_{other.core_}
    , registry_{other.registry_}
    , client_{other.client_}
    , mutex_{std::move(other.mutex_)}
  {
    other.loop_ = nullptr;
    other.context_ = nullptr;
    other.core_ = nullptr;
    other.registry_ = nullptr;
    other.client_ = nullptr;
  }

  virtual bool connect();
  virtual void disconnect();
  virtual void on_terminate(int signo);
  virtual const std::string & get_name()
  {
    return name_;
  }
};

}  // namespace pw
