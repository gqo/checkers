#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// Checks if co-ords are in bounds in 2d array
bool inBounds(int row, int col) {
    if(((row >= 0)&&(row < 6))&&((col >=0 )&&(col < 6))) { return 1; }
    else { return 0; }
}

// Checks for possible moves, sets vector of possible moves in pair<int,int> form
void setPossibles(int& row, int& col, int (&b_array)[6][6],
    std::vector<std::pair<int,int> >& possibles) {
    int piece_type = b_array[row][col];
    std::cout << "Ran setPossibles, before clear, vector size is: " << possibles.size() << std::endl;
    for(int i = 0; i < possibles.size(); i++) { possibles.pop_back(); }
    if(possibles.size() != 0) { // Check if clear vector doesn't work
        for(int i = 0; i < possibles.size(); i++) { possibles.pop_back(); }
    }
    std::cout << "Ran setPossibles, after clear, vector size is: " << possibles.size() << std::endl;
    switch(piece_type) {
        case 1: // White
            // Left
            if(inBounds(row+1,col-1)) {
                switch(b_array[row+1][col-1]) {
                    case 0:
                        possibles.push_back(std::make_pair(row+1,col-1));
                        break;
                    case 2:
                        if(inBounds(row+2,col-2)){
                            if(b_array[row+2][col-2] == 0) {
                                possibles.push_back(std::make_pair(row+2,col-2));
                            }
                        }
                        break;
                    default:
                        break; 
                }
            }
            // Right
            if(inBounds(row+1,col+1)) {
                switch(b_array[row+1][col+1]) {
                    case 0:
                        possibles.push_back(std::make_pair(row+1,col+1));
                        break;
                    case 2:
                        if(inBounds(row+2,col+2)){
                            if(b_array[row+2][col+2] == 0) {
                                possibles.push_back(std::make_pair(row+2,col+2));
                            }
                        }
                        break;
                    default:
                        break; 
                }
            }
            break;
        case 2: // Black
            // Left
            if(inBounds(row-1,col-1)) {
                switch(b_array[row-1][col-1]) {
                    case 0:
                        possibles.push_back(std::make_pair(row-1,col-1));
                        break;
                    case 1:
                        if(inBounds(row-2,col-2)){
                            if(b_array[row-2][col-2] == 0) {
                                possibles.push_back(std::make_pair(row-2,col-2));
                            }
                        }
                        break;
                    default:
                        break; 
                }
            }
            // Right
            if(inBounds(row-1,col+1)) {
                switch(b_array[row-1][col+1]) {
                    case 0:
                        possibles.push_back(std::make_pair(row-1,col+1));
                        break;
                    case 1:
                        if(inBounds(row-2,col+2)){
                            if(b_array[row-2][col+2] == 0) {
                                possibles.push_back(std::make_pair(row-2,col+2));
                            }
                        }
                        break;
                    default:
                        break; 
                }
            }
            break;
        default:
            break;
    }
    std::cout << "Finished setPossibles, vector size is: " << possibles.size() << std::endl;
}

void drawPossibles(sf::RenderWindow& window, sf::RectangleShape& phlight, 
    std::vector<std::pair<int,int> >& possibles) {
    int x;
    int y;
    for(int i = 0; i < possibles.size(); i++) {
        x = possibles[i].second;
        y = possibles[i].first;
        phlight.setPosition(x*100+3,y*100+3);
        window.draw(phlight);
    }
}

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

// Debug function for printing the contents of the board array
void printBArray(int (&b_array)[6][6]) {
    for(int i = 0; i < 6; i++) {
        std::cout << '{';
        for(int j = 0; j < 6; j++) {
            std::cout << b_array[i][j];
            if(j != 5) { std::cout << ','; }
        }
        std::cout << "}," << std::endl;
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
    // Initialize click highlight square
    sf::RectangleShape hlight(sf::Vector2f(94,94));
    hlight.setFillColor(sf::Color::Transparent);
    hlight.setOutlineThickness(3);
    hlight.setOutlineColor(sf::Color::Red);
    hlight.setPosition(103,103);
    // Initialize possible move highlight square
    sf::RectangleShape phlight(sf::Vector2f(94,94));
    phlight.setFillColor(sf::Color::Transparent);
    phlight.setOutlineThickness(3);
    phlight.setOutlineColor(sf::Color::Yellow);
    phlight.setPosition(103,103);
    // Initialize vars for tracking clicks
        // Co-ords for board, set on click, from top left
        int m_xcord_old = 0; 
        int m_ycord_old = 0;
        // int m_xcord_new = 0; 
        // int m_ycord_new = 0;
        // Tracks if piece held 
        bool held = 0; // false = not held
    bool hvalid = 0; // tracks if hlight should be drawn
    // Current type of piece (black, white, nothing)
    int piece_type = 0;
    /* Intialize 2d board array
        Note: Board co-ordinates are classified as (row,column) as such it
        can be confusing that the x-axis and y-axis are switched between
        SFML recognition stuff and these (row,column) setups. Example:
        SFML mouse co-ordinates are given as (x,y) position of mouse in window
        from the top left. Essentially, x is the column and y is the row.
        So SFML (x,y) == b_array(y,x) */
    int b_array[6][6] = 
    {
        {0,1,0,1,0,1},
        {1,0,2,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,1,0,2},
        {2,0,2,0,2,0},
    };
    // Initialize vector for possible move pairs
    std::vector<std::pair<int,int> > possibles;
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
                        // Prints b_array on space keypress
                        case sf::Keyboard::Space:
                            printBArray(b_array);
                            break;
                        // Default for unhandled keypress
                        default:
                            break;
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    // Gets mouse co-ords and sets highlight on left click, 
                    // otherwise break
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        if(!held) {
                            // Gets x and y co-ords of board of mouse click
                            m_xcord_old = event.mouseButton.x / 100;
                            m_ycord_old = event.mouseButton.y / 100;
                            // Sets highlight box to last square clicked
                            hlight.setPosition(m_xcord_old*100+3,m_ycord_old*100+3);
                            piece_type = b_array[m_ycord_old][m_xcord_old];
                            setPossibles(m_ycord_old,m_xcord_old,b_array,possibles);
                            if(piece_type != 0) { 
                                hvalid = 1;
                                // setPossibles(m_ycord_old,m_xcord_old,b_array,possibles);
                            } 
                            else { hvalid = 0; }
                            held = !held;
                        } else {
                            // m_xcord_new = event.mouseButton.x / 100;
                            // m_ycord_new = event.mouseButton.y / 100;
                            held = !held;
                        }
                    }
                    break;
                // Default for unhandled event type
                default:
                    break;
            }
        }
        window.clear(); // Clears window for drawing on clean slate
        window.draw(board); // Draws board sprite
        if(held && hvalid) { 
            window.draw(hlight);
            drawPossibles(window,phlight,possibles);
        }
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
(row, column) for any 2d array pair

*/