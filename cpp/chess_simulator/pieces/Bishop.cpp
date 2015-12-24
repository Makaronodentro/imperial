/*
 * Bishop Class : Inherits from abstract Class "ChessPiece"
 *------------------------------------------------------------
 * Description: a class representing a Bishop piece. 
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
#include "Bishop.h"

Bishop::Bishop (Colour _colour) : ChessPiece (_colour, "Bishop") {}

Bishop::~Bishop () {}

bool Bishop::validateMove(string from, 
                        string to, 
                        map<string, ChessPiece*> board){
                            
    // Check NorthWest move
    if(isNW(from, to) && checkNW(from, to, board)){ return true; }
    
    // Check NorthEast move
    if(isNE(from, to) && checkNE(from, to, board)){ return true; }
    
    // Check SouthEast move
    if(isSE(from, to) && checkSE(from, to, board)){ return true; }
    
    // Check SouthWest move
    if(isSW(from, to) && checkSW(from, to, board)){ return true; }
    
    // If all possible moves don't return true, the move is invalid
    return false;
}