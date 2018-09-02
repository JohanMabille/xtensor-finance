#ifndef MONTE_CARLO_HPP
#define MONTE_CARLO_HPP

#include "xtensor-python/pytensor.hpp"

namespace mc
{

    class diffusion_model
    {
    public:

        using vector_type = xt::pytensor<double, 1>;

        virtual ~diffusion_model() {}

        virtual void get_drift(double time, const vector_type& spot, vector_type& drift) const = 0;
        virtual void get_volatility(double time, const vector_type& spot, vector_type& vol) const = 0;

        //virtual double drift(double spot, double time) const = 0;
        //virtual double volatility(double spot, double time) const = 0;
    };

    class mc_engine
    {
    public:

        mc_engine(const diffusion_model* model);

        void run_simulation(double initial_value,
                            double maturity,
                            npy_intp nb_path);
        const xt::pytensor<double, 2>& get_path() const;

    private:

        const diffusion_model* p_model;
        xt::pytensor<double, 2> m_path;
    };
}

#endif

