#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Initialize popup window, i.e. the game window
    sf::RenderWindow window(sf::VideoMode(840,840), "Checkers");
    // Initialize background shape and look
    sf::RectangleShape background(sf::Vector2f(800,800));
    background.setFillColor(sf::Color::Black);
    background.setOutlineThickness(20);
    background.setOutlineColor(sf::Color::Red);
    background.setPosition(20,20);
    // Initialize board texture
    sf::Texture b_texture;
    if (!b_texture.loadFromFile("c_board800.png")) {
        std::cout << "Error importing board texture!" << std::endl;
    }
    // Initialize board sprite
    sf::Sprite board;
    board.setTexture(b_texture);
    board.setPosition(20,20);
    // Creates game window instance
    while (window.isOpen()) {
        // Tracks interactions with window
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                // Window closed
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code) {
                        // Closes window on escape keypress
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        // Default for unhandled keypress
                        default:
                            break;
                    }
                    break;
                // Default for unhandled event type
                default:
                    break;
            }
        }
        window.clear(); // Clears window for drawing on clean slate
        window.draw(background); // Draws background
        window.draw(board); // Draws board sprite
        window.display();
    }
    return 0;
}