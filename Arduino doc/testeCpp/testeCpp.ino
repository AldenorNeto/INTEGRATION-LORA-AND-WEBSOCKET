#include <iostream>
#include <cstring>
using namespace std;
void setup(){
  
Serial.begin(9600);
Serial.println();
    string s = "geeksforgeeks";

    int n = s.length();
 
    // declaring character array
    char char_array[n + 1];
 
    // copying the contents of the
    // string to char array
    strcpy(char_array, s.c_str());
 
    for (int i = 0; i < n; i++)
        Serial.println(char_array[i]);
}

void loop() {

}

 
