//
// Created by Akaash Kolachina on 12/6/20.
//

#ifndef RUBIKS_CUBE_PATTERN_BUTTON_H
#define RUBIKS_CUBE_PATTERN_BUTTON_H
#include "visualizer/button.h"
#include "core/move_manager.h"
#include "vector"
#include "string"
namespace rubiks_cube {

    /**
     * A class for creating Buttons that execute a pattern onto a Rubik's Cube
     * when clicked
     */
    class PatternButton: public Button {
    public:
        // Default constructor is needed for RubiksCubeApp to compile
        PatternButton() = default;

        /**
         * Constructs a PatternButton object
         * @param moves the vector of moves contained in the pattern
         * @param top_left_bound the coordinates of the top-left corner of the
         * button
         * @param bottom_right_bound the coordinates of the bottom-right corner
         * of the button
         * @param color the color of the button
         * @param label the text on the button
         */
        PatternButton(const std::vector<std::string>& moves,
                      const glm::vec2& top_left_bound,
                      const glm::vec2& bottom_right_bound,
                      const ci::ColorT<float>& color, const std::string& label);

        /**
         * Clicks the button(executes the pattern onto the cube)
         * @param rubiks_cube the cube the pattern is being executed on
         */
        void OnClick(RubiksCube& rubiks_cube) const;

        /**
         * Returns the vector of moves the button executes
         * @return the vecotr of strings representing the moves the cube does
         * when clicked
         */
        const std::vector<std::string>& GetMoves() const;
    private:
        std::vector<std::string> moves_;
    };
}
#endif //RUBIKS_CUBE_PATTERN_BUTTON_H
