//
// Created by Lyosha12 on 30.04.2018.
//

#include <cmath>
#include "C.hpp"

C::C(Fluctlight const& background, sf::VideoMode screen)
    : Fractal(background, false)
    , generator_stalk(screen.width*0.40f, {-90, 45, 8})
{
    generateNextLevel(screen);
}

void C::generateNextLevel(sf::VideoMode screen) {
    std::vector<Level::Part> level;
    if(generator_stalk.isBasisExist()) {
        level.push_back(generateBasis(screen));
    
        if(generator_stalk.isBranchExist())
            level.push_back(generateBranches(level.at(0)));
    } else
        return;
    
    levels.push_back(std::move(level));
    generator_stalk.cut();
}

std::vector<sf::Transform> C::
generateBasisPosition(sf::Transform const& to_branch, float line_length) {
    auto sign = [] (auto x) { return x >= 0 ? 1 : -1; };
    
    auto base = sf::Transform(to_branch)
        .translate(line_length, 0)
        .rotate(
            sign(rand()%2-1)*generator_stalk.getRotateAngles(2) +
            sign(rand()%2-1)*(
                generator_stalk.getRotateAngles(2)*
                (rand()%151 / 100.0f)
            )
        );
    
    return { base };
}

std::vector<sf::Transform> C::
generateBranchPositions(sf::Transform const& basis_position) {
    std::vector<sf::Transform> branches;
    
    size_t const count_branches_on_side = 2;
    float const branch_interval = (generator_stalk.getBasisLength()) / count_branches_on_side;
    auto sign = [] (auto x) { return x >= 0 ? 1 : -1; };
    
    for(int i = -count_branches_on_side; i != count_branches_on_side; ++i) {
        branches.push_back(
            sf::Transform(basis_position)
                .translate(abs(i)*branch_interval*1.2f + sign(i)*branch_interval/2 - branch_interval/3.5f, 0)
                .rotate(sign(i) * (generator_stalk.getRotateAngles(1) + sign(rand()%2 - 1)*generator_stalk.getRotateAngles(1)*(rand()%51 / 100.0f)))
        );
    }
    
    return branches;
}


Fractal::Level::Part C::generateBasis(sf::VideoMode screen) {
    std::vector<sf::Transform> positions;
    if(levels.size() > 0) {
        // Bases from bases
        for(size_t i = 0; i != levels.back().parts.size(); ++i) {
            auto const& cur_part = levels.back().parts[i];
            
            for(size_t j = 0; j != cur_part.transforms.size(); ++j) {
                auto const& cur_stalk = cur_part.transforms[j];
                
                std::vector<sf::Transform> new_positions =
                    generateBasisPosition(
                        cur_stalk, cur_part.texture->getSize().x
                    );
                
                positions.insert(
                    positions.end(),
                    make_move_iterator(new_positions.begin()),
                    make_move_iterator(new_positions.end())
                );
            }
        }
        
        // Bases there it's branches from prev level
        positions.insert(
            positions.end(),
            levels.back().parts.at(1).transforms.begin(),
            levels.back().parts.at(1).transforms.end()
        );
    } else
        positions.push_back(
            sf::Transform()
                .translate(screen.width/2, screen.height * 0.95f)
                .rotate(generator_stalk.getRotateAngles(0))
        );
    
    std::pair<sf::Sprite, std::unique_ptr<sf::Texture>> basis_sprite =
        generator_stalk.getSpriteBasis();
    Level::Part base(
        basis_sprite.first,
        std::move(basis_sprite.second),
        std::move(positions)
    );
    
    return base;
}
Fractal::Level::Part C::generateBranches(Fractal::Level::Part const& basis) {
    std::pair<sf::Sprite, std::unique_ptr<sf::Texture>> branch_sprite =
        generator_stalk.getSpriteBranch();
    
    std::vector<sf::Transform> positions;
    for(auto const& cur_basis: basis.transforms) {
        std::vector<sf::Transform> branch_positions = generateBranchPositions(cur_basis);
        
        positions.insert(
            positions.end(),
            make_move_iterator(branch_positions.begin()),
            make_move_iterator(branch_positions.end())
        );
    }
    
    Level::Part branches(
        branch_sprite.first,
        std::move(branch_sprite.second),
        std::move(positions)
    );
    
    return branches;
}




C::GeneratorStalk::GeneratorStalk(float line_length, std::vector<int> rotate_angles)
    // https://en.sfml-dev.org/forums/index.php?topic=23955.0
    : basis  { sf::Lines, 2 }
    , branch { sf::Lines, 2 }
    , rotate_angles(rotate_angles)
{
    branch[0].position = basis[0].position = {0.5, 0};
    basis[1].position = {line_length, 0};
    branch[1].position = basis[1].position*scale_factor;
}

int     C::GeneratorStalk::getRotateAngles  (int index        ) const {
    return rotate_angles[index];
}
size_t  C::GeneratorStalk::getBasisLength   (                 ) const {
    return static_cast<size_t> (basis[1].position.x);
}
size_t  C::GeneratorStalk::getBranchLength  (                 ) const {
    return static_cast<size_t> (branch[1].position.x);
}

void    C::GeneratorStalk::cut              (                 )       {
    basis[1].position.x *= scale_factor;
    branch[1].position.x *= scale_factor;
    rotate_angles[1] *= scale_factor*1.5;
}
bool    C::GeneratorStalk::isBasisExist     (                 ) const {
    return getBranchLength() > 0;
}
bool    C::GeneratorStalk::isBranchExist    (                 ) const {
    return getBranchLength() > 1;
}

std::unique_ptr<sf::Texture> C::GeneratorStalk::
generateStalkTexture(size_t width, size_t height, sf::VertexArray const& line) {
    
    buffer.create(width, height);
    buffer.clear({255, 255, 255, 0});
    buffer.draw(line);
    buffer.display();
    
    return std::unique_ptr<sf::Texture> (new sf::Texture(buffer.getTexture()));
}

std::pair<sf::Sprite, std::unique_ptr<sf::Texture>> C::GeneratorStalk::
getSpriteBasis() {
    std::unique_ptr<sf::Texture> texture =
        generateStalkTexture(static_cast<size_t>(getBasisLength() + 0.5), 1, basis);
    return { sf::Sprite(*texture), std::move(texture) };
}

std::pair<sf::Sprite, std::unique_ptr<sf::Texture>> C::GeneratorStalk::
getSpriteBranch() {
    std::unique_ptr<sf::Texture> texture =
        generateStalkTexture(
            static_cast<size_t>(getBranchLength() + 0.5), 1, branch
        );
    return { sf::Sprite(*texture), std::move(texture) };
}