#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include <sstream> // stringstream
#include "node.h"

using namespace std;


class Tree {

    public:
        int node_count;
        int depth;

        Tree(vector<vector<string>> data);
        Tree(string csv_file);
        ~Tree();

        void train();
        // string test();
        string predict(vector<string> features);
        void setSplitCriterion(string criterion);


    private:
        Node* root;
        vector<Node *> nodes;
        Node* returnCorrectChild(Node* parent, string targetLabel);
        
    
};
