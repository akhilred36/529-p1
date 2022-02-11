#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include "tree.h"

class Forest{
    public:
        int numTrees;
        string pruneMethod;
        string criterion;
        vector<vector<vector<string>>> datasets;

        Forest(vector<vector<string>> data);
        Forest(vector<vector<vector<string>>> baggedDatasets);
        Forest(vector<vector<vector<string>>> baggedDatasets, string pruneMethod, string criterion);
        ~Forest();

        void train();
        void setSplitCriterion(string criterion);
        void setPruneMethod(string method);
        string predict(vector<string> features);

    private:
        vector<Tree> trees;
};