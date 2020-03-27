#include <vector>
#include <string>
#include "Hash.h"

using namespace std;

int hashFunction(string s, int M) {
   // Your Code Here
   int sum = 0;
   for(int i = 0; s[i] != '\0'; ++i){
     sum = sum + s[i];
   }
   return sum % M;
 }

 int countCollisions (int M, vector<string> inputs) {
 	int res = 0;
 	// Your Code Here
   int myArray[M + 1];  //default to 0
   for(unsigned long i = 0; i < inputs.size(); ++i){
     int key = hashFunction(inputs[i], M);
     if(myArray[key] == 1){
       ++res;
     }
     myArray[key] = 1;
   }
 	return res;
 }
