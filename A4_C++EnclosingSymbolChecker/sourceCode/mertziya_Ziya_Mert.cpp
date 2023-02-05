#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "mertziya_Ziya_Mert_DynStackHW4.h"
using namespace std;

int main(){
    
    DynStack stack; // stack which is going to implemented.
    ifstream input;
    string filename;
    do{
        cout << "Please enter the file name: ";
        cin >> filename;
        input.open(filename.c_str());
        if(input.fail()){
            cout << "File not found." << endl;
        }
    }while(input.fail());
    
    char ch;
    int line = 1;
    while (input.get(ch)){
        if(ch == '\n'){line++;}
        else if(ch == '(' || ch == '[' || ch == '{')
        {
            stack.push(ch, line);
            cout << "Found the opening symbol "<< ch << " at line " << line << endl;
            
        }
        else if(ch == ')' || ch == ']' || ch == '}'){
            if(stack.isEmpty()){
                cout << "ERROR!!! Found the closing symbol " << ch <<" but there are no unclosed opening symbols!" << endl;
                input.clear();
                input.close();
                return 0;
            }
            else{
                if(! stack.isEmpty()){
                    char temp_symbol;
                    int temp_line = 0;
                    stack.pop(temp_symbol, temp_line);
                    if(ch == ')'){
                        if('(' != temp_symbol){
                            cout << "ERROR!!! Found the closing symbol " << ch << " but the last unclosed opening symbol is " << temp_symbol << " at line "
                                << temp_line << endl;
                            input.clear();
                            input.close();
                            return 0;
                        }
                        else{
                            cout << "Found the closing symbol " << ch << " at line " << line
                            << " which closes the opening symbol " << temp_symbol << " at line "
                            << temp_line << endl;
                        }
                    }
                    
                    if(ch == ']'){
                        if('[' != temp_symbol){
                            cout << "ERROR!!! Found the closing symbol " << ch << " but the last unclosed opening symbol is " << temp_symbol << " at line "
                                << temp_line << endl;
                            input.clear();
                            input.close();
                            return 0;
                        }
                        else{
                            cout << "Found the closing symbol " << ch << " at line " << line
                            << " which closes the opening symbol " << temp_symbol << " at line "
                            << temp_line << endl;
                        }
                    }
                    
                    if(ch == '}'){
                        if('{' != temp_symbol){
                            cout << "ERROR!!! Found the closing symbol " << ch << " but the last unclosed opening symbol is " << temp_symbol << " at line "
                                << temp_line << endl;
                            input.clear();
                            input.close();
                            return 0;
                        }
                        else{
                            cout << "Found the closing symbol " << ch << " at line " << line
                            << " which closes the opening symbol " << temp_symbol << " at line "
                            << temp_line << endl;
                        }
                    }
                }
            }
        }
    }
    
    if(stack.isEmpty()){
        cout << "File processed successfully. No errors were found." << endl;
    }
    else{
        cout << "ERROR!!! The following opening symbols were not closed:" <<endl;
        while(!stack.isEmpty()){
            char temp_c;
            int temp_i;
            stack.pop(temp_c, temp_i);
            cout << "  Symbol " << temp_c << " at line " << temp_i << endl;
        }
    }
    input.clear();
    input.close();
    return 0;
}
