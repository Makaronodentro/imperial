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
#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : public ChessPiece {
    
  public:
    Bishop (Colour _colour);
    ~Bishop ();

    virtual bool validateMove(string from, 
                         string to, 
                         map<string, ChessPiece*> board);
};

#endif