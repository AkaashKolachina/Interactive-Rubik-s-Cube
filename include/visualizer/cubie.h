//
// Created by Akaash Kolachina on 11/15/20.
//

#ifndef RUBIKS_CUBE_CUBIE_H
#define RUBIKS_CUBE_CUBIE_H

#include "cinder/gl/gl.h"
#include <vector>
namespace rubiks_cube {
    /**
     * Class for creating and maintaining cubies(the smaller cubes the make up
     * a Rubik's cube)
     */
    class Cubie {
    public:
        Cubie() = default;

        /**
         * Creates a cubie block
         * @param size the pixel length of each dimension
         * @param position the position of the center of the cubie
         * @param offset the width of each face
         */
        Cubie(double size, const ci::vec3& position,
              double offset);

        /**
         * Draws the cubie
         */
        void Draw(const glm::vec3& positions);

        /**
         * Returns the position vector
         * @return the position vector
         */
        const ci::vec3& GetPosition() const;

        /**
         * Returns the vector of colors of the cubie
         * @return the vector of the colors
         */
        const std::vector<ci::ColorT<float>>& GetColors() const;

        /**
         * Sets the vector of colors of the cubie
         * @param colors the vector of colors
         */
        void SetColors(std::vector<ci::ColorT<float>> colors);

        /**
         * Sets the position meber variable
         * @param new_position the new position position_ is being set to
         */
        void SetPosition(const ci::vec3& new_position);
    private:
        double size_;
        // Offset determines the width of the faces
        double offset_;
        ci::vec3 position_;
        // Indexed in this order: front,back,top,bottom,right,left
        std::vector<ci::ColorT<float>> colors_;
    };
}
#endif //RUBIKS_CUBE_CUBIE_H
