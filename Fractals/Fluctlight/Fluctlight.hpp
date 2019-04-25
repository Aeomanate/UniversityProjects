//
// Created by Lyosha12 on 27.04.2018.
//

#ifndef TEST_SFML_FLUCTLIGHT_HPP
#define TEST_SFML_FLUCTLIGHT_HPP

#include <tuple>
#include <chrono>
using namespace std::chrono_literals;

#include <SFML/Graphics.hpp>

#include "../TimeCounter/TimeCounter.hpp"

class Fluctlight {
    using byte = unsigned char;
    
  public:
    template <class IntervalType = std::chrono::nanoseconds>
    Fluctlight(IntervalType interval = 0ns)
        : time_controller(interval)
    { }
    
    operator sf::Color();
    sf::Color get() const;
    sf::Color getInverted() const;
  
  private:
    std::tuple<int, int, int> getColorOffsets();
    void spontaneouslyChangeRandColorDirection();
    void offsetColors(std::tuple<int, int, int> offsets);
    int recalculate_direction(sf::Uint8 color, int color_index);
    int makeDirection(bool isDirectionPositive);
    
    
    int getColorIndex(char color_name);
    int getRandColorIndex();
    
    void changeColorDirection(int color_index);
    void changeColorActivity(int color_index);
    void randomChangeColorsActivity();
    
    bool isColorHasReachedBorder(sf::Uint8 color);
    bool isColorHasReachedUpBorder(sf::Uint8 color);
    bool isColorHasReachedDownBorder(sf::Uint8 color);
    bool isOneOfColorsReachedBorder();
    
    bool checkColorsActivity();
    bool isColorActive(int color_index);
    bool isDirectionPositive(int color_index);
  
  private:
    sf::Color color = {126, 50, 168};
    union Offset {
        union {
            struct {
                // 0 == -, 1 == +.
                byte A: 1;
                byte B: 1;
                byte G: 1;
                byte R: 1;
                byte : 4; // Missed.
            } rgba;
        } direction;
        
        union {
            struct {
                // Value of increase/decrease color R/G/B/A index.
                byte : 4; // Missed.
                byte A: 1;
                byte B: 1;
                byte G: 1;
                byte R: 1;
            } rgba;
        } color;
        // Direction/Color.
        //             RGBA rgba
        byte value { 0b1000'1000 };
    } offset;
    
    TimeCounter<std::chrono::steady_clock> time_controller;
};


#endif //TEST_SFML_FLUCTLIGHT_HPP
