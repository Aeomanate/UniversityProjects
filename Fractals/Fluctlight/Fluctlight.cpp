//
// Created by Lyosha12 on 27.04.2018.
//

#include "Fluctlight.hpp"

Fluctlight::
operator sf::Color() {
    if(time_controller.isIntervalPassed()) {
        offsetColors(getColorOffsets());
    }
    
    return color;
}

sf::Color Fluctlight::
get() const {
    return color;
}
sf::Color Fluctlight::
getInverted() const {
    sf::Uint8 max = std::numeric_limits<sf::Uint8>::max();
    return sf::Color(max - color.r, max - color.g, max - color.b);
}



std::tuple<int, int, int> Fluctlight::
getColorOffsets() {
    int offset_r = recalculate_direction(color.r, getColorIndex('R'));
    int offset_g = recalculate_direction(color.g, getColorIndex('G'));
    int offset_b = recalculate_direction(color.b, getColorIndex('B'));
    spontaneouslyChangeRandColorDirection();
    return { offset_r, offset_g, offset_b };
}
void Fluctlight::
spontaneouslyChangeRandColorDirection() {
    if(int chance = rand()%100;
    
       0 <= chance && chance <= 15 && time_controller.isIntervalPassed(10) &&
       !isOneOfColorsReachedBorder()
       
      )
    {
        changeColorDirection(getRandColorIndex());
    }
}

void Fluctlight::
offsetColors(std::tuple<int, int, int> offsets) {
    auto [offset_r, offset_g, offset_b] = offsets;
    
    // #define TEST_COLOR_OUTPUT
    #ifdef TEST_COLOR_OUTPUT
    static std::ofstream out("Debug output fluctlight.txt");
        static bool once = false;
        if(!once) {
            out << "Size offset: " << sizeof(Offset) << std::endl;
            out << "Old: (Activity)/(Increase).  " << std::endl;
            once = true;
        }
        out <<
            "R: " <<
            std::setw(3) << std::right << (int)color.r <<
            "(" << isColorActive(getColorIndex('R')) << ")/" <<
            "(" << std::setw(2) << offset_r << ")  " <<
    
            "G: " <<
            std::setw(3) << std::right << (int)color.g <<
            "(" << isColorActive(getColorIndex('G')) << ")/" <<
            "(" << std::setw(2) << offset_g << ")  " <<
    
            "B: " <<
            std::setw(3) << std::right << (int)color.b <<
            "(" << isColorActive(getColorIndex('B')) << ")/" <<
            "(" << std::setw(2) << offset_b << ")  " <<
    
            std::endl;
    #endif
    
    color.r = static_cast<sf::Uint8> (color.r + offset_r*offset.color.rgba.R);
    color.g = static_cast<sf::Uint8> (color.g + offset_g*offset.color.rgba.G);
    color.b = static_cast<sf::Uint8> (color.b + offset_b*offset.color.rgba.B);
    
}

int Fluctlight::
recalculate_direction(sf::Uint8 color, int color_index) {
    
    if(isColorHasReachedBorder(color)) {
        // A direction should not create an overflow in next step.
        if(isColorActive(color_index))
            changeColorDirection(color_index);
        
        randomChangeColorsActivity(); // Just for fun.
        if(!checkColorsActivity())
            changeColorActivity(getRandColorIndex());
        
    }
    
    // Return direction for requested index: 1 or -1.
    return makeDirection(isDirectionPositive(color_index));
}

int Fluctlight::
makeDirection(bool isDirectionPositive) {
    return ~0 + isDirectionPositive + isDirectionPositive;
}


int Fluctlight::
getColorIndex(char color_name) {
    return color_name == 'R' ? 3 :
           color_name == 'G' ? 2 :
           color_name == 'B' ? 1 :
           // color_name == 'A' ? 0 : // Not use in Fluctlight
           throw std::logic_error("not of RGB");
}

int Fluctlight::
getRandColorIndex() {
    return 1 + rand()%3; // Besides alpha channel.
}


void Fluctlight::
changeColorDirection(int color_index) {
    offset.value ^= 1 << color_index;
}

void Fluctlight::
changeColorActivity(int color_index) {
    offset.value ^= 1 << color_index << 4;
}

void Fluctlight::
randomChangeColorsActivity() {
    int inactive_bits = (rand()%8) << 1;
    int active_bits = (rand()%8) << 1;
    offset.value &= ~(inactive_bits << 4);
    offset.value |= active_bits << 4;
}


bool Fluctlight::
isColorHasReachedBorder(sf::Uint8 color) {
    return isColorHasReachedUpBorder(color) || isColorHasReachedDownBorder(color);
}

bool Fluctlight::
isColorHasReachedUpBorder(sf::Uint8 color) {
    return 255 == color;
}

bool Fluctlight::
isColorHasReachedDownBorder(sf::Uint8 color) {
    return 0 == color;
}

bool Fluctlight::
isOneOfColorsReachedBorder() {
    return isColorHasReachedBorder(color.r) &&
           isColorHasReachedBorder(color.g) &&
           isColorHasReachedBorder(color.b);
}


bool Fluctlight::
checkColorsActivity() {
    return static_cast<bool> (offset.value & (0b1110 << 4));
}

bool Fluctlight::
isColorActive(int color_index) {
    return static_cast<bool> (offset.value & (1 << color_index << 4));
}

bool Fluctlight::
isDirectionPositive(int color_index) {
    return static_cast<bool> (offset.value & (1 << color_index));
}


