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
 *
 *  NOTES: The program has been check for memory leaks with vlagrind.
 */
#include "ChessBoard.h"

// Constructs the board and starts a new game by calling resetboard()
ChessBoard::ChessBoard(){
    resetBoard();
}

// Destructs the board by removing any pieces left to avoid memory leaks
ChessBoard::~ChessBoard(){
    removePieces();
}

// Resets the board and restarts the game
void ChessBoard::resetBoard(){
    // Delete any pieces that may be present
    removePieces();
    
    // Sets turn to Colour WHITE
    turn = WHITE;
    // Resets status to Status NORMAL
    gameStatus = NORMAL;
  
    // Create White Pieces
    board["A1"] = new Rook(WHITE);
    board["B1"] = new Knight(WHITE);
    board["C1"] = new Bishop(WHITE);
    board["D1"] = new Queen(WHITE);
    board["E1"] = new King(WHITE);
    board["F1"] = new Bishop(WHITE);
    board["G1"] = new Knight(WHITE);
    board["H1"] = new Rook(WHITE);
    
    board["A2"] = new Pawn(WHITE);
    board["B2"] = new Pawn(WHITE);
    board["C2"] = new Pawn(WHITE);
    board["D2"] = new Pawn(WHITE);
    board["E2"] = new Pawn(WHITE);
    board["F2"] = new Pawn(WHITE);
    board["G2"] = new Pawn(WHITE);
    board["H2"] = new Pawn(WHITE);
    
    // Create Black Pieces
    board["A8"] = new Rook(BLACK);
    board["B8"] = new Knight(BLACK);
    board["C8"] = new Bishop(BLACK);
    board["D8"] = new Queen(BLACK);
    board["E8"] = new King(BLACK);
    board["F8"] = new Bishop(BLACK);
    board["G8"] = new Knight(BLACK);
    board["H8"] = new Rook(BLACK);
    
    board["A7"] = new Pawn(BLACK);
    board["B7"] = new Pawn(BLACK);
    board["C7"] = new Pawn(BLACK);
    board["D7"] = new Pawn(BLACK);
    board["E7"] = new Pawn(BLACK);
    board["F7"] = new Pawn(BLACK);
    board["G7"] = new Pawn(BLACK);
    board["H7"] = new Pawn(BLACK);
  
    // Initialize empty cells
    string index = "A3";
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            board[index] = NULL;
            index[0]++;
        }
        index[0] = 'A';
        index[1]++;
    }
    
    // Announce new game is ready
    cout<<"A new chess game is started!"<<endl;
}

// Iterates through the board and deletes all the pieces
void ChessBoard::removePieces(){
    string index = "A1";
    
    for(int i = 0; i < 8; i++){
        index[0] = 'A' + i;
        for(int j = 0; j < 8; j++){
            index[1] = '1' + j;
            delete board[index];
        }
    }
}

// Draws the current state of the board
void ChessBoard::draw(){
    string index = "A8";

    for(int i = 8; i >= 0; i--){
        cout<<" ";
        if(i == 8){
           for(int j = 0; j < 8; j++){
                    cout<<"  "<<index[0]<<" ";
                    
                index[0]++;
            }
            cout<<" "<<endl;
            cout<<" ---------------------------------"<<endl;
            index[0] = 'A';
        }
        else{
            for(int j = 0; j < 8; j++){
                if(!board[index])
                    cout<<"|   ";
                else
                    cout<<"| "<<board[index]->getSymbol()<<" ";
                    
                index[0]++;
            }
            cout<<"| "<<i + 1<<endl;
            if(i != 0)
                cout<<" ----+---+---+---+---+---+---+----"<<endl;
            else
                cout<<" ---------------------------------"<<endl;
            index[1]--;
            index[0] = 'A';
        }
    }
    
}

/* SUBMITMOVE(string from, string to) 
 * -----------------------------------------------------------------------------
 * 1. - Check Game Status (default is NORMAL)
 *     a. - If STALEMATE or CHECKMATE, announce status and returns
 *     b. - If CHECK or NORMAL proceed 
 * 2. - Validate Move
 *     a. Check move by calling loudMoveChecks(from, to). Return if fail 
 *     b. If in CHECK, also attemptMove(from, to) to see if it rescues the king
 * 3. - Announce move, by calling the appropriate printer
 * 4. - Make move by setting the 'to' pointer equal to 'from'
 * 5. - Update game status by calling updateStatus()
 */

