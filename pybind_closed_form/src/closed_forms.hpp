#ifndef CLOSED_FORMS_HPP
#define CLOSED_FORMS_HPP

namespace cf
{
    double ncdf(double x);
    double bs_time_value(double fwd, double strike, double volatility, double maturity);
    double bs_price(double fwd, double strike, double volatility, double maturity, bool is_call);
    double bs_discounted_price(double spot, double strike, double volatility, double maturity, double rate, bool is_call);

    class vanilla_payoff
    {
    public:

        vanilla_payoff(double strike, double maturity, bool call);

        double get_strike() const noexcept;
        double get_maturity() const noexcept;
        bool is_call() const noexcept;

    private:

        double m_strike;
        double m_maturity;
        bool m_is_call;
    };

    double vanilla_discounted_payoff(double spot, double strike, double maturity, double rate, bool is_call);
    double vanilla_discounted_payoff(double spot, double rate, const vanilla_payoff& payoff);
}

#endif
