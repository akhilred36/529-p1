# 529-p1
Decision Tree Classifier implementation in C++

# Compilation:
To compile the project, run  
``` bash
make rf
```

# Prediction
To train and predict using a single Decision Tree Classifier after compiling the project, run:  
``` bash
./rfTest.o <splitCriterion> 1 numFeatures <pruneMethod> <confidence> <trainDataset(csv)> <testDataset(csv)>
```
where numFeatures is the total number of features available listed in the training dataset - excludes the target. The output will be a .csv file titled "predictions.csv".

To train and predict using a Random Forest Classifier after compiling the project, run:
``` bash
./rfTest.o <splitCriterion> <numBags> <minAttrs> <pruneMethod> <confidence> <trainDataset(csv)> <testDataset(csv)>
```
The output will be a .csv file titled "predictions.csv".

# Options for hyperparameters
| Hyperparameter | Description | Options |  
| -------------- | ----------- | --------| 
| splitCriterion | Select method used to calculate information gain.| gini, entropy, misclassificationError |
| numBags | Set number of trees for the Random Forest| Integer > 0|
| minAttrs |  Minimum number of attributes to be passed into each tree. | Integer > 0|
| toggleChiSquared | Select method for pruning. Default checks for a class target purity threshold of 0.9 and prunes accordingly. | chiSquared, default |
| confidence | Set confidence measure for Chi Squared test if using it. | Real number [0, 1] |
| trainDataset(csv) | Select the name of the training dataset. It is assumed that the target column is the last column, and the file is in csv format that contains headers. | Name of the file *.csv |
| testDataset(csv) | Select the name of the testing dataset. It is assumed that the the file is in csv format that contains headers. | Name of the file *.csv |

# Optimal Configuration for data preprocessing and hyperparameter tuning
Run the following code for optimal results.  
Note: It is assumed that the input train and test datasets have been preprocessed such that the DNA sequence has been split into 60 separate features, with each feature being represented in a separate column. It is also assumed that the file contains headers and that the target column is the last column.  
``` bash
./rfTest.o entropy 24 3 chiSquared 0.98 <trainFile> <testFile> 
```