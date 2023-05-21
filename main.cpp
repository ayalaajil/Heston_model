#include <iostream>
#include "option_pricer.h"

using namespace std;
int main() {

        // Instantiate the option
        Option option(100.0, 1.0, "call");
        // Set the Heston model parameters
        HestonModel model(0.2, 0.1, 0.5); // Example values

        // Set other necessary variables
        double assetPrice = 100.0; // Example value
        double riskFreeRate = 0.05; // Example value
        double timeStep = 0.01; // Example value
        int numSteps = 100; // Example value

        // Simulate the Heston model
        simulateHestonModel(assetPrice, riskFreeRate, timeStep, numSteps, model);

        // Price the option
        double optionPrice = priceEuropeanOption(option, assetPrice, riskFreeRate, model);

        // Print the result
        cout <<"The "<<option.type<<" price: " << optionPrice << endl;

        return 0;

}


