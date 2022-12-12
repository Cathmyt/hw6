#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
			std::string temp = k;
			unsigned long long w[5] = {0, 0, 0, 0, 0};

			for (int j = 0; j < 5; j++) {
				int substringStart = std::max(0, int(temp.size() - (j + 1) * 6));
				int substringEnd = temp.size() - j * 6;
				std::string substring = temp.substr(substringStart, substringEnd - substringStart);
				for (int i = 0; i < (int)substring.size(); i++) {
					w[j] += pow(36, i) * letterDigitToNumber(substring[i]);
				}
			}

		 	HASH_INDEX_T result = 0;
    	for (unsigned int i = 0; i < 5; i++) {
				result += rValues[i] * w[i];
    	}
    	return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
			if (letter >= 'a' && letter <= 'z') {
				return letter - 'a';  
			}
			else if (letter >= '0' && letter <= '9') {
				return letter - '0' + 26;
			}
			else return -1;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif

