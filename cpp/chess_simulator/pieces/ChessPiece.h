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
#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <map>
#include <string>
#include <iostream>
#include <cmath>

//#include "ChessInfo.hpp"

using namespace std;

enum Colour {WHITE, BLACK};

class ChessPiece {

  protected:
    // Attributes
    Colour colour;
    string type;
    string symbol;
    
  public:
    ChessPiece(Colour _colour, string _type);
    virtual ~ChessPiece() = 0;

    /*** Geters ***/
    
    // Returns Piece Colour
    Colour getColour();
    // Returns PieceType
    string getType();
    // Returns Piece Symbol
    string getSymbol();
    
    // Abstract function - to be implemented by each class
    virtual bool validateMove(string from, 
                              string to, 
                              map<string, ChessPiece*> board) = 0;
                              
    
    /*
     * Booleans that determine the direction of the move.
     */
    
    // Vertical moves
    bool isN(string from, string to);
    bool isS(string from, string to);
    
    // Horizontal moves
    bool isW(string from, string to);
    bool isE(string form, string to);
    
    // Diagonal moves
    bool isNE(string from, string to);
    bool isSE(string from, string to);
    bool isSW(string from, string to);
    bool isNW(string form, string to);
    
    
    /*
     * Booleans that check the path between start and the end square.
     */
     
    // Vertical moves
    bool checkN(string from, string to, map<string, ChessPiece*> board);
    bool checkS(string from, string to, map<string, ChessPiece*> board);
    
    // Horizontal moves
    bool checkW(string from, string to, map<string, ChessPiece*> board);
    bool checkE(string form, string to, map<string, ChessPiece*> board);
    
    // Diagonal moves
    bool checkNE(string from, string to, map<string, ChessPiece*> board);
    bool checkSE(string from, string to, map<string, ChessPiece*> board);
    bool checkSW(string from, string to, map<string, ChessPiece*> board);
    bool checkNW(string form, string to, map<string, ChessPiece*> board);
};
#endif
