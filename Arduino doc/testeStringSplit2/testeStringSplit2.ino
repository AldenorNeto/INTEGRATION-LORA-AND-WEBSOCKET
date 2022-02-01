#include <iostream>
#include <sstream>


using namespace std;

void setup() {
  Serial.begin(115200);
   // string a ser separada
   string tokenString { "aaa, bbb, ccc,,ddd   ,   eee" };

   // as sub-strings separadas vão ser colocadas neste vetor
   vector<string> tokens;

   // stream de strings de input inicializado com a string a ser separada
   istringstream tokenizer { tokenString };

   string token;

   // separa as sub-strings por vírgula e coloca no vetor destino
   while (getline(tokenizer, token, ',')){
    printf(token);
   }
      //tokens.push_back(token);

   // mostra na tela as sub-strings separadas
   Serial.println(tokens[1].toString());
   /*for (const string& token: tokens){
       cout << "* [" << token << "]\n";
       printf(" %s", token );
   }*/

}

void loop() {
  // put your main code here, to run repeatedly:

}
