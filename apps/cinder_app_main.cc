#include <visualizer/rubiks_cube_app.h>

using rubiks_cube::RubiksCubeApp;

void prepareSettings(RubiksCubeApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(RubiksCubeApp, ci::app::RendererGl, prepareSettings);
