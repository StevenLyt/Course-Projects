#include <string>
class Hashtable
{
public:
    // probing can take values 0, 1, 2
    // 0 means that your Hashtable must use linear probing,
    // 1 means quadratic probing,
    // and 2 means double hashing.
    Hashtable(bool debug = false, unsigned probing = 0);
    ~Hashtable();
    void add(std::string k);
    int count(std::string k) const;
    void reportAll(std::ostream&) const;

private:
    int hash(std::string k) const;            // hash function
    int double_hashing(std::string k) const;  // second hash function, only for double hashing

    void resize();

    int size;      // number of actual items
    int capacity;  // max capacity
    unsigned probing;
    bool debug;
    int capacity_index;                  // the index of current capacity in prime1[]
    std::pair<std::string, int>* table;  // stores data
    int primes1[28]
            = {11,       23,       47,       97,        197,       397,       797,       1597,      3203,    6421,
               12853,    25717,    51437,    102877,    205759,    411527,    823117,    1646237,   3292489, 6584983,
               13169977, 26339969, 52679969, 105359969, 210719881, 421439783, 842879579, 1685759167};
    int primes2[28]
            = {7,        19,       43,       89,        193,       389,       787,       1583,      3191,    6397,
               12841,    25703,    51431,    102871,    205721,    411503,    823051,    1646221,   3292463, 6584957,
               13169963, 26339921, 52679927, 105359939, 210719881, 421439749, 842879563, 1685759113};
    int r[5];  // for calculating hash function

    bool* empty;
};