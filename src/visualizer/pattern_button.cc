//
// Created by Akaash Kolachina on 12/6/20.
//
#include "visualizer/pattern_button.h"

using std::vector;
using std::string;
namespace rubiks_cube {
    PatternButton::PatternButton(const std::vector<std::string> &moves,
                                              const glm::vec2 &top_left_bound,
                                              const glm::vec2 &bottom_right_bound,
                                              const ci::ColorT<float> &color,
                                              const std::string &label):
                                              Button(top_left_bound,
                                                     bottom_right_bound,
                                                     color,label),moves_(moves){

    }

    void PatternButton::OnClick(RubiksCube& rubiks_cube) const {
        MoveManager::ExecuteMoves(rubiks_cube, moves_);
    }

    const vector<string> &PatternButton::GetMoves() const {
        return moves_;
    }
}






