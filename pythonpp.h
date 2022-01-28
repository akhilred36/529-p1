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

void println(string s);

void print(string s);

void println(int s);

void print(int s);

void println(float s);

void print(float s);



