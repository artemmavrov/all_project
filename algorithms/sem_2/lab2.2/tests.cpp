#include "hashing.cpp"

using namespace std;

//tests in progress
int main() {
    std::vector<Sample> trainData, validData;
    read_csv("C:/Users/artem/Desktop/labs/algoritms/lab2.2/entrypoint/data_train.csv", trainData);
    read_csv("C:/Users/artem/Desktop/labs/algoritms/lab2.2/entrypoint/dataset.csv", validData);
    
    LogisticRegression model;
    model.train(trainData, validData);

    vector<double> metrics = model.evaluate(validData);
    cout << "TP: " << metrics[0] << ", TN: " << metrics[1]
          << ", FP: " << metrics[2] << ", FN: " << metrics[3] << std::endl;
 }