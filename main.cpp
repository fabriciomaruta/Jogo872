#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "playback.hpp"

#include <iostream>

#include "model.hpp"

#include<ncurses.h>

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int main(){
  
}
