#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.hpp"

int main() {
    sf::Font font;
    if (!font.loadFromFile("fonts/montserrat.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Button");
    window.setFramerateLimit(60);
    
    Button button("Click Me!", 
                  sf::Vector2f(300, 250), 
                  sf::Vector2f(200, 80),
                  font);
    
    button.setNormalColor(sf::Color(46, 204, 113));
    button.setHoverColor(sf::Color(39, 174, 96));
    button.setPressedColor(sf::Color(22, 160, 133));
    button.setOnClick([]() {
        std::cout << "Button clicked!" << std::endl;
    });
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            button.update(window, event);
        }
        
        window.clear(sf::Color(30, 30, 46));
        window.draw(button);
        window.display();
    }
    
    return 0;
}