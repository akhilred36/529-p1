#include "pythonpp.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <math.h>

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

// get unique values of all attribute choices 
vector<string> getUniqueAttributes(vector<vector<string>> data, int attribute){
    vector<string> result;
    set<string> attr_set;
    for(int i=0; i<data.size(); i++){
        attr_set.insert(data.at(i).at(attribute));
    }
    result.assign(attr_set.begin(), attr_set.end());
    return result;
}

// cut out attribute column, and return k subsets based on k choices for said attribute
vector<vector<vector<string>>> attribute_based_split(vector<vector<string>> data, int attribute, vector<string> values){
    vector<vector<vector<string>>> result;
    for(int i=0; i<values.size(); i++){
        result.push_back(vector<vector<string>> {});
    }
    for(int i=0; i<data.size(); i++){
        for(int j=0; j<values.size(); j++){
            if(data.at(i).at(attribute).compare(values.at(j)) == 0){
                result.at(j).push_back(data.at(i));
            }
        }
    }
    return result;
}

//Returns singular pair of subdataset and attribute label based on the value passed in
pair<string, vector<vector<string>>> attribute_based_split_labelled(vector<vector<string>> data, int attribute, string value){
    pair<string, vector<vector<string>>> result;
    result.first = value;
    result.second = vector<vector<string>>{};
    for(int i=0; i<data.size(); i++){
        if(data.at(i).at(attribute).compare(value) == 0){
            result.second.push_back(data.at(i));
        }
    }
    return result;
}

//Returns all pairs of subdatasets based on all possible values of the attribute passed in.
vector<pair<string, vector<vector<string>>>> attribute_based_split_labelled_all(vector<vector<string>> data, int attribute){
    vector<pair<string, vector<vector<string>>>> result;
    vector<string> values = getUniqueAttributes(data, attribute);
    vector<vector<vector<string>>> all_subdatasets = attribute_based_split(data, attribute, values);
    for(int i=0; i<values.size(); i++){
        result.push_back(pair<string, vector<vector<string>>>{});
        result.at(i).first = values.at(i);
    }
    for(int i=0; i<all_subdatasets.size(); i++){
        for(int j=0; j<values.size(); j++){
            if(all_subdatasets.at(i).at(0).at(attribute).compare(values.at(j)) == 0){
                result.at(j).second = all_subdatasets.at(i);
            }
        }
    }
    return result;
}

// return sub-datasets, each containing homogeneous values for the chosen attribute
vector<vector<vector<string>>> attribute_based_filter(vector<vector<string>> data, int attribute){
    vector<vector<vector<string>>> result;
    vector<string> uniqueValues = getUniqueAttributes(data, attribute);
    for(int i=0; i<uniqueValues.size(); i++){
        result.push_back(vector<vector<string>> {});
    }
    for(int i=0; i<data.size(); i++){
        for(int j=0; j<uniqueValues.size(); j++){
            if((data.at(i).at(attribute)).compare(uniqueValues[j]) == 0){
                result.at(j).push_back(data.at(i));
            }
        }
    }
    return result;
}

// Get the misclassification error for a dataset, given the attribute's column id, and target's column id
double getMisclassificationError(vector<vector<string>> data, int target){
    vector<string> unq_targets = getUniqueAttributes(data, target);
    vector<double> counts;
    vector<double> probabilities;
    int total = data.size();
    for(int i=0; i<unq_targets.size(); i++){
        counts.push_back(0);
    }
    for(int i=0; i<data.size(); i++){
        for(int j=0; j<unq_targets.size(); j++){
            if((data.at(i).at(target)).compare(unq_targets[j]) == 0){
                counts[j] += 1;
            }
        }
    }
    for(int i=0; i<counts.size(); i++){
        probabilities.push_back(counts[i]/total);
    }
    double max = *max_element(probabilities.begin(), probabilities.end());
    return 1-max;
}

// Get the entropy measure for a dataset, given the attribute's column id, and target's column id
double getEntropy(vector<vector<string>> data, int target){
    vector<string> unq_targets = getUniqueAttributes(data, target);
    vector<double> counts;
    vector<double> probabilities;
    int total = data.size();
    for(int i=0; i<unq_targets.size(); i++){
        counts.push_back(0);
    }
    for(int i=0; i<data.size(); i++){
        for(int j=0; j<unq_targets.size(); j++){
            if((data.at(i).at(target)).compare(unq_targets[j]) == 0){
                counts[j] += 1;
            }
        }
    }
    for(int i=0; i<counts.size(); i++){
        probabilities.push_back(counts[i]/total);
    }
    double result = 0;
    for(int i=0; i<probabilities.size(); i++){
        result += (-1)*(log2(probabilities[i])*probabilities[i]);
    }
    return result;
}

// Get the Gini index for a dataset, given the attribute's column id, and target's column id
double getGini(vector<vector<string>> data, int target){
    vector<string> unq_targets = getUniqueAttributes(data, target);
    vector<double> counts;
    vector<double> probabilities;
    int total = data.size();
    for(int i=0; i<unq_targets.size(); i++){
        counts.push_back(0);
    }
    for(int i=0; i<data.size(); i++){
        for(int j=0; j<unq_targets.size(); j++){
            if((data.at(i).at(target)).compare(unq_targets[j]) == 0){
                counts[j] += 1;
            }
        }
    }
    for(int i=0; i<counts.size(); i++){
        probabilities.push_back(counts[i]/total);
    }
    double sum = 0;
    for(int i=0; i<probabilities.size(); i++){
        sum += (probabilities[i] * probabilities[i]);
    }
    double result = 1-sum;
    return result;
}

