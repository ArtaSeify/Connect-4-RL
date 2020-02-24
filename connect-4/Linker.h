#pragma once
#include <boost/python/module.hpp>
#include "PythonFunctions.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(connect4) {
    //Initialise libraries
    Py_Initialize();
    np::initialize();
    
    // Define functions
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