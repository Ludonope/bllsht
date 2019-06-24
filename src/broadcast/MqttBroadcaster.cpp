#include "MqttBroadcaster.hpp"
#include "MqttCallback.hpp"
#include "mqtt/async_client.h"

namespace bllsht::broadcast {
MqttBroadcaster::MqttBroadcaster()
    : m_client("127.0.0.1", "bllsht_server"), m_cb(m_client, m_queue) {
  mqtt::connect_options connOpts{

  };
  connOpts.set_keep_alive_interval(20);
  connOpts.set_clean_session(true);

  std::cout << "[MQTT] Connecting mqtt client" << std::endl;
  m_client.set_callback(m_cb);
  mqtt::token_ptr conntok = m_client.connect(connOpts, nullptr, m_cb);
  std::cout << "[MQTT] Waiting for the connection...";
  conntok->wait();
  std::cout << "[MQTT] Connected" << std::endl;
}

MqttBroadcaster::~MqttBroadcaster() {
  // Double check that there are no pending tokens
  auto toks = m_client.get_pending_delivery_tokens();
  if (!toks.empty())
    std::cout << "[MQTT] Warning: there are pending delivery tokens"
              << std::endl;

  // Disconnect
  std::cout << "[MQTT] Disconnecting..." << std::endl;
  mqtt::token_ptr conntok = m_client.disconnect();
  conntok->wait();
  std::cout << " done" << std::endl;
}

void MqttBroadcaster::broadcast(Packet &data) {
  auto pubmsg = mqtt::make_message("telemetry", data.dump());
  m_client.publish(pubmsg);
}

bool MqttBroadcaster::fetch(Packet &data) {
  return m_queue.pop(data);
}
} // namespace bllsht::broadcast