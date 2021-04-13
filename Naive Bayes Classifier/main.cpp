#include "bayes.h"
#include <fstream>
#include <iostream>

using namespace std;
int main(int argc, char** argv)
{
    if (argc < 4)
    {
        cout << "No enough files provided!";
        return -1;
    }
    Bayes bayes;

    string train = argv[1], classify = argv[2], output = argv[3];

    // training process
    ifstream in_train(train);
    int n;
    in_train >> n;
    string a;
    getline(in_train, a);
    for (int i = 0; i < n; i++)
    {
        string t;
        getline(in_train, t);
        bayes.train(t);
    }
    in_train.close();

    // classify
    ifstream in_classify(classify);
    ofstream out(output);
    in_classify >> n;
    getline(in_classify, a);
    for (int i = 0; i < n; i++)
    {
        string t;
        getline(in_classify, t);
        string result = bayes.guess(t);
        out << result << endl;
    }
    in_classify.close();
    out.close();
}