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
        map<string, vector<string> > follow_table;

    public:
        // Constructor
        ManagerError() {
            initFollowTable();
        }

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

        // Inicializamos la tabla de follows
        void initFollowTable(){
            follow_table["DO"] = {"$$"};
            follow_table["BL"] = {"$$"};
            follow_table["TE"] = {"2p", "2t", "2z", "2*", "2$", "2_", ">o"};
            follow_table["TS"] = {"wo", "/n", "2p", "2t", "2z", "2*", "2s", "2$", "2_", ">o", "1*", "1$", "1_","<o"};
            follow_table["OP"] = {">o"};
            follow_table["CO"] = {")c"};
            follow_table["FU"] = {"}f"};
            follow_table["PA"] = {")p"};
        }

        void findFollow(string a, string b){
            
        }
};

#endif
