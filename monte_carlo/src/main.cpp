#define FORCE_IMPORT_ARRAY
#include "xtensor-python/pyarray.hpp"
#include "xtensor-python/pyvectorize.hpp"

#include "monte_carlo.hpp"

namespace py = pybind11;

namespace mc
{
    // Trampoline class, required so we can overload
    // virtual methods in python
    class py_diffusion_model : public diffusion_model
    {
    public:

        using diffusion_model::diffusion_model;
        using vector_type = diffusion_model::vector_type;

        void get_drift(double time, const vector_type& spot, vector_type& drift) const override
        {
            PYBIND11_OVERLOAD_PURE(void, diffusion_model, get_drift, time, spot, drift);
        }

        void get_volatility(double time, const vector_type& spot, vector_type& vol) const override
        {
            PYBIND11_OVERLOAD_PURE(void, diffusion_model, get_volatility, time, spot, vol);
        }
    };
}

PYBIND11_MODULE(xtensor_monte_carlo, m)
{
    // Required at the beginning of the module definition
    xt::import_numpy();
    
    py::class_<mc::diffusion_model, mc::py_diffusion_model> model(m, "diffusion_model");
    model.def(py::init<>())
         .def("get_drift", &mc::diffusion_model::get_drift)
         .def("get_volatility", &mc::diffusion_model::get_volatility);

    py::class_<mc::mc_engine>(m, "mc_engine")
        .def(py::init<const mc::diffusion_model*>())
        .def("run_simulation", &mc::mc_engine::run_simulation)
        .def("get_path", &mc::mc_engine::get_path);
}