// Get the information gain for a dataset, given the attribute's column id, target's column id, and split criterion (gini or entropy)
double getGain(vector<vector<string>> data, string criterion, int attribute, int target){
    double result;
    int data_length = data.size();
    vector<string> classes = getUniqueAttributes(data, target);
    vector<string> attributes = getUniqueAttributes(data, attribute);
    int attributes_length = attributes.size();
    int length_classes = classes.size();
    if(criterion.compare("entropy") == 0){
        double impurity_parent = getEntropy(data, target);
        vector<vector<vector<string>>> subDatasets = attribute_based_filter(data, attribute);
        double sum = 0;
        for(int i=0; i<subDatasets.size(); i++){
            double entropy = getEntropy(subDatasets.at(i), target);
            double calc = (((double) (subDatasets.at(i)).size())/(double) data.size())*entropy;
            sum += calc;
        }
        result = impurity_parent - sum;
        return result;
    }
    else if(criterion.compare("gini") == 0){
        double impurity_parent = getGini(data, target);
        vector<vector<vector<string>>> subDatasets = attribute_based_filter(data, attribute);
        double sum = 0;
        for(int i=0; i<subDatasets.size(); i++){
            double gini = getGini(subDatasets.at(i), target);
            sum += (((double)(subDatasets.at(i)).size())/(double) data.size()) * gini;
        }
        result = impurity_parent - sum;
        return result;
    }
    else if(criterion.compare("misclassificationError") == 0){
        double impurity_parent = getMisclassificationError(data, target);
        vector<vector<vector<string>>> subDatasets = attribute_based_filter(data, attribute);
        double sum = 0;
        for(int i=0; i<subDatasets.size(); i++){
            double me = getMisclassificationError(subDatasets.at(i), target);
            sum += ((double) ((subDatasets.at(i)).size())/(double) data.size()) * me;
        }
        result = impurity_parent - sum;
        return result;
    }
    else{
        println("Invalid split criterion. Returning 0");
        return 0;
    }
    return result;
}

//Returns child's index with maximum information gain
int getMaxGainIndex(vector<vector<string>> data, string criterion, int target){
    vector<double> gains;
    for(int i=0; i<data.at(0).size(); i++){
        if(i != target){
            gains.push_back(getGain(data, criterion, i, target));
            print("Gain: ");
            println((float) gains[i]);
        }
    }
    int maxElementIndex = max_element(gains.begin(),gains.end()) - gains.begin();
    return maxElementIndex;
}

double chiSquaredLookup(double degreeFreedom, double alpha){

}

//incomplete. still need to calculate expected counts
double chiSquaredValue(vector<vector<string>> parentData, int attribute, double confidence, int target){
    vector<string> classes = getUniqueAttributes(parentData, target);
    vector<string> unqValues = getUniqueAttributes(parentData, attribute);
    int numClasses = classes.size();
    int numValues = unqValues.size();
    vector<pair<string, int>> classCountParent;
    for(int i=0; i<classes.size(); i++){
        pair<string, int> temp;
        temp.first = classes.at(i);
        temp.second = 0;
        classCountParent.push_back(temp);
    }
    for(int i=0; i<parentData.size(); i++){
        for(int j=0; j<classCountParent.size(); j++){
            if(parentData.at(i).at(target).compare(classCountParent.at(j).first) == 0){
                classCountParent.at(j).second = classCountParent.at(j).second + 1;
            }
        }
    }
    vector<pair<string, vector<vector<string>>>> splitData_all = attribute_based_split_labelled_all(parentData, attribute);
    vector<pair<pair<string, string>, double>> expectedCounts;
    vector<pair<pair<string, string>, double>> realCounts;

    for(int i=0; i<splitData_all.size(); i++){
        string child_attr = splitData_all.at(i).first;
        vector<pair<string, vector<vector<string>>>> subSplitData_all = attribute_based_split_labelled_all(splitData_all.at(i).second, target-1);
        for(int j=0; j<subSplitData_all.size(); j++){
            pair<string, string> tempStringPair;
            tempStringPair.first = child_attr;
            tempStringPair.second = subSplitData_all.at(j).first;
            pair<pair<string, string>, double> countPair;
            countPair.first = tempStringPair;
            countPair.second = (double) 0;
            expectedCounts.push_back(countPair);
            realCounts.push_back(countPair);
        }
    }
    for(int i=0; i<splitData_all.size(); i++){
        string attr = splitData_all.at(i).first;
        for(int j=0; j<classes.size(); j++){
            string class_ = classes.at(j);
            for(int k=0; k<realCounts.size(); k++){
                if(((realCounts.at(k).first.first).compare(attr) == 0) && ((realCounts.at(k).first.second).compare(class_) == 0)){
                    realCounts.at(k).second = realCounts.at(k).second + 1;
                }
            }
        }
    }
}

bool chiSquaredTest(vector<vector<string>> parentData, int attribute, double confidence, int target){
    double alpha = 1 - confidence;

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

void println(short s){
    cout << s << endl;
}

void print(short s){
    cout << s;
}

void println(long s){
    cout << s << endl;
}

void print(long s){
    cout << s;
}

void println(float s){
    cout << s << endl;
}

void print(float s){
    cout << s;
}

void println(double s){
    cout << s << endl;
}

void print(double s){
    cout << s;
}
