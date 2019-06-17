#include "MqttBroadcaster.hpp"

namespace bllsht::broadcast {
  MqttBroadcaster::MqttBroadcaster() : m_client("127.0.0.1", "bllsht") {
    // mqtt::callback cb;
    // client.set_callback(cb);

    mqtt::connect_options conopts;
    mqtt::message willmsg("test", "test playload", 1, true);
    mqtt::will_options will(willmsg);
    conopts.set_will(will);

    std::cout << "  ...OK" << std::endl;

    std::cout << "\nConnecting..." << std::endl;
    mqtt::token_ptr conntok = m_client.connect(conopts);
    std::cout << "Waiting for the connection..." << std::endl;
    conntok->wait();
    std::cout << "  ...OK" << std::endl;
  }

  MqttBroadcaster::~MqttBroadcaster() {
		// Double check that there are no pending tokens
		auto toks = m_client.get_pending_delivery_tokens();
		if (!toks.empty())
			std::cout << "Error: There are pending delivery tokens!" << std::endl;

		// Disconnect
		std::cout << "\nDisconnecting..." << std::endl;
		mqtt::token_ptr conntok = m_client.disconnect();
		conntok->wait();
		std::cout << "  ...OK" << std::endl;
  }
}