void ChessBoard::submitMove(string from, string to){
    if(gameStatus == NORMAL){
        if(!loudMoveChecks(from, to)) return;
        
        // Anounce move
        if(board[to] == NULL){
            printMove(from, to);
        }
        else{
            printTake(from, to);
        }
        
        // Make move
        delete board[to];
        board[to] = board[from];
        board[from] = NULL;
        
        // Update status
        updateStatus();
    }
    else if(gameStatus == CHECK){
        if(!loudMoveChecks(from, to)){ return; }
        
        if(!attemptMove(from, to)){
            printInvalidInCheck(from, to);
            return;
        }
        
        // Anounce move
        if(board[to] == NULL){
            printMove(from, to);
        }
        else{
            printTake(from, to);
        }
        
        // Make move
        delete board[to];
        board[to] = board[from];
        board[from] = NULL;
        
        // Update status
        updateStatus();
    }
    else if(gameStatus == CHECKMATE){
        printCheckmate();
    }
    else if(gameStatus == STALEMATE){
        printStalemate();
    }
}

/*** MOVE CHECKS ***/
/* Checklist:
 * ----------
 * Validate Input Length. Important to be done here, prevents segfaults
 * Check if input is within the boundaries.
 * Check if 'from' == 'to'
 * Check if 'from' is empty. Important to be done here, prevents segfaults
 * Check if turn is the same colour as the 'from' piece
 * Check if 'to' is of the same colour as 'from'
 * Check if the specific type of piece can perform that move and if the path
 *   between 'from' and 'to' is clear. Call piece func. validateMove()
 *
 * If all checks succeed return true
 *
 * NOTE: The two functions are identical yet loud announces the type of error
 *       in stdout.
 */
bool ChessBoard::loudMoveChecks(string from, string to){
    
    // Validate input (Prevents segfaults for later checks)
    if(from.length() != 2 || to.length() != 2){
        cout<<"Invalid submitmove() parameters!"<<endl;
        return false;
    }
    
    // Check from boundaries
    if(from[0] < 'A' || from[0] > 'H'){
        cout<<"Invalid 'from' index, file out of bounds"<<endl;
        return false;
    }
    else if(from[1] < '1' || from[1] > '8'){
        cout<<"Invalid 'from' index, rank out of bounds"<<endl;
        return false;
    }
    
    // Check to boundaries
    if(to[0] < 'A' || to[0] > 'H'){
        cout<<"Invalid 'to' index, file out of bounds"<<endl;
        return false;
    }
    else if(to[1] < '1' || to[1] > '8'){
        cout<<"Invalid 'to' index, rank out of bounds"<<endl;
        return false;
    }
    
    // Identical indices.
    if(from.compare(to) == 0){
        cout<<"Your piece is already at the destination!"<<endl;
        return false;
    }
    
    // Check for empty cell first to avoid segfaults
    if(!board[from]){
        cout<<"There is no piece at position "<<from<<"!"<<endl;
        return false;
    }

    // Get from cell piece colour
    Colour colourFrom = board[from]->getColour();

    // Check turn and colour of piece
    if(colourFrom != turn && turn == BLACK){
        cout<<"It is not White's turn to move!"<<endl;
        return false;
    }
    else if(colourFrom != turn && turn == WHITE){
        cout<<"It is not Black's turn to move!"<<endl;
        return false;
    }

    // Check if destination is not empty
    if(board[to]){
        // Check piece colour at destination
        if(colourFrom == board[to]->getColour()){
        cout<<"A piece may not take a piece of the same colour!"<<endl;
        return false;
        }
    }
    
    // Check if piece can perform the move and if the path is clear
    if(!board[from]->validateMove(from, to, board)){
            printInvalid(from, to);
            return false;
    }
    else{
        return true;
    }
}
bool ChessBoard::silentMoveChecks(string from, string to){
    
    // Validate input
    if(from.length() != 2 || to.length() != 2){
        return false;
    }
    
    // Identical indices.
    if(from.compare(to) == 0){
        return false;
    }
    
    // Check from boundaries
    if(from[0] < 'A' || from[0] > 'H'){
        return false;
    }
    else if(from[1] < '1' || from[1] > '8'){
        return false;
    }
    
    // Check to boundaries
    if(to[0] < 'A' || to[0] > 'H'){
        return false;
    }
    else if(to[1] < '1' || to[1] > '8'){
        return false;
    }
    
    // Check for empty cell first to avoid segfaults
    if(!board[from]){
        return false;
    }

    // Get from cell piece colour
    Colour colourFrom = board[from]->getColour();

    // Check turn and colour of piece
    if(colourFrom != turn && turn == BLACK){
        return false;
    }
    else if(colourFrom != turn && turn == WHITE){
        return false;
    }

    // Check if destination is not empty
    if(board[to]){
        // Check piece colour at destination
        if(colourFrom == board[to]->getColour()){
        return false;
        }
    }
    
    // Check if piece can perform the move and if the path is clear
    if(!board[from]->validateMove(from, to, board)){
            return false;
    }
    else{
        return true;
    }
}


