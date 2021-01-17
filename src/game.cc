#include "game.h"
#include <algorithm>

Game::Game() {
    current_player = Game::PieceState::X;
    move_counter = 0;
    
    std::for_each(board.begin(), board.end(), [](std::array<PieceState, 3>& arr) {
        arr.fill(PieceState::Empty);
    });
}

bool Game::set_piece(int y, int x) {
    if (board[y][x] != Game::PieceState::Empty)
        return false;
    board[y][x] = current_player;
    move_counter++;
    if (current_player == Game::PieceState::X)
        current_player = Game::PieceState::O;
    else
        current_player = Game::PieceState::X;

    return true;
}

Game::PieceState Game::get_piece(int y, int x) {
    return board[y][x];
}

Game::PieceState Game::check_three(Game::PieceState a, Game::PieceState b, Game::PieceState c) {
    if (a == b && b == c && a != Game::PieceState::Empty)
        return a;
    else
        return Game::PieceState::Empty;
}

Game::Result Game::state_to_result(Game::PieceState state) {
    if (state == Game::PieceState::X) return Game::Result::XWon;
    if (state == Game::PieceState::O) return Game::Result::OWon;
    return Game::Result::InProgress;
}
Game::Result Game::get_result() {
    Game::Result cur;
    // Rows
    for (int i = 0; i < 3; i++) {
        cur = state_to_result(check_three(board[i][0], board[i][1], board[i][2]));
        if (cur != Game::Result::InProgress) return cur;
    }
    // Columns
    for (int i = 0; i < 3; i++) {
        cur = state_to_result(check_three(board[0][i], board[1][i], board[2][i]));
        if (cur != Game::Result::InProgress) return cur;
    }
    // Diagonals
    cur = state_to_result(check_three(board[0][0], board[1][1], board[2][2]));
    if (cur != Game::Result::InProgress) return cur;
    cur = state_to_result(check_three(board[0][2], board[1][1], board[2][0]));
    if (cur != Game::Result::InProgress) return cur;
    
    if (move_counter == 9) return Game::Result::Draw;
    return Game::Result::InProgress;
}
