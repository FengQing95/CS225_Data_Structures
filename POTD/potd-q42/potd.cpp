#include <unordered_map>

using namespace std;

unordered_map<string, int> common_elems(unordered_map<string, int> & mapA,
                                        unordered_map<string, int> & mapB) {

    // your code here
    unordered_map<string, int> res;

    auto it = mapB.begin();
    while (it != mapB.end()) {
      unordered_map<string, int>::const_iterator cur = mapA.find(it->first);

      if (cur != mapA.end()) {
          res.insert(make_pair(it->first, (it->second + cur->second)));
          cur = mapA.erase(cur);
          it = mapB.erase(it);
          continue;
      }
      ++it;
    }

    return res;
}
