#include "bayes.h"

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>

using namespace std;

Bayes::Bayes() {}

Bayes::~Bayes() {}

void Bayes::print()
{
    for (auto it = data_.begin(); it != data_.end(); ++it)
    {
        std::cout << it->first << ":" << class_count_[it->first] << std::endl;
        auto sub = it->second;
        for (auto itt = sub.begin(); itt != sub.end(); ++itt)
        {
            std::cout << "(" << itt->first << " " << itt->second << ")";
        }
        std::cout << std::endl;
    }
}

void Bayes::train(string& s)
{
    stringstream ss(s);
    set<string> attributes;
    string object;
    ss >> object;
    // ignore duplicates
    while (!ss.eof())
    {
        string attribute;
        ss >> attribute;
        attributes.insert(attribute);
    }
    for (auto it = attributes.begin(); it != attributes.end(); ++it)
    {
        data_[object][*it]++;
    }
    class_count_[object]++;
}

string Bayes::guess(string& s)
{
    stringstream ss(s);
    double max_chance = 0;
    string max_object;
    // all attributes for guessing
    set<string> attributes;
    // ignore duplicates
    while (!ss.eof())
    {
        string attribute;
        ss >> attribute;
        attributes.insert(attribute);
    }

    // calcuate the conditional probablity of each object given these attributes
    for (auto it = data_.begin(); it != data_.end(); ++it)
    {
        double prob = calculate(it->first, attributes);
        if (prob > max_chance)
        {
            max_chance = prob;
            max_object = it->first;
        }
    }
    return max_object;
}

double Bayes::calculate(string object, set<string>& attributes)
{
    // P(object | attributes) = P(object & attributes) / P(attributes)
    // P(object & attributes) = P(object) * product(P(attribute | object))
    double numerator = class_count_[object];

    for (auto it = attributes.begin(); it != attributes.end(); ++it)
    {
        // Laplacian smoothing
        numerator *= (double)(1 + data_[object][*it]) / (1 + class_count_[object]);
    }

    // P(attributes) = sum(P(attributes & object))
    double denominator = 0;
    for (auto it = data_.begin(); it != data_.end(); ++it)
    {
        double t = class_count_[it->first];
        for (auto it_set = attributes.begin(); it_set != attributes.end(); ++it_set)
        {
            // Laplacian smoothing
            t *= (double)(1 + data_[it->first][*it_set]) / (1 + class_count_[it->first]);
        }
        denominator += t;
    }
    cout << numerator / denominator;
    return numerator / denominator;
}
