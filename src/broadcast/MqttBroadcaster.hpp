#ifndef BLLSHT_BROADCAST_MQTTBROADCASTER_HPP
#define BLLSHT_BROADCAST_MQTTBROADCASTER_HPP

#include "bllsht/IBroadcaster.hpp"
#include "mqtt/async_client.h"
#include "mqtt/client.h"
#include "MqttCallback.hpp"
#include "json/json.hpp"
#include "bllsht/SafeQueue.hpp"
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace bllsht::broadcast {

class MqttBroadcaster : public IBroadcaster {
public:
  MqttBroadcaster();
  virtual ~MqttBroadcaster();

  virtual void broadcast(Packet &data);
  virtual bool fetch(Packet &data);

private:
  mqtt::async_client m_client;
  MqttCallback m_cb;
  SafeQueue<Packet> m_queue;
};
} // namespace bllsht::broadcast

#endif // BLLSHT_BROADCAST_MQTTBROADCASTER_HPP