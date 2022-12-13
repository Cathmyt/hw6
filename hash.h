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

    	for (int j = 4; j >= 0; j--) {
				int size = temp.size();
				for (int i = size-1; i >=0; i--) {
					if (i < 6 && i < (int)temp.size()) {
						int pos = temp[abs(i+1-temp.size())];
						w[j] += letterDigitToNumber(pos) * pow(36,i);
					}
    		}
				int k = 0;
				while (k < 6 && temp.size() != 0) {
					temp.pop_back();
					k++;
				}
			}

      HASH_INDEX_T result = 0;
      for (unsigned int i = 0; i < 5; i++) {
				std::cout << w[i] << std::endl;
        result += rValues[i] * w[i];
      }
      return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it 
			if (letter >= 65 && letter <= 90 ) {
				return letter - 65;
      }
      else if (letter >= 48 && letter <= 57 ) {
				return letter - 22;
    	}
      else if (letter >= 97 &&letter <= 122 ) {
        return letter - 97;
      }
      return -1;
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