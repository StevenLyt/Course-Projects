#include "clothing.h"

#include "product.h"
#include "util.h"
#include <sstream>

using namespace std;

Clothing::Clothing(
        const std::string category,
        const std::string name,
        double price,
        int qty,
        const std::string size,
        const std::string brand)
        : Product(category, name, price, qty), size_(size), brand_(brand)
{
}

Clothing::~Clothing() {}

set<string> Clothing::keywords() const
{
    set<string> s = parseStringToWords(name_);
    set<string> t = parseStringToWords(brand_);
    s = setUnion(s, t);
    return s;
}

string Clothing::displayString() const
{
    stringstream ss;
    ss << name_ << "\n"
       << "Size: " << size_ << " Brand: " << brand_ << "\n"
       << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}