#include <string>
#include <stack>

using namespace std;

bool isValid(string input) {
    stack<char> st;
    if(input == ""){return true;}
    else{
      for(unsigned i = 0; i < input.size(); i++){
        char cur = input[i];

        if(cur == '(' || cur == '[' || cur == '{'){st.push(cur);}

        else if(cur == ')'){
          if(! st.empty() && st.top() == '('){st.pop();}
          else{return false;}
        }

        else if(cur == ']'){
          if(! st.empty() && st.top() == '['){st.pop();}
          else{return false;}
        }

        else if(cur == '}'){
          if(! st.empty() && st.top() == '{'){st.pop();}
          else{return false;}
        }

        else{continue;}
      }
    }
    if(st.empty()){return true;}
    else{return false;}
}
