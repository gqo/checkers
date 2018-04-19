#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
// For array co-ordinate calculation, specifically abs() and ceil()
#include <math.h>

// Checks if co-ords are in bounds in 2d array
bool inBounds(int row, int col) {
    if(((row >= 0)&&(row < 6))&&((col >=0 )&&(col < 6))) { return 1; }
    else { return 0; }
}

// Checks for possible moves at specific co-ordinate, sets vector of possible moves in pair<int,int> form
void setPossibles(int& row, int& col, int (&b_array)[6][6], std::vector<std::pair<int,int> >& possibles, bool& cposs) {
    std::cout << "setPossibles ran! cposs = " << cposs << std::endl;
    int capture = 0; // 0 = no capture moves, 1 = one capture move, 2 = two capture moves
    int piece_type = b_array[row][col];
    for(int i = 0; i < possibles.size(); i++) { possibles.pop_back(); }
    if(possibles.size() != 0) { // Check if clear vector doesn't work
        for(int i = 0; i < possibles.size(); i++) { possibles.pop_back(); }
    }
    switch(piece_type) {
        case 1: // White move check
            // Left diagonal move check
            if(inBounds(row+1,col-1)) {
                switch(b_array[row+1][col-1]) {
                    case 0:
                        if(!cposs) { // If capture possible, regular move not possible
                            possibles.push_back(std::make_pair(row+1,col-1));
                        }
                        break;
                    case 2:
                        if(inBounds(row+2,col-2)){
                            if(b_array[row+2][col-2] == 0) {
                                possibles.push_back(std::make_pair(row+2,col-2));
                                capture++;
                                cposs = 1;
                            }
                        }
                        break;
                    default:
                        break; 
                }
            }
            // Right diagonal move check
            if(inBounds(row+1,col+1)) {
                switch(b_array[row+1][col+1]) {
                    case 0:
                        if(capture == 0 && !cposs) { // If capture possible, regular move not possible
                            possibles.push_back(std::make_pair(row+1,col+1)); 
                        }
                        break;
                    case 2:
                        if(inBounds(row+2,col+2)){
                            if(b_array[row+2][col+2] == 0) {
                                if(capture == 0 && possibles.size() == 1) {
                                    possibles.pop_back();
                                }
                                possibles.push_back(std::make_pair(row+2,col+2));
                                cposs = 1;
                            }
                        }
                        break;
                    default:
                        break; 
                }
            }
            break;
        case 2: // Black move check
            // Left diagonal move check
            if(inBounds(row-1,col-1)) {
                switch(b_array[row-1][col-1]) {
                    case 0:
                        if(!cposs) { // If capture possible, regular move not possible
                            possibles.push_back(std::make_pair(row-1,col-1));
                        }
                        break;
                    case 1:
                        if(inBounds(row-2,col-2)){
                            if(b_array[row-2][col-2] == 0) {
                                possibles.push_back(std::make_pair(row-2,col-2));
                                capture++;
                                cposs = 1;
                            }
                        }
                        break;
                    default:
                        break; 
                }
            }
            // Right diagonal move check
            if(inBounds(row-1,col+1)) {
                switch(b_array[row-1][col+1]) {
                    case 0:
                        if(capture == 0 && !cposs) { // If capture possible, regular move not possible
                            possibles.push_back(std::make_pair(row-1,col+1)); 
                        }
                        break;
                    case 1:
                        if(inBounds(row-2,col+2)){
                            if(b_array[row-2][col+2] == 0) {
                                if(capture == 0 && possibles.size() == 1) {
                                    possibles.pop_back();
                                }
                                possibles.push_back(std::make_pair(row-2,col+2));
                                cposs = 1;
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
}

// Checks for possibles across the board. Returns 0 if no possible moves left,
// returns 1 if white has possible moves left, returns 2 if black has possible moves left,
// returns 3 if both have possible moves left
int checkPossibles(int(&b_array)[6][6], std::vector<std::pair<int,int> >& possibles, bool& cposs) {
    int ret = 0;
    for(int i = 0; i < 6; i++) { // Rows
        for(int j = 0; j < 6; j++) { // Cols
            if(b_array[i][j] == 1 && ret == 0) {
                setPossibles(i,j,b_array,possibles,cposs);
                if(possibles.size() != 0) { ret = 1; } // If a white move exists, inc by 1
            }
            else if(b_array[i][j] == 2 && ret < 2) {
                setPossibles(i,j,b_array,possibles,cposs);
                if(possibles.size() != 0) { ret += 2; } // If a black move exists, inc by 2
            }
            if(ret == 3) { return ret; } // If both exist, return, no need to check more
        }
    }
    return ret;
}

// Sets capture possible var if there's a capture move possible currently
void setCPoss(int player, int(&b_array)[6][6], std::vector<std::pair<int,int> >& possibles, bool& cposs) {
    for(int i = 0; i < 6; i++) { // Rows
        for(int j = 0; j < 6; j++) { // Cols
            if(b_array[i][j] == player) { setPossibles(i,j,b_array,possibles,cposs); }
        }
    }
}

// Highlights the possible moves in yellow box
void drawPossibles(sf::RenderWindow& window, sf::RectangleShape& phlight, std::vector<std::pair<int,int> >& possibles) {
    int x;
    int y;
    for(int i = 0; i < possibles.size(); i++) {
        x = possibles[i].second;
        y = possibles[i].first;
        phlight.setPosition(x*100+3,y*100+3);
        window.draw(phlight);
    }
}

// Finds the co-ordinate pair between two co-ordinate pairs
std::pair<int,int> findBetween(std::pair<int,int>& origin, std::pair<int,int>& dest) {
    int row = ceil((origin.first+dest.first)/2);
    int col = ceil((origin.second+dest.second)/2);
    return std::make_pair(row,col);
}

// Checks if destination is in possible calculated moves
bool isValidMove(std::pair<int,int>& dest, std::vector<std::pair<int,int> >& possibles) {
    for(int i = 0; i < possibles.size(); i++) {
        if(possibles[i] == dest) { return 1; }
    }
    return 0;
}

// Moves piece and accounts for removing captured pieces
bool movePiece(std::pair<int,int>& origin, std::pair<int,int>& dest, 
    int (&b_array)[6][6]) {
    bool capture = 0;
    // "Moves" piece from origin to destination co-ordinates
    b_array[dest.first][dest.second] = b_array[origin.first][origin.second];
    // Checks distance between co-ords to see if there's a capture taking place
    if(abs(dest.first-origin.first) == 2) {
        std::pair<int,int> between = findBetween(origin,dest);
        b_array[between.first][between.second] = 0;
        capture = 1;
    }
    // "Removes" piece from origin co-ordinates because it was "moved"
    b_array[origin.first][origin.second] = 0;
    return capture;
}

// Function for drawing game pieces
void drawPieces(sf::CircleShape& piece, int (&b_array)[6][6], sf::RenderWindow& window) {
    for(int i = 0; i < 6; i++) { // Rows
        for(int j = 0; j < 6; j++) { // Cols
            if(b_array[i][j] != 0) {
                if(b_array[i][j] == 1) { piece.setFillColor(sf::Color::White); }
                else if(b_array[i][j] == 2) { piece.setFillColor(sf::Color::Black); }
                piece.setPosition(j*100+10,i*100+10);
                window.draw(piece);
            }
        }
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
    // Initialize piece shape
    sf::CircleShape piece(40);
    piece.setOutlineThickness(5);
    piece.setOutlineColor(sf::Color(80,80,80)); // Grey outline
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
        int m_xcord = 0; 
        int m_ycord = 0;
        std::pair<int,int> origin;
        std::pair<int,int> dest;
        // Tracks if piece held 
        bool held = 0; // false = not held
    bool hvalid = 0; // tracks if hlight should be drawn
    // Current type of piece (black, white, nothing)
    int piece_type = 0;
    // Intialize vars for tracking game vals
        // Turn tracker
        bool turn = 1; // White = 1; Black = 0;
        // Piece capture counts
        int bcaps = 0; // # of pieces Black has captured
        int wcaps = 0; // # of pieces White has captured
        // Win return code
        int win = 0; // 0 = no win, 1 = White win, 2 = Black win, 3 = Tie (should be rare, if not impossible)
        // Possible moves return code
        int poss = 3; // 3 = both have moves, 2 = black has moves, 1 = white has moves, 0 = none have moves (game over)
        // Capture possible
        bool cposs = 0; // False = no capture possible
    /* Intialize 2d board array
        Note: Board co-ordinates are classified as (row,column) as such it
        can be confusing that the x-axis and y-axis are switched between
        SFML recognition stuff and these (row,column) setups. Example:
        SFML mouse co-ordinates are given as (x,y) position of mouse in window
        from the top left. Essentially, x is the column and y is the row.
        So SFML (x,y) == b_array(y,x) */
    int b_array[6][6] = // Board for playing
    {
        {0,1,0,1,0,1},
        {1,0,1,0,1,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,2,0,2,0,2},
        {2,0,2,0,2,0},
    };
    // int b_array[6][6] = // Board for default testing
    // {
    //     {0,1,0,1,0,1},
    //     {1,0,2,0,0,0},
    //     {0,0,0,0,0,0},
    //     {0,0,0,0,0,0},
    //     {0,0,0,1,0,2},
    //     {2,0,2,0,2,0},
    // };
    // int b_array[6][6] = // Board for win-by-capture testing
    // {
    //     {0,0,0,0,0,0},
    //     {0,1,0,0,0,0},
    //     {0,0,0,0,0,0},
    //     {0,0,0,2,0,0},
    //     {0,0,0,0,0,0},
    //     {0,0,0,0,0,0},
    // };
    // int b_array[6][6] = // Board for win-by-forfeit testing
    // {
    //     {0,0,0,0,0,0},
    //     {0,0,0,2,0,0},
    //     {0,0,0,0,0,0},
    //     {0,0,1,0,0,0},
    //     {0,0,0,0,1,0},
    //     {0,0,0,0,0,0},
    // };
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
                        // If nobody has won, allow movement
                        if(win == 0) {
                            // Gets x and y co-ords of board of mouse click
                            m_xcord = event.mouseButton.x / 100;
                            m_ycord = event.mouseButton.y / 100;
                            // Gets whether square is black, white, or empty
                            piece_type = b_array[m_ycord][m_xcord];
                            // If a player clicks on a piece that isn't theirs,
                            // behave as if they clicked an empty space
                            if(turn && (piece_type == 2)) { piece_type = 0; }
                            else if(!turn && (piece_type == 1)) { piece_type = 0; }
                            if(piece_type != 0 || held) {
                                if(!held) {
                                    // Sets highlight box to last square clicked
                                    hlight.setPosition(m_xcord*100+3,m_ycord*100+3);
                                    // Calculates possible moves
                                    setPossibles(m_ycord,m_xcord,b_array,possibles,cposs);
                                    // Creates original board co-ordinates
                                    origin = std::make_pair(m_ycord,m_xcord);
                                    // If not empty, highlight clicked square
                                    if(piece_type != 0) { hvalid = 1; } 
                                    else { hvalid = 0; }
                                    // Piece is being "held"
                                    held = !held;
                                } else {
                                    // Creates destination board co-ordinates
                                    dest = std::make_pair(m_ycord,m_xcord);
                                    // Checks if move is valid and then moves pieces
                                    if(isValidMove(dest,possibles)) {
                                        // Checks if piece was captured during move, iterates
                                        // capture totals respectively.
                                        if(movePiece(origin,dest,b_array)) {
                                            if(turn) { 
                                                wcaps++; 
                                                if(wcaps == 6) { // If White captures all pieces, White wins
                                                    win = 1; 
                                                    window.setTitle("WHITE won!");
                                                }
                                            }
                                            else { 
                                                bcaps++;
                                                if(bcaps == 6) { // If Black captures all pieces, Black wins
                                                    win = 2;
                                                    window.setTitle("BLACK won!");
                                                }
                                            }
                                        }
                                        cposs = 0; // If cposs is not reset here, check possible can end up thinking there are
                                        // no moves possible if there are ONLY regular moves possible
                                        poss = checkPossibles(b_array,possibles,cposs);
                                        // Checks if moves are possible and handles forfeit-wins and skipped turns
                                        switch(poss) {
                                            case 0:
                                                if(wcaps == bcaps) {
                                                    win = 3;
                                                    window.setTitle("It's a TIE!");
                                                }
                                                else if(wcaps > bcaps) {
                                                    win = 1;
                                                    window.setTitle("WHITE won!");
                                                }
                                                else {
                                                    win = 2;
                                                    window.setTitle("BLACK won!");
                                                }
                                                break;
                                            case 1:
                                                if(turn && poss == 1) { turn = !turn; } // Toggles turn vals so that Black turn is skipped
                                                break;
                                            case 2:
                                                if(!turn && poss == 2) { turn = !turn; } // Toggles turn vals so that White turn is skipped
                                                break;
                                            default:
                                                break;
                                        }
                                        // Switch turns
                                        turn = !turn;
                                        cposs = 0;
                                        if(turn) { setCPoss(1,b_array,possibles,cposs); }
                                        else{ setCPoss(2,b_array,possibles,cposs); }
                                    }
                                    // Piece is "released"
                                    held = !held;
                                }
                            }
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
        drawPieces(piece,b_array,window); // Draws game pieces
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