#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

void parseC() {
    string str;
    bool hasComment = false, hasStringLiterals = false, hasCharLiterals = false, hasDigits = false;
    while(getline(cin, str)) {
        string identifer;
        string digits;
        string str_literals;
        string char_literals;
        for(int i=0; i<(int)str.size(); i++) {
            //current character is a whitespace, skip to read next character
            if(isspace(str[i]) && !hasStringLiterals) {
                continue;
            }
            
            //handle comments
            //current character is part of comment signs
            if(str[i] == '*' && i<(int)str.size()-1) {
                if(str[i+1] == '/') {
                    hasComment = false;
                    i++;
                    continue;
                }
            }
            if(str[i] == '/' && i<(int)str.size()-1) {
                if(str[i+1] == '/') { //when comments begin with "//", skip to read next line
                    break;
                } else if(str[i+1] == '*') { //when comments begin with "/*", set true
                    hasComment =  true;
                    continue;
                }
            }
            if(hasComment) {
                continue;
            }
            
            //handle string literals
            if(hasStringLiterals && !hasCharLiterals && !hasDigits) {
                if(str[i] == '\"' && i>0 && str[i-1] != '\\') {
                    str_literals += '\"';
                    if(str[i-1] != '\\') {
                        cout<<str_literals<<endl;
                        hasStringLiterals = false;
                        str_literals = "";
                    }
                    continue;
                }
                if(str[i] == '\\') {
                    str_literals += '\\';
                    continue;
                }
                str_literals += str[i];
                continue;
            }
            
            if(str[i] == '\"' && !hasStringLiterals && !hasCharLiterals && !hasDigits) {
                hasStringLiterals = true;
                str_literals += '\"';
                continue;
            }
            
            //handle charatcter literals
            if(hasCharLiterals && !hasStringLiterals && !hasDigits) {
                if(str[i] == '\'') {
                    char_literals += '\'';
                    hasCharLiterals = false;
                    cout<<char_literals<<endl;
                    char_literals = "";
                    continue;
                }
                if(str[i] == '\\') {
                    char_literals += '\\';
                    continue;
                }
                char_literals += str[i];
                continue;
            }
            
            if(str[i] == '\''  && !hasCharLiterals && !hasStringLiterals && !hasDigits) {
                char_literals += '\'';
                hasCharLiterals = true;
                continue;
            }
            
            //handle identifers
            if((isalpha(str[i]) && !hasDigits) || str[i] == '_' || (isdigit(str[i]) && identifer.size()>0)) {
                identifer += str[i];
                if(i<(int)str.size()-1 && !isalpha(str[i+1]) && str[i+1]!='_' && !isdigit(str[i+1])) {
                    cout<<identifer<<endl;
                    identifer = "";
                }
                continue;
            }
            
            //handle digits
            if(hasDigits && !hasStringLiterals && !hasCharLiterals) {
                if(!isdigit(str[i]) && str[i]!='.' && str[i]!='e') {
                    hasDigits = false;
                    cout<<digits<<endl;
                    digits = "";
                    cout<<str[i]<<endl;
                    continue;
                }
                digits += str[i];
                if(i == (int)str.size()-1) {
                    hasDigits = false;
                    cout<<digits<<endl;
                    digits = "";
                }
                continue;
            }
            
            if(isdigit(str[i]) && !hasDigits && !hasStringLiterals && !hasCharLiterals) {
                digits += str[i];
                hasDigits = true;
                continue;
            }
            
            //handle operators
            string op = "";
            if(str[i] == '+') {
                op += str[i];
                if(i<(int)str.size()-1 && (str[i+1] == '+' || str[i+1] == '=')) {
                    op += str[i+1];
                    i = i+1;
                }
                cout<<op<<endl;
                continue;
            }
            if(str[i] == '-') {
                op += str[i];
                if(i<(int)str.size()-1 && (str[i+1] == '-' || str[i+1] == '=')) {
                    op += str[i+1];
                    i = i+1;
                }
                cout<<op<<endl;
                continue;
            }
            if(str[i] == '*') {
                op += str[i];
                if(i<(int)str.size()-1 && str[i+1] == '=') {
                    op += str[i+1];
                    i = i+1;
                }
                cout<<op<<endl;
                continue;
            }
            if(str[i] == '/') {
                op += str[i];
                if(i<(int)str.size()-1 && str[i+1] == '=') {
                    op += str[i+1];
                    i = i+1;
                }
                cout<<op<<endl;
                continue;
            }
            if(str[i] == '%') {
                op += str[i];
                if(i<(int)str.size()-1 && str[i+1] == '=') {
                    op += str[i+1];
                    i = i+1;
                }
                cout<<op<<endl;
                continue;
            }
            if(str[i] == '=') {
                op += str[i];
                if(i<(int)str.size()-1 && str[i+1] == '=') {
                    op += str[i+1];
                    i = i+1;
                }
                cout<<op<<endl;
                continue;
            }
            if(str[i] == '!') {
                op += str[i];
                if(i<(int)str.size()-1 && str[i+1] == '=') {
                    op += str[i+1];
                    i = i+1;
                }
                cout<<op<<endl;
                continue;
            }
            if(str[i] == '^') {
                op += str[i];
                if(i<(int)str.size()-1 && str[i+1] == '=') {
                    op += str[i+1];
                    i = i+1;
                }
                cout<<op<<endl;
                continue;
            }
            if(str[i] == '&') {
                op += str[i];
                if(i<(int)str.size()-1 && (str[i+1] == '&' || str[i+1] == '=')) {
                    op += str[i+1];
                    i = i+1;
                }
                cout<<op<<endl;
                continue;
            }
            if(str[i] == '|') {
                op += str[i];
                if(i<(int)str.size()-1 && (str[i+1] == '|' || str[i+1] == '=')) {
                    op += str[i+1];
                    i = i+1;
                }
                cout<<op<<endl;
                continue;
            }
            if(str[i] == '>') {
                op += str[i];
                if(i<(int)str.size()-1 && str[i+1] == '=') {
                    op += str[i+1];
                    i = i+1;
                } else if(i<(int)str.size()-1 && str[i+1] == '>') {
                    op += str[i+1];
                    i = i+1;
                    if(i<(int)str.size()-1 && str[i+1] == '=') {
                        op += str[i+1];
                        i = i+1;
                    }
                }
                cout<<op<<endl;
                continue;
            }
            if(str[i] == '<') {
                op += str[i];
                if(i<(int)str.size()-1 && str[i+1] == '=') {
                    op += str[i+1];
                    i = i+1;
                } else if(i<(int)str.size()-1 && str[i+1] == '<') {
                    op += str[i+1];
                    i = i+1;
                    if(i<(int)str.size()-1 && str[i+1] == '=') {
                        op += str[i+1];
                        i = i+1;
                    }
                }
                cout<<op<<endl;
                continue;
            }
            
            //other symbols
            cout<<str[i]<<endl;
            
        }//end of for loop
    }
}

int main() {
    parseC();
    return 0;
}
