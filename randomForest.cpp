#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include "tree.h"
#include "randomForest.h"

Forest::Forest(vector<vector<string>> dataset){
    
}

Forest::Forest(vector<vector<vector<string>>> baggedDatasets){
    datasets = baggedDatasets;
}

Forest::Forest(vector<vector<vector<string>>> baggedDatasets, string pm, string c){
    datasets = baggedDatasets;
    pruneMethod = pm;
    criterion = c;
}

void Forest::setSplitCriterion(string c){
    criterion = c;
}

void Forest::setPruneMethod(string m){
    pruneMethod = m;
}

