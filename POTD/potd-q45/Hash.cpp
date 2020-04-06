#include <vector>
#include "Hash.h"

void doubleHashInput(std::vector<int> &v, int elem){
    int i = firstHash(elem, v.size());
    if (v[i] == -1) {v[i] = elem;}
    else {
        while (v[i] != -1) {i = (i + secondHash(elem)) % v.size();}
        v[i] = elem;
    }
}

int firstHash(int elem, int len) {
    return (elem * 4) % len;
}

int secondHash(int elem) {
    return 3 - (elem % 3);
}
