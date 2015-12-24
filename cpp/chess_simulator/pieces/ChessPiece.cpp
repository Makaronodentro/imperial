/*
 * ChessPiece Class : Abstract class for pieces to inherit
 *------------------------------------------------------------
 * Description: a class representing the common attributes of a ChessPiece. 
 *
 * Attributes: (inherited) colour -> the Colour of the piece {WHITE || BLACK}
 *             (inherited) type ->  a string with the piece's name
 *             (inherited) symbol -> a unicode string with the piece's symbol
 *
 * Public Methods: 
 *          Bishop : Description -> constructs the bishop.
 *                   Parameters  -> Colour. Sets the piece's colour
 *                   Return      -> Does not return.
 *          
 *    validateMove : Description -> Checks if the piece can move to the endIndex
 *                   Parameters  -> strings startIndex and endIndex, the board
 *                   Return      -> True if the move is valid. False otherwise.
 *
 *       getColour : Description -> Returns the colour of the piece
 *                   Parameters  -> -
 *                   Return      -> Colour colour of the piece
 *         getType : Description -> Returns the type of the piece
 *                   Parameters  -> -
 *                   Return      -> String type.
 *       getSymbol : Description -> Returns the symbol of the piece
 *                   Parameters  -> -
 *                   Return      -> String symbol
 */
#include "ChessPiece.h"

ChessPiece::ChessPiece(Colour _colour, string _type){
    // Initialize Attributes
    colour = _colour;
    type = _type;
    
    // Assign symbols
    if(!type.compare("King")){
        if(colour == 1)
            symbol = "\u2654";
        else
            symbol = "\u265A";
    }
    else if(!type.compare("Queen")){
        if(colour == 1)
            symbol = "\u2655";
        else
            symbol = "\u265B";
    }
    else if(!type.compare("Rook")){
        if(colour == 1)
            symbol = "\u2656";
        else
            symbol = "\u265C";
    }
    else if(!type.compare("Bishop")){
        if(colour == 1)
            symbol = "\u2657";
        else
            symbol = "\u265D";
    }
    else if(!type.compare("Knight")){
        if(colour == 1)
            symbol = "\u2658";
        else
            symbol = "\u265E";
    }
    else if(!type.compare("Pawn")){
        if(colour == 1)
            symbol = "\u2659";
        else
            symbol = "\u265F";
    }
}

ChessPiece::~ChessPiece() {}

/*** GETERS ***/
string ChessPiece::getSymbol(){
    return symbol;
}
string ChessPiece::getType(){
    return type;
}
Colour ChessPiece::getColour(){
    return colour;
}


/*
 * Verify move direction
 */

bool ChessPiece::isN(string from, string to){
    // Check if the piece is moving up and stays within the same file
    return (from[0] == to[0] && to[1] > from[1]);
}
bool ChessPiece::isS(string from, string to){
    // Check if the piece is moving down and stays within the same file
    return (from[0] == to[0] && to[1] < from[1]);
}

bool ChessPiece::isW(string from, string to){
    // Check if the piece is moving left and if it stays on the same rank
    return (from[1] == to[1] && to[0] < from[0]);
}
bool ChessPiece::isE(string from, string to){
    // Check if the piece is moving right and if it stays on the same rank
    return (from[1] == to[1] && to[0] > from[0]);
}

// If both file and rank differences are negative and equal in value, NorthEast
bool ChessPiece::isNE(string from, string to){
    return ((from[0] - to[0]) == from[1] - to[1] && from[1] - to[1] < 0);
}
// If positive file and negative rank differences and equal in value, NorthWest
bool ChessPiece::isNW(string from, string to){
    return ((from[0] - to[0]) * (-1) == from[1] - to[1] && from[1] - to[1] < 0);
}
// If both file and rank differences are positive and equal in value, SouthWest
bool ChessPiece::isSW(string from, string to){
    return ((from[0] - to[0]) == from[1] - to[1] && from[1] - to[1] > 0);
}
// If negative file and positive rank differences and equal in value, SouthEast
bool ChessPiece::isSE(string from, string to){
    return ((from[0] - to[0]) * (-1) == from[1] - to[1] && from[1] - to[1] > 0);
}


/*
 * Booleans that check the path
 */ 
 
// Vertical moves
bool ChessPiece::checkN(string from, string to, map<string, ChessPiece*> board){
    // Increase rank to check square above from
    from[1]++;
    // Until you reach the to index
    while(from.compare(to) != 0){
        // If you encounter a piece in between return false
        if(board[from] != NULL) { return false; }
        // Increase rank
        from[1]++;
    }
    
    return true;
}
bool ChessPiece::checkS(string from, string to, map<string, ChessPiece*> board){
    // Decrease rank to check square below from
    from[1]--;
    // Until you reach the to index
    while(from.compare(to) != 0){
        // If you encounter a piece in between return false
        if(board[from] != NULL) { return false; }
        // Decrease rank
        from[1]--;
    }
    
    return true;
}

// Horizontal moves
bool ChessPiece::checkW(string from, string to, map<string, ChessPiece*> board){
    // Decrease file to check square left of from
    from[0]--;
    // Until you reach the to index
    while(from.compare(to) != 0){
        // If you encounter a piece in between return false
        if(board[from] != NULL) { return false; }
        // Decrease file
        from[0]--;
    }
    
    return true;
}
bool ChessPiece::checkE(string from, string to, map<string, ChessPiece*> board){
    // Increase file to check square right of from
    from[0]++;
    // Until you reach the to index
    while(from.compare(to) != 0){
        // If you encounter a piece in between return false
        if(board[from] != NULL) { return false; }
        // Increase file
        from[0]++;
    }
    
    return true;
}

// Diagonal Moves
bool ChessPiece::checkNE(string from, string to, map<string, ChessPiece*> board){
    // Increase both file and rank to check NE of from
    from[0]++;
    from[1]++;
    // Until you reach the to index
    while(from.compare(to) != 0){
        // If you encounter a piece in between return false
        if(board[from] != NULL) { return false; }
        // Increase both file and rank
        from[0]++;
        from[1]++;
    }
    
    return true;
}
bool ChessPiece::checkNW(string from, string to, map<string, ChessPiece*> board){
    // Decrease file and increase rank to check NW of from
    from[0]--;
    from[1]++;
    // Until you reach the to index
    while(from.compare(to) != 0){
        // If you encounter a piece in between return false
        if(board[from] != NULL) { return false; }
        // Decrease file and increase rank
        from[0]--;
        from[1]++;
    }
    
    return true;
}
bool ChessPiece::checkSW(string from, string to, map<string, ChessPiece*> board){
    // Decrease both file and rank to check SW of from
    from[0]--;
    from[1]--;
    // Until you reach the to index
    while(from.compare(to) != 0){
        // If you encounter a piece in between return false
        if(board[from] != NULL) { return false; }
        // Decrease both file and rank
        from[0]--;
        from[1]--;
    }
    
    return true;
}
bool ChessPiece::checkSE(string from, string to, map<string, ChessPiece*> board){
    // Decrease rank and increase file to check NW of from
    from[0]++;
    from[1]--;
    // Until you reach the to index
    while(from.compare(to) != 0){
        // If you encounter a piece in between return false
        if(board[from] != NULL) { return false; }
        // Decrease rank and increase file
        from[0]++;
        from[1]--;
    }
    
    return true;
}