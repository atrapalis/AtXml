//Functions.cpp
#include "Functions.h"

namespace antxml {
    /// Returns the index of the minimum value from an array of integers.
	/** @param integers The array of integers.
        @param size The size of the array. */
    int FindMinimum(int integers[], int size) {
        if (size < 1)
            return -1;
        
        int index = 0;
        int minimum = integers[0];

        for (int i = 0; i < size; i++)
            if (integers[i] < minimum) {
                minimum = integers[i];
                index = i;
            }

        return index;
    }
}
