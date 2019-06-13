#include "egse/EGSE.hpp"
#include <chrono>
#include <iostream>
#include <thread>

void start() {
  auto egse = bllsht::EGSE("config.yaml");
  bool quit = false;

  while (!quit) {
    egse.updateData();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
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