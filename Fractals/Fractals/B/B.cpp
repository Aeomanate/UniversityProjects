//
// Created by Lyosha12 on 30.04.2018.
//

#include "B.hpp"

B::B(Fluctlight const& background, sf::VideoMode screen)
    : Fractal(background, false)
    , generator(4*screen.height/7)
{
    generateNextLevel(sf::VideoMode());
    // Set to top-bottom
    levels[0].parts.front().transforms = {
        sf::Transform().translate(screen.width/2, screen.height - 1)
    };
    
    generateNextLevel(sf::VideoMode());
    // Set to top-bottom. Besides, lift up on texture height.
    levels[1].parts.front().transforms = {
        levels[0].parts.front().transforms[0] *
        sf::Transform().translate(0, levels[1].parts.front().texture->getSize().y * -1.0f)
    };
}

void B::
generateNextLevel([[maybe_unused]] sf::VideoMode screen) {
    if(levels.size() > 1 && !generator.toHalve())
        return;
    
    std::unique_ptr<sf::Texture> texture = generateTexture(
        levels.size() == 0 ? 1 : generator.getBasisLength(),
        generator.getBasisLength()/2
    );
    sf::Sprite sprite = generateSprite(texture);
    
    std::vector<sf::Transform> positions;
    if(levels.size() > 1)
        positions = generatePositions();
    
    std::vector<Level::Part> parts;
    parts.emplace_back(sprite, std::move(texture), std::move(positions));
    levels.push_back(move(parts));
}

std::unique_ptr<sf::Texture> B::
generateTexture(size_t width, size_t height) {
    buffer.create(width, height);
    buffer.clear({255, 255, 255, 0});
    buffer.draw(generator, sf::Transform().translate(0, height - 1).scale(1, -1));
    buffer.display();
    return std::unique_ptr<sf::Texture> (new sf::Texture(buffer.getTexture()));
}

sf::Sprite B::
generateSprite(std::unique_ptr<sf::Texture> const& texture) {
    sf::Sprite sprite(*texture);
    
    // Set the center of transforms from left-up corner to top-bottom
    sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y - 1);
    
    return sprite;
}

std::vector<sf::Transform> B::
generatePositions() {
    std::vector<sf::Transform> transforms;
    
    for(auto const& cur_bottom: levels.back().parts.front().transforms) {
        sf::Transform cur_top =
            cur_bottom * sf::Transform().translate(
                0, levels.back().parts.front().texture->getSize().y * -1.0f
            );
        
        float halfWidth = levels.back().parts.front().texture->getSize().x / 2;
        
        sf::Transform peak_left(cur_top * sf::Transform().translate(-halfWidth + 0.01f, 0));
        sf::Transform peak_right(cur_top * sf::Transform().translate(halfWidth - 0.01f, 0));
        
        transforms.push_back(peak_left);
        transforms.push_back(peak_right);
    }
    
    return transforms;
}



B::Generator::Generator(float basis) // https://en.sfml-dev.org/forums/index.php?topic=23955.0
    : left_line   { {{0.5           , 0}}, {{0.5      , basis/2 }} }
    , right_line  { {{basis - 1     , 0}}, {{basis - 1, basis/2 }} }
    , bottom_line { {{0.5           , 0}}, {{basis - 1, 0       }} }
{}

void B::Generator::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(left_line, std::size(left_line), sf::Lines, states);
    target.draw(right_line, std::size(right_line), sf::Lines, states);
    target.draw(bottom_line, std::size(bottom_line), sf::Lines, states);
}

bool B::Generator::
toHalve() {
    left_line[1].position.y = right_line[1].position.y /= 2;
    
    right_line[0].position.x =
    right_line[1].position.x =
    bottom_line[1].position.x /= 2;
    
    // Magic.
    int correction = int(bottom_line[1].position.x - 0.5f);
    right_line[0].position.x =
    right_line[1].position.x =
    bottom_line[1].position.x = correction + !(correction%2);
    
    // Check for ability to use generator.
    return left_line[1].position.y > 1 && right_line[0].position.x > 1;
}

size_t B::Generator::
getBasisLength() const {
    return static_cast<size_t> (bottom_line[1].position.x);
}