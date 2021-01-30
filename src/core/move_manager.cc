//
// Created by Akaash Kolachina on 11/24/20.
//
#include "core/move_manager.h"
using std::string;
using std::vector;
namespace rubiks_cube {
    void MoveManager::ExecuteMove(RubiksCube &cube, const std::string &move) {
        // Move is only valid if it is one or two characters
        if (move.empty() || move.size() > 2) {
            return;
        }

        bool is_clockwise = true;
        if (move.size() == 2 && move[1] == '\'') {
            // If the move has a ' symbol at the end, that means it is counter
            // clockwise
            is_clockwise = false;
        }

        // To execute a move we just need to add the turn animation of the move
        // to the cube, once the animation is done running, the rotation of the
        // actual data will be handled then.
        // Note that in some turns is_clockwise is negated, this is because
        // clockwise relative to that side is actually in the opposite direction
        // of clockwise in the plane that side is on as a whole
        size_t dim = cube.GetDimension();
        // The center cubie is indexed at (dim-1) / 2 for all indices for a cube
        // of any size
        Cubie cube_center = cube.GetCubeData()[(dim - 1) / 2][(dim - 1) / 2][(dim - 1) / 2];
        if (tolower(move[0]) == 'l') {
            TurnAnimation left_turn = TurnAnimation({1,0,0},
                                                    cube_center.GetPosition(),
                                                    is_clockwise,0,
                                                    move);
            cube.AddTurn(left_turn);
        } else if (tolower(move[0]) == 'r') {
            TurnAnimation right_turn = TurnAnimation({1,0,0},
                                                     cube_center.GetPosition(),
                                                    !is_clockwise,2,
                                                    move);
            cube.AddTurn(right_turn);
        } else if (tolower(move[0]) == 'u') {
            TurnAnimation up_turn = TurnAnimation({0,1,0},
                                                  cube_center.GetPosition(),
                                                    !is_clockwise,2,move);
            cube.AddTurn(up_turn);
        } else if (tolower(move[0]) == 'd') {
            TurnAnimation down_turn = TurnAnimation({0,1,0},
                                                    cube_center.GetPosition(),
                                                  is_clockwise,0,move);
            cube.AddTurn(down_turn);
        } else if (tolower(move[0]) == 'f') {
            TurnAnimation front_turn = TurnAnimation({0,0,1},
                                                     cube_center.GetPosition(),
                                                  !is_clockwise,2,move);
            cube.AddTurn(front_turn);
        } else if (tolower(move[0]) == 'b') {
            TurnAnimation back_turn = TurnAnimation({0,0,1},
                                                    cube_center.GetPosition(),
                                                     is_clockwise,0,move);
            cube.AddTurn(back_turn);
        }
    }

    void MoveManager::ExecuteMoves(RubiksCube &cube,
                                   const std::vector<std::string> &moves) {
        for (const string& move : moves) {
            ExecuteMove(cube, move);
        }
    }

    void MoveManager::UndoMoves(RubiksCube &cube,
                                const std::vector<std::string> &moves) {
        vector<string> reverse_moves;
        // Add the negation of the moves to the vector in reverse order
        for (int idx = moves.size() - 1; idx >= 0; idx--) {
            reverse_moves.push_back(NegateMove(moves[idx]));
        }
        if (!reverse_moves.empty()) {
            // Execute new move sequence
            ExecuteMoves(cube, reverse_moves);
        }
    }

    std::string MoveManager::MakeMoveSymbol(string key,
                                            bool is_clockwise) {
        // If the move is clockwise, the symbol is just the key pressed,
        // otherwise it is the key plus an apostrophe
        if (is_clockwise) {
            return key;
        } else {
            return key + "\'";
        }

    }

    void MoveManager::UpdateMoves(RubiksCube &cube) {
        cube.Update();
        if (!cube.GetMoves().empty()) {
            // If there is a move in the queue, execute it and remove it from
            // the queue
            Rotations::TurnSide(cube.GetMoves().front(),cube);
            cube.PopMove();
        }
    }

    std::string MoveManager::NegateMove(const std::string &move) {
        string new_move;
        if (move.size() == 1) {
            new_move = move + '\'';
        } else if (move.size() == 2) {
            // It is assumed that the move passed was of the proper format,
            // so the second character is an apostrophe
            new_move = move[0];
        }
        return new_move;
    }
}
