#pragma
#include <iostream>

class Option{
public:
    double strike;
    double maturity;
    std::string type;
    Option(double S,double T, std::string t);
};

class HestonModel{
public:
    double volatility;
    double meanReversion;
    double correlation;

    HestonModel(double vol,double reversion,double corr);
};

void simulateHestonModel(double initialPrice, double riskFreeRate, double timeStep, int numSteps, const HestonModel& model);
double cdfStandardNormal(double x);
double priceEuropeanOption(const Option& option, double assetPrice, double riskFreeRate, const HestonModel& model);

