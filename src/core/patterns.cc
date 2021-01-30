//
// Created by Akaash Kolachina on 12/7/20.
//
#include "core/patterns.h"
using std::vector;
using std::string;
namespace rubiks_cube {
    const std::vector<std::string> & Patterns::GetCheckerBoard()  {
        return checkerboard_;
    }

    const std::vector<std::string> &Patterns::GetSuperFlip() {
        return superflip_;
    }

    const std::vector<std::string> &Patterns::GetCubeInCubeInCube() {
        return cube_in_a_cube_in_a_cube_;
    }

    const std::vector<std::string> &Patterns::GetYinYang() {
        return yinyang_;
    }

    const std::vector<std::string> &Patterns::GetTwistedPeaks() {
        return twisted_peaks_;
    }

    const std::vector<std::string> &Patterns::GetKilt() {
        return kilt_;
    }

    const std::vector<std::string> &Patterns::GetCross() {
        return cross_;
    }
}
