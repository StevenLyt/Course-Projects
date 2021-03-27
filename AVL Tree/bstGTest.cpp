#include "bst.h"
#include "gtest/gtest.h"
#include <vector>

#include <iostream>
using namespace std;

class BstGTest : public testing::Test {
protected:

	BstGTest() : bst() {
	}

	virtual ~BstGTest() {
	}

	virtual void SetUp() {
		pair<int, char> pair8(8, 'D');
        pair<int, char> pair4(4, 'B');
        pair<int, char> pair12(12, 'F');
        pair<int, char> pair2(2, 'A');
        pair<int, char> pair6(6, 'C');
        pair<int, char> pair10(10, 'E');
        bst.insert(pair8);
        bst.insert(pair4);
        bst.insert(pair12);
        bst.insert(pair2);
        bst.insert(pair6);
        bst.insert(pair10);
	}

	virtual void TearDown() {
	}

	BinarySearchTree<int, char> bst;
};

TEST_F(BstGTest, InsertNominal) {
    int keyNum = 2;
    BinarySearchTree<int, char>::iterator it;
    for (it = bst.begin(); it != bst.end(); ++it) {
        EXPECT_EQ(keyNum, it->first);
        keyNum += 2;
    }
}

TEST_F(BstGTest, InsertUpdate) {
    // 12, F --> 12, G
    char val = 'A';
    int keyNum = 2;
    pair<int, char> newPair12(12, 'G');
    bst.insert(newPair12);
    BinarySearchTree<int, char>::iterator it = bst.begin();
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(keyNum, it->first);
        EXPECT_EQ(val, it->second);
        ++it;
        keyNum += 2;
        val += 1;
    }
    EXPECT_EQ(12, it->first);
    EXPECT_EQ('G', it->second);
}

TEST_F(BstGTest, remove2Children) {
    bst.remove(8);
    // 2, 4, 6, 10, 12
    int keyNum = 2;
    BinarySearchTree<int, char>::iterator it = bst.begin();
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(keyNum, it->first);
        keyNum += 2;
        ++it;
    }
    EXPECT_EQ(10, it->first);
    ++it;
    EXPECT_EQ(12, it->first);
}

TEST_F(BstGTest, remove1Child) {
    // Promote Left child
    bst.remove(12);
    // 2, 4, 6, 8, 10
    BinarySearchTree<int, char>::iterator it = bst.begin();
    for (int i = 2; i <= 10; i += 2) {
        EXPECT_EQ(i, it->first);
        ++it;
    }
    bst.remove(2);
    // Promote right child
    bst.remove(4);
    it = bst.begin();
    for (int i = 6; i <= 10; i += 2) {
        EXPECT_EQ(i, it->first);
        ++it;
    }
}

TEST_F(BstGTest, removeLeaf) {
    bst.remove(6);
    // 2, 4, 8, 10, 12
    BinarySearchTree<int, char>::iterator it = bst.begin();
    EXPECT_EQ(2, it->first);
    ++it;
    EXPECT_EQ(4, it->first);
    ++it;
    EXPECT_EQ(8, it->first);
    ++it;
    EXPECT_EQ(10, it->first);
    ++it;
    EXPECT_EQ(12, it->first);
}

TEST_F(BstGTest, isBalanced) {
    EXPECT_EQ(true, bst.isBalanced());
    bst.remove(4);
    //2, 6, 8, 10, 12
    pair<int, char> pair1(1, 'b');
    bst.insert(pair1);
    EXPECT_EQ(true, bst.isBalanced());
    bst.remove(6);
    pair<int, char> pair0(0, 'a');
    bst.insert(pair0);
    EXPECT_EQ(false, bst.isBalanced());
}

TEST_F(BstGTest, clear) {
    bst.clear();
    EXPECT_EQ(true, bst.empty());
}