#include "pythonpp.h"
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

using namespace std;

vector<vector<string>> read_csv(string filename){ //From https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
    vector<vector<string>> result;
    ifstream myFile(filename); // Create an input filestream
    if(!myFile.is_open()) throw runtime_error("Could not open file"); // Make sure the file is open
    string line, attribute; // Helper vars
    if(myFile.good())
    {
        while(getline(myFile, line)){ // Extract the first line in the file
            vector<string> row;
            stringstream ss(line); // Create a stringstream from line
            while(getline(ss, attribute, ',')){ // Extract each column name
                row.push_back(attribute); // Push attributes to row
            }
            result.push_back(row); //Push rows to the result vector
        }
    }
    myFile.close(); // Close file
    return result;
}

//Print 2 dimensional dataframe
void printDataFrame(vector<vector<string>> data){
    for(int i=0; i<data.size(); i++){
        for(int j=0; j<data.at(i).size(); j++){
            cout << data.at(i).at(j) << " ";
        }
    cout << "\n";
    }
    return; 
}

//Print 1 dimensional row/column
void printColumns(vector<string> data){
    for(int i=0; i<data.size(); i++){
        cout << data.at(i) << " ";
    }
    cout << "\n";
}

//Separate attributes from target and return as a pair
pair<vector<vector<string>>, vector<string>> seperateTargets(vector<vector<string>> data, int targetIndex){
    pair<vector<vector<string>>, vector<string>> result;
    vector<string> targets;
    for(int i=0; i<data.size(); i++){
        vector<string> row;
        for(int j=0; j<data.at(i).size(); j++){
            if(j == targetIndex){
                targets.push_back(data.at(i).at(j));
            }
            else{
                row.push_back(data.at(i).at(j));
            }
        }
        result.first.push_back(row);
    }
    result.second = targets;
    return result;
}

//Separate column headers and return as a pair
pair<vector<string>, vector<vector<string>>> seperateHeader(vector<vector<string>> data){
    pair<vector<string>, vector<vector<string>>> result;
    for(int i=0; i<data.size(); i++){
        vector<string> row;
        for(int j=0; j<data.at(i).size(); j++){
            row.push_back(data.at(i).at(j));
        }
        if(i == 0){
            result.first = row;
        }
        else{
            result.second.push_back(row);
        }
    }
    return result;
}

//Shuffle dataframe
vector<vector<string>> shuffleDataFrame(vector<vector<string>> data){
    auto rng = default_random_engine {};
    shuffle(data.begin(), data.end(), rng);
    return data;
}

//Split dataframe into train and test based on trainRatio(between 0 and 1)
pair<vector<vector<string>>, vector<vector<string>>> train_test_split(vector<vector<string>> data, float trainRatio){
    pair<vector<vector<string>>, vector<vector<string>>> result;
    int lastTrainIdx = (int) (trainRatio * (float) data.size());
    println(lastTrainIdx);
    for(int i=0; i<data.size(); i++){
        if(i < lastTrainIdx){
            result.first.push_back(data.at(i));
        }
        else{
            result.second.push_back(data.at(i));
        }
    }
    return result;
}

//Print wrappers - polymorphism for various data types
void println(string s){
    cout << s << endl;
}

void print(string s){
    cout << s;
}

void println(int s){
    cout << s << endl;
}

void print(int s){
    cout << s;
}

void println(float s){
    cout << s << endl;
}

void print(float s){
    cout << s;
}