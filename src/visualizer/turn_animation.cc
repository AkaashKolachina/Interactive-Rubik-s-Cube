//
// Created by Akaash Kolachina on 11/25/20.
//
#include "visualizer/turn_animation.h"
using glm::vec3;
using std::string;
namespace rubiks_cube {

    TurnAnimation::TurnAnimation(const vec3 &rotation_axis,
                                 const vec3 &cube_center, bool is_clockwise,
                                 size_t layer, const string& move_name) {
        rotation_axis_ = rotation_axis;
        face_center_ = cube_center;
        is_clockwise_ = is_clockwise;
        layer_ = layer;
        move_name_ = move_name;
        // The axis name is the coord in the rotation axis that has a value
        // of 1
        if (rotation_axis.x == 1) {
            axis_name_ = 'x';
        } else if (rotation_axis_.y == 1) {
            axis_name_ = 'y';
        } else if (rotation_axis_.z == 1) {
            axis_name_ = 'z';
        }
    }

    void TurnAnimation::RunRotation(Cubie &cubie) {
        // Set is_finished to true slightly before the animation is actually,
        // finished to make the animation line up better to the actual data
        // rotation
        if ((angle_slice_ * (increment_ + 2)) >= M_PI_2) {
            is_finished_ = true;
        }
        RotateSide(cubie);
    }

    bool TurnAnimation::IsFinished() const {
        return is_finished_;
    }

    char TurnAnimation::GetAxisName() const {
        return axis_name_;
    }

    size_t TurnAnimation::GetLayer() const {
        return layer_;
    }

    const std::string & TurnAnimation::GetMoveName() const {
        return move_name_;
    }

    void TurnAnimation::RotateSide(Cubie &cubie) {
        ci::gl::pushModelMatrix();
        ci::gl::translate(face_center_);
        float angle = angle_slice_ * increment_;
        // If the animation is in a counter clockwise direction,
        // negate the angle
        if (!is_clockwise_) {
            angle *= -1;
        }
        ci::gl::rotate(angle, rotation_axis_);
        cubie.Draw(cubie.GetPosition() - face_center_);
        ci::gl::popModelMatrix();
        increment_ ++;
    }
}
