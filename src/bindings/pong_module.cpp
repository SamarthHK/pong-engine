//
// Created by munna-01 on 10/22/26.
//
#include <pybind11/pybind11.h>
#include "game.h"

namespace py = pybind11;

PYBIND11_MODULE(pong_module, m) {
    py::enum_<pong::Move>(m, "Move")
        .value("UP", pong::Move::UP)
        .value("NONE", pong::Move::NONE)
        .value("DOWN", pong::Move::DOWN)
        .export_values();

    py::class_<pong::StepResult>(m, "StepResult")
        .def_readonly("ball_x", &pong::StepResult::ball_x)
        .def_readonly("ball_y", &pong::StepResult::ball_y)
        .def_readonly("player_one_x", &pong::StepResult::player_one_x)
        .def_readonly("player_one_y", &pong::StepResult::player_one_y)
        .def_readonly("player_two_x", &pong::StepResult::player_two_x)
        .def_readonly("player_two_y", &pong::StepResult::player_two_y)
        .def_readonly("winner", &pong::StepResult::winner)
        .def_readonly("game_over", &pong::StepResult::game_over);

    py::class_<pong::Game>(m, "Game")
        .def(py::init<int, int, int, int, int, int, float, float, float, float>(),
             py::arg("ball_radius") = 10,
             py::arg("player_width") = 10,
             py::arg("player_height") = 100,
             py::arg("field_width") = 640,
             py::arg("field_height") = 480,
             py::arg("player_offset") = 80,
             py::arg("player_accel") = 2000.0f,
             py::arg("player_top_speed") = 500.0f,
             py::arg("ball_accel") = 1.05f,
             py::arg("ball_vel") = 170.0f)
        .def("step", &pong::Game::step,
             py::arg("player_one_move"),
             py::arg("player_two_move"),
             py::arg("delta_time"));
}
