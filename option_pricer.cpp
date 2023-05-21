#include "option_pricer.h"
#include <iostream>
#include <utility>
#include "cmath"
#include "random"

using namespace std;

Option::Option(double S, double T, string t):
    strike(S),maturity(T), type(std::move(t)) {}

HestonModel::HestonModel(double vol, double reversion, double corr) : volatility(vol),meanReversion(reversion),correlation(corr){}

void simulateHestonModel(double initialPrice, double riskFreeRate, double timeStep, int numSteps, const HestonModel& model){
    double assetPrice = initialPrice;
    double volatility = model.volatility;

    for (int i = 0; i < numSteps; ++i){
        // Create a random number generator engine
        random_device rd;
        mt19937 generator1(rd());
        mt19937 generator2(rd());


        // Define the range
        double minValue = 0.0;
        double maxValue = 1.0;

        // Create a uniform distribution in the specified range
        normal_distribution<double> distribution(minValue, maxValue);

        double randomNumber1;
        randomNumber1 =  distribution(generator1);

        double randomNumber2;
        randomNumber2 =  distribution(generator2);

        assetPrice *= exp((riskFreeRate - 0.5 * volatility*volatility)* timeStep + sqrt(timeStep * volatility)* randomNumber1);
        volatility += model.meanReversion * (model.volatility - volatility)* timeStep + model.correlation* sqrt(volatility*timeStep)*randomNumber2;
    }
}

double cdfStandardNormal(double x){
    return 0.5*(1.0 + erf(x/ sqrt(2.0)));
}

double priceEuropeanOption(const Option& option, double assetPrice, double riskFreeRate, const HestonModel& model){
    // Calculate the relevant parameters
    double d1 = (log(assetPrice / option.strike) + (riskFreeRate + 0.5 * model.volatility * model.volatility) * option.maturity) / (sqrt(option.maturity) * model.volatility);
    double d2 = d1 - sqrt(option.maturity) * model.volatility;

    // Calculate the option price using the Black Scholes formula
    if (option.type == "call") {
        double callPrice = assetPrice * cdfStandardNormal(d1) - option.strike * exp(-riskFreeRate * option.maturity) * cdfStandardNormal(d2);
        return callPrice;
    } else if (option.type == "put") {
        double putPrice = option.strike * exp(-riskFreeRate * option.maturity) * cdfStandardNormal(-d2) - assetPrice * cdfStandardNormal(-d1);
        return putPrice;
    } else {
        cout << "Invalid option type!" << endl;
        return 0.0;
    }
}