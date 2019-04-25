//
// Created by Lyosha12 on 30.04.2018.
//

#include "A.hpp"


A::
A(Fluctlight const& background, sf::VideoMode screen)
    : Fractal(background)
    , generator(6*screen.width*0.95f)
{
    generateNextLevel(sf::VideoMode());
    levels[0].parts.front().transforms.push_back(
        sf::Transform().translate(screen.width/2, screen.height/2)
    );
}

void A::
generateNextLevel([[maybe_unused]] sf::VideoMode screen) {
    if(!generator.toDivide())
        return;
    
    std::unique_ptr<sf::Texture> texture = generateTexture(
        static_cast<size_t>(generator.getBasisLength() + 0.5), 1
    );
    sf::Sprite sprite = generateSprite(texture);
    
    std::vector<sf::Transform> positions;
    if(levels.size() != 0)
        for(auto const& cur_position: levels.back().parts.front().transforms) {
            std::vector<sf::Transform> new_positions = generatePositions(cur_position);
            positions.insert(positions.end(), new_positions.begin(), new_positions.end());
        }
    
    
    std::vector<Level::Part> parts;
    parts.emplace_back(sprite, std::move(texture), std::move(positions));
    levels.push_back(move(parts));
}


std::unique_ptr<sf::Texture> A::
generateTexture(size_t width, size_t height) {
    buffer.create(width, height);
    buffer.draw(generator);
    buffer.display();
    return std::unique_ptr<sf::Texture> (new sf::Texture(buffer.getTexture()));
}

sf::Sprite A::
generateSprite(std::unique_ptr<sf::Texture> const& texture) {
    sf::Sprite sprite(*texture);
    
    // Set the center of transforms from left-up corner to top-bottom
    sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y - 1);
    
    return sprite;
}

std::vector<sf::Transform> A::
generatePositions(sf::Transform line_center) {
    std::vector<sf::Transform> positions;
    float length = generator.getBasisLength();
    
    auto add = [&positions] (sf::Transform const& what) mutable {
        positions.push_back(what);
    };
    
    add(line_center.translate( -length*3 + length/2, 0       )); // 1
    add(line_center.translate( length/2, -length/2).rotate(90)); // 2
    add(line_center.translate(-length  ,  0       )           ); // 3
    line_center.rotate(-90);
    add(line_center.translate( length/2, -length/2)           ); // 4
    add(line_center.translate( length  ,  0                  )); // 5
    add(line_center.translate( length/2,  length/2).rotate(90)); // 6
    line_center.rotate(-90);
    add(line_center.translate(-length/2,  length/2)           ); // 7
    add(line_center.translate(-length/2,  length/2).rotate(90)); // 8
    line_center.rotate(-90);
    add(line_center.translate( length/2,  length/2)           ); // 9
    add(line_center.translate( length  , 0                   )); // 10
    add(line_center.translate( length/2,  length/2).rotate(90)); // 11
    line_center.rotate(-90);
    add(line_center.translate(-length/2,  length/2           )); // 12
    add(line_center.translate(-length/2,  length/2).rotate(90)); // 13
    line_center.rotate(-90);
    add(line_center.translate( length/2,  length/2           )); // 14
    add(line_center.translate( length  , 0                   )); // 15
    add(line_center.translate( length/2, -length/2).rotate(90)); // 16
    add(line_center.translate(-length  , 0                   )); // 17
    line_center.rotate(-90);
    add(line_center.translate( length/2, -length/2           )); // 18
    
    return positions;
}




A::Generator::Generator(float line_length) // https://en.sfml-dev.org/forums/index.php?topic=23955.0
    : line { {{0.5, 0}}, {{static_cast<int>(line_length) - 0.5f, 0}} }
{ }

void A::
Generator::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(line, std::size(line), sf::Lines, states);
}

bool A::
Generator::toDivide() {
    line[1].position.x = static_cast<int>(line[1].position.x / 6);
    
    // Check for ability to use generator.
    return line[1].position.x > 1;
}

size_t A::
Generator::getBasisLength() const {
    return static_cast<size_t> (line[1].position.x);
}
