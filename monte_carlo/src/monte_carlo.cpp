#include "monte_carlo.hpp"
#include "xtensor/xrandom.hpp"
#include "xtensor/xview.hpp"

namespace mc
{

    mc_engine::mc_engine(const diffusion_model* model)
        : p_model(model)
    {
    }

    void mc_engine::run_simulation(double initial_value, double maturity, npy_intp nb_path)
    {
        using tensor_type = xt::pytensor<double, 1>;
        using shape_type = tensor_type::shape_type;
        shape_type sh = {nb_path};
        npy_intp nb_steps = npy_intp(maturity * 365 + 1);
        m_path.resize({nb_path, nb_steps});

        xt::pytensor<double, 1> spot(sh, initial_value);
        xt::view(m_path, xt::all(), 0) = spot;
        xt::pytensor<double, 1> drift(sh);
        xt::pytensor<double, 1> vol(sh);
        double dt = maturity / nb_steps;
        xt::pytensor<double, 2> dw = std::sqrt(dt) * xt::random::randn<double>({nb_path, nb_steps});

        for(npy_intp i = 1; i < nb_steps; ++i)
        {
            double t = dt * i;
            p_model->get_drift(t, spot, drift);
            p_model->get_volatility(t, spot, vol);
            spot = spot * (1 + drift * dt + xt::view(dw, xt::all(), i) * vol);
            xt::view(m_path, xt::all(), i) = spot;
        }
    }
    
    const xt::pytensor<double, 2>& mc_engine::get_path() const
    {
        return m_path;
    }


}

