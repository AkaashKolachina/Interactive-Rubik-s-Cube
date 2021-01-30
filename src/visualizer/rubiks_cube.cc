//
// Created by Akaash Kolachina on 11/17/20.
//
#include <visualizer/rubiks_cube.h>
using glm::vec3;
using std::vector;
namespace rubiks_cube {
    RubiksCube::RubiksCube(size_t dim, float size) {
        InitializeCubeSize(dim);
        dimension_ = dim;
        vec3 starting_pos = vec3(250, 250, 0);
        for (size_t x_idx = 0; x_idx < dim; x_idx++) {
            for (size_t y_idx = 0; y_idx < dim; y_idx++) {
                for (size_t z_idx = 0; z_idx < dim; z_idx++) {
                    float x = (size * x_idx) + starting_pos.x;
                    float z = (size * z_idx) + starting_pos.z;
                    float y = (size * y_idx) + starting_pos.y;
                    cube_data_[x_idx][y_idx][z_idx] = Cubie(size, {x, y, z}, 1);
                }
            }
        }
    }

    void RubiksCube::Draw() {
        size_t dim = cube_data_.size();
        for (size_t x_idx = 0; x_idx < dim; x_idx++) {
            for (size_t y_idx = 0; y_idx < dim; y_idx++) {
                for (size_t z_idx = 0; z_idx < dim; z_idx++) {
                    // If there is no turn draw the cubie normally, else use
                    // TurnAnimation to draw the cubie
                    if (turns_.empty()) {
                        cube_data_[x_idx][y_idx][z_idx].Draw(
                                cube_data_[x_idx][y_idx][z_idx].GetPosition());
                    } else {
                        if (turns_.front().GetAxisName() == 'x') {
                            if (turns_.front().GetLayer() == x_idx) {
                                DrawTurn(cube_data_[x_idx][y_idx][z_idx]);
                                continue;
                            }

                        } else if (turns_.front().GetAxisName() == 'y') {
                            if (turns_.front().GetLayer() == y_idx) {
                                DrawTurn(cube_data_[x_idx][y_idx][z_idx]);
                                continue;
                            }
                        } else if (turns_.front().GetAxisName() == 'z') {
                            if (turns_.front().GetLayer() == z_idx) {
                                DrawTurn(cube_data_[x_idx][y_idx][z_idx]);
                                continue;
                            }
                        }
                        cube_data_[x_idx][y_idx][z_idx].Draw(
                                cube_data_[x_idx][y_idx][z_idx].GetPosition());
                    }
                }
            }
        }
    }

    void RubiksCube::Update() {
        if (!turns_.empty() && turns_.front().IsFinished()) {
            moves_.push(turns_.front().GetMoveName());
            turns_.pop();
        }
    }

    cube_vector & RubiksCube::GetCubeData() {
        return cube_data_;
    }

    size_t RubiksCube::GetDimension() const {
        return dimension_;
    }

    const std::queue<TurnAnimation>& RubiksCube::GetTurns() const {
        return turns_;
    }

    const std::queue<std::string>& RubiksCube::GetMoves() {
        return moves_;
    }

    void RubiksCube::AddTurn(const TurnAnimation &turn) {
        turns_.push(turn);
    }

    void RubiksCube::UpdateCubeData(size_t x_idx, size_t y_idx, size_t z_idx,
                                    Cubie &new_cubie) {
        cube_data_[x_idx][y_idx][z_idx] = new_cubie;
    }

    void RubiksCube::PopMove() {
        moves_.pop();
    }

    void RubiksCube::InitializeCubeSize(size_t dim) {
        cube_vector cube_data;
        for (size_t x_idx = 0; x_idx < dim; x_idx++) {
            vector<vector<Cubie>> y_data;
            for (size_t y_idx = 0; y_idx < dim; y_idx++) {
                vector<Cubie> z_data;
                for (size_t z_idx = 0; z_idx < dim; z_idx++) {
                    z_data.push_back(Cubie());
                }
                y_data.push_back(z_data);
            }
            cube_data.push_back(y_data);
        }
        cube_data_ = cube_data;
    }

    void RubiksCube::DrawTurn(Cubie &cubie) {
        // If the turn is still animating, draw the animation, otherwise
        // draw the cubie normally
        if (!turns_.front().IsFinished()) {
            turns_.front().RunRotation(cubie);
        } else {
            // Note this line of code should never be run as update will remove
            // a turn once it is finished, but it is here just in case
            cubie.Draw(cubie.GetPosition());
        }
    }
}