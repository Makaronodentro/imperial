/*
 * King Class : Inherits from abstract Class "ChessPiece"
 *------------------------------------------------------------
 * Description: a class representing a King piece. 
 *
 * Attributes: (inherited) colour -> the Colour of the piece {WHITE || BLACK}
 *             (inherited) type ->  a string with the piece's name
 *             (inherited) symbol -> a unicode string with the piece's symbol
 *
 * Public Methods: 
 *          King : Description -> constructs the piece.
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
#include "King.h"

King::King(Colour _colour) : ChessPiece (_colour, "King") {}

King::~King() {}

bool King::validateMove(string from, 
                        string to, 
                        map<string, ChessPiece*> board){
     /*
     * NOTE: All input has been sanitized by the board.
     * - indices are within bounds
     * - the indexTo does not point to a piece of the same colour
     */
    
    // Since loudMoveChecks has checked 'to' there is no use for the board
    // Silence warning for the unused parameter board
    (void) board;
    
    // Check Vertical move of 1 square
    if(isN(from, to) && to[1] - from[1] == 1) { return true; }
    if(isS(from, to) && from[1] - to[1] == 1) { return true; }
    
    // Check Horizontal move of 1 square
    if(isE(from, to) && to[0] - from[0] == 1) { return true; }
    if(isW(from, to) && from[0] - to[0] == 1) { return true; }
    
    // Check Diagonal move of 1 square
    if(isNE(from, to) && to[1] - from[1] == 1) { return true; }
    if(isNW(from, to) && to[1] - from[1] == 1) { return true; }
    if(isSE(from, to) && from[1] - to[1] == 1) { return true; }
    if(isSW(from, to) && from[1] - to[1] == 1) { return true; }                        

    return false;
}