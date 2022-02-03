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


class DataFrame{
    //Implement system efficient access/edit/deletion methods
    
};

vector<vector<string>> read_csv(string filename);

void printDataFrame(vector<vector<string>> data);

void printColumns(vector<string> data);

pair<vector<vector<string>>, vector<string>> seperateTargets(vector<vector<string>> data, int targetIndex);

pair<vector<string>, vector<vector<string>>> seperateHeader(vector<vector<string>> data);

vector<vector<string>> shuffleDataFrame(vector<vector<string>> data);

pair<vector<vector<string>>, vector<vector<string>>> train_test_split(vector<vector<string>> data, float trainRatio);

vector<vector<vector<string>>> attribute_based_split(vector<vector<string>> data, int attribute, vector<string> values);

vector<string> getUniqueAttributes(vector<vector<string>> data, int attribute);

double getGain(vector<vector<string>> data, string criterion, int attribute, int target);

double getGini(vector<vector<string>> data, int target);

double getEntropy(vector<vector<string>> data, int target);

double getMisclassificationError(vector<vector<string>> data, int target);

vector<vector<vector<string>>> attribute_based_filter(vector<vector<string>> data, int attribute);

pair<string, vector<vector<string>>> attribute_based_split_labelled(vector<vector<string>> data, int attribute, string value);

vector<pair<string, vector<vector<string>>>> attribute_based_split_labelled_all(vector<vector<string>> data, int attribute);

int getMaxGainIndex(vector<vector<string>> data, string criterion, int target);

void println(string s);

void print(string s);

void println(int s);

void print(int s);

void println(float s);

void print(float s);

void println(double s);

void print(double s);

void println(short s);

void print(short s);

void println(long s);

void print(long s);


