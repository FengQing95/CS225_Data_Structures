#include <string>
#include "potd.h"

string getFortune(const string &s){
  int tem = s.length() % 5;
  if(tem == 0){return "case 1";}
  else if(tem == 1){return "case 2";}
  else if(tem == 2){return "case 3";}
  else if(tem == 3){return "case 4";}
  else{return "case 5";}
}
