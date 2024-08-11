/**
 * @file BinaryTree.h
 * @author Zaki Shaik, Alexander Smith (you@domain.com)
 * @brief This file is the header file for BinaryNode. It contains
 * an operator for printing the contents of the tree to console, a private
 * method for determining if it is the leaf of another node, and several
 * methods for assisting its use in a tree.
 * @version 1.0
 * @date 2021-06-08
 * @copyright Copyright (c) 2021
 *
 */
#ifndef ASS5_BinaryTree_H
#define ASS5_BinaryTree_H

#include <iostream>

using namespace std;

class BinaryTree;

class BinaryNode {
  friend class BinaryTree; // Declares Binary Tree as able to use its
                           // components.
  friend ostream &operator<<(ostream &os, const BinaryTree &list); // Ditto
  // for this operator in ostream

private:
  explicit BinaryNode(int data); // A constructor.

  int data; // The integer the method contains.

  BinaryNode *left; // The left leaf.

  BinaryNode *right; // The right leaf.

  bool leftThread;

  bool rightThread;

  bool isLeaf() const;

public:
  int getData() const; // Gets data

  BinaryNode *getLeft() const; // Gets the left leaf

  BinaryNode *getRight() const; // Gets the right leaf.

  bool getLeftThread() const; // Checks to see if the left leaf exists

  bool getRightThread() const; // Checks to see if the right leaf exists
};

/**
 * @brief This class is an iterator used to assist the Binary Tree class.
 *
 */
class iteratorBST {
  friend class BinaryTree;
  friend class BinaryNode;

  friend ostream &operator<<(ostream &os, const BinaryTree &list);

  friend bool operator++(iteratorBST &iterator, int);

private:
  BinaryNode *current;

public:
  explicit iteratorBST(BinaryNode *root);

  bool next();

  bool hasNext() const;

  BinaryNode *getCurrent() const;
};

/**
 * @brief This class is the Binary Tree. It is a Binary tree of type BinaryNode.
 * It is designed to impliment the nodes in the tree format, properly ordering
 * them and has several methods for operating such a tree.
 *
 */
class BinaryTree {

  friend ostream &operator<<(ostream &os, const BinaryTree &list); // Allows
  // ostream access to the classes information

private:
  BinaryNode *root; // The root of the tree.

  bool addHelper(int data, BinaryNode *node);

  bool removeHelper(int data, BinaryNode *node, BinaryNode *parent);

  bool containsHelper(int target, BinaryNode *node) const;

  void treeCreate(int start, int end);

  int copyConstHelper(BinaryNode *treePtr);

  void treeThreads(BinaryNode *treePtr);

  BinaryNode *findNode(int target, BinaryNode *treePtr) const;

public:
  explicit BinaryTree(int n); // The constructor

  BinaryTree(const BinaryTree &copied); // The copy constructor

  BinaryNode *getRoot() const;

  virtual ~BinaryTree(); // The deconstructor

  bool add(int data);

  bool remove(int data);

  bool contains(int data) const;

  bool isEmpty() const;

  void clear(BinaryNode *subTreePtr);

  int getHeight(BinaryNode *treePtr);
};
#include "BinaryTree.cpp"
#endif // ASS5_BinaryTree_H
