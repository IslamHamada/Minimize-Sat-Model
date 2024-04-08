#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/types.h>

#include "minisat/core/Solver.h"
#include "EvalMaxSAT/lib/EvalMaxSAT/src/EvalMaxSAT.h"

using namespace std;
using namespace Minisat;

vector<int> minimize_model2(Solver& s);
bool verify_model(vector<int> &mini_model, Solver &s);
void loadCnfFromFile(Solver &s, const char *file_name);
void loadCnfFromfile2(EvalMaxSAT<Solver_cadical>& solver, const char *file_name);
bool compare_both_approaches(const char *file_name, ofstream &fout);

int main() {

    ofstream fout;
    fout.open("/home/islam/CLionProjects/Sat/SatSolvingCourse/output.csv");
    char* file_path = "/home/islam/CLionProjects/Sat/SatSolvingCourse/uf20-91/uf20-01.cnf";
    compare_both_approaches(file_path, fout);

//    DIR *dr;
//    struct dirent *en;
//    char* directory = "/home/islam/CLionProjects/Sat/SatSolvingCourse/UF75.325.100";
//    dr = opendir(directory); //open all directory
//    if (dr) {
//        while ((en = readdir(dr)) != NULL) {
//            cout << en->d_name << endl;
//            if(strcmp(en->d_name, ".") == 0 || strcmp(en->d_name, "..") == 0)
//                continue;
//            char file_path[1000];
//            strcpy(file_path, directory);
//            strcat(file_path, "/");
//            strcat(file_path, en->d_name);
//            compare_both_approaches(file_path, fout);
//            cout << "---------------------------------------------------------------" << endl;
//        }
//        closedir(dr); //close all directory
//    }
//    fout.close();

    return 1;
}

// load the dual encoding of a cnf formula into the maxsat solver
void loadCnfFromfile2(EvalMaxSAT<Solver_cadical>& solver, const char *file_name) {
    fstream new_file;
    new_file.open(file_name, ios::in);
    if(new_file.is_open()){
        string sa;
        while(getline(new_file, sa) && sa[0] == 'c');
        stringstream ss(sa);
        string word;
        ss >> word; ss >> word; ss >> word;
        int vars = stoi(word);
        for(int i = 0; i < vars; i++) {
            int l_p = solver.newVar();
            int l_n = solver.newVar();
            solver.addClause({-l_p, -l_n});
            solver.addClause({-l_p}, 1);
            solver.addClause({-l_n}, 1);
        }
        ss >> word;
        int clss = stoi(word);
        int i = 0;
        while(getline(new_file, sa) && clss-- > 0){
            vector<int> cls;
            stringstream ss2(sa);
            ss2 >> word;
            int v = stoi(word);
            while(v != 0){
                if(v > 0)
                    cls.push_back(abs(v) * 2 - 1);
                else
                    cls.push_back(abs(v) * 2);
                ss2 >> word;
                v = stoi(word);
            }
            solver.addClause(cls);
            i++;
        }
    }
}

// load the cnf formula into the sat solver
void loadCnfFromFile(Solver &s, const char *file_name) {
    fstream new_file;
    new_file.open(file_name, ios::in);
    if(new_file.is_open()) {
        string sa;
        while (getline(new_file, sa) && sa[0] == 'c');
        stringstream ss(sa);
        string word;
        ss >> word;
        ss >> word;
        ss >> word;
        int vars = stoi(word);
        for (int i = 0; i < vars; i++) s.newVar();
        ss >> word;
        int clss = stoi(word);
        int i = 0;
        while (getline(new_file, sa) && clss-- > 0) {
            vec<Lit> cls;
            stringstream ss2(sa);
            ss2 >> word;
            int v = stoi(word);
            while (v != 0) {
                cls.push(mkLit(abs(v) - 1, v < 0));
                ss2 >> word;
                v = stoi(word);
            }
            s.addClause(cls);
            i++;
        }
    }
}

// function HDL_clause from the paper
// My understanding of it is the following: if there's no alternative watch literal to l that is mapped to true,
// then the other current watch literal has to be in the minimal model, otherwise replace the watch literal l
// with another true literal and update the watch literals relation
void HDL_clause(Solver& s, int cls_idx_in_w, CRef cref, Lit& l, vector<int>& model, vector<Lit>& min_model){
    Clause& cls = s.ca[cref];
    Lit* l_p = NULL;
    int l_p_idx = -1;
    for(int i = 2; i < cls.size(); i++){
        if(std::find(model.begin(), model.end(), cls[i].x) != model.end()){
            l_p = &cls[i];
            l_p_idx = i;
            break;
        }
    }

    // make sure l is in data[1]
    if(cls[0].x == l.x){
        cls[0] = cls[1];
        cls[1] = l;
    }

    // ToDo how to remove a clause from a watch literal list
    // ToDo use examples that test this part
    if(l_p == NULL) {
        min_model.push_back(cls[0]);
    } else {
//        cout << "shout" << endl;
        Solver::Watcher w(cref, cls[1]);
        s.watches[~(*l_p)].push(w);
//        for(int i = cls_idx_in_w; i + 1 < s.watches[~l].size(); i++){
//            s.watches[~l][i] = s.watches[~l][i + 1];
//        }
//        s.watches[~l].shrink(1);
        // swap clause literals
        Lit l_p_temp = *l_p;
        cls[l_p_idx] = cls[1];
        cls[1] = l_p_temp;
    }
}

