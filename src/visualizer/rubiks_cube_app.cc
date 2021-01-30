#include <visualizer/rubiks_cube_app.h>

using std::string;
using std::vector;
using glm::vec2;
namespace rubiks_cube {
    RubiksCubeApp::RubiksCubeApp() {
        ci::app::setWindowSize(kWindowSize, kWindowSize);
        // This is an arbitrary point that the camera is initially pointed toward
        (*cam).lookAt(ci::vec3(50,50,200),
                      {280, 280,20});
        // Connects the CameraPersp object to UI events
        cam_ui = ci::CameraUi(cam, getWindow());

        // Initialize buttons
        InitializeButtons();
        // Set random seed for ScrambleCube() and random button
        srand(time(NULL));
    }

    RubiksCubeApp::~RubiksCubeApp() {
        delete cam;
    }

    void RubiksCubeApp::draw() {
        ci::Color8u background_color(112, 128, 144);  // Light gray
        ci::gl::clear(background_color);
        // Enable 2d drawing and draw buttons
        ci::gl::setMatricesWindow(getWindowSize());
        // Draw all the buttons
        checkerboard_btn_.Draw(25);
        kilt_btn_.Draw(25);
        twisted_peaks_btn_.Draw(25);
        cross_btn_.Draw(25);
        yin_yang_btn_.Draw(25);
        superflip_btn_.Draw(25);
        cube_in_cube_in_cube_btn_.Draw(15);
        scramble_btn_.Draw(25);
        solve_btn_.Draw(25);
        random_btn_.Draw(25);
        // Turn on buffering
        ci::gl::enableDepthRead();
        ci::gl::enableDepthWrite();
        // Set matrices to align with CameraPersp Object
        ci::gl::setMatrices(*cam);
        rubiks_cube_.Draw();

        // Turn off buffering to allow for 2d drawing
        ci::gl::disableDepthRead();
        ci::gl::disableDepthWrite();
    }

    void RubiksCubeApp::update() {
        MoveManager::UpdateMoves(rubiks_cube_);
    }

    void RubiksCubeApp::keyDown(ci::app::KeyEvent event) {
        bool is_clockwise = true;
        if (last_key == ci::app::KeyEvent::KEY_SPACE) {
            // If the user hit space before the key, the move will be counter
            // clockwise
            is_clockwise = false;
        }

        if (event.getCode() == ci::app::KeyEvent::KEY_l) {
            string move = MoveManager::MakeMoveSymbol("l", is_clockwise);
            MoveManager::ExecuteMove(rubiks_cube_, move);
            // Add move to vector of moves made
            moves_made.push_back(move);
        } else if (event.getCode() == ci::app::KeyEvent::KEY_r) {
            string move = MoveManager::MakeMoveSymbol("r", is_clockwise);
            MoveManager::ExecuteMove(rubiks_cube_, move);
            moves_made.push_back(move);
        } else if (event.getCode() == ci::app::KeyEvent::KEY_u) {
            string move = MoveManager::MakeMoveSymbol("u", is_clockwise);
            MoveManager::ExecuteMove(rubiks_cube_, move);
            moves_made.push_back(move);
        } else if (event.getCode() == ci::app::KeyEvent::KEY_d) {
            string move = MoveManager::MakeMoveSymbol("d", is_clockwise);
            MoveManager::ExecuteMove(rubiks_cube_, move);
            moves_made.push_back(move);
        } else if (event.getCode() == ci::app::KeyEvent::KEY_f) {
            string move = MoveManager::MakeMoveSymbol("f", is_clockwise);
            MoveManager::ExecuteMove(rubiks_cube_, move);
            moves_made.push_back(move);
        } else if (event.getCode() == ci::app::KeyEvent::KEY_b) {
            string move = MoveManager::MakeMoveSymbol("b", is_clockwise);
            MoveManager::ExecuteMove(rubiks_cube_, move);
            moves_made.push_back(move);
        } else if (event.getCode() == ci::app::KeyEvent::KEY_ESCAPE) {
            // Escape should disable cam_ui to allow for button clicks
            cam_ui.disable();
        }
        // Update last key
        last_key = event.getCode();
    }

    void RubiksCubeApp::mouseDrag(ci::app::MouseEvent event) {
        cam_ui.mouseDrag(event);
    }

    void RubiksCubeApp::mouseDown(ci::app::MouseEvent event) {
        vector<PatternButton> pattern_btns = {cube_in_cube_in_cube_btn_, cross_btn_,
                                              checkerboard_btn_, superflip_btn_,
                                              yin_yang_btn_,twisted_peaks_btn_,
                                              kilt_btn_};
        for (const PatternButton& button : pattern_btns) {
            if (button.IsClicked(event.getPos())) {
                // If the button is clicked first undo any existing moves on
                // the cube, then execute the pattern, then record the moves that
                // were executed
                SolveCube();
                button.OnClick(rubiks_cube_);
                AddMoves(button.GetMoves());
            }
        }

        if (solve_btn_.IsClicked(event.getPos())) {
            SolveCube();
        } else if (scramble_btn_.IsClicked(event.getPos())) {
            ScrambleCube();
        } else if (random_btn_.IsClicked(event.getPos())) {
            size_t random_idx = rand() % pattern_btns.size();
            SolveCube();
            pattern_btns[random_idx].OnClick(rubiks_cube_);
            AddMoves(pattern_btns[random_idx].GetMoves());
        }
        // Cam_ui must be enabled again to allow for rotating the cube
        cam_ui.enable();
    }

