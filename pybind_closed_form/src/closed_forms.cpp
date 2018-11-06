#include "closed_forms.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace cf
{
    double ncdf(double x)
    {
        return 0.5 * std::erfc(-x / std::sqrt(2));
    }

    double bs_time_value(double fwd, double strike, double volatility, double maturity)
    {
        if(strike == 0.)
        {
            return 0.;
        }
        else
        {
            double stddev = volatility * std::sqrt(maturity);
            if(stddev == 0.)
            {
                return 0.;
            }
            double tmp = std::log(fwd/strike) / stddev;
            double d1 = tmp + 0.5 * stddev;
            double d2 = tmp - 0.5 * stddev;
            double res;
            if(fwd > strike)
            {
                res = strike * ncdf(-d2) - fwd * ncdf(-d1);
            }
            else
            {
                res = fwd * ncdf(d1) - strike * ncdf(d2);
            }
            if(res <= std::numeric_limits<double>::min())
            {
                res = 0.;
            }
            return res;
        }
    }

    double bs_discounted_price(double spot, double strike, double volatility, double maturity, double rate, bool is_call)
    {
        double df = std::exp(-rate * maturity);
        double fwd = spot / df;
        return df * bs_price(fwd, strike, volatility, maturity, is_call);
    }

    double bs_price(double fwd, double strike, double volatility, double maturity, bool is_call)
    {
        double intrinsic_value = std::max(is_call ? fwd - strike : strike - fwd, 0.);
        return intrinsic_value + bs_time_value(fwd, strike, volatility, maturity);
    }

    double vanilla_discounted_payoff(double spot, double strike, double maturity, double rate, bool is_call)
    {
        double df = std::exp(-rate * maturity);
        double fwd = spot / df;
        return df * std::max(is_call ? fwd - strike : strike - fwd, 0.);
    }

    double vanilla_discounted_payoff(double spot, double rate, const vanilla_payoff& payoff)
    {
        return vanilla_discounted_payoff(spot, payoff.get_strike(), payoff.get_maturity(), rate, payoff.is_call());
    }

    vanilla_payoff::vanilla_payoff(double strike, double maturity, bool call)
        : m_strike(strike), m_maturity(maturity), m_is_call(call)
    {
    }

    double vanilla_payoff::get_strike() const noexcept
    {
        return m_strike;
    }

    double vanilla_payoff::get_maturity() const noexcept
    {
        return m_maturity;
    }

    bool vanilla_payoff::is_call() const noexcept
    {
        return m_is_call;
    }
}

