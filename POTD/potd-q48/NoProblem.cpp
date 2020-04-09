
vector<string> NoProblem(int start, vector<int> created, vector<int> needed) {

    // your code here
    vector<string> res;
    int cur = start;

    for (size_t i = 0; i < needed.size(); ++i) {
        if (cur < needed[i]) {res.push_back("No problem. :(");}
        else {
            cur -= needed[i];
            res.push_back("No problem! :D");
        }
        cur += created[i];
    }
    return res;
}
