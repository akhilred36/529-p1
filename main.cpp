#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include <sstream> // stringstream
#include <time.h>
#include <stdlib.h>
#include "tree.h"
#include "pythonpp.h"


using namespace std;

class DecisionTreeClassifier{

};


int main(){
    //Initialize vector of string vectors for the dataframe
    vector<vector<string>> data; 
    data = read_csv("car_evaluation.csv");
    pair<vector<string>, vector<vector<string>>> seperatedData = seperateHeader(data);
    vector<string> columns = seperatedData.first;
    vector<vector<string>> dataPoints = seperatedData.second;
    pair<vector<vector<string>>, vector<string>> attr_targets = seperateTargets(seperatedData.second, 6); 
    vector<vector<string>> shuffled = shuffleDataFrame(seperatedData.second);
    //printDataFrame(shuffled);
    pair<vector<vector<string>>, vector<vector<string>>> data_split = train_test_split(shuffled, 0.8);
    print("Length of Train data: ");
    int trainSize = data_split.first.size();
    println(trainSize);
    print("Length of Test data: ");
    int testSize = data_split.second.size();
    println(testSize);
    return 0;
}