// this is function implied_w from the paper
// for each clause in s, apply function HDL_clause. Read the comments above
// the function HDL_clause.
void implied_w(Solver& s, Lit l, vector<int>& model, vector<Lit>& min_model){
    vec<Solver::Watcher>& w_l = s.watches[~l];
    for(int i = 0; i < w_l.size(); i++){
        Solver::Watcher w = w_l[i];
        CRef cref = w.cref;
        HDL_clause(s, i, cref, l, model, min_model);
    }
}

// this is function implied_w_0 from the paper
// the purpose of this function is to replace any of the false watch literals
// with another watch literal
void implied_w_0(Solver& s, vector<int>& model, vector<Lit>& min_model){
    for(int i = 0; i < model.size(); i++){
        Lit l = mkLit(model[i] / 2, model[i] % 2);
        implied_w(s, ~l, model, min_model);
    }
}

// apply the algorithm of the paper to a minimize model of sat
// zero represents true, while one represents false
vector<int> minimize_model2(Solver& s){
//    cout << "minimize_model2" << endl;
    vector<int> model;
    vector<Lit> min_model;

    vector<Var> all_vars;

    // get all vars of s
    for(int i = 0; i < s.nVars(); i++){
        all_vars.push_back(i);
    }

    // check which vars are propagated and store them in min model and the rest to be checked later
//    for(Var x : all_vars){
//        if(s.vardata[x].level == 0) {
//            min_model.push_back(mkLit(x * 2 + toInt(s.modelValue(x))));
//        }
//    }

    for(int i = s.nVars() - 1; i >= 0; i--){
        if(s.modelValue(i) == l_True){
            model.push_back(i * 2);
        } else {
            model.push_back(i * 2 + 1);
        }
    }

    implied_w_0(s, model, min_model);

    for(int i = 0; i < model.size();){
        Lit l = mkLit(model[i] / 2, model[i] % 2);
        bool in_min_model = false;
        for(int j = 0; j < min_model.size(); j++){
            if(l.x == min_model[j].x) {
                i++;
                in_min_model = true;
                break;
            }
        }
        if(in_min_model) continue;
        model.erase(model.begin() + i);
        implied_w(s, l, model, min_model);
    }

    std::sort(min_model.begin(), min_model.end());
    for(int i = 0; i + 1 < min_model.size();){
        if(min_model[i] == min_model[i + 1]){
            min_model.erase(min_model.begin() + i + 1);
        } else {
            i++;
        }
    }
    vector<int> rv;
    for(int i = 0; i < min_model.size(); i++){
//        cout << var(min_model[i]) << " -> " << sign(min_model[i]) << endl;
        rv.push_back(min_model[i].x);
    }
    return rv;
}

// verify that 'mini_model' is actually a model of the cnf formula in the solver 's'
bool verify_model(vector<int> &mini_model, Solver &s) {
    for(int i = 0; i < s.clauses.size(); i++){
        CRef cref = s.clauses[i];
        Clause& cls = s.ca[cref];
        bool sat_cls = false;
        for(int j = 0; j < cls.size(); j++){
            for(int k = 0; k < mini_model.size(); k++){
                if(cls[j].x == mini_model[k]){
                    sat_cls = true;
                    break;
                }
            }
            if(sat_cls) break;
        }
        if(!sat_cls) {
            return false;
        }
    }
    return true;
}

bool compare_both_approaches(const char *file_name, ofstream &fout) {
//    char* file_name = "/home/islam/CLionProjects/Sat/SatSolvingCourse/uf20-91/uf20-015.cnf";
    Solver s;
    loadCnfFromFile(s, file_name);

    float sat_time = clock();
    if(!s.solve()){
        cout << "unsat" << endl;
        return 0;
    }
    sat_time = (clock() - sat_time) / CLOCKS_PER_SEC;
    cout << "Sat time: " << sat_time << endl;
    cout << "Full model size: " << s.nVars() << endl;

    float min_time = clock();
    vector<int> mini_model = minimize_model2(s);
    min_time = (clock() - min_time) / CLOCKS_PER_SEC;
    cout << "Minimal Model size: " << mini_model.size() << endl;
    cout << "Minimizing min_time: " << min_time << endl;
    cout << "Total time: " << sat_time + min_time << endl;

    // verify 'mini_model' is a model
    if(!verify_model(mini_model, s)){
        cout << "Not a model" << endl;
        return 0;
    }
    // verify that no other smaller model of 'mini_model' is a model
    for(int i = 0; i < mini_model.size(); i++){
        vector<int> test_model;
        std::copy(mini_model.begin(), mini_model.end(),std::back_inserter(test_model));
        test_model.erase(test_model.begin() + i);
        if(verify_model(test_model, s)){
            cout << "Not a minimal model" << endl;
            cout << "bug" << endl;
            return 0;
        }
    }

    EvalMaxSAT s2;
    loadCnfFromfile2(s2, file_name);
    float max_sat_time = clock();
    if(!s2.solve()){
        std::cout << "Error" << endl;
        return 0;
    }
    max_sat_time = (clock() - max_sat_time) / CLOCKS_PER_SEC;

    cout << "smallest model size: " << s2.getCost() << endl;
    cout << "smallest model time: " << max_sat_time << endl;

    fout << sat_time + min_time << "\t" << max_sat_time << "\t" << mini_model.size() << "\t" << s2.getCost() << endl;
}