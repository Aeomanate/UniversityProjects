//
// Created by Lyosha12 on 30.04.2018.
//

#ifndef LAB_3_B_HPP
#define LAB_3_B_HPP

#include <SFML/Graphics.hpp>
#include "../Base/Fractal.hpp"


class B: public Fractal {
  public:
    B(Fluctlight const& background, sf::VideoMode screen);
    void generateNextLevel(sf::VideoMode screen) override;
    
  private:
    std::unique_ptr<sf::Texture> generateTexture(size_t width, size_t height);
    sf::Sprite generateSprite(std::unique_ptr<sf::Texture> const& texture);
    std::vector<sf::Transform> generatePositions();
    
  private:
    class Generator: public sf::Drawable {
      public:
        Generator(float basis);
    
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        bool toHalve();
        size_t getBasisLength() const;
        
      private:
        sf::Vertex left_line[2];
        sf::Vertex right_line[2];
        sf::Vertex bottom_line[2];
    } generator;
    sf::RenderTexture buffer;
    
};


#endif //LAB_3_B_HPP
