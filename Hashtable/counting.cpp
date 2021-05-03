#include "avlbst.h"
#include "hashtable.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 6)
    {
        cout << "Not enough information!";
        return -1;
    }

    string input = argv[1], output = argv[2];
    int x = atoi(argv[3]), d = atoi(argv[4]), r = atoi(argv[5]);

    // preprocessing
    ifstream in(input);
    vector<string> data;
    string temp;
    while (in >> temp)
    {
        string t;
        for (char c : temp)
        {
            if (isalpha(c))
                t += tolower(c);
        }
        if (!t.empty())
            data.push_back(t);
    }
    in.close();

    clock_t start;
    double duration;
    start = clock();

    ofstream out(output);

    // repeats r times
    for (int i = 0; i < r; i++)
    {
        Hashtable ht(d, x);
        AVLTree<string, int> mp;

        if (x != 3)
        {
            for (string& str : data)
                ht.add(str);
        }
        else
        {
            // AVL
            for (string& str : data)
            {
                auto it = mp.find(str);
                if (it != mp.end())
                {
                    it->second++;
                }
                else
                {
                    mp.insert(make_pair(str, 1));
                }
            }
        }
        if (i == r - 1)
        {
            duration = (clock() - start) / (double)CLOCKS_PER_SEC;
            // output the number of occurrences for all words
            if (x != 3)
            {
                ht.reportAll(out);
            }
            else
            {
                for (auto it = mp.begin(); it != mp.end(); ++it)
                {
                    out << it->first << " " << it->second << endl;
                }
            }
        }
    }
    cout << duration / r << endl;
    out.close();
}
