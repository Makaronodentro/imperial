/*
 * ChessBoard Class
 *------------------------------------------------------------------------------
 * Description: Brings together the pieces and enables a game of chess.
 *
 * Attributes: board      -> a map containing pointers to all the pieces
 *             turn       -> the colour of the pieces allowed to move
 *                        {WHITE || BLACK}
 *             gameStatus -> the current status of the game 
 *                        {NORMAL || CHECK || CHECKMATE || STALEMATE}
 *
 * Public Methods: 
 *      ChessBoard : Description -> constructs the board by calling resetboard.
 *                   Parameters  -> -
 *                   Return      -> Does not return.
 *     ~ChessBoard : Description -> destructs the board by calling removePieces
 *                   Parameters  -> -
 *                   Return      -> Does not return.
 *
 *      resetboard : Description -> Removes any existing pieces, sets turn and
 *                               status variables, initiates the board and 
 *                               allocates the pieces.
 *                   Parameters  -> -
 *                   Return      -> -
 *
 *      submitMove : Description -> Checks if the move is possible, performs it
 *                               and updates the game status.
 *                   Parameters  -> string fromIndex, string toIndex
 *                   Return      -> -
 *
 *            draw : Description -> Draws in stdout the current board
 *                   Parameters  -> -
 *                   Return      -> -
 */
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>
#include <iostream>
#include <string>

#include "pieces/ChessPiece.h"
#include "pieces/King.h"
#include "pieces/Queen.h"
#include "pieces/Bishop.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Pawn.h"

using namespace std;

// Status of the current game
enum Status {NORMAL, CHECK, CHECKMATE, STALEMATE};

class ChessBoard {
    private:
        /*
         * Private Attributes
         */
         
        // Map to hold the locations of all pieces
        map<string, ChessPiece*> board;
        
        // Colour {WHITE, BLACK} declared in ChessPiece.h
            // No pieces no turn colour !
        Colour turn;
        // The status of the current game
        Status gameStatus;
        
        /*
         * Private Functions
         */
        
        // Helper to resetboard() and destructor()
        void removePieces();
        
        /*** MOVE CHECKS FOR SUBMIT MOVE***/
        bool loudMoveChecks(string from, string to);
        bool silentMoveChecks(string from, string to);
        
        /*** GAME STATUS UPDATE ***/
        // Checks the game status and takes care of the turn
        void updateStatus();
            
            // Helpers to checkStatus //
            // Checks if king of Colour col is threatened
            bool isCheck(Colour col);
            // Checks for Checkmate
            bool isCheckmate();
            // Checks for stalemate
            bool isStalemate();
        
                // Helper's to is* functions
                // returns the index of the king with colour col
                string findKing(Colour col);
                // attempts to make a move
                bool attemptMove(string from, string to);

        /*** PRINTERS ***/
        
        // Announces a successful move
        void printMove(string from, string to);
        // Announces a successful take
        void printTake(string from, string to);
        
        // Announces that the specific piece cannot perform this move
        void printInvalid(string from, string to);
        // Announces that piece couldn't move because player is in check
        void printInvalidInCheck(string from, string to);
        
        // Announces check
        void printCheck();
        // Announces checkmate
        void printCheckmate();
        // Announces stalemate
        void printStalemate();
    
    public:
    ChessBoard();
    ~ChessBoard();
        
    // Restarts the game    
    void resetBoard();
        
    // Submits a move -> Performs move and updates gameStatus
    void submitMove(string from, string to);   
        
    // Draws the current state of the board
    void draw();
};
#endif