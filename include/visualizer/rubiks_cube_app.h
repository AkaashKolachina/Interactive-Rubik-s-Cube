#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/CameraUi.h"
#include "cinder/gl/gl.h"
#include "visualizer/cubie.h"
#include "visualizer/rubiks_cube.h"
#include "core/rotations.h"
#include "core/move_manager.h"
#include "core/patterns.h"
#include "visualizer/button.h"
#include "visualizer/pattern_button.h"
#include <string>
#include <fstream>

namespace rubiks_cube {

/**
 * The App displaying an interactive Rubik's Cube
 */
class RubiksCubeApp : public ci::app::App {
 public:
  /**
   * Creates an app for displaying an interactive Rubik's Cube
   */
  RubiksCubeApp();

  /**
   * Deletes all member variables stored in the heap
   */
  ~RubiksCubeApp();


  /**
   * Draws the interactive Rubik's Cube
   */
  void draw() override;

  /**
   * Updates the member variables of the app
   */
  void update() override;

  /**
   * Turns the cube depending on the key pressed by the user.
   * l turns the cube's left layer, r turns the right layer, u turns the top(up)
   * layer, d turns the bottom layer(down), b turns the back layer, and f turns
   * the front layer. All these turns are clockwise unless spacebar was hit before
   * the turn
   * @param event the keypress event
   */
  void keyDown(ci::app::KeyEvent event) override;

  /**
   * Moves the cube when the mouse is dragged
   * @param event the mouse event
   */
  void mouseDrag(ci::app::MouseEvent event) override;

  void mouseDown(ci::app::MouseEvent event) override;



  const double kWindowSize = 875;
  const double kMargin = 10;
  const double kButtonLength = 180;
  const double kButtonWidth = 40;

 private:
    RubiksCube rubiks_cube_ = RubiksCube(3,29);
    ci::CameraUi cam_ui;
    ci::CameraPersp* cam = new ci::CameraPersp();
    // The library housing all the patterns used in the app
    Patterns pattern_library_ = Patterns();
    PatternButton checkerboard_btn_;
    PatternButton cross_btn_;
    PatternButton yin_yang_btn_;
    PatternButton superflip_btn_;
    PatternButton cube_in_cube_in_cube_btn_;
    PatternButton kilt_btn_;
    PatternButton twisted_peaks_btn_;
    Button solve_btn_;
    Button scramble_btn_;
    // A button for executing a random pattern
    Button random_btn_;

    // The last key pressed, this is used to determine whether or not the space
    // bar was hit before the current key press
    int last_key = 0;
    // A record of all the moves made since the cube's last "solve"
    std::vector<std::string> moves_made;

    /**
     * Reverses all the moves made to give the cube the impression of being
     * solved
     */
    void SolveCube();

    /**
     * Scrambles the cube
     */
    void ScrambleCube();

    /**
     * Adds a vector of moves to the moves_made_
     * @param moves the vector of moves being added
     */
    void AddMoves(const std::vector<std::string>& moves);

    /**
     * Initializes all the buttons used in the app
     */
    void InitializeButtons();
};

}
