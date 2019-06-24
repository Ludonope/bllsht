#include "egse/EGSE.hpp"
#include "broadcast/MqttBroadcaster.hpp"
#include "BroadcastPacket.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <iomanip>

void start() {
  bool quit = false;
  auto broadcaster = bllsht::broadcast::MqttBroadcaster();
  auto egse = bllsht::EGSE("sensors.json");

  while (!quit) {
    egse.updateData();
    egse.broadcastData(broadcaster);
    bllsht::broadcast::Packet packet;

    while (broadcaster.fetch(packet)) {
      // std::cout << packet.dump() << std::endl;
      egse.executeCommand(packet);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  // auto data1 = bllsht::broadcast::make_packet("LOX Tank", "TC", 352.9, "psi");
  // auto data2 = bllsht::broadcast::make_packet("LOX Tank", "TC", 42.0);
  // broadcaster.broadcast(data1);
  // broadcaster.broadcast(data2);

  // while (!quit) {
  // }
}

int main() {
  try {
    start();
  } catch (std::exception const &e) {
    std::cerr << "Fatal error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}