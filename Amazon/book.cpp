#include "book.h"

#include "product.h"
#include "util.h"
#include <sstream>

using namespace std;

Book::Book(
        const std::string category,
        const std::string name,
        double price,
        int qty,
        const std::string isbn,
        const std::string author)
        : Product(category, name, price, qty), author_(author), isbn_(isbn)
{
}

Book::~Book() {}

set<string> Book::keywords() const
{
    set<string> s = parseStringToWords(name_);
    set<string> t = parseStringToWords(author_);
    s = setUnion(s, t);
    s.insert(isbn_);
    return s;
}

string Book::displayString() const
{
    stringstream ss;
    ss << name_ << "\n"
       << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
       << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}