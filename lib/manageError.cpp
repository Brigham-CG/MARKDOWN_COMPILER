#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <unordered_set>
#include <stack>
#include "token.cpp"

using namespace std;

#ifndef MANAGEERROR_CPP
#define MANAGEERROR_CPP

class ManagerError {
    private:
        vector<tuple<string, string>> errors;

    public:
        void add_error(string error, string context) {
            make_tuple(error, context);
            errors.push_back(make_tuple(error, context));
        }

        void print_errors() {
            for (auto error : errors) {
                cout << "\t [+] "<< get<1>(error) << endl;
            }
        }

        bool has_errors() {
            if (errors.size() > 0) {
                return true;
            }
            return false;
        }

        void what_is_missing(){
            Token tokenAux;
            tokenAux.createTableOfRelations();
            //tokenAux.printTableOfRelations();

            for(int j = 0; j < errors.size(); j++){
                for(int i = 0; i < tokenAux.tableOfRelations.size(); i++){
                    if(get<0>(tokenAux.tableOfRelations[i]).get_string() == get<0>(errors[j]) || get<1>(tokenAux.tableOfRelations[i]).get_string() == get<0>(errors[j])){
                        get<1>(errors[j]) = get<1>(errors[j]) + " Se esperaba: " + get<1>(tokenAux.tableOfRelations[i]).get_string() + " o " + get<0>(tokenAux.tableOfRelations[i]).get_string();
                        break;
                    }
                }
            }
        }
};

#endif
