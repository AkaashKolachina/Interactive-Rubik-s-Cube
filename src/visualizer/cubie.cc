//
// Created by Akaash Kolachina on 11/15/20.
//
#include <visualizer/cubie.h>
using ci::vec3;
using std::vector;
namespace rubiks_cube {
    Cubie::Cubie(double size, const vec3& position,
                 double offset) {
        size_ = size;
        position_ = position;
        colors_ = { ci::ColorT<float>(1,0,0),
                    ci::ColorT<float>(1,.65,0),
                    ci::ColorT<float>(0,0,1),
                    ci::ColorT<float>(0,1,0),
                    ci::ColorT<float>(1,1,0),
                    ci::ColorT<float>(1,1,1)};
        offset_ = offset;
    }

    void Cubie::Draw(const glm::vec3& positions) {
        float x = positions.x;
        float y = positions.y;
        float z = positions.z;
        // The black cube is slightly larger so that when the faces are drawn
        // a black outline is visible on each cubie
        ci::gl::color(ci::Color("black"));
        ci::gl::drawCube({x,y,z}, {size_ + offset_,size_ + offset_,
                                   size_ + offset_});
        // The faces are drawn by drawing six cubes and moving each one slightly
        // by an offset to give the illusion of it being one cube with a little
        // bit sticking out of each face
        ci::gl::color(colors_[0]); // Front side
        ci::gl::drawCube({x,y,z + offset_}, {size_ - offset_,
                                             size_ - offset_, size_});

        ci::gl::color(colors_[1]); // Back side
        ci::gl::drawCube({x,y,z - offset_}, {size_ - offset_,
                                             size_ - offset_,size_});

        ci::gl::color(colors_[2]); // Top side
        ci::gl::drawCube({x,y + offset_,z}, {size_ - offset_,
                                             size_,size_ - offset_});

        ci::gl::color(colors_[3]); // Bottom side
        ci::gl::drawCube({x,y - offset_,z}, {size_ - offset_,
                                             size_,size_ - offset_});

        ci::gl::color(colors_[4]); // Right side
        ci::gl::drawCube({x + offset_,y,z}, {size_,size_ - offset_
                                             ,size_ - offset_});

        ci::gl::color(colors_[5]); // Left side
        ci::gl::drawCube({x - offset_,y,z}, {size_,
                                             size_ - offset_,size_ - offset_});
    }


    const ci::vec3& Cubie::GetPosition() const {
        return position_;
    }

    const std::vector<ci::ColorT<float>> & Cubie::GetColors() const {
        return colors_;
    }

    void Cubie::SetColors(std::vector<ci::ColorT<float>> colors) {
        colors_ = colors;
    }

    void Cubie::SetPosition(const ci::vec3 &new_position) {
        position_ = new_position;
    }
}
