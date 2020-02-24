#pragma once
#include <boost/python/detail/wrap_python.hpp>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <iostream>
#include "Constants.h"
#include "Board.h"

namespace p = boost::python;
namespace np = boost::python::numpy;
using namespace Connect4;

bool playPiece(PyObject* o)
{
    return Board::Instance()->playPiece(PyLong_AsLong(o));
}

int getResult()
{
    return int(Board::Instance()->getState());
}

bool getTurn()
{
    return Board::Instance()->getTurn();
}

void printBoard()
{
    Board::Instance()->printBoard(true);
}

int cSize()
{
    return CSIZE;
}

int rSize()
{
    return RSIZE;
}

int actionSize()
{
    return ACTIONSIZE;
}

np::ndarray getEmptyBoard()
{
    return np::from_data(&Board::Instance()->getEmptyBoard(), 
                            np::dtype::get_builtin<bool>(),
                            p::make_tuple(CSIZE, RSIZE),
                            p::make_tuple(sizeof(bool) * RSIZE, sizeof(bool)),
                            p::object());
}

np::ndarray getPlayerOneBoard()
{
    return np::from_data(&Board::Instance()->getPlayerOneBoard(),
                            np::dtype::get_builtin<bool>(),
                            p::make_tuple(CSIZE, RSIZE),
                            p::make_tuple(sizeof(bool) * RSIZE, sizeof(bool)),
                            p::object());
}

np::ndarray getPlayerTwoBoard()
{
    return np::from_data(&Board::Instance()->getPlayerTwoBoard(),
                            np::dtype::get_builtin<bool>(),
                            p::make_tuple(CSIZE, RSIZE),
                            p::make_tuple(sizeof(bool) * RSIZE, sizeof(bool)),
                            p::object());
}

np::ndarray getLegalMoves()
{
    return np::from_data(&Board::Instance()->getLegalMoves(),
                            np::dtype::get_builtin<bool>(),
                            p::make_tuple(CSIZE),
                            p::make_tuple(sizeof(bool)),
                            p::object());
}

void reset()
{
    Board::Instance()->reset();
}