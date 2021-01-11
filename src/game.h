#pragma once
class Game {
    public:
        // Represents the state of a spot in a tic tac toe board.
        enum PieceState {
            X, O, Empty
        };

        // Represents the result of a game.
        enum Result {
            XWon, OWon, Draw, InProgress
        };

        Game();

        // Set piece in game on specified coordinates.
        // Returns true if the setting was successful, i.e. the spot wasn't already occupied.
        bool set_piece(int y, int x);
        
        PieceState get_piece(int y, int x);

        PieceState current_player;
        int move_counter;

        // Get the result of the game. 
        Result get_result();
    private:
        PieceState board[3][3];

        PieceState check_three(PieceState a, PieceState b, PieceState c);
        Result state_to_result(PieceState state);
};
