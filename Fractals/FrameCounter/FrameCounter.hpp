//
// Created by Lyosha12 on 30.04.2018.
//

#ifndef LAB_3_FPS_HPP
#define LAB_3_FPS_HPP

#include <chrono>
using namespace std::chrono_literals;

#include "../TimeCounter/TimeCounter.hpp"

template <class ClockType = std::chrono::steady_clock>
class FrameCounter {
  public:
    template <class IntervalType = std::chrono::seconds>
    FrameCounter(IntervalType interval): controller(interval) { }
    
    size_t get() {
        ++current;
        if(controller.isIntervalPassed()) {
            fixed = current;
            current = 0;
        
            avg_fixed += fixed;
            ++count_checks;
        
            return fixed;
        } else {
            return fixed;
        }
    }
    size_t getAvg() const {
        return avg_fixed / count_checks;
    }
  
  private:
    size_t current = 0;
    size_t fixed = 0;
    size_t avg_fixed = 0;
    size_t count_checks = 1;
    TimeCounter<ClockType> controller;
};


#endif //LAB_3_FPS_HPP
