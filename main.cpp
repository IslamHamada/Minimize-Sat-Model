#include <iostream>
#include <vector>
#include "minisat/core/Solver.h"
//#include "minisat/core/SolverTypes.h"
#include "minisat/mtl/Vec.h"
#include "minisat/mtl/Sort.h"
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;
using namespace Minisat;

vector<int> minimize_model(Solver& s, vector<int>& top_level_assignment);
vector<int> minimize_model2(Solver& s);
bool verify_model(vector<int> &mini_model, Solver &s);

int main() {
    Solver s;
//    fstream new_file;
//    new_file.open("/home/islam/CLionProjects/Sat/mini/Flat200-479/flat200-1.cnf", ios::in);
//    if(new_file.is_open()){
//        string sa;
//        while(getline(new_file, sa) && sa[0] == 'c');
//        stringstream ss(sa);
//        string word;
//        ss >> word; ss >> word; ss >> word;
//        int vars = stoi(word);
//        for(int i = 0; i < 2*vars; i++) s.newVar();
//        ss >> word;
//        int clss = stoi(word);
////        clss = 7;
//        int i = 0;
//        while(getline(new_file, sa) && clss-- > 0){
////            cout << i << endl;
//            vec<Lit> cls;
//            stringstream ss2(sa);
//            ss2 >> word;
//            int v = stoi(word);
//            while(v != 0){
////                cout << v << " ";
//                cls.push(mkLit(abs(v) - 1, v < 0));
//                ss2 >> word;
//                v = stoi(word);
//            }
////            cout << endl;
//            s.addClause(cls);
//            i++;
//        }
//    }
////    exit(0);
    for(int i = 0; i < 20; i++){
        s.newVar();
    }
////    s.newVar(true, false);
////    s.newVar(true, false);
//    s.newVar(true);
////    s.newVar(true);
////    s.newVar(true);
////    s.newVar(true);
////    s.newVar(true);
////    s.newVar(true);
    s.addClause(mkLit(0));
//    s.addClause(mkLit(0), mkLit(1), mkLit(2));
////    vec<Lit> cls;
////    cls.push(mkLit(0));
////    cls.push(mkLit(1));
////    cls.push(mkLit(2));
////    cls.push(mkLit(3));
////    s.addClause(cls);
////    vec<Lit> cls1;
////    cls1.push(mkLit(0));
////    cls1.push(mkLit(1));
//
//// test 1
////    s.addClause(mkLit(0), mkLit(3, true));
////    s.addClause(mkLit(0), mkLit(2));
////    s.addClause(mkLit(2, true), mkLit(1), mkLit(3));
//
//// test 2
////    s.addClause(mkLit(0), mkLit(1, true));
////    s.addClause(mkLit(1), mkLit(2));
////    s.addClause(mkLit(1), mkLit(3, true));
////    s.addClause(mkLit(0, true), mkLit(2, true), mkLit(3));
//
//// test 3
////    s.addClause(mkLit(0), mkLit(1));
////    s.addClause(mkLit(1, true), mkLit(2));
//
//// test 4
////    s.addClause(mkLit(0), mkLit(1, true));
////    s.addClause(mkLit(0, true), mkLit(4));
////    s.addClause(mkLit(1, true), mkLit(1), mkLit(2, true));
////    s.addClause(mkLit(2), mkLit(3));
////    s.addClause(mkLit(1, true), mkLit(2, true), mkLit(3, true));
////    s.addClause(mkLit(1), mkLit(3), mkLit(4));
//
//// test 5
//    s.addClause(mkLit(4), mkLit(18, true), mkLit(19));
//    s.addClause(mkLit(3), mkLit(5, true));
//    s.addClause(mkLit(5, true), mkLit(8, true), mkLit(15, true));
//    s.addClause(mkLit(20, true), mkLit(7), mkLit(16, true));
//    s.addClause(mkLit(10), mkLit(13, true), mkLit(7, true));
//    s.addClause(mkLit(12, true), mkLit(9, true), mkLit(17));
//    s.addClause(mkLit(17), mkLit(5));
//
////    cout << s.clauses.size() << endl;
//    s.random_seed = rand();
////    s.verbosity = 1;
//
////    while(s.solve()) {
    float sat_time = clock();
    vector<int> all_vars;
    vector<int> top_level_assigment;
    for(int i = 0; i < s.nVars(); i++){
        if(s.vardata[i].level == 0){
            top_level_assigment.push_back(i * 2 + toInt(s.assigns[i]));
        }
    }
    if(!s.solve()){
        cout << "unsat" << endl;
        return 0;
    }
    cout << "Sat time: " << (clock() - sat_time) / CLOCKS_PER_SEC << endl;
    vector<int> model;
    cout << "Full model: " << s.nVars() << endl;
    for(int i = 0; i < s.nVars(); i++){
//        cout << i << " -> " << toInt(s.model[i]) << endl;
//        Minisat::lbool v = s.modelValue(i);
//        v = 0;
//        cout << toInt(v) << endl;
//        printf("%d", v);
//        model.push_back(2 * i + toInt(s.model[i]));
    }
//
    cout << "---------------" << endl;
    cout << "Minimal Model" << endl;
    float min_time = clock();
    vector<int> mini_model = minimize_model(s, top_level_assigment);
    cout << "Minimizing min_time: " << (clock() - min_time) / CLOCKS_PER_SEC << endl;
    cout << "Minimal Model size: " << mini_model.size() << endl;
////    vector<int> mini_model = model;
    cout << "---------------" << endl;
    cout << "verify: model" << endl;
    if(!verify_model(mini_model, s)){
        cout << "Not a model" << endl;
        return 0;
    }
    cout << "---------------" << endl;
    cout << "verify: no smaller model" << endl;
    for(int i = 0; i < mini_model.size(); i++){
//        cout << i << endl;
        vector<int> test_model;
        std::copy(mini_model.begin(), mini_model.end(),std::back_inserter(test_model));
        test_model.erase(test_model.begin() + i);
        if(verify_model(test_model, s)){
            cout << "Not a minimal model" << endl;
            cout << i << endl;
//            return 0;
        }
    }
////    vec<Lit> cls;
////    for(int i = 0; i < mini_model.size(); i++){
////        cls.push(mkLit(mini_model[i] / 2, !(mini_model[i] % 2)));
////            cout << mini_model[i] / 2 << " " << !(mini_model[i] % 2) << endl;
////    }
////    s.addClause(cls);
////    }
    return 0;
}

