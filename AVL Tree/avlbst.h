#ifndef RBBST_H
#define RBBST_H

#include "bst.h"
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

struct KeyError
{
};

/**
 * A special kind of node for an AVL tree, which adds the height as a data member, plus
 * other additional helper functions. You do NOT need to implement any functionality or
 * add additional data members or helper functions.
 */
template<typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
 * An explicit constructor to initialize the elements by calling the base class constructor and setting
 * the color to red since every new node will be red when it is first inserted.
 */
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
        : Node<Key, Value>(key, value, parent), height_(1)
{
}

/**
 * A destructor which does nothing.
 */
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{
}

/**
 * A getter for the height of a AVLNode.
 */
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
 * A setter for the height of a AVLNode.
 */
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
 * An overridden function for getting the parent since a static_cast is necessary to make sure
 * that our node is a AVLNode.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}

/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/

template<class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert(const std::pair<const Key, Value>& new_item);  // TODO
    virtual void remove(const Key& key);                               // TODO
protected:
    virtual void nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key, Value>* curr, AVLNode<Key, Value>* parent);
    void removeFix(AVLNode<Key, Value>* curr);
    void rotateLeft(AVLNode<Key, Value>* curr);
    void rotateRight(AVLNode<Key, Value>* curr);
};

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* curr)
{
    // six pointer relatioship need to be adjusted
    AVLNode<Key, Value>* child = curr->getRight();

    // curr's right child
    // child's left child's parent
    if (child->getLeft() != NULL)
    {
        child->getLeft()->setParent(curr);
        curr->setRight(child->getLeft());
    }
    else
    {
        curr->setRight(NULL);
    }

    // child's parent
    // curr's parent's child
    if (curr->getParent() != NULL)
    {
        AVLNode<Key, Value>* parent = curr->getParent();
        child->setParent(parent);
        if (parent->getLeft() == curr)
        {
            parent->setLeft(child);
        }
        else
        {
            parent->setRight(child);
        }
    }
    else
    {
        child->setParent(NULL);
    }

    // curr's parent
    // child's left child
    curr->setParent(child);
    child->setLeft(curr);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* curr)
{
    // six pointer relatioship need to be adjusted
    AVLNode<Key, Value>* child = curr->getLeft();

    // curr's left child
    // child's right child's parent
    if (child->getRight() != NULL)
    {
        child->getRight()->setParent(curr);
        curr->setLeft(child->getRight());
    }
    else
    {
        curr->setLeft(NULL);
    }

    // child's parent
    // curr's parent's child
    if (curr->getParent() != NULL)
    {
        AVLNode<Key, Value>* parent = curr->getParent();
        child->setParent(parent);
        if (parent->getLeft() == curr)
        {
            parent->setLeft(child);
        }
        else
        {
            parent->setRight(child);
        }
    }
    else
    {
        child->setParent(NULL);
    }

    // curr's parent
    // child's right child
    curr->setParent(child);
    child->setRight(curr);
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* curr, AVLNode<Key, Value>* parent)
{
    if (parent == NULL || parent->getParent() == NULL)
    {
        return;
    }

    AVLNode<Key, Value>* grand = parent->getParent();
    int grand_height;
    if (grand->getLeft() == NULL && grand->getRight() == NULL)
    {
        grand_height = 1;
    }
    else if (grand->getLeft() == NULL)
    {
        grand_height = grand->getRight()->getHeight() + 1;
    }
    else if (grand->getRight() == NULL)
    {
        grand_height = grand->getLeft()->getHeight() + 1;
    }
    else
    {
        grand_height = std::max(grand->getLeft()->getHeight(), grand->getRight()->getHeight()) + 1;
    }

    // case 1: g height doesn't change, done
    if (grand->getHeight() == grand_height)
    {
        return;
    }

    // case 2: g is balance, continue to call insert_fix(parent, grand)
    grand->setHeight(grand_height);
    if (grand->getLeft() == NULL)
    {
        if (grand->getRight()->getHeight() == 1)
        {
            insertFix(parent, grand);
            return;
        }
    }
    else if (grand->getRight() == NULL)
    {
        if (grand->getLeft()->getHeight() == 1)
        {
            insertFix(parent, grand);
            return;
        }
    }
    else if (abs(grand->getLeft()->getHeight() - grand->getRight()->getHeight()) <= 1)
    {
        insertFix(parent, grand);
        return;
    }
    // case 3: g is unbalance, fix it, and done

    // zig-zig
    // rotateRight(g)
    if (grand->getLeft() == parent && parent->getLeft() == curr)
    {
        rotateRight(grand);
        grand->setHeight(grand->getHeight() - 2);
        parent->setHeight(std::max(parent->getLeft()->getHeight(), parent->getRight()->getHeight()) + 1);
    }
    // rotateLeft(g)
    else if (grand->getRight() == parent && parent->getRight() == curr)
    {
        rotateLeft(grand);
        grand->setHeight(grand->getHeight() - 2);
        parent->setHeight(std::max(parent->getLeft()->getHeight(), parent->getRight()->getHeight()) + 1);
    }
    // zig-zag
    // rotateLeft(p) then rotateRight(g)
    else if (grand->getLeft() == parent && parent->getRight() == curr)
    {
        rotateLeft(parent);
        rotateRight(grand);
        grand->setHeight(grand->getHeight() - 2);
        parent->setHeight(parent->getHeight() - 1);
        curr->setHeight(std::max(curr->getLeft()->getHeight(), curr->getRight()->getHeight()) + 1);
    }
    // rotateRight(p) then rotateLeft(g)
    else
    {
        rotateRight(parent);
        rotateLeft(grand);
        grand->setHeight(grand->getHeight() - 2);
        parent->setHeight(parent->getHeight() - 1);
        curr->setHeight(std::max(curr->getLeft()->getHeight(), curr->getRight()->getHeight()) + 1);
    }

    // adjust root_
    if (parent->getParent() == NULL)
    {
        this->root_ = parent;
    }
    else if (curr->getParent() == NULL)
    {
        this->root_ = curr;
    }
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value>& new_item)
{
    // TODO
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->root_);
    AVLNode<Key, Value>* parent = NULL;

    if (this->root_ == NULL)
    {
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
        return;
    }

    while (curr != NULL)
    {
        if (new_item.first == curr->getKey())
        {
            curr->setValue(new_item.second);
            return;
        }
        if (new_item.first > curr->getKey())
        {
            parent = curr;
            curr = curr->getRight();
        }
        else
        {
            parent = curr;
            curr = curr->getLeft();
        }
    }
    curr = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
    if (parent->getKey() > curr->getKey())
    {
        parent->setLeft(curr);
    }
    else
    {
        parent->setRight(curr);
    }

    // look at parent to check balance
    // height of its parent is 2, it's good, just return
    if (parent->getHeight() == 2)
    {
        return;
    }
    // height of its parent is 1, update to 2, call insertFix(curr, parent)
    parent->setHeight(2);
    insertFix(curr, parent);
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* curr)
{
    if (curr == NULL)
    {
        return;
    }
    // check if curr is balanced
    bool balanced = false;

    if (curr->getLeft() == NULL || curr->getRight() == NULL)
    {
        if (curr->getLeft() == NULL && curr->getRight() == NULL)
        {
            balanced = true;
        }
        else if (curr->getLeft() == NULL && curr->getRight()->getHeight() <= 1)
        {
            balanced = true;
        }
        else if (curr->getRight() == NULL && curr->getLeft()->getHeight() <= 1)
        {
            balanced = true;
        }
    }
    else if (abs(curr->getLeft()->getHeight() - curr->getRight()->getHeight()) <= 1)
    {
        balanced = true;
    }

    // case 1: curr is unbalanced, fix it, then removeFix(parent)
    if (!balanced)
    {

        AVLNode<Key, Value>* tall_child;
        //  std::cout << "###" << tall_child->getKey();

        if (curr->getLeft() == NULL)
        {
            tall_child = curr->getRight();
        }
        else if (curr->getRight() == NULL)
        {
            tall_child = curr->getLeft();
        }
        else if (curr->getRight()->getHeight() > curr->getLeft()->getHeight())
        {
            tall_child = curr->getRight();
        }
        else
        {
            tall_child = curr->getLeft();
        }

        AVLNode<Key, Value>* tall_grandchild;
        if (tall_child->getLeft() == NULL)
        {
            tall_grandchild = tall_child->getRight();
        }
        else if (tall_child->getRight() == NULL)
        {
            tall_grandchild = tall_child->getLeft();
        }
        else if (tall_child->getRight()->getHeight() > tall_child->getLeft()->getHeight())
        {
            tall_grandchild = tall_child->getRight();
        }
        else if (tall_child->getRight()->getHeight() < tall_child->getLeft()->getHeight())
        {
            tall_grandchild = tall_child->getLeft();
        }
        // break tie in preference of zig-zig
        else
        {
            if (curr->getLeft() == tall_child)
            {
                tall_grandchild = tall_child->getLeft();
            }
            else
            {
                tall_grandchild = tall_child->getRight();
            }
        }

        // zig-zig
        // rotateLeft(curr)
        if (curr->getRight() == tall_child && tall_child->getRight() == tall_grandchild)
        {
            rotateLeft(curr);
            // adjust height
            if (curr->getLeft() == NULL && curr->getRight() == NULL)
            {
                curr->setHeight(1);
            }
            else if (curr->getLeft() == NULL || curr->getRight() == NULL)
            {
                curr->setHeight(2);
            }
            else
            {
                curr->setHeight(std::max(curr->getLeft()->getHeight(), curr->getRight()->getHeight()) + 1);
            }
            tall_child->setHeight(
                    std::max(tall_child->getLeft()->getHeight(), tall_child->getRight()->getHeight()) + 1);
        }
        // rotateRight(curr)
        else if (curr->getLeft() == tall_child && tall_child->getLeft() == tall_grandchild)
        {
            rotateRight(curr);
            // adjust height
            if (curr->getLeft() == NULL && curr->getRight() == NULL)
            {
                curr->setHeight(1);
            }
            else if (curr->getLeft() == NULL || curr->getRight() == NULL)
            {
                curr->setHeight(2);
            }
            else
            {
                curr->setHeight(std::max(curr->getLeft()->getHeight(), curr->getRight()->getHeight()) + 1);
            }
            tall_child->setHeight(
                    std::max(tall_child->getLeft()->getHeight(), tall_child->getRight()->getHeight()) + 1);
        }
        // zig-zag
        // rotateLeft(tall_child) then rotateRight(curr)
        else if (curr->getLeft() == tall_child && tall_child->getRight() == tall_grandchild)
        {
            rotateLeft(tall_child);
            rotateRight(curr);
            // adjust height
            if (curr->getLeft() == NULL && curr->getRight() == NULL)
            {
                curr->setHeight(1);
            }
            else if (curr->getLeft() == NULL || curr->getRight() == NULL)
            {
                curr->setHeight(2);
            }
            else
            {
                curr->setHeight(std::max(curr->getLeft()->getHeight(), curr->getRight()->getHeight()) + 1);
            }

            if (tall_child->getLeft() == NULL && tall_child->getRight() == NULL)
            {
                tall_child->setHeight(1);
            }
            else if (tall_child->getLeft() == NULL || tall_child->getRight() == NULL)
            {
                tall_child->setHeight(2);
            }
            else
            {
                tall_child->setHeight(
                        std::max(tall_child->getLeft()->getHeight(), tall_child->getRight()->getHeight()) + 1);
            }
            tall_grandchild->setHeight(
                    std::max(tall_grandchild->getLeft()->getHeight(), tall_grandchild->getRight()->getHeight()) + 1);
        }
        // rotateRight(tall_child) then rotateLeft(curr)
        else
        {
            rotateRight(tall_child);
            rotateLeft(curr);
            // adjust height
            if (curr->getLeft() == NULL && curr->getRight() == NULL)
            {
                curr->setHeight(1);
            }
            else if (curr->getLeft() == NULL || curr->getRight() == NULL)
            {
                curr->setHeight(2);
            }
            else
            {
                curr->setHeight(std::max(curr->getLeft()->getHeight(), curr->getRight()->getHeight()) + 1);
            }

            if (tall_child->getLeft() == NULL && tall_child->getRight() == NULL)
            {
                tall_child->setHeight(1);
            }
            else if (tall_child->getLeft() == NULL || tall_child->getRight() == NULL)
            {
                tall_child->setHeight(2);
            }
            else
            {
                tall_child->setHeight(
                        std::max(tall_child->getLeft()->getHeight(), tall_child->getRight()->getHeight()) + 1);
            }
            tall_grandchild->setHeight(
                    std::max(tall_grandchild->getLeft()->getHeight(), tall_grandchild->getRight()->getHeight()) + 1);
        }
        // adjust root_
        if (tall_child->getParent() == NULL)
        {
            this->root_ = tall_child;
        }
        else if (tall_grandchild->getParent() == NULL)
        {
            this->root_ = tall_grandchild;
        }
        removeFix(curr->getParent());
        return;
        // end of case 1
    }
    int height;
    if (curr->getLeft() == NULL && curr->getRight() == NULL)
    {
        height = 1;
    }
    else if (curr->getLeft() == NULL)
    {
        height = curr->getRight()->getHeight() + 1;
    }
    else if (curr->getRight() == NULL)
    {
        height = curr->getLeft()->getHeight() + 1;
    }
    else
    {
        height = std::max(curr->getLeft()->getHeight(), curr->getRight()->getHeight()) + 1;
    }
    // case 2: curr's height doesn't change, done!
    if (curr->getHeight() == height)
    {
        return;
    }
    // case 3: curr is balanced but its height changes, fix it, then removeFix(parent)
    curr->setHeight(height);
    removeFix(curr->getParent());
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
    // if the key doesn't exist
    if (this->internalFind(key) == NULL)
    {
        return;
    }

    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    AVLNode<Key, Value>* parent = NULL;
    if (curr->getParent() != NULL)
    {
        parent = curr->getParent();
    }

    // 0 children
    if (curr->getRight() == NULL && curr->getLeft() == NULL)
    {
        if (curr != this->root_)
        {
            if (curr->getParent()->getLeft() == curr)
            {
                curr->getParent()->setLeft(NULL);
            }
            else
            {
                curr->getParent()->setRight(NULL);
            }
        }
        else
        {
            this->root_ = NULL;
        }
        delete curr;
    }

    // 1 child
    else if (curr->getRight() == NULL || curr->getLeft() == NULL)
    {
        if (curr != this->root_)
        {
            if (curr->getRight() == NULL)
            {
                if (curr->getParent()->getLeft() == curr)
                {
                    curr->getParent()->setLeft(curr->getLeft());
                }
                else
                {
                    curr->getParent()->setRight(curr->getLeft());
                }
                curr->getLeft()->setParent(curr->getParent());
            }
            else
            {
                if (curr->getParent()->getLeft() == curr)
                {
                    curr->getParent()->setLeft(curr->getRight());
                }
                else
                {
                    curr->getParent()->setRight(curr->getRight());
                }
                curr->getRight()->setParent(curr->getParent());
            }
        }
        else
        {
            if (curr->getRight() == NULL)
            {
                this->root_ = curr->getLeft();
                curr->getLeft()->setParent(NULL);
            }
            else
            {
                this->root_ = curr->getRight();
                curr->getRight()->setParent(NULL);
            }
        }
        delete curr;
    }
    else
    {
        // 2 children
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(curr));
        nodeSwap(curr, pred);
        if (curr->getParent() != NULL)
        {
            parent = curr->getParent();
        }
        // 0 children
        if (curr->getRight() == NULL && curr->getLeft() == NULL)
        {
            if (curr != this->root_)
            {
                if (curr->getParent()->getLeft() == curr)
                {
                    curr->getParent()->setLeft(NULL);
                }
                else
                {
                    curr->getParent()->setRight(NULL);
                }
            }
            else
            {
                this->root_ = NULL;
            }
            delete curr;
        }

        // 1 child
        else
        {
            if (curr != this->root_)
            {
                if (curr->getRight() == NULL)
                {
                    if (curr->getParent()->getLeft() == curr)
                    {
                        curr->getParent()->setLeft(curr->getLeft());
                    }
                    else
                    {
                        curr->getParent()->setRight(curr->getLeft());
                    }
                    curr->getLeft()->setParent(curr->getParent());
                }
                else
                {
                    if (curr->getParent()->getLeft() == curr)
                    {
                        curr->getParent()->setLeft(curr->getRight());
                    }
                    else
                    {
                        curr->getParent()->setRight(curr->getRight());
                    }
                    curr->getRight()->setParent(curr->getParent());
                }
            }
            else
            {
                if (curr->getRight() == NULL)
                {
                    this->root_ = curr->getLeft();
                    curr->getLeft()->setParent(NULL);
                }
                else
                {
                    this->root_ = curr->getRight();
                    curr->getRight()->setParent(NULL);
                }
            }
            delete curr;
        }
    }
    // check if balance through ancestry
    removeFix(parent);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}

#endif
