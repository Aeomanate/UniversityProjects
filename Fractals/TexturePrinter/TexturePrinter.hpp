//
// Created by Lyosha12 on 30.04.2018.
//

#ifndef LAB_3_TEXTUREPRINTER_HPP
#define LAB_3_TEXTUREPRINTER_HPP

#include <string>
#include <memory>
#include <utility>
#include <SFML/Graphics.hpp>

class TexturePrinter {
  public:
    TexturePrinter(std::string font_name = "arial") {
        if(!font.loadFromFile(font_name += ".ttf"))
            throw std::runtime_error("Font <" + font_name + "> not loaded. "
                                     "Try to drop it with this executable");
        
        text.setFont(font);
    }
    void operator() (sf::RenderWindow& target) {
        target.draw(text);
    }
    
    TexturePrinter& setString(std::string str = "Test") {
        text.setString(str);
        return *this;
    }
    TexturePrinter& setCharacterPixelSize(size_t size) {
        text.setCharacterSize(size);
        return *this;
    }
    TexturePrinter& setColor(sf::Color new_color) {
        text.setFillColor(new_color);
        return *this;
    }
    TexturePrinter& setPosition(sf::Vector2f new_position) {
        text.setPosition(new_position);
        return *this;
    }
    
  
  private:
    sf::Font font;
    sf::Text text;
};


#endif //LAB_3_TEXTUREPRINTER_HPP
