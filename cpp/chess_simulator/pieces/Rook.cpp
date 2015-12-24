/*
 * Rook Class : Inherits from abstract Class "ChessPiece"
 *------------------------------------------------------------
 * Description: a class representing a Rook piece. 
 *
 * Attributes: (inherited) colour -> the Colour of the piece {WHITE || BLACK}
 *             (inherited) type ->  a string with the piece's name
 *             (inherited) symbol -> a unicode string with the piece's symbol
 *
 * Public Methods: 
 *          Rook : Description -> constructs the piece.
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
#include "Rook.h"

Rook::Rook(Colour _colour) : ChessPiece (_colour, "Rook") {}

Rook::~Rook() {}

bool Rook::validateMove(string from, 
                        string to, 
                        map<string, ChessPiece*> board){

    // Verify North move and check Path
    if(isN(from, to) && checkN(from, to, board)) { return true; }
    
    // Verify South move and check Path
    if(isS(from, to) && checkS(from, to, board)) { return true; }
    
    // Verify East move and check Path
    if(isE(from, to) && checkE(from, to, board)) { return true; }
    
    // Verify West move and check Path
    if(isW(from, to) && checkW(from, to, board)) { return true; }
    
    return false;
                                 
}