/*** GAME STATUS UPDATE ***/
/* Procedure
 * ---------
 * 1. Called after move has been made, so switch turn
 * 2. Check if the king of the player about to move is in check
 *   a. If also in checkmate announce it and set status to CHECKMATE
 *   b. Else announce simple check and set status to CHECK
 * 3. If not in check, check for stalemate. If true announce and set status
 * 4. If none of the above is true the status of the game is NORMAL
 */
void ChessBoard::updateStatus(){
    // Switch turn as the move is over
    turn = turn == WHITE ? BLACK : WHITE;
    
    // Check whether the move caused the opponent to be in check
    if(isCheck(turn)){
        // If in check, check to see if he doesn't have any valid moves.
        if(isCheckmate()){
            // If not announce end of game
            // set status to CHECKMATE so that no more moves are accepted
            printCheckmate();
            gameStatus = CHECKMATE;
        }
        else{
            // If in check but with valid moves, announce check
            // set status to CHECK so that exrta scrutiny is added to moves
            printCheck();
            gameStatus = CHECK;
        }
    }
    // If not in check
    // Check whether the opponent has any valid moves
    else if(isStalemate()){
        // If not announce end of game
        // set status to STALEMATE so that no more moves are accepted
        printStalemate();
        gameStatus = STALEMATE;
    }
    else{
        // If none of the above are true, status is NORMAL
        gameStatus = NORMAL;
    }
}

/* isCheck(Colour col)
 * ---------
 * Checks whether the king of Colour col is threatened by any pieces
 * 
 * 1. Temporarily switch turn to enable opponent's pieces to move
 * 2. Iterate through the board and try to find a piece that can take the king
*/
bool ChessBoard::isCheck(Colour col){
    string index = "A1"; // Index for traversing the map
    string king = findKing(col); // get the index of the king in question
    
    // Switch turn to enable King's opponents to pass move checks
    turn = (turn == WHITE ? BLACK : WHITE);
    
    // Iterate through the board and try to find if a piece can take the king
    for(int i = 0; i < 8; i++){
        index[0] = 'A' + i;
        for(int j = 0; j < 8; j++){
            index[1] = '1' + j;
            if(silentMoveChecks(index, king)){
                
                // If there is valid move, reset turn and return true
                turn = (turn == WHITE ? BLACK : WHITE);
                return true;
            }
        }
    }
    
    // If there is no valid move, reset turn and return false
    turn = (turn == WHITE ? BLACK : WHITE);
    return false;
}

