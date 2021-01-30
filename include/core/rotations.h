//
// Created by Akaash Kolachina on 11/20/20.
//

#ifndef RUBIKS_CUBE_ROTATIONS_H
#define RUBIKS_CUBE_ROTATIONS_H
#include <string>
#include <visualizer/cubie.h>
#include <visualizer/rubiks_cube.h>
namespace rubiks_cube {
    class Rotations {
    public:
        /**
         * Turns a side based on the move specified
         * @param move_name the name of the move (Extensive details on how to
         * name a move are provided in the README)
         * @param cube the cube the rotation is being applied to
         */
        static void TurnSide(const std::string& move_name,RubiksCube& cube);

        /**
         * Turns the left side of the cube
         * @param cube the cube the rotations is being applied to
         * @param is_clockwise whether or not the turn is in the clockwise
         * direction
         */
        static void TurnLeftSide(RubiksCube& cube, bool is_clockwise);

        /**
         * Turns the right side of the cube
         * @param cube the cube the rotations is being applied to
         * @param is_clockwise whether or not the turn is in the clockwise
         * direction
         */
        static void TurnRightSide(RubiksCube& cube, bool is_clockwise);

        /**
         * Turns the top side of the cube
         * @param cube the cube the rotations is being applied to
         * @param is_clockwise whether or not the turn is in the clockwise
         * direction
         */
        static void TurnTopSide(RubiksCube& cube, bool is_clockwise);

        /**
         * Turns the bottom side of the cube
         * @param cube the cube the rotations is being applied to
         * @param is_clockwise whether or not the turn is in the clockwise
         * direction
         */
        static void TurnBottomSide(RubiksCube& cube, bool is_clockwise);

        /**
         * Turns the front side of the cube
         * @param cube the cube the rotations is being applied to
         * @param is_clockwise whether or not the turn is in the clockwise
         * direction
         */
        static void TurnFrontSide(RubiksCube& cube, bool is_clockwise);

        /**
         * Turns the bottom side of the cube
         * @param cube the cube the rotations is being applied to
         * @param is_clockwise whether or not the turn is in the clockwise
         * direction
         */
        static void TurnBackSide(RubiksCube& cube, bool is_clockwise);

    private:
        /**
         * Rotates a cubie positively along its z axis
         * @param cubie the cubie being rotated
         */
        static void RotateZConstant(Cubie& cubie);

        /**
         * Rotates a cubie positively along its x axis
         * @param cubie the cubie being rotated
         */
        static void RotateXConstant(Cubie& cubie);

        /**
         * Rotates a cubie positively along its y axis
         * @param cubie the cubie being rotated
         */
        static void RotateYConstant(Cubie& cubie);

        /**
         * Moves the cubies in a y side(top to bottom) in the positive direction
         * @param cube the cube the rotation is being applied to
         * @param y_idx the index of the y layer (0 corresponds to the bottom
         * layer and the top layer would be the dimension on the cube - 1)
         */
        static void MoveCubiesYSide(RubiksCube& cube,
                                    size_t y_idx);

        /**
         * Moves the cubies in a x side(left to right) in the positive direction
         * @param cube the cube the rotation is being applied to
         * @param x_idx the index of the x layer (0 corresponds to the left
         * layer and the right layer would be the dimension on the cube - 1)
         */
        static void MoveCubiesXSide(RubiksCube& cube,
                                    size_t x_idx);

        /**
         * Moves the cubies in a z side(back to front) in the positive direction
         * @param cube the cube the rotation is being applied to
         * @param z_idx the index of the z layer (0 corresponds to the back
         * layer and the front layer would be the dimension on the cube - 1)
         */
        static void MoveCubiesZSide(RubiksCube& cube,
                                    size_t z_idx);
    };
}
#endif //RUBIKS_CUBE_ROTATIONS_H
