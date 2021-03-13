#include "mydatastore.h"

#include "product.h"
#include "user.h"
#include "util.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct ProdNameSorter
{
    bool operator()(Product* p1, Product* p2) { return (p1->getName() < p2->getName()); }
};
MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore()
{
    for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
    {
        delete *it;
    }
    for (set<User*>::iterator it = users_.begin(); it != users_.end(); ++it)
    {
        delete *it;
    }
}

void MyDataStore::addProduct(Product* p) { products_.insert(p); }

void MyDataStore::addUser(User* u) { users_.insert(u); }

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    map<string, set<Product*>> mapping;
    for (unsigned int i = 0; i < terms.size(); i++)
    {
        string term = terms[i];
        for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
        {
            set<string> key = (*it)->keywords();
            if (key.find(term) != key.end())
            {
                mapping[term].insert(*it);
            }
        }
    }

    set<Product*> final = mapping.begin()->second;
    // Or
    if (type)
    {
        for (map<string, set<Product*>>::iterator it = mapping.begin(); it != mapping.end(); ++it)
        {
            final = setUnion(final, it->second);
        }
    }
    // And
    else
    {
        for (map<string, set<Product*>>::iterator it = mapping.begin(); it != mapping.end(); ++it)
        {
            final = setIntersection(final, it->second);
        }
    }

    vector<Product*> result(final.begin(), final.end());

    if (result.begin() != result.end())
    {
        sort(result.begin(), result.end(), ProdNameSorter());
    }
    retainHit_ = result;

    return result;
}

/**
 * Reproduce the database file from the current Products and User values
 */
// need modify
void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << endl;
    for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
    {
        (*it)->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for (set<User*>::iterator it = users_.begin(); it != users_.end(); ++it)
    {
        (*it)->dump(ofile);
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addCart(string username, int hit)
{
    for (set<User*>::iterator it = users_.begin(); it != users_.end(); ++it)
    {
        if (convToLower((*it)->getName()) == username)
        {
            carts_[*it].push_back(retainHit_[hit - 1]);
        }
    }
}

void MyDataStore::viewCart(string username)
{
    for (set<User*>::iterator it = users_.begin(); it != users_.end(); ++it)
    {
        if (convToLower((*it)->getName()) == username)
        {
            for (unsigned int i = 0; i < carts_[*it].size(); i++)
            {
                cout << "Item " << i + 1 << endl;
                cout << carts_[*it][i]->displayString();
                cout << endl;
            }
            return;
        }
    }

    cout << "Invalid username" << endl;
    return;
}

void MyDataStore::buyCart(std::string username)
{
    for (set<User*>::iterator it = users_.begin(); it != users_.end(); ++it)
    {
        if (convToLower((*it)->getName()) == username)
        {
            for (unsigned int i = 0; i < carts_[*it].size(); i++)
            {
                if (carts_[*it][i]->getQty() > 0 && (*it)->getBalance() >= carts_[*it][i]->getPrice())
                {
                    carts_[*it][i]->subtractQty(1);
                    (*it)->deductAmount(carts_[*it][i]->getPrice());
                    carts_[*it].erase(carts_[*it].begin() + i);
                    i--;
                }
            }
            return;
        }
    }

    cout << "Invalid username" << endl;
    return;
}
