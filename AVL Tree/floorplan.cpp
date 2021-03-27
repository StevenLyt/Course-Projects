#include "avlbst.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

struct Rectangle
{
    int ID;
    int length;
    int height;
};

// Typedefs for you input and output map. Start with
// std::map but once the backtracking search algorithm is working
// try to use your AVL-tree map implementation by changing these
// typedef's
typedef AVLTree<int, Rectangle> InputMapType;
typedef AVLTree<int, std::pair<int, int>> OutputMapType;

// Allowed global variables: the dimensions of the grid
int n;  // X-dim size
int m;  // Y-dim size

// No other global variables are allowed

// A dummy operator << for Rectangles so the BST and AVL BST will
// compile with their printRoot() implementations
std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
    os << r.ID;
    return os;
}

// A dummy operator << for pairs so the BST and AVL BST will
// compile with their printRoot() implementations
template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p)
{
    os << p.first << "," << p.second;
    return os;
}

void printSolution(std::ostream& os, InputMapType& input, OutputMapType& output)
{
    for (OutputMapType::iterator it = output.begin(); it != output.end(); ++it)
    {
        InputMapType::iterator rbit = input.find(it->first);
        os << it->first << " ";
        os << it->second.first << " ";
        os << it->second.second << " ";
        os << rbit->second.length << " ";
        os << rbit->second.height << endl;
    }
}

// Changes the grid entries to their opposite values for the
// rectangle r starting at x1,y1
void flip(int x1, int y1, const Rectangle& r, vector<vector<bool>>& grid)
{
    for (int x = x1; x < x1 + r.length; x++)
    {
        for (int y = y1; y < y1 + r.height; y++)
            grid[x][y] = !grid[x][y];
    }
}

// TODO: Write your backtracking search function here

// check if the space where the rectangle is to be placed is empty
bool isValid(int x1, int y1, const Rectangle& r, vector<vector<bool>>& grid)
{
    if (x1 + r.length > n || y1 + r.height > m)
    {
        return false;
    }
    for (int i = x1; i < x1 + r.length; i++)
    {
        for (int j = y1; j < y1 + r.height; j++)
        {
            if (grid[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool plan(InputMapType::iterator it, vector<vector<bool>>& grid, int curr, int x, OutputMapType& pos)
{
    // reach the end
    if (curr == x)
    {
        return true;
    }

    // try all possible positions with both orientations
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!grid[i][j] && isValid(i, j, it->second, grid))
            {
                flip(i, j, it->second, grid);
                pos.insert(make_pair(it->first, make_pair(i, j)));
                InputMapType::iterator it_copy = it;
                if (plan(++it, grid, curr + 1, x, pos))
                {
                    return true;
                }
                it = it_copy;
                flip(i, j, it->second, grid);
                pos.remove(it->first);
            }

            // try the other orientation
            swap(it->second.length, it->second.height);
            if (!grid[i][j] && isValid(i, j, it->second, grid))
            {
                flip(i, j, it->second, grid);
                pos.insert(make_pair(it->first, make_pair(i, j)));
                InputMapType::iterator it_copy = it;
                if (plan(++it, grid, curr + 1, x, pos))
                {
                    return true;
                }
                it = it_copy;
                flip(i, j, it->second, grid);
                pos.remove(it->first);
            }
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "please specify an input and output file";
        return 0;
    }
    ifstream ifile(argv[1]);
    stringstream ss;
    string line;
    ofstream ofile(argv[2]);
    int x;
    getline(ifile, line);
    ss << line;
    ss >> n;
    ss >> m;
    ss >> x;

    InputMapType input;
    OutputMapType output;
    for (int i = 0; i < x; i++)
    {
        getline(ifile, line);
        stringstream ss2(line);
        Rectangle r;
        ss2 >> r.ID;
        ss2 >> r.length;
        ss2 >> r.height;
        input.insert(std::make_pair(r.ID, r));
    }
    ifile.close();
    vector<vector<bool>> grid;

    for (int i = 0; i < n; i++)
    {
        grid.push_back(vector<bool>(m, false));
    }
    InputMapType::iterator it = input.begin();
    bool solution_exists = false;

    // TODO:  Call your backtracking search function here]
    int sum = 0;
    for (; it != input.end(); ++it)
    {
        sum += it->second.length * it->second.height;
    }
    it = input.begin();
    if (sum <= n * m)
    {
        solution_exists = plan(it, grid, 0, x, output);
    }
    if (!solution_exists)
    {
        ofile << "No solution found.";
    }
    else
    {
        printSolution(ofile, input, output);
    }
    ofile.close();
    return 0;
}