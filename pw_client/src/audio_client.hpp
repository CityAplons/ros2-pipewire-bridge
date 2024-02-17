#pragma once

#include "client.hpp"

namespace pw
{

enum class AudioDirection { IN, OUT };

class AudioClient : public Client
{
private:
  struct pw_stream * stream_;

  static void stream_destroy_ev_(void * data);
  static void stream_state_ev_(
    void * data, enum pw_stream_state old,
    enum pw_stream_state state, const char * error);
  static void stream_control_info_ev_(
    void * data, uint32_t id,
    const struct pw_stream_control * control);
  static void stream_io_changed_ev_(
    void * data, uint32_t id, void * area,
    uint32_t size);
  static void stream_param_changed_ev_(
    void * data, uint32_t id,
    const struct spa_pod * param);
  static void stream_add_buffer_ev_(void * data, struct pw_buffer * buffer);
  static void stream_remove_buffer_ev_(void * data, struct pw_buffer * buffer);
  static void stream_process_ev_(void * data);
  static void stream_drained_ev_(void * data);
  static void stream_command_ev_(void * data, const struct spa_command * command);
  static void stream_trigger_done_ev_(void * data);
  const struct pw_stream_events stream_events = {
    PW_VERSION_STREAM_EVENTS,    // .version
    stream_destroy_ev_,          // .destroy
    stream_state_ev_,            // .state_changed
    stream_control_info_ev_,     // .control_info
    stream_io_changed_ev_,       // .io_changed
    stream_param_changed_ev_,    // .param_changed
    stream_add_buffer_ev_,       // .add_buffer
    stream_remove_buffer_ev_,    // .remove_buffer
    stream_process_ev_,          // .process
    stream_drained_ev_,          // .drained
    stream_command_ev_,          // .command
    stream_trigger_done_ev_,     // .trigger_done
  };

public:
  explicit AudioClient(const std::string & name, AudioDirection type);
  explicit AudioClient(AudioClient && other)
  : stream_{other.stream_}
  {
    other.stream_ = nullptr;
  }
  ~AudioClient();
};

}  // namespace pw
