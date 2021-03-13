#include <fstream>
#include <iostream>
using namespace std;

class ColorMap
{
public:
    ColorMap(int countries, int row, int col);
    ~ColorMap();
    void fill(std::istream& in);  // fill in map with input values
    void preCheck();              // fill in adjacent with 1 or 0 by going through map
    bool coloring(int index);     // actual coloring process
    bool isValid();               // check whether no bordering countries share same color
    void printColor();

private:
    int countries;
    int row;
    int col;
    char** map;
    int* way_of_color;
    bool** adjacent;
    void helper(int r, int c);
};

ColorMap::ColorMap(int countries, int row, int col) : countries(countries), row(row), col(col)
{
    map = new char*[row];
    for (int i = 0; i < row; i++)
    {
        map[i] = new char[col];
    }
    way_of_color = new int[countries];
    for (int i = 0; i < countries; i++)
    {
        way_of_color[i] = 0;
    }
}

ColorMap::~ColorMap()
{
    for (int i = 0; i < row; i++)
    {
        delete [] map[i];
    }
    delete [] map;

    for (int i = 0; i < countries; i++)
    {
        delete [] adjacent[i];
    }
    delete [] adjacent;
    delete [] way_of_color;
}

void ColorMap::fill(std::istream& in)
{
    for (int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            in >> map[i][j];
        }
    }
}

void ColorMap::preCheck()
{
    adjacent = new bool*[countries];
    for (int i = 0; i < countries; i++)
    {
        adjacent[i] = new bool[countries];
        for (int j = 0; j < countries; j++)
        {
            adjacent[i][j] = false;
        }

    }
    helper(0, 0);
}

void ColorMap::helper(int r, int c)
{
    if (r == row - 1 && c != col - 2)
        return;

    if (c == col - 1 && r != row - 2)
        return;

    if (r == row - 1)
    {
        char curr = map[r][c];
        char right = map[r][c + 1];
        if (right != curr)
        {
            adjacent[curr - 'A'][right - 'A'] = true;
            adjacent[right - 'A'][curr - 'A'] = true;
        }
        return;
    }
    if (c == col - 1)
    {
        char curr = map[r][c];
        char down = map[r + 1][c];
        if (down != curr)
        {
            adjacent[curr - 'A'][down - 'A'] = true;
            adjacent[down - 'A'][curr - 'A'] = true;
        }
        return;
    }

    char curr = map[r][c];
    char down = map[r + 1][c];
    char right = map[r][c + 1];
    if (down != curr)
    {
        adjacent[curr - 'A'][down - 'A'] = true;
        adjacent[down - 'A'][curr - 'A'] = true;
    }
    if (right != curr)
    {
        adjacent[curr - 'A'][right - 'A'] = true;
        adjacent[right - 'A'][curr - 'A'] = true;
    }
    helper(r + 1, c);
    helper(r, c + 1);
}

bool ColorMap::coloring(int index)
{
    if (index == countries)
        return true;

    for (int i = 1; i <= 4; i++)
    {
        way_of_color[index] = i;
        if (isValid() && coloring(index + 1))
            return true;
        way_of_color[index] = 0;
    }
    return false;
}

bool ColorMap::isValid()
{
    for (int i = 0; i < countries; i++)
    {
        for (int j = i + 1; j < countries; j++)
        {
            if (way_of_color[i] != 0 && adjacent[i][j] && way_of_color[i] == way_of_color[j])
                return false;
        }
    }
    return true;
}

void ColorMap::printColor()
{
    for (int i = 0; i < countries; i++)
    {
        std::cout << char('A' + i) << " " << way_of_color[i] << std::endl;
    }
}

int main(int argc, char** argv)
{
    ifstream infile(argv[1]);
    int countries, row, col;
    infile >> countries >> row >> col;
    string s;
    getline(infile, s);
    ColorMap cm(countries, row, col);
    cm.fill(infile);

    cm.preCheck();
    cm.coloring(0);
    cm.printColor();
}