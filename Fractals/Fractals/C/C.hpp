//
// Created by Lyosha12 on 30.04.2018.
//

#ifndef LAB_3_C_HPP
#define LAB_3_C_HPP

#include <SFML/Graphics.hpp>

#include "../Base/Fractal.hpp"
#include "../../Utilites/WindowForTests/WindowForTests.hpp"

class C: public Fractal {
  private:
    class GeneratorStalk {
      public:
        GeneratorStalk(float line_length, std::vector<int> rotate_angles);
       
        int getRotateAngles(int index) const;
        size_t getBasisLength() const;
        size_t getBranchLength() const;
        
        void cut();
        bool isBasisExist() const;
        bool isBranchExist() const;
    
        std::pair<sf::Sprite, std::unique_ptr<sf::Texture>> getSpriteBasis();
        std::pair<sf::Sprite, std::unique_ptr<sf::Texture>> getSpriteBranch();

      private:
        std::unique_ptr<sf::Texture> generateStalkTexture(
            size_t width,
            size_t height,
            sf::VertexArray const& line
        );
  
      private:
        sf::VertexArray basis;
        sf::VertexArray branch;
        float const scale_factor = 0.40f;
        std::vector<int> rotate_angles;
        sf::RenderTexture buffer;
    };
    
  public:
    C(Fluctlight const& background, sf::VideoMode screen);
    void generateNextLevel(sf::VideoMode screen) override;
  
  private:
    std::vector<sf::Transform> generateBasisPosition(
        sf::Transform const& line_begin,
        float line_length
    );
    std::vector<sf::Transform> generateBranchPositions(
        sf::Transform const& basis_position
    );
    
    Level::Part generateBasis(sf::VideoMode screen);
    Level::Part generateBranches(Fractal::Level::Part const& basis);
  private:
    GeneratorStalk generator_stalk;
};


#endif //LAB_3_C_HPP
