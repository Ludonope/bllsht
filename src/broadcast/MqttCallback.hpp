#ifndef BLLSHT_BROADCAST_MQTTCALLBACK_HPP
#define BLLSHT_BROADCAST_MQTTCALLBACK_HPP

#include "bllsht/BroadcastPacket.hpp"
#include "bllsht/SafeQueue.hpp"
#include <mqtt/async_client.h>

namespace bllsht::broadcast {
class MqttCallback : public virtual mqtt::callback,
                     public virtual mqtt::iaction_listener {
public:
  MqttCallback(mqtt::async_client &cli, SafeQueue<Packet> &queue);

private:
  void reconnect();
  virtual void on_failure(mqtt::token const &tok);
  virtual void on_success(mqtt::token const &tok);
  virtual void connection_lost(std::string const &cause);
  virtual void message_arrived(mqtt::const_message_ptr msg);

  int m_nretry;
  mqtt::async_client &m_cli;
  SafeQueue<Packet> &m_queue;
};
} // namespace bllsht::broadcast

#endif // BLLSHT_BROADCAST_MQTTCALLBACK_HPP