    void RubiksCubeApp::SolveCube() {
        // Undo the moves made by the player and empty the vector
        MoveManager::UndoMoves(rubiks_cube_, moves_made);
        moves_made.clear();
    }

    void RubiksCubeApp::ScrambleCube() {
        vector<string> all_moves = {"l","l'","r","r'","f","f'","b","b'",
                                    "u","u'","d","d'"};
        size_t min_num_of_moves = 5;
        size_t max_num_of_moves = 25;
        // Add a minimum number of moves so that the loop runs at least that
        // number of times
        size_t num_of_moves = (rand() % max_num_of_moves) + min_num_of_moves;
        for (size_t count = 0; count < num_of_moves; count++) {
            size_t rand_idx = rand() % all_moves.size();
            MoveManager::ExecuteMove(rubiks_cube_, all_moves[rand_idx]);
            moves_made.push_back(all_moves[rand_idx]);
        }
    }

    void RubiksCubeApp::AddMoves(const std::vector<std::string> &moves) {
        for (const string& move : moves) {
            moves_made.push_back(move);
        }
    }

    void RubiksCubeApp::InitializeButtons() {
        double distance_to_next_button = kWindowSize / 7;
        // Left Side Buttons
        vec2 distance_to_bottom_right = vec2(kButtonLength,kButtonWidth);
        vec2 top_left = vec2(kMargin,5 *kMargin);
        vec2 bottom_right = top_left +  distance_to_bottom_right;
        checkerboard_btn_ = PatternButton(
                pattern_library_.GetCheckerBoard(),
                top_left,bottom_right,
                ci::ColorT<float>(1,0,0),"Checker Board");

        top_left = vec2(top_left.x, bottom_right.y + distance_to_next_button);
        bottom_right = top_left + distance_to_bottom_right;
        kilt_btn_ = PatternButton(
                pattern_library_.GetKilt(),
                top_left,bottom_right,
                ci::ColorT<float>(1,.65,0),"Kilt");

        top_left = vec2(top_left.x, bottom_right.y + distance_to_next_button);
        bottom_right = top_left + distance_to_bottom_right;
        cross_btn_ = PatternButton(
                pattern_library_.GetCross(),
                top_left,bottom_right,
                ci::ColorT<float>(1,1,0),"Cross");

        top_left = vec2(top_left.x, bottom_right.y + distance_to_next_button);
        bottom_right = top_left + distance_to_bottom_right;
        twisted_peaks_btn_ = PatternButton(
                pattern_library_.GetTwistedPeaks(),
                top_left,bottom_right,
                ci::ColorT<float>(.5,.5,.5),"Twisted Peaks");

        top_left = vec2(top_left.x, bottom_right.y + distance_to_next_button);
        bottom_right = top_left + distance_to_bottom_right;
        yin_yang_btn_ = PatternButton(
                pattern_library_.GetYinYang(),
                top_left,bottom_right,
                ci::ColorT<float>(1,1,1),"Yin Yang");

        // Right side buttons
        top_left = vec2(kWindowSize - (kMargin + kButtonLength),5 *kMargin);
        bottom_right = top_left + distance_to_bottom_right;
        superflip_btn_ = PatternButton(
                pattern_library_.GetSuperFlip(),
                top_left,bottom_right,
                ci::ColorT<float>(.5,0,1),"Super Flip");

        top_left = vec2(top_left.x, bottom_right.y + distance_to_next_button);
        bottom_right = top_left + distance_to_bottom_right;
        cube_in_cube_in_cube_btn_ = PatternButton(
                pattern_library_.GetCubeInCubeInCube(),
                top_left,bottom_right,
                ci::ColorT<float>(0,0,1),
                        "  Cube In a Cube In a Cube");

        top_left = vec2(top_left.x, bottom_right.y + distance_to_next_button);
        bottom_right = top_left + distance_to_bottom_right;
        scramble_btn_ = Button(top_left,bottom_right,ci::ColorT<float>(0,1,1),
                "Scramble");

        top_left = vec2(top_left.x, bottom_right.y + distance_to_next_button);
        bottom_right = top_left + distance_to_bottom_right;
        solve_btn_ = Button(top_left,bottom_right,ci::ColorT<float>(0,1,0),
                               "Solve");

        top_left = vec2(top_left.x, bottom_right.y + distance_to_next_button);
        bottom_right = top_left + distance_to_bottom_right;
        random_btn_ = Button(top_left,bottom_right,ci::ColorT<float>(1,.5,.75),
                               "Surprise Me!");
    }
}
