//
// Created by Akaash Kolachina on 11/24/20.
//

#ifndef RUBIKS_CUBE_MOVE_MANAGER_H
#define RUBIKS_CUBE_MOVE_MANAGER_H
#include <visualizer/rubiks_cube.h>
#include <core/rotations.h>
#include <string>

namespace rubiks_cube {

    /**
     * Class for handling the logistics of moves. This includes creating proper
     * symbols for the moves, updating moves in a Rubik's Cube, and executing
     * sequences of moves
     */
    class MoveManager {
    public:
        /**
         * Executes given move on a cube
         * @param cube the cube the move is being executed on
         * @param move the move being executed (Details of how to name a move is
         * extensively covered in the README)
         */
        static void ExecuteMove(RubiksCube& cube, const std::string& move);

        /**
         * Executes a series of moves
         * @param cube the cube the moves are being executed on
         * @param moves the vector of moves being executed
         */
        static void ExecuteMoves(RubiksCube& cube,
                                 const std::vector<std::string>& moves);

        /**
         * Executes the negation of the specified moves in reverse order
         * @param cube the cube the execution is being done on
         * @param moves the moves being negated and done in reverse
         */
        static void UndoMoves(RubiksCube& cube,
                              const std::vector<std::string>& moves);

        /**
         * Creates a move name given the letter of the move and it's direction
         * @param letter the letter of the move
         * @param is_clockwise whether or not the move is clockwise
         * @return the move name
         */
        static std::string MakeMoveSymbol(std::string letter, bool is_clockwise);

        /**
         * Updates the moves queue in a given RubiksCube
         * @param cube the cube the update is being applied to
         */
        static void UpdateMoves(RubiksCube& cube);
    private:
        /**
         * Takes in a given move name and the name of the move that will negate
         * it
         * @param move the given move
         * @return a string with the name of the move that will negate the given
         * move
         */
        static std::string NegateMove(const std::string& move);
    };
}

#endif //RUBIKS_CUBE_MOVE_MANAGER_H
