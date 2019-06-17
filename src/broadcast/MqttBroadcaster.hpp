#ifndef BLLSHT_BROADCAST_MQTTBROADCASTER_HPP
#define BLLSHT_BROADCAST_MQTTBROADCASTER_HPP

#include "bllsht/IBroadcaster.hpp"
#include "mqtt/client.h"
#include <iostream>
#include <sstream>
#include <string>

namespace bllsht::broadcast {
class MqttBroadcaster : public IBroadcaster {
public:
  MqttBroadcaster();
  virtual ~MqttBroadcaster();

  virtual void broadcast(std::string const &component, std::string const &type,
                         double const &value) {
    broadcast(component, type, value, "");
  }
  virtual void broadcast(std::string const &component, std::string const &type,
                         double const &value, std::string const &unit) {
    _broadcast(component, type, value, unit);
  }

  virtual void broadcast(std::string const &component, std::string const &type,
                         bool const &value) {
    broadcast(component, type, value, "");
  }
  virtual void broadcast(std::string const &component, std::string const &type,
                         bool const &value, std::string const &unit) {
    _broadcast(component, type, value, unit);
  }

private:
  template <typename T>
  void _broadcast(std::string const &component, std::string const &type,
                  T const &value, std::string const &unit) {
    std::ostringstream os;
    os << '[' << component << "] " << type << ": " << value << unit;
    auto pubmsg = mqtt::make_message("telemetry", os.str());

    m_client.publish(pubmsg);
  }

  mqtt::async_client m_client;
};
} // namespace bllsht::broadcast

#endif // BLLSHT_BROADCAST_MQTTBROADCASTER_HPP