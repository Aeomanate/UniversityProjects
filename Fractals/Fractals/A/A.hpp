//
// Created by Lyosha12 on 30.04.2018.
//

#ifndef LAB_3_A_HPP
#define LAB_3_A_HPP

#include <SFML/Graphics.hpp>
#include "../Base/Fractal.hpp"

class A: public Fractal {
  public:
    A(Fluctlight const& background, sf::VideoMode screen);
    void generateNextLevel(sf::VideoMode screen) override;
    
  private:
    std::unique_ptr<sf::Texture> generateTexture(size_t width, size_t height);
    sf::Sprite generateSprite(std::unique_ptr<sf::Texture> const& texture);
    std::vector<sf::Transform> generatePositions(sf::Transform line_center);
  
  private:
    class Generator: public sf::Drawable {
      public:
        Generator(float line_length);
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        bool toDivide();
        size_t getBasisLength() const;
      
      private:
        sf::Vertex line[2];
        
    } generator;
    sf::RenderTexture buffer;
};


#endif //LAB_3_A_HPP
