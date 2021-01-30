//
// Created by Akaash Kolachina on 12/5/20.
//

#ifndef RUBIKS_CUBE_BUTTON_H
#define RUBIKS_CUBE_BUTTON_H
#include "cinder/gl/gl.h"
#include "string"
namespace rubiks_cube {
    /**
     * Class for button objects
     */
    class Button {
    public:
        // Default constructor is needed for RubiksCubeApp to compile
        Button() = default;

        /**
         * Constructs a Button object
         * @param top_left_bound the coordinates of the top-left corner of the
         * button
         * @param bottom_right_bound the coordinates of the bottom-right corner
         * of the button
         * @param color the color of the button
         * @param label the text on the button
         */
        Button(const glm::vec2& top_left_bound,
               const glm::vec2& bottom_right_bound,
               const ci::ColorT<float>& color, const std::string& label);

        /**
         * Determines if a button has been clicked
         * @param mouse_pos the position of the mouse click
         * @return true if the button is clicked, false otherwise
         */
        bool IsClicked(const glm::vec2& mouse_pos) const;


        /**
         * Draws the button
         * @param font_size the size of the label
         */
        void Draw(size_t font_size);
    private:
        glm::vec2 top_left_bound_;
        glm::vec2 bottom_right_bound_;
        ci::ColorT<float> color_;
        std::string label_;
    };
}
#endif //RUBIKS_CUBE_BUTTON_H
