//Functions.cpp
#include "Functions.h"

namespace AtXml {
    /// Returns the minimum value from an array of integers.
	/** @param Integers The array of integers.
        @param Size The size of the array. */
    int FindMinimum(int Integers[], int Size) {
        int r = 0;

        for (int i=0; i<Size; i++) {
            if (Integers[r] < 0) {
                if (Integers[i] > -1) r = i;
            } else if (Integers[i] > 0 && Integers[i] < Integers[r]) r = i;
        }

        return r;
    }
}
