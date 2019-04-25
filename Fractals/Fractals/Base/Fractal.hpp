//
// Created by Lyosha12 on 29.04.2018.
//

#ifndef LAB_3_FRACTAL_HPP
#define LAB_3_FRACTAL_HPP

#include <chrono>
using namespace std::chrono_literals;

#include <SFML/Graphics.hpp>

#include "../../Fluctlight/Fluctlight.hpp"
#include "../../TimeCounter/TimeCounter.hpp"

class Fractal: public sf::Drawable {
  public:
    virtual void generateNextLevel(sf::VideoMode screen) = 0;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    void updateColor();
    
  protected:
    template <class IntervalType = std::chrono::seconds>
    Fractal(
        Fluctlight const& background,
        bool isPrintLevelsIndividual = true,
        IntervalType interval = 1s
    ): background(background)
     , is_print_only_one_level(isPrintLevelsIndividual)
     , controller(interval)
    { }
  
  protected:
    struct Level: sf::Drawable {
        struct Part: sf::Drawable {
            Part(
                sf::Sprite sprite,
                std::unique_ptr<sf::Texture> texture,
                std::vector<sf::Transform>&& transforms
            );
            Part(Part const&) = delete;
            Part(Part&& other);
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
            // Mutable need for adaptation to mutable background color.
            // Sprite position as default - (0, 0).
            mutable sf::Sprite sprite;
            std::unique_ptr<sf::Texture> texture = nullptr;
            // Transforms sprite positions starts at (0, 0).
            std::vector<sf::Transform> transforms;
        };
    
        Level(Level&& other);
        Level(std::vector<Part> parts);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        std::vector<Part> parts;
    };
  
  protected:
    Fluctlight const& background;
    std::vector<Level> levels;
    mutable int cur_level_to_print = 0;
    bool is_print_only_one_level;
    mutable TimeCounter<std::chrono::steady_clock> controller;
};


#endif //LAB_3_FRACTAL_HPP
