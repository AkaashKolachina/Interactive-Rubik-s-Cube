//
// Created by Akaash Kolachina on 11/17/20.
//

#ifndef RUBIKS_CUBE_RUBIKS_CUBE_H
#define RUBIKS_CUBE_RUBIKS_CUBE_H
#include <visualizer/cubie.h>
#include <visualizer/turn_animation.h>
#include <queue>
#include <string>
namespace rubiks_cube {
    // A 3d-vector of cubies meant to represent the data of the Rubik's Cube
    typedef std::vector<std::vector<std::vector<Cubie>>> cube_vector;

    /**
     * Class for creating and handling RubiksCube objects
     */
    class RubiksCube {
    public:
        /**
         * Constructs a RubiksCube object
         * @param dim the dimension of the cube (a 3x3 rubik's cube has
         * a dim of 3)
         * @param size the pixel length of the cubies in the cube
         */
        RubiksCube(size_t dim, float size);

        /**
         * Draws the Rubik's cube
         */
        void Draw();

        /**
         * Updates the member variables of RubiksCube, specifically the turn and
         * move queues.
         */
        void Update();

        /**
         * Returns the cube_data_ member variable
         * @return the cube_data_ member variable
         */
        cube_vector& GetCubeData();

        /**
         * Returns the cube's dimension
         * @return the cube's dimension
         */
        size_t GetDimension() const;

        /**
         * Return the queue of turn animations
         * @return the turns_ member variable
         */
        const std::queue<TurnAnimation>& GetTurns() const;

        /**
         * Returns the moves_ queue
         * @return the moves_ queue
         */
        const std::queue<std::string>& GetMoves();

        /**
         * Updates a given spot in cube_data_ with a new cubie
         * @param x_idx the index in the x direction of cube_data_.
         * For reference, the rightmost layer would have an x index of 0
         * @param y_idx the index in the y direction of cube_data_.
         * For reference, the bottom layer would have a y index of 0
         * @param z_idx the index in the z direction of cube_data_.
         * For reference, the back layer would have a z index of 0
         * @param new_cubie the new cubie that goes in the given spot
         */
        void UpdateCubeData(size_t x_idx,size_t y_idx,size_t z_idx,
                            Cubie& new_cubie);

        /**
         * Adds a TurnAnimation to the turns_ queue
         * @param turn the TurnAnimation to be added
         */
        void AddTurn(const TurnAnimation& turn);

        /**
         * Removes a move from the move_ queue
         */
        void PopMove();
    private:
        // A 3d vector storing all the cubies that make up the cube
        // It is referenced as follows: cube_data[x_idx][y_idx][z_idx]. X-idx
        // corresponds to the layer of the cube in the right-left direction, with
        // the right layer having an x_idx of 0. Y_idx corresponds to the layer
        // of the cube in the bottom-top direction, with the bottom layer having
        // a y_idx of 0. The z_idx corresponds to layers in the cube in the
        // back-front direction, with the back layer having a z_idx of 0
        cube_vector cube_data_;
        size_t dimension_;
        // A queue of all the animations that still need to be run on the cube
        std::queue<TurnAnimation> turns_;
        // A queue of all the moves that need to be run on the cube, unlike
        // turns_ this queue is managed externally, in rubiks_cube_app
        std::queue<std::string> moves_;

        /**
         * Initializes the cube_vector to be with a given dimension to make
         * initializing the cubies slightly cleaner
         * @param dim the dimension of the rubiks cube
         */
        void InitializeCubeSize(size_t dim);

        /**
         * Draws the turn animation on a given cubie
         * @param cubie the given cubie
         */
        void DrawTurn(Cubie& cubie);
    };
}

#endif //RUBIKS_CUBE_RUBIKS_CUBE_H
