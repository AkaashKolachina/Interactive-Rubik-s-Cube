//
// Created by Akaash Kolachina on 11/20/20.
//
#include "core/rotations.h"
using std::vector;
using glm::vec3;
namespace rubiks_cube {
    void Rotations::TurnSide(const std::string &move_name, RubiksCube &cube) {
        // Move is only valid if it is one or two characters
        if (move_name.empty() || move_name.size() > 2) {
            return;
        }

        bool is_clockwise = true;
        if (move_name.size() == 2 && move_name[1] == '\'') {
            // If the move has a ' symbol at the end, that means it is counter
            // clockwise
            is_clockwise = false;
        }

        if (tolower(move_name[0]) == 'l') {
            TurnLeftSide(cube, is_clockwise);
        } else if (tolower(move_name[0]) == 'r') {
            TurnRightSide(cube, is_clockwise);
        } else if (tolower(move_name[0]) == 'u') {
            TurnTopSide(cube, is_clockwise);
        } else if (tolower(move_name[0]) == 'd') {
            TurnBottomSide(cube, is_clockwise);
        } else if (tolower(move_name[0]) == 'f') {
            TurnFrontSide(cube, is_clockwise);
        } else if (tolower(move_name[0]) == 'b') {
            TurnBackSide(cube, is_clockwise);
        }
    }

    // Each turn consists of two parts: first the cubies of the side
    // are moved to their new spot in the cube_data vector, then each cubie is
    // rotated along either its x,y, or z axis depending on the turn
    void Rotations::TurnBottomSide(RubiksCube &cube, bool is_clockwise) {
        size_t dim = cube.GetDimension();
        // 3 clockwise turns is equivalent to a counter clockwise turn
        if (is_clockwise) {
            MoveCubiesYSide(cube, 0);
        } else {
            for (int count = 0; count < 3; count++) {
                MoveCubiesYSide(cube, 0);
            }
        }

        for (size_t x_idx = 0; x_idx < dim; x_idx++) {
            for (size_t z_idx = 0; z_idx < dim; z_idx ++) {
                // a y index of 0 corresponds to the bottom layer
                if (is_clockwise) {
                    RotateYConstant(cube.GetCubeData().at(x_idx).at(0).at(z_idx));
                } else {
                    // A counter clockwise turn is equivalent to 3 clockwise turns
                    for (size_t count = 0; count < 3; count++) {
                        RotateYConstant(cube.GetCubeData().at(x_idx).at(0).at(z_idx));
                    }
                }
            }
        }
    }

    void Rotations::TurnTopSide(RubiksCube &cube, bool is_clockwise) {
        size_t dim = cube.GetDimension();
        if (is_clockwise) {
            for (int count = 0; count < 3; count++) {
                MoveCubiesYSide(cube, dim - 1);
            }
        } else {
            MoveCubiesYSide(cube, dim - 1);
        }

        for (size_t x_idx = 0; x_idx < dim; x_idx++) {
            for (size_t z_idx = 0; z_idx < dim; z_idx ++) {
                // a y index of dim - 1 corresponds to the top layer
                if (is_clockwise) {
                    // A clockwise turn is equivalent to 3 counter clockwise turns
                    for (size_t count = 0; count < 3; count++) {
                        RotateYConstant(cube.GetCubeData().at(x_idx).at(dim - 1).at(z_idx));
                    }
                } else {
                    RotateYConstant(cube.GetCubeData().at(x_idx).at(dim - 1).at(z_idx));
                }
            }
        }
    }

    void Rotations::TurnLeftSide(RubiksCube &cube, bool is_clockwise) {
        size_t dim = cube.GetDimension();
        if (is_clockwise) {
            for (int count = 0; count < 3; count++) {
                MoveCubiesXSide(cube, 0);
            }
        } else {
            MoveCubiesXSide(cube, 0);
        }

        for (size_t y_idx = 0; y_idx < dim; y_idx++) {
            for (size_t z_idx = 0; z_idx < dim; z_idx ++) {
                if (is_clockwise) {
                    for (size_t count = 0; count < 3; count++) {
                        RotateXConstant(cube.GetCubeData().at(0).at(y_idx).at(z_idx));
                    }
                } else {
                    RotateXConstant(cube.GetCubeData().at(0).at(y_idx).at(z_idx));
                }
            }
        }
    }

    void Rotations::TurnRightSide(RubiksCube &cube, bool is_clockwise) {
        size_t dim = cube.GetDimension();
        if (is_clockwise) {
            MoveCubiesXSide(cube, dim - 1);
        } else {
            for (int count = 0; count < 3; count++) {
                MoveCubiesXSide(cube, dim - 1);
            }
        }

        for (size_t y_idx = 0; y_idx < dim; y_idx++) {
            for (size_t z_idx = 0; z_idx < dim; z_idx ++) {
                if (is_clockwise) {
                    RotateXConstant(cube.GetCubeData().at(dim - 1).at(y_idx).at(z_idx));
                } else {
                    for (size_t count = 0; count < 3; count++) {
                        RotateXConstant(cube.GetCubeData().at(dim - 1).at(y_idx).at(z_idx));
                    }
                }
            }
        }
    }

    void Rotations::TurnFrontSide(RubiksCube &cube, bool is_clockwise) {
        size_t dim = cube.GetDimension();
        if (is_clockwise) {
            MoveCubiesZSide(cube, dim- 1);
        } else {
            for (int count = 0; count < 3; count++) {
                MoveCubiesZSide(cube, dim - 1);
            }
        }

        for (size_t x_idx = 0; x_idx < dim; x_idx++) {
            for (size_t y_idx = 0; y_idx < dim; y_idx ++) {
                if (is_clockwise) {
                    RotateZConstant(cube.GetCubeData().at(x_idx).at(y_idx).at(dim - 1));
                } else {
                    for (size_t count = 0; count < 3; count++) {
                        RotateZConstant(cube.GetCubeData().at(x_idx).at(y_idx).at(dim - 1));
                    }
                }
            }
        }
    }

