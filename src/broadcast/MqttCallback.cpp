#include "MqttCallback.hpp"

namespace bllsht::broadcast {
MqttCallback::MqttCallback(mqtt::async_client &cli, SafeQueue<Packet> &queue)
    : m_nretry(), m_cli(cli), m_queue(queue) {}

void MqttCallback::reconnect() {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  mqtt::connect_options connOpts;
  connOpts.set_keep_alive_interval(20);
  connOpts.set_clean_session(true);

  try {
    m_cli.connect(connOpts, nullptr, *this);
  } catch (const mqtt::exception &exc) {
    std::cerr << "[MQTT] Error: " << exc.what() << std::endl;
    exit(1);
  }
}

// Re-connection failure
void MqttCallback::on_failure(const mqtt::token &tok) {
  std::cout << "[MQTT] Reconnection failed" << std::endl;
  if (++m_nretry > 5) {
    exit(1);
  }
  reconnect();
}

// Re-connection success
void MqttCallback::on_success(const mqtt::token &tok) {
  std::cout << "[MQTT] Reconnection success" << std::endl;
  m_cli.subscribe("bllsht_command", 2);
}

void MqttCallback::connection_lost(const std::string &cause) {
  std::cout << "[MQTT] Connection lost" << std::endl;
  if (!cause.empty()) {
    std::cout << "[MQTT]\tcause: " << cause << std::endl;
  }

  std::cout << "[MQTT] Reconnecting" << std::endl;
  m_nretry = 0;
  reconnect();
}

void MqttCallback::message_arrived(mqtt::const_message_ptr msg) {
  // std::cout << "Message arrived" << std::endl;
  // std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
  // std::cout << "\t'" << msg->to_string() << "'\n" << std::endl;
  m_queue.push(nlohmann::json::parse(msg->to_string()));
}
} // namespace bllsht::broadcast
