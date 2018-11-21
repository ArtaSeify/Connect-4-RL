#pragma once
//#include <boost/python/detail/wrap_python.hpp>
//#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <iostream>
#include "Constants.h"
#include "Board.h"




//namespace p = boost::python;
//namespace np = boost::python::numpy;
using namespace Connect4;

// Python callable function of playPiece
PyObject* playPiece(PyObject *, PyObject* o)
{
    return PyBool_FromLong(Board::Instance()->playPiece(PyLong_AsLong(o)));
}

PyObject* printBoard(PyObject *, PyObject* o)
{
    Board::Instance()->printBoard(true);
    return Py_None;
}

/*np::ndarray getEmptyBoard(PyObject *, PyObject* o)
{
    np::ndarray py_array = np::from_data(Board::Instance()->getEmptyBoard().data(), 
                                        np::dtype::get_builtin<bool>(),
                                        p::make_tuple((CSIZE, RSIZE)),
                                        p::make_tuple(sizeof(bool)),
                                        p::object());
    for (int row = 0; row < RSIZE; ++row)
    {
        for (int column = 0; column < CSIZE; ++column)
        {
            std::cout << p::extract<char const *>(p::str(py_array)) << std::endl;
        }
    }
    return py_array;
}*/