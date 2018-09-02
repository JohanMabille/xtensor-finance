// FORCE_IMPORT_ARRAY must be defined before including
// any header from xtensor-python. Other files that
// do not include any header from numpy can be included
// before.
#define FORCE_IMPORT_ARRAY
#include "xtensor-python/pyarray.hpp"
#include "xtensor-python/pyvectorize.hpp"

#include "closed_forms.hpp"

namespace py = pybind11;

PYBIND11_MODULE(xtensor_closed_forms, m)
{
    // Required at the beginning of the module definition
    xt::import_numpy();

    m.doc() = "Closed-forms for pricing vanilla options";

    // - xt::pyvectorize turns its scalar function into a vectorial function,
    // thus we can now call b_discounted_price with numpy arrays!
    // - py::arg enable passing parameter by name from the Python
    m.def("bs_discounted_price", xt::pyvectorize(cf::bs_discounted_price<double>),
          "computes the discounted blackscholes price of an option",
          py::arg("spot"), py::arg("strike"), py::arg("volatility"),
          py::arg("maturity"), py::arg("rate"), py::arg("is_call"));

    m.def("vanilla_discounted_payoff", xt::pyvectorize(cf::vanilla_discounted_payoff<double>),
          py::arg("spot"), py::arg("strike"), py::arg("maturity"), py::arg("rate"),
          py::arg("is_call"));

    m.def("bs_price", xt::pyvectorize(cf::bs_price<double>),
          "computes the blackscholes price of an option",
          py::arg("fwd"), py::arg("strike"), py::arg("volatility"),
          py::arg("maturity"), py::arg("is_call"));

    m.def("bs_time_value", xt::pyvectorize(cf::bs_time_value<double>),
          "computes the blackscholes time value of an option",
          py::arg("fwd"), py::arg("strike"), py::arg("volatility"),
          py::arg("maturity"));

    m.def("ncdf", xt::pyvectorize(cf::ncdf<double>),
          "cumulative distribution function for the normal distribution",
          py::arg("x"));
}

