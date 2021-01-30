//
// Created by Akaash Kolachina on 12/1/20.
//
#include <catch2/catch.hpp>
#include <visualizer/rubiks_cube.h>
#include <visualizer/turn_animation.h>
#include <core/move_manager.h>
#include <string>

using rubiks_cube::TurnAnimation;
using rubiks_cube::RubiksCube;
using rubiks_cube::MoveManager;

// ExecuteMove is tested implicitly in both the following test cases
TEST_CASE("ExecuteMoves properly adds turns to the cube") {
    RubiksCube cube = RubiksCube(3,10);
    MoveManager::ExecuteMoves(cube,{"r","f'","b"});
    TurnAnimation first_animation = cube.GetTurns().front();
    TurnAnimation last_animation = cube.GetTurns().back();
    REQUIRE(cube.GetTurns().size() == 3);
    // Check first animation is correct
    REQUIRE(first_animation.GetMoveName() == "r");
    REQUIRE(first_animation.GetAxisName() == 'x');
    REQUIRE(first_animation.GetLayer() == 2);
    // Check last animation is correct
    REQUIRE(last_animation.GetMoveName() == "b");
    REQUIRE(last_animation.GetAxisName() == 'z');
    REQUIRE(last_animation.GetLayer() == 0);
}

TEST_CASE("UndoMoves properly adds turns to the cube") {
    RubiksCube cube = RubiksCube(3,10);
    MoveManager::UndoMoves(cube,{"r","f'","b","d"});
    TurnAnimation first_animation = cube.GetTurns().front();
    TurnAnimation last_animation = cube.GetTurns().back();
    REQUIRE(cube.GetTurns().size() == 4);
    // Check first animation is correct
    // The move should be a turn of the last item in the move vector except in
    // the opposite direction
    REQUIRE(first_animation.GetMoveName() == "d'");
    REQUIRE(first_animation.GetAxisName() == 'y');
    REQUIRE(first_animation.GetLayer() == 0);
    // Check last animation is correct
    REQUIRE(last_animation.GetMoveName() == "r'");
    REQUIRE(last_animation.GetAxisName() == 'x');
    REQUIRE(last_animation.GetLayer() == 2);
}

TEST_CASE("MakeMoveSymbols works as intended") {
    SECTION("MakeMoveSymbols properly makes a counter clockwise move") {
        REQUIRE(MoveManager::MakeMoveSymbol("l", false) == "l'");
    }
    SECTION("MakeMoveSymbols properly makes a clockwise move") {
        REQUIRE(MoveManager::MakeMoveSymbol("b", true) == "b");
    }
}
