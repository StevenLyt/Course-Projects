#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>
#include <set>
#include <vector>

class MyDataStore : public DataStore
{
public:
    MyDataStore();
    virtual ~MyDataStore();

    virtual void addProduct(Product* p);

    virtual void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    virtual void dump(std::ostream& ofile);

    void addCart(std::string username, int hit);
    void viewCart(std::string username);
    void buyCart(std::string username);

private:
    std::set<Product*> products_;
    std::set<User*> users_;
    std::map<User*, std::vector<Product*>> carts_;
    std::vector<Product*> retainHit_;
};

#endif