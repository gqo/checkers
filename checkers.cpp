#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// Function for initializing game pieces (unnecessary, but ugly otherwise)
void initPieces(std::vector<sf::CircleShape>& pieces) {
    int y = 30; // y-axis starting place
    int x = 130; // x-axis starting place
    // For loop for creation of white pieces
    for(int i = 0; i < 6; i++) {
        if(i == 3){
            y = 130;
            x = 30;
        }
        sf::CircleShape piece_wh(40);
        piece_wh.setFillColor(sf::Color::White);
        piece_wh.setOutlineThickness(5);
        piece_wh.setOutlineColor(sf::Color(80,80,80)); // Grey outline
        piece_wh.setPosition(x,y);
        pieces.push_back(piece_wh);
        x += 200;
    }
    y = 430;
    x = 130;
    for(int i = 0; i < 6; i++) {
        if(i == 3){
            y = 530;
            x = 30;
        }
        sf::CircleShape piece_bl(40);
        piece_bl.setFillColor(sf::Color::Black);
        piece_bl.setOutlineThickness(5);
        piece_bl.setOutlineColor(sf::Color(80,80,80)); // Grey outline
        piece_bl.setPosition(x,y);
        pieces.push_back(piece_bl);
        x += 200;
    }
}

// Function for drawing game pieces
void drawPieces(std::vector<sf::CircleShape>& pieces, sf::RenderWindow& window) {
    for(int i = 0; i < pieces.size(); i++) {
        window.draw(pieces[i]);
    }
}

int main() {
    // Initialize popup window, i.e. the game window
    sf::RenderWindow window(sf::VideoMode(640,640), "Checkers"); // (x-axis, y-axis)
    // Initialize background shape and look
    sf::RectangleShape background(sf::Vector2f(600,600));
    background.setFillColor(sf::Color::Black);
    background.setOutlineThickness(20);
    background.setOutlineColor(sf::Color::Red);
    background.setPosition(20,20);
    // Initialize board texture
    sf::Texture b_texture;
    if(!b_texture.loadFromFile("c_board600.png")) {
        std::cout << "Error importing board texture!" << std::endl;
    }
    // Initialize board sprite
    sf::Sprite board;
    board.setTexture(b_texture);
    board.setPosition(20,20);
    // Initialize white checker piece
    // sf::CircleShape piece_wh(40);
    // piece_wh.setFillColor(sf::Color::White);
    // piece_wh.setOutlineThickness(5);
    // piece_wh.setOutlineColor(sf::Color(80,80,80)); // Grey outline
    // // piece_wh.setPosition(130,30);
    // Initialize black checker piece
    // sf::CircleShape piece_bl(40);
    // piece_bl.setFillColor(sf::Color::Black);
    // piece_bl.setOutlineThickness(5);
    // piece_bl.setOutlineColor(sf::Color(80,80,80)); // Grey outline
    // piece_bl.setPosition(30,530);
    // Initialize vector for tracking pieces
    std::vector<sf::CircleShape> pieces;
    initPieces(pieces);
    // Creates game window instance
    while(window.isOpen()) {
        // Tracks interactions with window
        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type) {
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
        drawPieces(pieces,window); // Draws game pieces
        window.display();
    }
    return 0;
}