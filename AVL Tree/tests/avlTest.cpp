#include "avlbst.h"
#include <iostream>

using namespace std;

int main()
{
    AVLTree<int, char> avl;

    // Nominal Insert
    pair<int, char> pair10(10, 'B');
    pair<int, char> pair12(12, 'C');
    pair<int, char> pair15(15, 'D');
    pair<int, char> pair20(20, 'E');
    pair<int, char> pair25(25, 'F');
    pair<int, char> pair30(30, 'G');
    avl.insert(pair20);
    avl.insert(pair12);
    avl.insert(pair30);
    avl.insert(pair10);
    avl.insert(pair15);
    avl.insert(pair25);
    avl.print();

    // Insert 5 (Left left zig-zig)
    pair<int, char> pair5(5, 'A');
    avl.insert(pair5);
    avl.print();

    // Insert 3 (Left left zig-zig)
    pair<int, char> pair3(3, 'z' - 3);
    avl.insert(pair3);
    avl.print();

    // Insert 24 (Left left zig-zig)
    cout << "insert 24" << endl;
    pair<int, char> pair24(24, 'q');
    avl.insert(pair24);
    avl.print();

    // Insert 8 (Right left zig-zag)
    cout << "insert 8" << endl;
    pair<int, char> pair8(8, 'z');
    // TODO
    avl.insert(pair8);
    avl.print();

    // Insert 13 (Left right zig-zag)
    pair<int, char> pair13(13, 'e');
    avl.insert(pair13);
    avl.print();

    // Insert-update 13
    cout << "pair value update" << endl;
    pair<int, char> pairUpdate(13, '*');
    avl.insert(pairUpdate);
    avl.print();

    cout << "removal----------" << endl;

    // -----------------------Removal----------------------------
    // Remove root
    cout << "Remove 20: " << endl;
    avl.remove(20);
    avl.print();

    // Leaf node
    cout << "Remove 12: " << endl;
    avl.remove(12);
    avl.print();

    // Leaf node: break-tie rotation
    cout << "Remove 13: " << endl;
    avl.remove(13);
    avl.print();

    // 1 child
    cout << "Remove 5: " << endl;
    avl.remove(5);
    avl.print();

    // Remove root: 2 children
    cout << "Remove 15: " << endl;
    avl.remove(15);
    avl.print();

    /* TODO:
     * cout
     */

    // Remove 8: right-left zig-zag
    cout << "Remove 8: " << endl;
    avl.remove(8);
    avl.print();

    cout << "Remove 24: " << endl;
    avl.remove(24);
    avl.print();
    cout << "Remove 25: " << endl;
    avl.remove(25);
    avl.print();

    cout << "remove 5" << endl;
    avl.remove(5);
    avl.print();

    cout << "remove 3" << endl;
    avl.remove(3);
    avl.print();

    cout << "remove 30" << endl;
    avl.remove(30);
    avl.remove(10);

    avl.print();
    cout << boolalpha << avl.empty() << endl;

    cout << "clear time!: " << endl;

    avl.clear();
    cout << boolalpha << avl.empty() << endl;

    return 0;
}