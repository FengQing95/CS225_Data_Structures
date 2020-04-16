#include <vector>
#include "Primes.h"

std::vector<int> *genPrimes(int M) {
    std::vector<int> *v = new std::vector<int>();
    // your code here
    bool records[M+1];
    for (int i = 0; i < M+1; i++) {
        records[i] = true;
    }

    for(int p = 2; p * p <= M; p++) {
        if (records[p]) {
            for (int i = p * p; i <= M; i += p) {
                records[i] = false;
            }
        }
    }

    for (int i = 2; i <= M; i++) {
        if(records[i]) {
            v->push_back(i);
        }
    }

    return v;
}
