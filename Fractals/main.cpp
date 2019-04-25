#include <string>
#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <memory>
#include <iomanip>
#include <chrono>
#include <thread>
#include <algorithm>
using namespace std::chrono_literals;

#include <windows.h>
#include <SFML/Graphics.hpp>

#include "Fluctlight/Fluctlight.hpp"
#include "Fractals/Base/Fractal.hpp"
#include "Fractals/A/A.hpp"
#include "Fractals/B/B.hpp"
#include "Fractals/C/C.hpp"
#include "FrameCounter/FrameCounter.hpp"
#include "TexturePrinter/TexturePrinter.hpp"
#include "Utilites/CycleIterator.hpp"
#include "Utilites/Misc.hpp"

class Lab3 {
  public:
    Lab3(sf::VideoMode screen = { 800, 600 }, std::string title = "Fractals")
        : window(screen, title)
        , fractal { new A(fluctlight, screen) }
    { }
    
    void run() {
        srand(static_cast<unsigned>(time(0)));
        ShowWindow(GetConsoleWindow(), SW_HIDE);
        
        while(window.isOpen()) {
            HandleEvents();
            draw();
            fractal->generateNextLevel(sf::VideoMode());
        }
    }
  
  private:
    void HandleEvents() {
        sf::Event e;
        while(window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::EventType::Closed:
                    window.close();
                    break;
    
                case sf::Event::EventType::MouseButtonPressed:
                    handleMouseClick(e.mouseButton.button);
                    break;
                    
                default:
                    break;
            }
        }
    }
    void handleMouseClick(sf::Mouse::Button button) {
        auto [width, height] = window.getSize();
        
        switch(button) {
            case sf::Mouse::Button::Left:
                fractal.reset((*--cur_fractal)(fluctlight, { width, height }));
                break;
        
            case sf::Mouse::Button::Right:
                fractal.reset((*++cur_fractal)(fluctlight, { width, height }));
                break;
        
            default:
                break;
        }
    }
    
    void draw() {
        window.clear(fluctlight);
        window.draw(
            **[this]() mutable {
                fractal->updateColor();
                return &fractal;
            }());
    
        text_printer.setPosition({0, 0})
                    .setColor(fluctlight.getInverted())
                    .setCharacterPixelSize(20)
                    .setString(
                        "FPS: " + std::to_string(fps.get()) + "\n" +
                        "FPS avg: " + std::to_string(fps.getAvg())
                    );
        text_printer(window);
    
        window.display();
    }
  
  
  private:
    sf::RenderWindow window;
    Fluctlight fluctlight { 15ms };
    std::unique_ptr<Fractal> fractal;
    
    FrameCounter<std::chrono::steady_clock> fps { 1s };
    TexturePrinter text_printer;
    
    using CtorPointer = Fractal*(*)(Fluctlight const&, sf::VideoMode&&);
    std::vector<CtorPointer> fractals = {
        createDerived<Fractal, A, Fluctlight const&, sf::VideoMode&&>,
        createDerived<Fractal, B, Fluctlight const&, sf::VideoMode&&>,
        createDerived<Fractal, C, Fluctlight const&, sf::VideoMode&&>
    };
    using CtorIterator = std::vector<CtorPointer>::iterator;
    CycleIterator<CtorIterator> cur_fractal { fractals.begin(), fractals.end() };
};

int main() {
    try { Lab3().run(); } catch(std::exception const& e) {
        ErrorPrinter(e.what()).print();
    }
    return 0;
    

}