    void Rotations::TurnBackSide(RubiksCube &cube, bool is_clockwise) {
        size_t dim = cube.GetDimension();
        if (is_clockwise) {
            for (int count = 0; count < 3; count++) {
                MoveCubiesZSide(cube, 0);
            }
        } else {
            MoveCubiesZSide(cube, 0);
        }

        for (size_t x_idx = 0; x_idx < dim; x_idx++) {
            for (size_t y_idx = 0; y_idx < dim; y_idx ++) {
                if (is_clockwise) {
                    for (size_t count = 0; count < 3; count++) {
                        RotateZConstant(cube.GetCubeData().at(x_idx).at(y_idx).at(0));
                    }
                } else {
                    RotateZConstant(cube.GetCubeData().at(x_idx).at(y_idx).at(0));
                }
            }
        }
    }


    // The cubie's colors are rearranged to simulate a rotation
    void Rotations::RotateZConstant(Cubie &cubie) {
        vector<ci::ColorT<float>> cloned_colors = cubie.GetColors();
        vector<ci::ColorT<float>> colors_after_turn = cubie.GetColors();
        colors_after_turn[2] = cloned_colors[5];
        colors_after_turn[3] = cloned_colors[4];
        colors_after_turn[4] = cloned_colors[2];
        colors_after_turn[5] = cloned_colors[3];
        cubie.SetColors(colors_after_turn);
    }

    void Rotations::RotateXConstant(Cubie &cubie) {
        vector<ci::ColorT<float>> cloned_colors = cubie.GetColors();
        vector<ci::ColorT<float>> colors_after_turn = cubie.GetColors();
        colors_after_turn[0] = cloned_colors[3];
        colors_after_turn[1] = cloned_colors[2];
        colors_after_turn[2] = cloned_colors[0];
        colors_after_turn[3] = cloned_colors[1];
        cubie.SetColors(colors_after_turn);
    }

    void Rotations::RotateYConstant(Cubie &cubie) {
        vector<ci::ColorT<float>> cloned_colors = cubie.GetColors();
        vector<ci::ColorT<float>> colors_after_turn = cubie.GetColors();
        colors_after_turn[0] = cloned_colors[5];
        colors_after_turn[1] = cloned_colors[4];
        colors_after_turn[4] = cloned_colors[0];
        colors_after_turn[5] = cloned_colors[1];
        cubie.SetColors(colors_after_turn);
    }

    void Rotations::MoveCubiesYSide(RubiksCube& cube,
                                    size_t y_idx) {
        size_t dim = cube.GetDimension();
        vector<Cubie> face;
        // Traverse the vector in reverse row-major order, then re-insert all
        // the cubies back into cube_data in col-major order to simulate the
        // cubie's rotating
        for (int x_idx = dim - 1; x_idx >= 0; x_idx--) {
            for (int z_idx = 0; z_idx < dim; z_idx++) {
                face.push_back(cube.GetCubeData()[x_idx][y_idx][z_idx]);
            }
        }
        size_t idx = 0;
        for (size_t z_idx = 0; z_idx < dim; z_idx++) {
            for (size_t x_idx = 0; x_idx < dim; x_idx++) {
                // Update the cubie at face[idx] to have the position of the
                // cubie it's replacing
                face[idx].SetPosition(cube.GetCubeData()[x_idx][y_idx][z_idx]
                .GetPosition());
                cube.UpdateCubeData(x_idx,y_idx,z_idx,face[idx]);
                idx++;
            }
        }
    }

    void Rotations::MoveCubiesXSide(RubiksCube &cube, size_t x_idx) {
        size_t dim = cube.GetDimension();
        vector<Cubie> face;

        for (int y_idx = dim - 1; y_idx >= 0; y_idx--) {
            for (int z_idx = 0; z_idx < dim; z_idx++) {
                face.push_back(cube.GetCubeData()[x_idx][y_idx][z_idx]);
            }
        }
        size_t idx = 0;
        for (size_t z_idx = 0; z_idx < dim; z_idx++) {
            for (size_t y_idx = 0; y_idx < dim; y_idx++) {
                // Update the cubie at face[idx] to have the position of the
                // cubie it's replacing
                face[idx].SetPosition(cube.GetCubeData()[x_idx][y_idx][z_idx]
                                              .GetPosition());
                cube.UpdateCubeData(x_idx,y_idx,z_idx,face[idx]);
                idx++;
            }
        }
    }

    void Rotations::MoveCubiesZSide(RubiksCube &cube, size_t z_idx) {
        size_t dim = cube.GetDimension();
        vector<Cubie> face;

        for (int x_idx = dim - 1; x_idx >= 0; x_idx--) {
            for (int y_idx = 0; y_idx < dim; y_idx++) {
                face.push_back(cube.GetCubeData()[x_idx][y_idx][z_idx]);
            }
        }
        size_t idx = 0;
        for (size_t y_idx = 0; y_idx < dim; y_idx++) {
            for (size_t x_idx = 0; x_idx < dim; x_idx++) {
                // Update the cubie at face[idx] to have the position of the
                // cubie it's replacing
                face[idx].SetPosition(cube.GetCubeData()[x_idx][y_idx][z_idx]
                                              .GetPosition());
                cube.UpdateCubeData(x_idx,y_idx,z_idx,face[idx]);
                idx++;
            }
        }
    }
}
