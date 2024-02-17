#include <pipewire/pipewire.h>

#include <mutex>

namespace pw
{

using pw_lockable = struct pw_thread_loop *;

class LoopMutex
{
  pw_lockable m_lockable;

public:
  LoopMutex(const pw_lockable lockable)
  : m_lockable(lockable) {}

  void update(const pw_lockable lockable)
  {
    m_lockable = lockable;
  }

  void lock()
  {
    pw_thread_loop_lock(m_lockable);
  }

  void unlock()
  {
    pw_thread_loop_unlock(m_lockable);
  }
};
} // namespace pw
