/*
 * Knight Class : Inherits from abstract Class "ChessPiece"
 *------------------------------------------------------------
 * Description: a class representing a Knight piece. 
 *
 * Attributes: (inherited) colour -> the Colour of the piece {WHITE || BLACK}
 *             (inherited) type ->  a string with the piece's name
 *             (inherited) symbol -> a unicode string with the piece's symbol
 *
 * Public Methods: 
 *          Knight : Description -> constructs the piece.
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
#include "Knight.h"

Knight::Knight(Colour _colour) : ChessPiece (_colour, "Knight") {}

Knight::~Knight() {}

bool Knight::validateMove(string from, 
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
    
    // If move is 2 squares horizontal and 1 square vertical
    if(abs(from[0] - to[0]) == 2 && abs(from[1] - to[1]) == 1){ return true; }
    // If move is 1 squares horizontal and 2 square vertical
    if(abs(from[0] - to[0]) == 1 && abs(from[1] - to[1]) == 2){ return true; }
    
    return false;
}