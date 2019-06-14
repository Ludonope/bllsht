#include "egse/EGSE.hpp"
#include <chrono>
#include <iostream>
#include <thread>

void start() {
  auto egse = bllsht::EGSE("sensors.json");
  bool quit = false;

  auto sensors = egse.readSensors();

  while (!quit) {
    egse.updateData();

    for (auto const &s : sensors) {
      std::cout << s->value() << std::endl;
    }
    std::cout << std::endl;

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