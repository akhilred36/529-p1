#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include <sstream> // stringstream

using namespace std;

namespace tree{

    class Node{
        //pointers to other nodes
        //Vector to hold node pointers
        int id;
        vector<Node *> children;
        string hypothesis;
        vector<string> hypothesis_choices;
        vector<vector<string>> subdataset;

        // constructor 
        // create/append child
        // Utilize custom dataframe
    };

    // creates and trains decision tree 
    void train(vector<vector<string>> data){
        vector<pair<string, double>> impurities;

    }

    // test performance (accuracy, precision, AUC)

    // prune tree

    // create/train RF/ensemble

    // test RF

    // get gini index

    // Testing frameworks


}

