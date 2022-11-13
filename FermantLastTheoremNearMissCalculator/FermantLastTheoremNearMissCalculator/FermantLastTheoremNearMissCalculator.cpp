// FermantLastTheoremNearMissCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
// Status: Still in progress
// Current Issues: I have set up the calculateNearMiss class, currently takes in the integer value for power and the integer value
// for the upper limit. We still need to figure out how to properly compare and find the near miss difference. When calculating
// the difference, sometimes I get a negative value, which is to be expected based on how I set this up, so we need to figure out a 
// way to avoid having this issue.
// 
//

#include <iostream>
#include <math.h>

void calculateNearMiss(int power, int limit) {

    if (power < 3)
        return;

    //64bit unsigned integers to minimize overflow
    uint64_t nearMissLowest = 0;
    uint64_t initialCalculation;
    uint64_t secondaryCalculation;
    uint64_t difference;

    for (int i = 3; i < limit; i++) {

        //for (int j = 1; j < limit; j++) {

            //Calculate (x^n + y^n)
            initialCalculation = pow(i, power) + pow(i+1, power);

            for (int k = i; k < limit; k++) {
                //Calculate (z^n)
                secondaryCalculation = pow(k, power);

                //Calculate Difference
                difference = secondaryCalculation - initialCalculation;

                //Set min value for nearMiss
                if (nearMissLowest == 0) {
                    nearMissLowest = difference;
                }

                //Check for difference
                if (difference < nearMissLowest) {
                    nearMissLowest = difference;
                    std::cout << "\nNear Miss " << i << "^" << power << "+" << i+1 << "^" << power << "=" << k << "^" << power
                        << " : " << nearMissLowest << "\n";
                }
                    
            }
        //}
    }
}

//Main class which drives our code
int main()
{
    int power;
    int calculationLimit;

    std::cout << "Fermant Last Theorem - Near Miss Calculator\n";
    std::cout << "Equation: x^n + y^n = z^n where x, y, z, n are positive integers 2 < n < 12\n";

    std::cout << "\nInput a value for 'n' (The power of the equation): ";
    std::cin >> power;

    std::cout << "\nInput limit for the calculations: ";
    std::cin >> calculationLimit;

    calculateNearMiss(power, calculationLimit);

    system("pause");
}





