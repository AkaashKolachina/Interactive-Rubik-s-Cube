//
// Created by Akaash Kolachina on 12/5/20.
//
#include <visualizer/button.h>
using glm::vec2;
using std::string;
namespace rubiks_cube {
    Button::Button(const vec2 &top_left_bound,
                   const vec2 &bottom_right_bound,
                   const ci::ColorT<float> &color, const std::string &label) {
        top_left_bound_ = top_left_bound;
        bottom_right_bound_ = bottom_right_bound;
        color_ = color;
        label_ = label;
    }

    bool Button::IsClicked(const vec2& mouse_pos) const {
        bool is_x_within_range = (top_left_bound_.x <= mouse_pos.x)
                && (bottom_right_bound_.x >= mouse_pos.x);
        bool is_y_within_range = (top_left_bound_.y <= mouse_pos.y)
                                 && (bottom_right_bound_.y>= mouse_pos.y);
        return is_x_within_range && is_y_within_range;
    }

    void Button::Draw(size_t font_size) {
        // Draw Button
        ci::gl::color(color_);
        ci::Rectf button(top_left_bound_, bottom_right_bound_);
        ci::gl::drawSolidRect(button);
        ci::gl::color(ci::Color("black"));
        // Draw black outline over the button
        ci::gl::drawStrokedRect(button,3);
        // Add label- the vector should be drawn  a little above the center of
        // the button to make it look properly centered
        vec2 offset = vec2(5,5);
        ci::gl::drawStringCentered(label_, button.getCenter() - offset,
                                   ci::Color("black"),
                                   ci::Font("arial",font_size));
    }
}
