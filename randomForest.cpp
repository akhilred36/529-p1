#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include "tree.h"
#include "randomForest.h"
#include "pythonpp.h"

Forest::Forest(vector<vector<string>> dataset, int target, int numBags, int minFeatureSize, string pruneMethod, string splitCriterion){
    datasetIndices = bagFeaturesIndices(dataset, target, numBags, minFeatureSize);
    datasetIndices = bagFeaturesIndices(dataset, target, numBags, minFeatureSize);
    datasets = bagFeatures(dataset, datasetIndices);
    for(int i=0; i<numBags; i++){
        trees.push_back(Tree(datasets.at(i)));
        trees.at(i).setSplitCriterion(splitCriterion);
    }
}

Forest::Forest(vector<vector<string>> dataset, int target, int numBags, int minFeatureSize){
    datasetIndices = bagFeaturesIndices(dataset, target, numBags, minFeatureSize);
    datasets = bagFeatures(dataset, datasetIndices);
    for(int i=0; i<numBags; i++){
        trees.push_back(Tree(datasets.at(i)));
        trees.at(i).setSplitCriterion("gini");
    }
}

void Forest::train(){
    if((int) trees.size() == 0){
        cout << "Error. No trees initialized." << endl;
        return;
    }
    else{
        for(int i=0; i<trees.size(); i++){
            trees.at(i).train();
        }
        return;
    }
}

string Forest::predict(vector<string> input){
    string result;
    vector<pair<string, int>> votes;
    for(int i=0; i<trees.size(); i++){
        vector<string> filteredFeatures;
        for(int j=0; j<datasetIndices.at(i).size() - 1; j++){ //Exclude target index
            filteredFeatures.push_back((string) input.at(datasetIndices.at(i).at(j)));
        }
        string prediction = trees.at(i).predict(filteredFeatures);
        bool found = false;
        for(int j=0; j<votes.size(); j++){
            if(votes.at(j).first.compare(prediction) == 0){
                found = true;
                votes.at(j).second = votes.at(j).second + 1;
            }
        }
        if(!found){
            pair<string, int> tmp;
            tmp.first = prediction;
            tmp.second = 1;
            votes.push_back(tmp);
        }
    }
    int maxVotes = 0;
    for(int i=0; i<votes.size(); i++){
        if(votes.at(i).second > maxVotes){
            result = votes.at(i).first;
            maxVotes = votes.at(i).second;
        }
    }
    if(maxVotes == 0){
        cout << "Error. Max vote is 0";
        return "0";
    }
    return result;
}

void Forest::setSplitCriterion(string c){
    criterion = c;
}

void Forest::setPruneMethod(string m){
    pruneMethod = m;
}

