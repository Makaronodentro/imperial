/*
 * Queen Class : Inherits from abstract Class "ChessPiece"
 *------------------------------------------------------------
 * Description: a class representing a Queen piece. 
 *
 * Attributes: (inherited) colour -> the Colour of the piece {WHITE || BLACK}
 *             (inherited) type ->  a string with the piece's name
 *             (inherited) symbol -> a unicode string with the piece's symbol
 *
 * Public Methods: 
 *          Queen : Description -> constructs the piece.
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
#include "Queen.h"

Queen::Queen(Colour _colour) : ChessPiece (_colour, "Queen") {}

Queen::~Queen() {}

bool Queen::validateMove(string from, 
                        string to, 
                        map<string, ChessPiece*> board){
                                 
    //Check if North move && the path in between
    if(isN(from, to) && checkN(from, to, board)){ return true; }
    
    //Check if South move && the path in between
    if(isS(from, to) && checkS(from, to, board)){ return true; }
    
    //Check if East move && the path in between
    if(isE(from, to) && checkE(from, to, board)){ return true; }
    
    //Check if West move && the path in between
    if(isW(from, to) && checkW(from, to, board)){ return true; }
    
    //Check if NorthWest move && the path in between
    if(isNW(from, to) && checkNW(from, to, board)){ return true; }
    
    //Check if NorthEast move && the path in between
    if(isNE(from, to) && checkNE(from, to, board)){ return true; }
    
    //Check if SouthEast move && the path in between
    if(isSE(from, to) && checkSE(from, to, board)){ return true; }
    
    //Check if SouthWest move && the path in between
    if(isSW(from, to) && checkSW(from, to, board)){ return true; }
    
    return false;
}