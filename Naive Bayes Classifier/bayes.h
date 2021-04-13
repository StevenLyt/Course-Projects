#include <map>
#include <set>
#include <string>
class Bayes
{
public:
    Bayes();
    ~Bayes();
    // store one piece of info into the database and train it
    void train(std::string& s);
    // use the database to guess which object it could most possibly be
    std::string guess(std::string& s);
    // help debug
    void print();

private:
    // calculate the conditional probablity of classification given attributes
    double calculate(std::string object, std::set<std::string>& attributes);
    // stores the occurrence of each classification with each attribute
    std::map<std::string, std::map<std::string, int>> data_;
    // stores the occurrence of each classification
    std::map<std::string, int> class_count_;
};