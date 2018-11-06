#include "pybind11/pybind11.h"
#include "closed_forms.hpp"

namespace py = pybind11;

PYBIND11_MODULE(pybind_closed_forms, m)
{
    m.doc() = "Closed-forms for pricing vanilla options";

    m.def("bs_discounted_price", cf::bs_discounted_price,
          "computes the discounted blackscholes price of an option",
          py::arg("spot"), py::arg("strike"), py::arg("volatility"),
          py::arg("maturity"), py::arg("rate"), py::arg("is_call"));

    m.def("bs_price", cf::bs_price,
          "computes the blackscholes price of an option",
          py::arg("fwd"), py::arg("strike"), py::arg("volatility"),
          py::arg("maturity"), py::arg("is_call"));

    m.def("bs_time_value", cf::bs_time_value,
          "computes the blackscholes time value of an option",
          py::arg("fwd"), py::arg("strike"), py::arg("volatility"),
          py::arg("maturity"));

    m.def("ncdf", cf::ncdf,
          "cumulative distribution function for the normal distribution",
          py::arg("x"));

    py::class_<cf::vanilla_payoff>(m, "VanillaPayoff")
        .def(py::init<double, double, bool>())
        .def("getStrike", &cf::vanilla_payoff::get_strike)
        .def("getMaturity", &cf::vanilla_payoff::get_maturity)
        .def("isCall", &cf::vanilla_payoff::is_call);

    m.def("vanilla_discounted_payoff", py::overload_cast<double, double, double, double, bool>(cf::vanilla_discounted_payoff),
          py::arg("spot"), py::arg("strike"), py::arg("maturity"), py::arg("rate"),
          py::arg("is_call"));

    m.def("vanilla_discounted_payoff", py::overload_cast<double, double, const cf::vanilla_payoff&>(cf::vanilla_discounted_payoff),
          py::arg("spot"), py::arg("rate"), py::arg("payoff"));
}

