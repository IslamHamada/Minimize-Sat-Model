# Sat Model minimizer. 
### It uses the state of a sat solver to turn a returned model into a minimal one.

It is based on the paper pseudocode provided in the following paper: Déharbe, D., Fontaine, P., Le Berre, D., & Mazure, B. (2013, October). Computing prime implicants. In 2013 Formal Methods in Computer-Aided Design (pp. 46-52). IEEE.

## Building The Project
The project requires two libraries:
1- A modified version of minisat2.2.0, a SAT solver, which is available in the repo,
2- EvalMaxSAT, which is a MaxSAT solver available on https://github.com/FlorentAvellaneda/EvalMaxSAT.

## The Main File
The main file contains all the needed functions. The main function reads a cnf file, computes a sat model for it, if it's satisfiable. Then applies the sat minimzing algorithm to shrink the model. It will also compute the smallest model using a MaxSat solver, then it compares the size of both minimal models and the time taken to compute each. The loaded cnf file can be changed by manually editing the address of the file read.
