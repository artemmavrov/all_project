#include <pybind11/pybind11.h>
#include "hashing_mod.h"  // твой C++ класс

namespace py = pybind11;

PYBIND11_MODULE(lr_module, m) {
    py::class_<LogisticRegression>(m, "LogisticRegression")
        .def(py::init<>())
        .def("fit", &LogisticRegression::fit)
        .def("predict", &LogisticRegression::predict);
}
