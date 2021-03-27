#include "avlbst.h"
#include <iostream>

using namespace std;

int main()
{
    AVLTree<int, char> avl;

    // pair<int, char> pair10(10, 'B');
    // pair<int, char> pair11(11, 'B');
    // pair<int, char> pair20(20, 'B');
    // pair<int, char> pair25(25, 'B');
    // pair<int, char> pair26(26, 'B');
    // pair<int, char> pair24(24, 'B');
    // pair<int, char> pair28(28, 'B');

    // avl.insert(pair20);
    // avl.insert(pair10);
    // avl.insert(pair26);
    // avl.insert(pair11);
    // avl.insert(pair24);
    // avl.insert(pair28);
    // avl.insert(pair25);
    // avl.print();

    // cout << "removal ----------------------------------------------------------------" << endl;

    // // -----------------------Removal----------------------------
    // cout << "remove 20" << endl;
    // avl.remove(20);
    // avl.print();

    // // PPT insert exercises:
    // // 10, 20, 30, 15, 25, 12, 5, 3, 8
    // pair<int, char> pair10(10, 'B');
    // pair<int, char> pair20(20, 'B');
    // pair<int, char> pair30(30, 'B');
    // pair<int, char> pair15(15, 'B');
    // pair<int, char> pair25(25, 'B');
    // pair<int, char> pair12(12, 'B');
    // pair<int, char> pair5(5, 'B');
    // pair<int, char> pair3(3, 'B');
    // pair<int, char> pair8(8, 'B');
    // avl.insert(pair10);
    // avl.insert(pair20);
    // avl.insert(pair30);
    // avl.insert(pair15);
    // avl.insert(pair25);
    // avl.insert(pair12);
    // avl.insert(pair5);
    // avl.insert(pair3);
    // avl.insert(pair8);
    // avl.print();

    // cout << "insert 2" << endl;
    // pair<int, char> pair2(2, 'B');
    // avl.insert(pair2);
    // avl.print();

    // 20, 10, 30, 8, 15, 25, 35, 5, 12, 17, 28, 14

    pair<int, char> pair20(20, 'B');
    pair<int, char> pair10(10, 'B');
    pair<int, char> pair30(30, 'B');
    pair<int, char> pair8(8, 'B');
    pair<int, char> pair15(15, 'B');
    pair<int, char> pair25(25, 'B');
    pair<int, char> pair35(35, 'B');
    pair<int, char> pair5(5, 'B');
    pair<int, char> pair12(12, 'B');
    pair<int, char> pair17(17, 'B');
    pair<int, char> pair28(28, 'B');
    pair<int, char> pair14(14, 'B');
    avl.insert(pair20);
    avl.insert(pair10);
    avl.insert(pair30);
    avl.insert(pair8);
    avl.insert(pair15);
    avl.insert(pair25);
    avl.insert(pair35);
    avl.insert(pair5);
    avl.insert(pair12);
    avl.insert(pair17);
    avl.insert(pair28);
    avl.insert(pair14);
    avl.print();

    // Left-right zigzag
    cout << "remove 30: " << endl;

    avl.remove(30);
    avl.print();

    cout << "clear time!: " << endl;

    avl.clear();
    cout << boolalpha << avl.empty() << endl;

    return 0;
}