#include "Friend.h"

int find(int x, std::vector<int>& parents) {
    return (parents[x] == x) ? x : find(parents[x], parents);
}

int findCircleNum(std::vector<std::vector<int>>& M) {
    if (M.empty()) {return 0;}

    int n = M.size();
    std::vector<int> parents;
    for (int i = 0; i < n; i++) {
        parents.push_back(i);
    }
    int res = n;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (M[i][j] == 1) {
                int parent_i = find(i, parents);
                int parent_j = find(j, parents);
                if (parent_i != parent_j) {
                    parents[parent_i] = parent_j;
                    res--;
                }
            }
        }
    }

    return res;
}
