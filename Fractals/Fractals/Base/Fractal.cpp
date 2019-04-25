//
// Created by Lyosha12 on 29.04.2018.
//

#include "Fractal.hpp"

void Fractal::
draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(controller.isIntervalPassed()) {
        cur_level_to_print = (cur_level_to_print + 1)%(levels.size() + 1);
    }
    
    if(cur_level_to_print - 1 < 0)
        return;
    
    for(int i = (cur_level_to_print - 1)*is_print_only_one_level;
        i <= (cur_level_to_print - 1);
        ++i)
    {
        target.draw(levels[i], states);
    }
}

void Fractal::
updateColor() {
    for(auto& level: levels)
        for(auto& part: level.parts)
            part.sprite.setColor(background.getInverted());
}





Fractal::Level::
Level(std::vector<Part> parts): parts(move(parts)) { }

Fractal::Level::
Level(Level&& other): parts(move(other.parts)) { }

void Fractal::Level::
draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(auto const& part: parts) {
        target.draw(part, states);
    }
}




Fractal::Level::Part::
Part(
    sf::Sprite sprite,
    std::unique_ptr<sf::Texture> texture,
    std::vector<sf::Transform>&& transforms
): sprite(sprite)
 , texture(move(texture))
 , transforms(move(transforms))
{ }

Fractal::Level::Part::
Part(Part&& other)
: sprite(other.sprite)
, texture(move(other.texture))
, transforms(move(other.transforms))
{ }

void Fractal::Level::Part::
draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(auto const& transform: transforms) {
        sf::RenderStates cur_state = states;
        cur_state.transform *= transform;
        target.draw(sprite, cur_state);
    }
}