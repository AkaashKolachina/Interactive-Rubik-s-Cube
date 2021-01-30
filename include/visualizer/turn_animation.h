//
// Created by Akaash Kolachina on 11/25/20.
//

#ifndef RUBIKS_CUBE_TURN_ANIMATION_H
#define RUBIKS_CUBE_TURN_ANIMATION_H
#include "visualizer/cubie.h"
#include "string"
namespace rubiks_cube {
    /**
     * Class for TurnAnimation objects, these objects are used to animate turns
     * on the Rubik's Cube
     */
    class TurnAnimation {
    public:
        /**
         * Constructs a turn animation
         * @param rotation_axis the axis of rotation for the turn
         * @param cube_center the center of the cube
         * @param is_clockwise whether or not the animation is clockwise
         * @param layer the layer of the cube the animation is applied to
         * @param move_name the name of the move the animation is animating
         */
        TurnAnimation(const glm::vec3& rotation_axis,const glm::vec3& cube_center,
                      bool is_clockwise, size_t layer, const std::string& move_name);

        /**
         * Runs a portion of the animation each time the function is called
         * @param cubie the cubie the animation is being applied to
         */
        void RunRotation(Cubie& cubie);

        /**
         * Returns true if the animation is finished, false otherwise
         * @return whether or not hte animation is finished
         */
        bool IsFinished() const;

        /**
         * Returns the name of the rotation axis
         * @return name of the rotation axis
         */
        char GetAxisName() const;

        /**
         * Returns the layer the animation is being applied to
         * @return the layer
         */
        size_t GetLayer() const;

        /**
         * Returns the name of the move
         * @return the name of the move
         */
        const std::string& GetMoveName() const;
    private:
        // The fraction of the angle completed each time RunRotation is called
        float angle_slice_ = .01 * M_PI_2;
        size_t increment_ = 0;
        bool is_finished_ = false;

        glm::vec3 rotation_axis_;
        glm::vec3 face_center_;
        bool is_clockwise_;
        char axis_name_;
        // Layer refers to the same data that x_idx, y_idx, and z_idx refer to
        // in the RubiksCube class, the only difference being "layer" makes more
        // semantic sense outside of the context of the vector.
        size_t layer_;
        std::string move_name_;

        /**
         * Draws a portion of the rotation- helper function for RunRotation
         * @param cubie the cubie the rotation is being applied to
         */
        void RotateSide(Cubie& cubie);
    };
}
#endif //RUBIKS_CUBE_TURN_ANIMATION_H
