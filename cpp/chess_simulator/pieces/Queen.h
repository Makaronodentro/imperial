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
#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

class Queen : public ChessPiece {
    
  public:
    Queen (Colour _colour);
    ~Queen ();

    virtual bool validateMove(string from, 
                         string to, 
                         map<string, ChessPiece*> board);
};

#endif