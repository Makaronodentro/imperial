/*
 * Pawn Class : Inherits from abstract Class "ChessPiece"
 *------------------------------------------------------------
 * Description: a class representing a Pawn piece. 
 *
 * Attributes: (inherited) colour -> the Colour of the piece {WHITE || BLACK}
 *             (inherited) type ->  a string with the piece's name
 *             (inherited) symbol -> a unicode string with the piece's symbol
 *
 * Public Methods: 
 *          Pawn : Description -> constructs the piece.
 *                   Parameters  -> Colour. Sets the piece's colour
 *                   Return      -> Does not return.
 *    Virtual:     
 *    validateMove : Description -> Checks if the piece can move to the endIndex
 *                   Parameters  -> strings startIndex and endIndex, the board
 *                   Return      -> True if the move is valid. False otherwise.
 *    Inherited:
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
#include "Pawn.h"

Pawn::Pawn(Colour _colour) : ChessPiece (_colour, "Pawn") {}

Pawn::~Pawn () {}

bool Pawn::validateMove(string from, 
                        string to, 
                        map<string, ChessPiece*> board){
    
    /*
    * For Pawns there are four possible moves.
    * 1 or 2 forward
    * 2 diagonal
    */ 
    
    /*
     * NOTE: All input has been sanitized by the board.
     * - indices are within bounds
     * - the indexTo does not point to a piece of the same colour
     */
     
    // White Pawns (They move "North")
    if(colour == WHITE){
        // Check single move
        if(isN(from, to) && to[1] - from[1] == 1 // Move is 1 square North
                         && board[to] == NULL)  // Pawn cannot capture forward
                         { return true; }
        // Check double move
        if(isN(from, to) && from[1] == '2' // Move is North, and it is the first
                         && to[1] - from[1] == 2 // Move is 2 squares
                         && checkN(from, to, board) // Check in between square
                         && board[to] == NULL)  // Pawn cannot capture forward
                         { return true; }
        
        // Check diagonals
        if(isNW(from, to) && to[1] - from[1] == 1 // Move is 1 square NorthWest
                          && board[to] != NULL){ return true; }
        if(isNE(from, to) && to[1] - from[1] == 1 // Move is 1 square NorthEast
                          && board[to] != NULL){ return true; }
    }
     
    // Black Pawns (They move "South")
    if(colour == BLACK){
        // Check single move
        if(isS(from, to) && from[1] - to[1] == 1 // Move is 1 square South
                         && board[to] == NULL) // Pawn cannot capture forward
                         { return true; } 
        // Check double move
        if(isS(from, to) && from[1] == '7' // Move is South, and it is the first
                         && from[1] - to[1] == 2 // Move is 2 squares
                         && checkS(from, to, board) // Check in between square
                         && board[to] == NULL)  // Pawn cannot capture forward
                         { return true; }
        
        // Check diagonals
            // Check if it is SE or SW
            // and if it also moves 1 square away return true
        if(isSE(from, to) && from[1] - to[1] == 1 // Move is 1 square SouthWest
                          && board[to] != NULL){ return true; }
        if(isSW(from, to) && from[1] - to[1] == 1 // Move is 1 square SouthEast
                          && board[to] != NULL){ return true; }
    }
    
    return false;
}