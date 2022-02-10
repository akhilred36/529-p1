#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>  
#include <stdexcept>  
#include <set>
#include "node.h"

using namespace std;

// Constructor intended for root node
Node::Node(string label, vector<vector<string>> data) {
    id_num = id_count;
    dataset.label = label;
    dataset.data = data;
    target = data.at(0).size() - 1;
    attribute = getMaxGainIndex(data, criterion, target);
    gain = getGain(data, criterion, attribute, target); 
    isLeaf = false;

    id_count = id_count + 1;                                     // Increment static variable

}

// Alternate constructor for non-root nodes
Node::Node(LabeledDataset data) {
    id_num = id_count;
    dataset = data;
    target = ((int) data.data.at(0).size()) - 1;
    isLeaf = false;
    attribute = getMaxGainIndex(data.data, criterion, target);
    gain = getGain(data.data, criterion, attribute, target);

    id_count++;                                                  // Increment static variable

    // If there are no more dvisions to make to the dataset, node is a leaf
    if ((getUniqueAttributes(data.data, target).size() == 1) || gain < 0.2) {
        isLeaf = true;
    }

}

Node::~Node() {
    // delete your children
    for (int i = 0; i < children.size(); i++) {
        delete children.at(i);
    }

}

bool vector<string> dataSetPurity(vector<vector<string>> data, int target) {
    vector<string>
}


void Node::initializeChildren() {
    if (isLeaf) {
        return;
    }

    
    vector<LabeledDataset> datasets = splitDataset(dataset);
    int n = (int) datasets.size();


    for (int i = 0; i < n; i++) {
        Node * child = new Node(datasets.at(i));

        children.push_back(child);
        
    }

    if (children.size() < 2) {
        isLeaf = true;
    }
}

vector<LabeledDataset> Node::splitDataset(LabeledDataset data) {
    vector<pair<string, vector<vector<string>>>> temp = attribute_based_split_labelled_all(data.data, attribute);

    vector<LabeledDataset> result;

    for (int i = 0; i < temp.size(); i = i + 1) {
        LabeledDataset subset;
        subset.label = temp[i].first;
        subset.data = temp[i].second;
        result.push_back(subset);
    }
     
    return result; 
}

int Node::getId() {
    return id_num;
}

string Node::getLabel() {
    return dataset.label;
}




// Set static variables
int Node::id_count = 0;
//int Node::target = 6; //data.at(0).size() - 1;
string Node::criterion = "misclassificationError";

// int main() {
//     // Import Dataset
//     vector<vector<string>> data = seperateHeader(read_csv("car_evaluation.csv")).second;
    
    

//     Node x("root", data);

//     x.initializeChildren();

//     return 0;
// }