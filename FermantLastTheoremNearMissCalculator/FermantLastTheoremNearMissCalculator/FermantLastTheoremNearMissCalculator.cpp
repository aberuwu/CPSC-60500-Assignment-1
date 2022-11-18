// FermantLastTheoremNearMissCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Cesar Mendoza   cesarimendoza@lewisu.edu
// Johnny Rebollar  johnnyrebollar@lewisu.edu
// 
// CPSC 60500 Section 5 FALL 2022
// 
// This program uses Pierre Fermat's "last theorem" to look for near misses 
// Status: Still in progress
// 
// Current Issues: This version is practically finished, just needs a good fire test in order to find bugs and or a clean up if needed.
// Please let me know.
// 
//

#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include<algorithm>

//Calculation value class object
class CalculationValues {
public:
    double relativeValue;
    double initialCalculationValue;
    double secondaryCalcutlationValue;
    int difference;
    int xvalue;
    int yvalue;
    int zvalue;
};


void calculateNearMiss(int power, int limit) {

    if (power < 3 || power > 12 || limit > 100) {
        std::cout << "\nvalue of n can't be less than 3 or greater than 12 - Limit can't be greater than 200... Terminatig..." << std::endl;
        return;
    }

    //64bit unsigned integers to minimize overflow
    uint64_t initialCalculation;
    uint64_t secondaryCalculation;
    uint64_t difference;
    double relativeSizeRatio;

    //list of z^n calculations
    std::vector<int> secondCalculations;
    
    //list of primary calculations containing all parameters
    std::vector<CalculationValues> primaryCalculations;
    CalculationValues calculationObject;
    
    //Calculate all (z^n) possibilities
    for (int k = 1; k < limit; k++) {
        secondaryCalculation = pow(k, power);
        secondCalculations.push_back(secondaryCalculation);
    }

    //Calculate all (x^n + y^n) possibilities
    for (int i = 1; i < limit; i++) {    
        for (int j = 1; j < limit; j++) {
            initialCalculation = pow(i, power) + pow(j + 1, power);
            
            for (int k = 0; k < secondCalculations.size(); k++) {

                int secondValue = secondCalculations.at(k);

                //Calculate difference
                if (initialCalculation > secondValue) {
                    difference = initialCalculation - secondValue;
                }
                else {
                    difference = secondValue - initialCalculation;
                }

                //Calculate relative size of miss
                relativeSizeRatio = (double)difference / (double)initialCalculation;

                calculationObject.initialCalculationValue = initialCalculation;
                calculationObject.secondaryCalcutlationValue = secondValue;
                calculationObject.relativeValue = relativeSizeRatio;
                calculationObject.difference = difference;
                calculationObject.xvalue = i;
                calculationObject.yvalue = j + 1;
                calculationObject.zvalue = k + 1;
                primaryCalculations.push_back(calculationObject);   
            }
        }
    }

    //Sort list by relative value quotient
    std::sort(primaryCalculations.begin(), primaryCalculations.end(), [](const CalculationValues& lhs, const CalculationValues& rhs) {
        return lhs.relativeValue > rhs.relativeValue;
        });

    //Print out values
    int iterationCounter = primaryCalculations.size();
    for (int p = 0; p < primaryCalculations.size(); p++) {

        std::cout << "\n#" << iterationCounter << " Near Miss " << primaryCalculations.at(p).xvalue << "^" << power << " + " << primaryCalculations.at(p).yvalue << "^" << power << " = " << primaryCalculations.at(p).zvalue << "^" << power
            << " | " << primaryCalculations.at(p).initialCalculationValue << " = " << primaryCalculations.at(p).secondaryCalcutlationValue << " | " << "Difference = " << primaryCalculations.at(p).difference << " | Relative Size Ratio: " << (primaryCalculations.at(p).relativeValue)*100 << std::setprecision(6) << "%\n";
        iterationCounter--;
    }

}

//Main class which drives our code
int main()
{


    do {
        int power;
        int calculationLimit;
        
        std::cout << "\n----------------------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "\nFermant Last Theorem - Near Miss Calculator\n";
        std::cout << "\nEquation: x^n + y^n = z^n where x, y, z, n are positive integers 2 < n < 12\n";
        std::cout << "\n --- Constraints: n can't be less than 3 or greater than 12 - limit can't be greater than 100 (for memory purposes)--- \n";
        std::cout << "\n----------------------------------------------------------------------------------------------------------------------" << std::endl;
        
        std::cout << "\nInput a value for 'n' (The power of the equation): ";
        std::cin >> power;

        std::cout << "\nInput limit for the calculations: ";
        std::cin >> calculationLimit;

        calculateNearMiss(power, calculationLimit);

        std::cout << "\n-------------------------------------------------------END------------------------------------------------------------\n";

        system("pause");
    } while (true);

   
}





