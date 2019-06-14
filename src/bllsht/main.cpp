#include "egse/EGSE.hpp"
#include "broadcast/GRPCBroadcaster.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <iomanip>

void start() {
  auto egse = bllsht::EGSE("sensors.json");
  bool quit = false;
  auto broadcaster = bllsht::broadcast::GRPCBroadcaster();

  while (!quit) {
    egse.updateData();
    egse.broadcastData(broadcaster);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
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