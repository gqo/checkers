#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// class piece 
// {
// public:
//     const bool color;
//     sf::CircleShape shape;
    
// };

// Function for initializing game pieces (unnecessary, but ugly otherwise)
void initPieces(std::vector<sf::CircleShape>& pieces) {
    int y = 10; // y-axis starting place
    int x = 110; // x-axis starting place
    // For loop for creation of white pieces
    for(int i = 0; i < 6; i++) {
        if(i == 3){
            y = 110;
            x = 10;
        }
        sf::CircleShape piece_wh(40);
        piece_wh.setFillColor(sf::Color::White);
        piece_wh.setOutlineThickness(5);
        piece_wh.setOutlineColor(sf::Color(80,80,80)); // Grey outline
        piece_wh.setPosition(x,y);
        pieces.push_back(piece_wh);
        x += 200;
    }
    y = 410;
    x = 110;
    for(int i = 0; i < 6; i++) {
        if(i == 3){
            y = 510;
            x = 10;
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
    // Initialize popup window, i.e. the game window. Note: cannot resize window
    sf::RenderWindow window(sf::VideoMode(600,600), "Checkers", 
        sf::Style::Titlebar | sf::Style::Close);
    // Initialize board texture
    sf::Texture b_texture;
    if(!b_texture.loadFromFile("c_board600.png")) {
        std::cout << "Error importing board texture!" << std::endl;
    }
    // Initialize board sprite
    sf::Sprite board;
    board.setTexture(b_texture);
    board.setPosition(0,0);
    // Initialize vector for tracking pieces and initialize them
    std::vector<sf::CircleShape> pieces;
    initPieces(pieces);
    // Initialize highlight square
    sf::RectangleShape hlight(sf::Vector2f(94,94));
    hlight.setFillColor(sf::Color::Transparent);
    hlight.setOutlineThickness(3);
    hlight.setOutlineColor(sf::Color::Red);
    hlight.setPosition(103,103);
    // Initialize ints for tracking co-ords of board clicks
    int m_xpos = 0;
    int m_ypos = 0;
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
                case sf::Event::MouseButtonPressed:
                    // Prints mouse position on left click, otherwise break
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        std::cout << "Left click!" << std::endl;
                        std::cout << "Mouse X: " << event.mouseButton.x << std::endl;
                        std::cout << "Mouse Y: " << event.mouseButton.y << std::endl;
                        // Gets x and y co-ords of board of mouse click
                        m_xpos = event.mouseButton.x / 100;
                        m_ypos = event.mouseButton.y / 100;
                        // Sets highlight box to last square clicked
                        hlight.setPosition(m_xpos*100+3,m_ypos*100+3);
                    }
                    break;
                // Default for unhandled event type
                default:
                    break;
            }
        }
        window.clear(); // Clears window for drawing on clean slate
        window.draw(board); // Draws board sprite
        window.draw(hlight);
        drawPieces(pieces,window); // Draws game pieces
        window.display();
    }
    return 0;
}

/* Notes

[0][1][2][3][4][5 ]
[6][7][8]......[11]
[12]...........[17]
[18]...........[23]
[24]...........[29]
[30]...........[35]

(30,30) (30,130) (30,230)
(130,30)(130,130)(130,230)

(x-axis, y-axis) for any co-ord pair in SFML

*/