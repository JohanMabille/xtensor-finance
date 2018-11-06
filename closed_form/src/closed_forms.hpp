#ifndef CLOSED_FORMS_HPP
#define CLOSED_FORMS_HPP

#include <algorithm>
#include <cmath>
#include <limits>

#include "xtensor-python/pyarray.hpp"

namespace cf
{
    template <class T>
    inline T ncdf(T x)
    {
        return 0.5 * std::erfc(-x / std::sqrt(2));
    }

    template <class T>
    inline T bs_time_value(T fwd, T strike, T volatility, T maturity)
    {
        if(strike == T(0))
        {
            return T(0);
        }
        else
        {
            T stddev = volatility * std::sqrt(maturity);
            if(stddev == T(0))
            {
                return T(0);
            }
            T tmp = std::log(fwd / strike) / stddev;
            T d1 = tmp + T(0.5) * stddev;
            T d2 = tmp - T(0.5) * stddev;
            T res;
            if(fwd > strike)
            {
                res = strike * ncdf(-d2) - fwd * ncdf(-d1);
            }
            else
            {
                res = fwd * ncdf(d1) - strike * ncdf(d2);
            }
            if(res <= std::numeric_limits<T>::min())
            {
                res = T(0);
            }
            return res;
        }
    }

    template <class T>
    inline T bs_price(T fwd, T strike, T volatility, T maturity, bool is_call)
    {
        T intrinsic_value = std::max(is_call ? fwd - strike : strike - fwd, T(0));
        return intrinsic_value + bs_time_value(fwd, strike, volatility, maturity);
    }

    template <class T>
    inline T bs_discounted_price(T spot, T strike, T volatility, T maturity, T rate, bool is_call)
    {
        T df = std::exp(-rate * maturity);
        T fwd = spot / df;
        return df * bs_price(fwd, strike, volatility, maturity, is_call);
    }

    template <class T>
    inline T vanilla_discounted_payoff(T spot, T strike, T maturity, T rate, bool is_call)
    {
        T df = std::exp(-rate * maturity);
        T fwd = spot / df;
        return df * std::max(is_call ? fwd - strike : strike - fwd, T(0));
    }

    using array_type = xt::pyarray<double, xt::layout_type::row_major>;

    template <class T>
    T distance_impl(const T& a, const T& b)
    {
        using std::sqrt;
        return sqrt(a * a + b * b);
    }

    inline double distance_s(double a, double b)
    {
        return distance_impl(a, b);
    }

    inline array_type distance(const array_type& a, const array_type& b)
    {
        return distance_impl(a, b);
    }
}

#endif
