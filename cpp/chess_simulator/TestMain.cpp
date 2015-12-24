// Main Program describing a short game between Alexander Alekhine, 
// and his opponent Vasic in 1931. Also tests chess move validation.

// Note: this file will be replaced during the automated testing.
#include <iostream>

using namespace std;

#include "ChessBoard.h"

int main() {
    
    cout << "===========================" << endl;
    cout << "Testing the Chess Engine" << endl;
    cout << "===========================" << endl;
    cout << endl;
    
    ChessBoard cb;
    cout << endl;

    cb.submitMove("D7", "D6");
    cout << endl;

    cb.submitMove("D4", "H6");
    cout << endl;

    cb.submitMove("D2", "D4");
    cout << endl;

    cb.submitMove("F8", "B4");
    cout << endl;
    
    cout << "===========================" << endl;
    cout << "        Error Testing      " << endl;
    cout << "===========================" << endl;
    cout << endl;

    cb.resetBoard();
    cout << endl;
    
    cb.submitMove("A1", "A4");
    cout << endl;
    
  // Invalid file and rank representation
  cb.submitMove ("A", "B");
  cb.submitMove ("ABC", "DEF");
  cb.submitMove ("A5H", "B6H");
  cb.submitMove ("This is total madness", "I can't believe it");
 
  // Source/Dest not valid
  cb.submitMove ("J9", "H8");
  cb.submitMove ("2D", "4D");
  cb.submitMove ("A1", "H0");
  
  // Empty Square
  cb.submitMove ("G3", "G4");
  
  // Wrong player's turn (Currently white's turn);
  cb.submitMove ("F7", "F6");
    
    cout << endl;
  cout << "============" << endl;
  cout << "Fool's Mate" << endl;
  cout << "============" << endl;
  cout << endl;
  
  cb.resetBoard();
  cb.submitMove ("F2", "F3");
  cb.submitMove ("E7", "E5");
  cb.submitMove ("G2", "G4");
  cb.submitMove ("D8", "H4");

  cb.draw();

  cout << endl;
  cout << "===============" << endl;
  cout << "Scholar's Mate" << endl;
  cout << "===============" << endl;
  cout << endl;

  cb.resetBoard();
  cb.submitMove ("E2", "E4");
  cb.submitMove ("E7", "E5");
  cb.submitMove ("D1", "H5");
  cb.submitMove ("B8", "C6");
  cb.submitMove ("F1", "C4");
  cb.submitMove ("G8", "F6");
  cb.submitMove ("H5", "F7");
  
  cb.draw();

  cout << endl;
  cout << "===========================" << endl;
  cout << "Hohmeister vs Frank (1993)" << endl;
  cout << "===========================" << endl;
  cout << endl;

  cb.resetBoard ();
  cb.submitMove ("D2", "D4");
  cb.submitMove ("E7", "E5");
  cb.submitMove ("D1", "D2");
  cb.submitMove ("E5", "E4");
  cb.submitMove ("D2", "F4");
  cb.submitMove ("F7", "F5");
  cb.submitMove ("H2", "H3");
  cb.submitMove ("F8", "B4");
  cb.submitMove ("B1", "D2");
  cb.submitMove ("D7", "D6");
  cb.submitMove ("F4", "H2");
  cb.submitMove ("C8", "E6");
  cb.submitMove ("A2", "A4");
  cb.submitMove ("D8", "H4");
  cb.submitMove ("A1", "A3");
  cb.submitMove ("C7", "C5");
  cb.submitMove ("A3", "G3");
  cb.submitMove ("F5", "F4");
  cb.submitMove ("F2", "F3");
  cb.submitMove ("E6", "B3");
  cb.submitMove ("D4", "D5");
  cb.submitMove ("B4", "A5");
  cb.submitMove ("C2", "C4");
  cb.submitMove ("E4", "E3");
  
  cb.draw();

  cout << endl;
  cout << "================================================" << endl;
  cout << "Anderssen vs Kieseritzky (1851) - Immortal Game" << endl;
  cout << "================================================" << endl;
  cout << endl;

  cb.resetBoard ();
  cb.submitMove ("E2", "E4");
  cb.submitMove ("E7", "E5");
  cb.submitMove ("F2", "F4");
  cb.submitMove ("E5", "F4");
  cb.submitMove ("F1", "C4");
  cb.submitMove ("D8", "H4");
  cb.submitMove ("E1", "F1");
  cb.submitMove ("B7", "B5");
  cb.submitMove ("C4", "B5");
  cb.submitMove ("G8", "F6");
  cb.submitMove ("G1", "F3");
  cb.submitMove ("H4", "H6");
  cb.submitMove ("D2", "D3");
  cb.submitMove ("F6", "H5");
  cb.submitMove ("F3", "H4");
  cb.submitMove ("H6", "G5");
  cb.submitMove ("H4", "F5");
  cb.submitMove ("C7", "C6");
  cb.submitMove ("G2", "G4");
  cb.submitMove ("H5", "F6");
  cb.submitMove ("H1", "G1");
  cb.submitMove ("C6", "B5");
  cb.submitMove ("H2", "H4");
  cb.submitMove ("G5", "G6");
  cb.submitMove ("H4", "H5");
  cb.submitMove ("G6", "G5");
  cb.submitMove ("D1", "F3");
  cb.submitMove ("F6", "G8");
  cb.submitMove ("C1", "F4");
  cb.submitMove ("G5", "F6");
  cb.submitMove ("B1", "C3");
  cb.submitMove ("F8", "C5");
  cb.submitMove ("C3", "D5");
  cb.submitMove ("F6", "B2");
  cb.submitMove ("F4", "D6");
  cb.submitMove ("C5", "G1");
  cb.submitMove ("E4", "E5");
  cb.submitMove ("B2", "A1");
  cb.submitMove ("F1", "E2");
  cb.submitMove ("B8", "A6");
  cb.submitMove ("F5", "G7");
  cb.submitMove ("E8", "D8");
  cb.submitMove ("F3", "F6");
  cb.submitMove ("G8", "F6");
  cb.submitMove ("D6", "E7");

    cb.draw();

  cout << endl;
  cout << "======================================" << endl;
  cout << "Gufeld vs Kavalek (1962) - Kavalanche" << endl;
  cout << "======================================" << endl;
  cout << endl;

  cb.resetBoard ();
  cb.submitMove ("E2", "E4");
  cb.submitMove ("E7", "E5");
  cb.submitMove ("G1", "F3");
  cb.submitMove ("B8", "C6");
  cb.submitMove ("F1", "B5");
  cb.submitMove ("F8", "C5");
  cb.submitMove ("C2", "C3");
  cb.submitMove ("F7", "F5");
  cb.submitMove ("D2", "D4");
  cb.submitMove ("F5", "E4");
  cb.submitMove ("F3", "G5");
  cb.submitMove ("C5", "B6");
  cb.submitMove ("D4", "D5");
  cb.submitMove ("E4", "E3");
  cb.submitMove ("G5", "E4");
  cb.submitMove ("D8", "H4");
  cb.submitMove ("D1", "F3");
  cb.submitMove ("G8", "F6");
  cb.submitMove ("E4", "F6");
  cb.submitMove ("G7", "F6");
  cb.submitMove ("D5", "C6");
  cb.submitMove ("E3", "F2");
  cb.submitMove ("E1", "D1");
  cb.submitMove ("D7", "C6");
  cb.submitMove ("B5", "E2");
  cb.submitMove ("C8", "E6");
  cb.submitMove ("F3", "H5");
  cb.submitMove ("H4", "H5");
  cb.submitMove ("E2", "H5");
  cb.submitMove ("E8", "E7");
  cb.submitMove ("B2", "B3");
  cb.submitMove ("E6", "D5");
  cb.submitMove ("C1", "A3");
  cb.submitMove ("E7", "E6");
  cb.submitMove ("H5", "G4");
  cb.submitMove ("F6", "F5");
  cb.submitMove ("G4", "H3");
  cb.submitMove ("H8", "G8");
  cb.submitMove ("B1", "D2");
  cb.submitMove ("D5", "G2");
  cb.submitMove ("H3", "G2");
  cb.submitMove ("G8", "G2");
  cb.submitMove ("H1", "F1");
  cb.submitMove ("A8", "D8");
  cb.submitMove ("D1", "E2");
  cb.submitMove ("D8", "D2");
  cb.submitMove ("E2", "D2");
  cb.submitMove ("E5", "E4");
  cb.submitMove ("A3", "F8");
  cb.submitMove ("F5", "F4");
  cb.submitMove ("B3", "B4");
  cb.submitMove ("G2", "G5");
  cb.submitMove ("F8", "C5");
  cb.submitMove ("G5", "C5");
  cb.submitMove ("B4", "C5");
  cb.submitMove ("B6", "C5");
  cb.submitMove ("A1", "B1");
  cb.submitMove ("F4", "F3");
  cb.submitMove ("B1", "B4");
  cb.submitMove ("E6", "F5");
  cb.submitMove ("B4", "D4");
  cb.submitMove ("C5", "D4");
  cb.submitMove ("C3", "D4");
  cb.submitMove ("F5", "F4");
  cout << endl << "--- Gufeld resigned ---" << endl;

    cb.draw();

    
    cout << "===========================" << endl;
    cout << "Alekhine vs. Vasic (1931)" << endl;
    cout << "===========================" << endl;
    cout << endl;

    cb.resetBoard();
    cout << endl;

    cb.submitMove("E2", "E4");
    cb.submitMove("E7", "E6");
    cout << endl;

    cb.submitMove("D2", "D4");
    cb.submitMove("D7", "D5");
    cout << endl;

    cb.submitMove("B1", "C3");
    cb.submitMove("F8", "B4");
    cout << endl;

    cb.submitMove("F1", "D3");
    cb.submitMove("B4", "C3");
    cout << endl;

    //cb.submitMove("H2", "H4");

    cb.submitMove("B2", "C3");
    cb.submitMove("H7", "H6");
    cout << endl;

    cb.submitMove("C1", "A3");
    cb.submitMove("B8", "D7");
    cout << endl;

    cb.submitMove("D1", "E2");
    cb.submitMove("D5", "E4");
    cout << endl;

    cb.submitMove("D3", "E4");
    cb.submitMove("G8", "F6");
    cout << endl;

    cb.submitMove("E4", "D3");
    cb.submitMove("B7", "B6");
    cout << endl;

    cb.submitMove("E2", "E6");
    cb.submitMove("F7", "E6");
    cout << endl;

    cb.submitMove("D3", "G6");
    cout << endl;
    
    cout << "===========================" << endl;
    cout << "White checkmate test" << endl;
    cout << "===========================" << endl;
    cout << endl; 
    
    cb.resetBoard();

    cb.submitMove("F2","F3");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("E7","E5");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("G2","G4");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("D8","H4");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;
    
    cout << "===========================" << endl;
    cout << "Black checkmate test" << endl;
    cout << "===========================" << endl;
    cout << endl; 

    cb.resetBoard();

    cb.submitMove("B1","C3");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("H7","H6");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("E2","E4");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("G7","G5");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;
    
    cb.submitMove("D2","D4");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("F7","F6");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("D1","H5");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;
    
    cout << "===========================" << endl;
    cout << "Stalemate test" << endl;
    cout << "===========================" << endl;
    cout << endl; 

    cb.resetBoard();

    cb.submitMove("C2","C4");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("H7","H5");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("H2","H4");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("A7","A5");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;
    
    cb.submitMove("D1","A4");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("A8","A6");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("A4","A5");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("A6","H6");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("A5","C7");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;
    
    cb.submitMove("F7","F6");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("C7","D7");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("E8","F7");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("D7","B7");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("D8","D3");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("B7","B8");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("D3","H7");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("B8","C8");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("F7","G6");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;

    cb.submitMove("C8","E6");
    cout << "* Valid" << endl;
    cout << endl;   cout << endl;
    
    cb.draw();
    
    return 0;
}