/* isCheckmate()
 * ---------
 * Checks whether the king of the current turn is under CHECKMATE
 * 
 * 1. Called if isCheck returns true. So it is assumed that the king is in check
 * 2. Iterate through the board and try to find any move that might result in
 *     the king not being in check anymore. Do so by calling attemptMove(), for
 *     each move. attemptMove(from, to) temporarily performs the move from -> to
 *     and then calls isCheck. Then returns true if isCheck returns false.
 * 3. If no move is found return true
*/
bool ChessBoard::isCheckmate(){
    // Indices used to attempt all possible moves
    string from = "A1"; // from index
    string to = "A1"; // to index

    // Attempt all possible moves and try to find one that results in no check
    for(int i = 0; i < 8; i++){
        to[0] = 'A' + i;
        for(int j = 0; j < 8; j++){
            to[1] = '1' + j;
            for(int k = 0; k < 8; k++){
                from[0] = 'A' + k;
                for(int l = 0; l < 8; l++){
                    from[1] = '1' + l;
                    
                    if(attemptMove(from, to)){
                         // draw();
                         // cout<<"Not checkmate, if you move "
                         //     <<from<<" to "<<to<<endl;
                        
                        // If a move is found return false
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

/* isStalemate()
 * ---------
 * Checks whether the player of the current turn is under STALEMATE
 * 
 * 1. Called if isCheck returns false. So it is assumed that the king is safe.
 * 2. Iterate through the board and try to find any move that will not result in
 *     the king being in check. Do so by calling attemptMove(), for each move.
 * 3. If no move is found return true
*/
bool ChessBoard::isStalemate(){
    // Indices used to attempt all possible moves
    string from = "A1"; // from index 
    string to = "A1"; // to index
    
    // Attempt all possible moves and try to find a valid one
    for(int i = 0; i < 8; i++){
        to[0] = 'A' + i;
        for(int j = 0; j < 8; j++){
            to[1] = '1' + j;
            for(int k = 0; k < 8; k++){
                from[0] = 'A' + k;
                for(int l = 0; l < 8; l++){
                    from[1] = '1' + l;
                    
                    if(attemptMove(from, to)){
                         // draw();
                         // cout<<"Not stalemate, if you move "
                         //     <<from<<" to "<<to<<endl;
                        
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

/* attemptMove(from, to)
 * ----------------------------------------------------------------------
 * Attempts a temporary move and checks if the king of the player who moved 
 * is left in CHECK.
 * 
 * Used by submitmove() to determine whether a move is valid under CHECK
 * Used by isCheckmate() to determine whether there are any valid moves
 * Used by isStalemate() to determine whether there are any valid moves
 */
bool ChessBoard::attemptMove(string from, string to){
    // Ensure that the move is legal
    if(silentMoveChecks(from, to)){
        
        // Perform the move
        board["tmp"] = board[to];
        board[to] = board[from];
        board[from] = NULL;
        
        // Check if the move results in check
        if(!isCheck(turn)){
            // Undo the move
            board[from] = board[to];
            board[to] = board["tmp"];
            
            // If the king is not threatened return true (move is possible)
            return true;
        }

        // Undo the move
        board[from] = board[to];
        board[to] = board["tmp"];
    }
    
    // If the king is threatened return false (attempted move is impossible)
    return false;
}

// Returns the index of the king with Colour col
string ChessBoard::findKing(Colour col){
    string index = "A1";
    
    for(int i = 0; i < 8; i++){
        index[0] = 'A' + i;
        for(int j = 0; j < 8; j++){
            index[1] = '1' + j;
            
            if(board[index] != NULL){
                if(board[index]->getType().compare("King") == 0 && 
                   board[index]->getColour() == col){
                       return index;
                }
            }
        }
    }
    
    return index;
}

/*** PRINTERS ***/

// Announces a successful move
void ChessBoard::printMove(string start, string end){
    cout<<(turn == WHITE ? "White's " : "Black's ")
                    <<board[start]->getType()<<" moves from "
                    <<start
                    <<" to "
                    <<end
                    <<endl;
}
// Announces a successful take
void ChessBoard::printTake(string start, string end){
     cout<<(turn == WHITE ? "White's " : "Black's ")
                    <<board[start]->getType()<<" moves from "
                    <<start
                    <<" to "
                    <<end
                    <<" taking "
                    <<(turn == BLACK ? "White's " : "Black's ")
                    <<board[end]->getType()
                    <<endl;
}

// Announces that the specific piece cannot perform this move
void ChessBoard::printInvalid(string start, string end){
    cout<<(turn == WHITE ? "White's " : "Black's ")
                    <<board[start]->getType()<<" cannot move to "
                    <<end
                    <<"!"
                    <<endl;
}
// Announces that piece couldn't move because player is in check
void ChessBoard::printInvalidInCheck(string start, string end){
    cout<<(turn == WHITE ? "White's " : "Black's ")
                    <<board[start]->getType()<<" cannot move to "
                    <<end
                    <<" while in check!"
                    <<endl;
}

// Announces check
void ChessBoard::printCheck () {
    cout<<(turn == BLACK ? "Black" : "White")
        <<" is in check"
        <<endl;
}
// Announces checkamte
void ChessBoard::printCheckmate() {
    cout<<(turn == BLACK ? "Black" : "White")
        <<" is in checkmate"
        << endl;
}
// Announces stalemate
void ChessBoard::printStalemate () {
    cout<<(turn == BLACK ? "Black" : "White")
        <<" is in stalemate"
        << endl;
}