//
// Created by Akaash Kolachina on 12/7/20.
//
#ifndef RUBIKS_CUBE_PATTERNS_H
#define RUBIKS_CUBE_PATTERNS_H
#include "string"
#include "vector"
namespace rubiks_cube {

    /**
     * Class for storing vectors of moves representing patterns
     */
    class Patterns {
    public:
        Patterns() = default;

        /**
         * Returns the moves for the checkerboard pattern
         * @return vector of strings representing moves to execute the
         * checkerboard pattern
         */
        const std::vector<std::string>& GetCheckerBoard();

        /**
         * Returns the moves for the superflip pattern
         * @return vector of strings representing moves to execute the
         * superflip pattern
         */
        const std::vector<std::string>& GetSuperFlip();

        /**
         * Returns the moves for the cube in a cube in a cube pattern
         * @return vector of strings representing moves to execute the
         * cube in a cube in a cube pattern
         */
        const std::vector<std::string>& GetCubeInCubeInCube();

        /**
         * Returns the moves for the yin-yang pattern
         * @return vector of strings representing moves to execute the
         * yin-yang pattern
         */
        const std::vector<std::string>& GetYinYang();

        /**
         * Returns the moves for the twisted peaks pattern
         * @return vector of strings representing moves to execute the
         * twisted peaks pattern
         */
        const std::vector<std::string>& GetTwistedPeaks();

        /**
         * Returns the moves for the kilt pattern
         * @return vector of strings representing moves to execute the
         * kilt pattern
         */
        const std::vector<std::string>& GetKilt();

        /**
         * Returns the moves for the cross pattern
         * @return vector of strings representing moves to execute the
         * cross pattern
         */
        const std::vector<std::string>& GetCross();
    private:
        std::vector<std::string> checkerboard_ = {"u", "u", "d", "d",
                                                  "l", "l", "r","r", "f",
                                                  "f", "b", "b"};

        std::vector<std::string> superflip_ = {"u","r","r","f","b","r","b","b",
                                               "r","u","u","l","b","b","r","u'",
                                               "d'","r","r","f","r'","l","b","b",
                                               "u","u","f","f"};

        std::vector<std::string> cube_in_a_cube_in_a_cube_ = {"u'","l'","u'",
                                                              "f'","r","r",
                                                              "b'","r","f",
                                                              "u","b","b","u",
                                                              "b'","l","u'","f",
                                                              "u","r","f'"};

        std::vector<std::string> yinyang_ = {"r","l","b","f","r","l","u'","d'",
                                             "f'","b'","u","d"};

        std::vector<std::string> twisted_peaks_ = {"f","b'","u","f","u","f","u",
                                                   "l","b","l","l","b'","u",
                                                   "f'","l","u","l'","b"};

        std::vector<std::string> kilt_ = {"u'","r","r","l","l","f","f","b","b",
                                         "u'","r","l","f","b'","u","f","f","d",
                                         "d","r","r","l","l","f","f","u","u","f",
                                         "f","u'","f","f"};

        std::vector<std::string> cross_ = {"r","r","l'","d","f","f","r'","d'",
                                           "r'","l","u'","d","r","d","b","b","r'",
                                           "u","d","d"};
    };
}
#endif //RUBIKS_CUBE_PATTERNS_H
