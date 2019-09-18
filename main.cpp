#include <iostream>
#include <Analisis/parser.h>
#include <Analisis/scanner.h>

using namespace std;
void analisis();

extern int yyparse();



int main(){

   while(true){
       string str;
       getline(cin,str);
       YY_BUFFER_STATE buffer = yy_scan_string(str.c_str());
       yyparse();
       cout << "\n" << endl;
   }


   return 0;
}



