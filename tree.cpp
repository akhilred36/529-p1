#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include "tree.h"





Tree::Tree(vector<vector<string>> data) {

    root = new Node("root", data);
    node_count = 1;
    nodes.push_back(root);

    // // Set static variables
    // Node::id_count = 0;
    // Node::criterion = "gini";          // By default
}

Tree::~Tree() {
    delete root;
}

void Tree::setSplitCriterion(string criterion) {
    Node::criterion = criterion;
}


void Tree::train() {
    int curr = 0;

    while (curr < node_count) {

        nodes.at(curr)->initializeChildren();
        

        if (nodes.at(curr)->isLeaf) {
            //printDataFrame(nodes.at(curr)->dataset.data);
            curr++;
            continue;
        }
        
        for (int i = 0; i < (int) nodes.at(curr)->children.size(); i++){ //  
            nodes.push_back(nodes.at(curr)->children.at(i));
            node_count++;
        }

        curr++;
        
    }
    print("Node count: ");
    println(node_count);

}

string Tree::predict(vector<string> features) {
    Node* curr = root;

    while (!curr->isLeaf) {
        curr = returnCorrectChild(curr, features.at(curr->attribute));
    }


    return curr->dataset.data.at(0).at(curr->target);   // solve this
}

Node* Tree::returnCorrectChild(Node* parent, string targetLabel) {

    for (int i = 0; i < parent->children.size(); i++){
        if (parent->children.at(i)->getLabel() == targetLabel) {
            return parent->children.at(i);
        }
    }

    return parent->children.at(0);
}


// Tree::test() {

// }

int main() {
    // Import Dataset
    vector<vector<string>> data = read_csv("train_refined.csv");

    pair<vector<vector<string>>, vector<vector<string>>> train_test = train_test_split(shuffleDataFrame(seperateHeader(data).second), 0.8);

    vector<vector<string>> train = train_test.first;
    vector<vector<string>> test = train_test.second;

    Tree t(train);

    t.setSplitCriterion("gini");

    t.train();

    int target_column = ((int) train.at(0).size()) - 1;   // Last column is target

    
    
    float correct = 0;
    float total = 0;

    pair<vector<vector<string>>, vector<string>> feature_label = seperateTargets(test, target_column);
    vector<vector<string>> X = feature_label.first;
    vector<string> Y = feature_label.second;


    for (int i = 0; i < (int) X.size(); i++) {
        if (t.predict(X.at(i)).compare(Y.at(i)) == 0) {
            correct = correct + 1;
        }

        total = total + 1;
    }  

    println("Test Acc.");
    println("------------------------------");
    print("Correct: ");
    println(correct);
    print("Total: ");
    println(total);
    print("Percent: ");
    println(correct / total);
    println("");

    correct = 0;
    total = 0;

    feature_label = seperateTargets(train, target_column);
    X = feature_label.first;
    Y = feature_label.second;


    for (int i = 0; i < (int) X.size(); i++) {
        if (t.predict(X.at(i)).compare(Y.at(i)) == 0) {
            correct = correct + 1;
        }

        total = total + 1;
    }

    println("Train Acc.");
    println("------------------------------");
    print("Correct: ");
    println(correct);
    print("Total: ");
    println(total);
    print("Percent: ");
    println(correct / total);





    return 0;
}