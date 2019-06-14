#include "egse/EGSE.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <iomanip>

void start() {
  auto egse = bllsht::EGSE("sensors.json");
  bool quit = false;

  auto sensors = egse.readSensors();

  while (!quit) {
    egse.updateData();

    for (auto const &s : sensors) {
      std::cout << s->name() << ": " << s->value() << '\n';
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