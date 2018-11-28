#pragma once
#include <boost/python/module.hpp>
#include "PythonFunctions.h"

using namespace boost::python;
/*
// methods that can be called from Python
static PyMethodDef connect4_methods[] = {
    // The first property is the name exposed to Python, fast_tanh, the second is the C++
    // function name that contains the implementation.
    { "playPiece", (PyCFunction)playPiece, METH_O, nullptr },
    { "printBoard", (PyCFunction)printBoard, METH_NOARGS, nullptr },
    { "getEmptyBoard", (PyCFunction)getEmptyBoard, METH_NOARGS, nullptr },

    // Terminate the array with an object containing nulls.
    { nullptr, nullptr, 0, nullptr }
};

// defines the module
static PyModuleDef connect4_module = {
    PyModuleDef_HEAD_INIT,
    "connect4",                                                     // Module name to use with Python import statements
    "Provides functionality for running the game of Connect 4",     // Module description
    0,
    connect4_methods                                                    // Structure that defines the methods of the module
};

// method that Python calls when it loads the module. must be named
// PyInit_<module-name>
PyMODINIT_FUNC PyInit_connect4() {
    return PyModule_Create(&connect4_module);
}*/

/* Define your module name within BOOST_PYTHON_MODULE */
BOOST_PYTHON_MODULE(connect4) {
    /* Initialise libraries */
    Py_Initialize();
    np::initialize();
    
    /* Define functions */
    def("playPiece", &playPiece);
    def("getResult", &getResult);
    def("getTurn", &getTurn);
    def("printBoard", &printBoard);
    def("CSIZE", &cSize);
    def("RSIZE", &rSize);
    def("action_size", &actionSize);
    def("getEmptyBoard", &getEmptyBoard);
    def("getPlayerOneBoard", &getPlayerOneBoard);
    def("getPlayerTwoBoard", &getPlayerTwoBoard);
    def("getLegalMoves", &getLegalMoves);
    def("reset", &reset);
}