vector<int> minimize_model(Solver& s, vector<int>& top_level_assignment){
    cout << "minimize_model" << endl;
    vector<Var> all_vars;
    vector<Var> vars_to_check;
    vector<Var> vars_in_min_model;
    for(int l : top_level_assignment){
        vars_in_min_model.push_back(l/2);
    }
    vector<int> clauses_refs_sat_by_propagation;

    // get all vars of s
    for(int i = 0; i < s.nVars(); i++){
        all_vars.push_back(i);
    }

    // check which vars are propagated and store them in min model and the rest to be checked later
//    for(Var x : all_vars){
//        if(s.vardata[x].level == 0) {
////            cout << x << endl;
////            vars_in_min_model.push_back(x);
//            vars_to_check.push_back(x);
//        }
//        else if(s.vardata[x].reason != CRef_Undef) {
////            cout << "Hello" << endl;
////            vars_in_min_model.push_back(x);
////            clauses_refs_sat_by_propagation.push_back(s.vardata[x].reason);
//            vars_to_check.push_back(x);
//        }
//        else {
//////            vars_in_min_model.push_back(x);
//            vars_to_check.push_back(x);
//        }
//    }

    // stores the refs of the clauses that didn't propagate assignments
    vector<int> clauses_refs_to_check;
    for(int i = 0; i < s.clauses.size(); i++){
        if(find(clauses_refs_sat_by_propagation.begin(), clauses_refs_sat_by_propagation.end(), s.clauses[i]) == clauses_refs_sat_by_propagation.end()){
            clauses_refs_to_check.push_back(s.clauses[i]);
        }
    }

    vector<int> clauses_idx_to_lits_count(clauses_refs_to_check.size(), 0);
    vector<vector<int>> lits_to_clauses_idx(all_vars.size() * 2);
    // store the relations between clauses refs and lits
    for(Var v : all_vars){
        int v_sign = toInt(s.modelValue(v));
        for(int i = 0; i < clauses_refs_to_check.size(); i++){
            Clause& cls = s.ca[clauses_refs_to_check[i]];
            for(int j = 0; j < cls.size(); j++){
                if(cls[j].x == v * 2 + v_sign){
                    clauses_idx_to_lits_count[i]++;
                    lits_to_clauses_idx[2 * v + v_sign].push_back(i);
                    break;
                }
            }
        }
    }

    // check which literals can be dropped of the model using the algorithm of the paper
    for(Var v : vars_to_check){
        int v_sign = toInt(s.model[v]);
        bool in_min_model = false;
        for(int i = 0; i < lits_to_clauses_idx[2 * v + v_sign].size(); i++){
            int cls_ref_idx = lits_to_clauses_idx[2 * v + v_sign][i];
            if(clauses_idx_to_lits_count[cls_ref_idx] == 1){
                vars_in_min_model.push_back(v);
                in_min_model = true;
                break;
            }
        }
        if(!in_min_model){
            for(int i = 0; i < lits_to_clauses_idx[2 * v + v_sign].size(); i++){
                int cls_ref_idx = lits_to_clauses_idx[2 * v + v_sign][i];
                clauses_idx_to_lits_count[cls_ref_idx]--;
            }
        }
    }

    vector<int> rv;
    std::sort(vars_in_min_model.begin(), vars_in_min_model.end());
    for(int i = 0; i < vars_in_min_model.size(); i++){
        int sign = s.modelValue(vars_in_min_model[i]) == l_False;
//        cout << vars_in_min_model[i] << " -> " << sign << endl;
        rv.push_back(vars_in_min_model[i] * 2 + sign);
    }
    return rv;
}

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

void implied_w(Solver& s, Lit l, vector<int>& model, vector<Lit>& min_model){
    vec<Solver::Watcher>& w_l = s.watches[~l];
    for(int i = 0; i < w_l.size(); i++){
//        cout << i << endl;
        Solver::Watcher w = w_l[i];
        CRef cref = w.cref;
        HDL_clause(s, i, cref, l, model, min_model);
    }
}

void implied_w_0(Solver& s, vector<int>& model, vector<Lit>& min_model){
    for(int i = 0; i < model.size(); i++){
//        cout << i << endl;
        Lit l = mkLit(model[i] / 2, model[i] % 2);
//        bool in_min_model = false;
//        for(int j = 0; j < min_model.size(); j++){
//            if(l.x == min_model[j].x) {
//                in_min_model = true;
//                break;
//            }
//        }
//        if(in_min_model) continue;
        implied_w(s, ~l, model, min_model);
    }
}

// zero represents true, while one represents false
vector<int> minimize_model2(Solver& s){
    cout << "minimize_model2" << endl;
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

bool verify_model(vector<int> &mini_model, Solver &s) {
    for(int i = 0; i < s.clauses.size(); i++){
        CRef cref = s.clauses[i];
        Clause& cls = s.ca[cref];
        bool sat_cls = false;
        for(int j = 0; j < cls.size(); j++){
//            cout << cls[j].x << " ";
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
//        cout << endl;
    }
    return true;
}
