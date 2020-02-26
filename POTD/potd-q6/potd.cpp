#include "potd.h"
#include <cmath>

namespace potd{
    int *raise(int *arr){
        // calculate the size of arr
        int size = 1;
        while (arr[size-1] >= 0){
            size++;
        }
        int * res = new int[size];
        int cur, next, i;
        for(i = 0; i <= size - 3; i++){
            cur = arr[i];
            next = arr[i+1];
            res[i] = pow(cur, next);
        }
        res[i] = arr[i];
        res[i+1] = arr[i+1];
        return res;
    }
}
