#include <catch2/catch.hpp>
#include <visualizer/rubiks_cube.h>
#include <core/rotations.h>
#include <string>

using rubiks_cube::RubiksCube;
using rubiks_cube::Rotations;
using rubiks_cube::Cubie;
// TurnSide implicitly tests all the other turn functions
TEST_CASE("Left Turns") {
    RubiksCube cube = RubiksCube(3,10);
    SECTION("l turns the left side clockwise") {
        Rotations::TurnSide("l",cube);
        // Arbitrary cubie on the left side should be rotated properly
        Cubie arb_cubie = cube.GetCubeData()[0][2][2];
        // To avoid being repetitive, I'm only making sure a few sides are
        // correct, but I vary which sides I test to remain exhaustive
        // This cubies front color should be blue
        REQUIRE(arb_cubie.GetColors()[0] == ci::ColorT<float>(0,0,1));
        // The cubies left color should still be white
        REQUIRE(arb_cubie.GetColors()[5] == ci::ColorT<float>(1,1,1));
    }

    SECTION("l' turns the left side counter clockwise") {
        Rotations::TurnSide("l'",cube);
        // Arbitrary cubie on the left side should be rotated properly
        Cubie arb_cubie = cube.GetCubeData()[0][0][0];

        // This cubies front color should be green
        REQUIRE(arb_cubie.GetColors()[0] == ci::ColorT<float>(0,1,0));
        // The cubies top color should be red
        REQUIRE(arb_cubie.GetColors()[2] == ci::ColorT<float>(1,0,0));
    }

}

TEST_CASE("Right Turns") {
    RubiksCube cube = RubiksCube(3,10);
    SECTION("r turns the right side clockwise") {
        Rotations::TurnSide("r",cube);
        Cubie arb_cubie = cube.GetCubeData()[2][2][2];

        // This cubies front color should be green
        REQUIRE(arb_cubie.GetColors()[0] == ci::ColorT<float>(0,1,0));
        // The cubies right color should still be yellow
        REQUIRE(arb_cubie.GetColors()[4] == ci::ColorT<float>(1,1,0));
    }

    SECTION("r' turns the right side counter clockwise") {
        Rotations::TurnSide("r'",cube);
        Cubie arb_cubie = cube.GetCubeData()[2][0][0];

        // This cubies front color should be blue
        REQUIRE(arb_cubie.GetColors()[0] == ci::ColorT<float>(0,0,1));
        // The cubies top color should be orange
        REQUIRE(arb_cubie.GetColors()[2] == ci::ColorT<float>(1,.65,0));
    }
}

TEST_CASE("Top Turns") {
    RubiksCube cube = RubiksCube(3,10);
    SECTION("u turns the top side clockwise") {
        Rotations::TurnSide("u",cube);
        Cubie arb_cubie = cube.GetCubeData()[2][2][2];

        // This cubies front color should be yellow
        REQUIRE(arb_cubie.GetColors()[0] == ci::ColorT<float>(1,1,0));
        // The cubies top color should still be blue
        REQUIRE(arb_cubie.GetColors()[2] == ci::ColorT<float>(0,0,1));
    }

    SECTION("u' turns the top side counter clockwise") {
        Rotations::TurnSide("u'",cube);
        Cubie arb_cubie = cube.GetCubeData()[2][2][0];

        // This cubies front color should be white
        REQUIRE(arb_cubie.GetColors()[0] == ci::ColorT<float>(1,1,1));
        // The cubies back color should be yellow
        REQUIRE(arb_cubie.GetColors()[1] == ci::ColorT<float>(1,1,0));
    }
}

TEST_CASE("Bottom Turns") {
    RubiksCube cube = RubiksCube(3,10);
    SECTION("d turns the bottom side clockwise") {
        Rotations::TurnSide("d",cube);
        Cubie arb_cubie = cube.GetCubeData()[2][0][2];

        // This cubies front color should be white
        REQUIRE(arb_cubie.GetColors()[0] == ci::ColorT<float>(1,1,1));
        // The cubies bottom color should still be green
        REQUIRE(arb_cubie.GetColors()[3] == ci::ColorT<float>(0,1,0));
    }

    SECTION("d' turns the bottom side counter clockwise") {
        Rotations::TurnSide("d'",cube);
        Cubie arb_cubie = cube.GetCubeData()[2][0][0];

        // This cubies front color should be yellow
        REQUIRE(arb_cubie.GetColors()[0] == ci::ColorT<float>(1,1,0));
        // The cubies right color should be orange
        REQUIRE(arb_cubie.GetColors()[4] == ci::ColorT<float>(1,.65,0));
    }
}

TEST_CASE("Front Turns") {
    RubiksCube cube = RubiksCube(3,10);
    SECTION("f turns the front side clockwise") {
        Rotations::TurnSide("f",cube);
        Cubie arb_cubie = cube.GetCubeData()[2][2][2];

        // This cubies left color should be green
        REQUIRE(arb_cubie.GetColors()[5] == ci::ColorT<float>(0,1,0));
        // The cubies front color should still be red
        REQUIRE(arb_cubie.GetColors()[0] == ci::ColorT<float>(1,0,0));
    }

    SECTION("f' turns the front side counter clockwise") {
        Rotations::TurnSide("f'",cube);
        Cubie arb_cubie = cube.GetCubeData()[2][0][2];

        // This cubies top color should be yellow
        REQUIRE(arb_cubie.GetColors()[2] == ci::ColorT<float>(1,1,0));
        // The cubies left color should be blue
        REQUIRE(arb_cubie.GetColors()[5] == ci::ColorT<float>(0,0,1));
    }
}

TEST_CASE("Back Turns") {
    RubiksCube cube = RubiksCube(3,10);
    SECTION("b turns the back side clockwise") {
        Rotations::TurnSide("b",cube);
        Cubie arb_cubie = cube.GetCubeData()[2][2][0];

        // This cubies left color should be blue
        REQUIRE(arb_cubie.GetColors()[5] == ci::ColorT<float>(0,0,1));
        // The cubies back color should still be orange
        REQUIRE(arb_cubie.GetColors()[1] == ci::ColorT<float>(1,.65,0));
    }

    SECTION("b' turns the back side counter clockwise") {
        Rotations::TurnSide("b'",cube);
        Cubie arb_cubie = cube.GetCubeData()[2][0][0];

        // This cubies front color should be red
        REQUIRE(arb_cubie.GetColors()[0] == ci::ColorT<float>(1,0,0));
        // The cubies left color should be green
        REQUIRE(arb_cubie.GetColors()[5] == ci::ColorT<float>(0,1,0));
    }
}

TEST_CASE("Rotations work after prior rotations(s)") {
    RubiksCube cube = RubiksCube(3,10);
    Rotations::TurnSide("r",cube);
    Rotations::TurnSide("f'",cube);
    Rotations::TurnSide("l",cube);

    SECTION("Check random cubie has correct colors") {
        Cubie cubie = cube.GetCubeData()[0][0][2];
        // Front color should be yellow
        REQUIRE(cubie.GetColors()[0] == ci::ColorT<float>(1,1,0));
        // Bottom color should be green
        REQUIRE(cubie.GetColors()[3] == ci::ColorT<float>(0,1,0));
    }

    SECTION("Check that another random cubie has correct colors") {
        Cubie cubie = cube.GetCubeData()[2][2][1];
        // Top color should be red
        REQUIRE(cubie.GetColors()[2] == ci::ColorT<float>(1,0,0));
        // Right color should be yellow
        REQUIRE(cubie.GetColors()[4] == ci::ColorT<float>(1,1,0));
    }
}


