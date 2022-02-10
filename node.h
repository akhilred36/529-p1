#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include <sstream> // stringstream
#include "pythonpp.h"

using namespace std;

// Holds subdatasets and their associated labels
struct LabeledDataset {
  string label;
  vector<vector<string>> data;
};

class Node{

    public:
        //Vector to hold node pointers
        static int id_count;
        static string criterion;
        int id_num;
        int target;
        
        Node * parent;
        double gain;
        vector<Node *> children;
        int attribute;
        struct LabeledDataset dataset;
        bool isLeaf;


        Node(string label, vector<vector<string>> data);

        Node(LabeledDataset data);

        ~Node();

        
        void initializeChildren();

        int getId();

        string getLabel();

    private:
        vector<LabeledDataset> splitDataset(LabeledDataset data);

        bool dataSetPurity(vector<vector<string>> data, int target);

};


// constructor 
// create/append child
// Utilize custom dataframe


// creates and trains decision tree 
// void train(vector<vector<string>> data){
// vector<pair<string, double>> impurities;

// }

// test performance (accuracy, precision, AUC)

// prune tree

// create/train RF/ensemble

// test RF

// get gini index

// Testing frameworks