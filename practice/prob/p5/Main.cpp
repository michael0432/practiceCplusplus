#include <iostream>
#include <string>
#include "Account.h"
#include "Bank.h"

using namespace std;

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

int main(){
    Bank b;
    string cmd;
    while(getline(cin,cmd)){
        vector<string> vs;
        split(cmd, vs, ' ');
        if(vs[0] == "login"){
            
        }
        else if(vs[0] == "create"){

        }
        else if(vs[0] == "delete"){

        }
        else if(vs[0] == "deposit"){

        }
        else if(vs[0] == "withdraw"){

        }
        else if(vs[0] == "transfer"){

        }
        else if(vs[0] == "merge"){

        }
        else if(vs[0] == "search"){

        }
        else if(vs[0] == "find"){

        }
    }
}