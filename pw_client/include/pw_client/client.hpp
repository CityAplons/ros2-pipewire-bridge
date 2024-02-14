#pragma once

namespace pw {

enum class ClientType {
  AUDIO_STREAM,
}

class Client {
 using pod_t = int; // TODO: remap
 
 public:
  Client(/* args */);
  ~Client();

  bool connect(ClientType type);
  pod_t read();


 private:
  /* data */
};

}  // namespace pw
