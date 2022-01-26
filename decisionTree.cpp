#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include <sstream> // stringstream

using namespace std;

class DecisionTreeClassifier{

};

class Node{
    //pointers to other nodes
    //Vector to hold node pointers
};

class Tree{
    
};


//From https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
vector<vector<string>> read_csv(string filename){
    vector<vector<string>> result;
    // Create an input filestream
    ifstream myFile(filename);
    // Make sure the file is open
    if(!myFile.is_open()) throw runtime_error("Could not open file");

    // Helper vars
    string line;
    string attribute;
    
    if(myFile.good())
    {
        // Extract the first line in the file
        while(getline(myFile, line)){
            vector<string> row;
            // Create a stringstream from line
            stringstream ss(line);
            // Extract each column name
            while(getline(ss, attribute, ',')){
                // Push attributes to row
                row.push_back(attribute);
            }
            //Push rows to the result vector
            result.push_back(row);
        }
    }
    // Close file
    myFile.close();
    return result;
}

void printDataFrame(vector<vector<string>> data){
    for(int i=0; i<data.size(); i++){
        for(int j=0; j<data.at(i).size(); j++){
            cout << data.at(i).at(j) << " ";
        }
    cout << "\n";
    }
    return; 
}

void printColumns(vector<string> data){
    for(int i=0; i<data.size(); i++){
        cout << data.at(i) << " ";
    }
    cout << "\n";
}

pair<vector<vector<string>>, vector<string>> separateTargets(vector<vector<string>> data){
    pair<vector<vector<string>>, vector<string>> result;
    
}

//Separate column headers and return as a pair<>
pair<vector<string>, vector<vector<string>>> separateHeader(vector<vector<string>> data){
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


int main(){
    //Initialize vector of string vectors for the dataframe
    vector<vector<string>> data; 
    data = read_csv("car_evaluation.csv");
    //cout << "data: \n";
    //printDataFrame(data);
    cout << "Columns: \n";
    pair<vector<string>, vector<vector<string>>> seperatedData = separateHeader(data);
    vector<string> columns = seperatedData.first;
    vector<vector<string>> dataPoints = seperatedData.second;
    printColumns(columns);
    cout << "\n \n \n" << "Data points: \n";
    //printDataFrame(dataPoints);
    return 0;
}