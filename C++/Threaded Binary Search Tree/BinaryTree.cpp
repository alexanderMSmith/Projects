/**
 * @file BinaryTree.cpp
 * @author Zaki Shaik, Alexander Smith (you@domain.com)
 * @brief This file is an implimentation of an integer binary tree. It contains
 * an operator for printing the contents of the tree to console, a
 * @version 1.0
 * @date 2021-06-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <iostream>

#include "BinaryTree.h"

using namespace std;

/**
 * @brief This
 *
 * @param os The ostream object that is written on and printed.
 * @param bst The binary tree that is being printed.
 * @return ostream& The contents of hte tree in the proper format.
 */
ostream &operator<<(ostream &os, const BinaryTree &bst) {

  if (bst.isEmpty()) {
    os << "empty tree";
    return os;
  }
  iteratorBST iterate(bst.getRoot());
  os << iterate.getCurrent()->getData() << " ";

  while (iterate++) {

    os << iterate.getCurrent()->getData() << " ";
  }
  return os;
}

/**
 * @brief Sets the iterator to the one next in line.
 *
 * @param itty The itterator being itterated.
 * @return true The iterator was iterated successfully
 * @return false The iterator was not iterated successfully
 */
bool operator++(iteratorBST &itty, int) { return itty.next(); }

/**
 * @brief Construct a new Binary Node:: Binary Node object
 *
 * @param data The starting data of the root.
 */
BinaryNode::BinaryNode(int data) : data{ data } {
  left = nullptr;
  right = nullptr;
  rightThread = false;
  leftThread = false;
}

/**
 * @brief Gets the data contained within the node.
 *
 * @return int The data in the node.
 */
int BinaryNode::getData() const { return data; }

/**
 * @brief This gets the left child of the node.
 *
 * @return BinaryNode* The left child of the node.
 */
BinaryNode *BinaryNode::getLeft() const {
  if (left == nullptr) {
    return nullptr;
  }
  return left;
}

/**
 * @brief This method gets the right child of the node.
 *
 * @return BinaryNode* The right child of the node.
 */
BinaryNode *BinaryNode::getRight() const {
  if (right == nullptr) {
    return nullptr;
  }
  return right;
}

/**
 * @brief This method gets checks to see if the left child exists.
 *
 * @return true The left child exists
 * @return false The left child does not exist.
 */
bool BinaryNode::getLeftThread() const { return leftThread; }

/**
 * @brief This method checks to see if the right child exists.
 *
 * @return true  The right decendant exists
 * @return false  The right child doesn't exist
 */
bool BinaryNode::getRightThread() const { return rightThread; }

/**
 * @brief Checks to see if the node is a leaf
 *
 * @return true This node is a leaf.
 * @return false This node is not a leaf
 */
bool BinaryNode::isLeaf() const {
  if ((this->left == nullptr && this->right == nullptr) ||
      (this->left == nullptr && this->rightThread == true) ||
      (this->right == nullptr && this->leftThread == true) ||
      (this->leftThread == true && this->rightThread == true)) {
    return true;
  }
  return false;
}

/**
 * @brief Construct a new iterator B S T::iterator B S T object
 *
 * @param root A node to be traversed to the left.
 */
iteratorBST::iteratorBST(BinaryNode *root) {
  current = root;
  while (current->getLeft() != nullptr) {
    current = current->getLeft();
  }
}

/**
 * @brief This method brings the iterator to the next part of the tree. This is
 * defined by going up or right depending on where in the tree the iterator is.
 *
 * @return true The method has successfull iterated.
 * @return false The method has not iterated.
 */
bool iteratorBST::next() {
  if (hasNext()) {
    if (current->getRight() != nullptr && current->getLeft() != nullptr &&
        !current->getLeftThread() && !current->getRightThread()) {
      current = current->getRight();
      while (!current->getLeftThread() && current->getLeft() != nullptr) {
        current = current->getLeft();
      }
    } else if (current != nullptr && current->getRight() != nullptr) {
      current = current->getRight();
    }
  } else {
    return false;
  }
  return true;
}

/**
 * @brief This checks to see if the iterator has a next node to go to
 *
 * @return true There is another node to go thorugh
 * @return false there is no other node to go through
 */
bool iteratorBST::hasNext() const { return current->getRight() != nullptr; }

/**
 * @brief This method gets the current iterator.
 *
 * @return BinaryNode* The iterator thats being returned.
 */
BinaryNode *iteratorBST::getCurrent() const { return current; }

/**
 * @brief Construct a new Binary Tree:: Binary Tree object
 *
 * @param n The starting nodes value.
 */
BinaryTree::BinaryTree(int n) {
  // indexes
  int start = 1;
  int end = n;
  int mid = (end + start) / 2;

  // create node, attach to this->root
  this->root = new BinaryNode(mid);
  treeCreate(start, mid);
  treeCreate(mid + 1, end);

  // add threads
  treeThreads(this->root);
}

/**
 * @brief A method that creates nodes with the values of a tree
 * in between two integers.
 *
 * @param start The starting node of the tree.
 * @param end The ending node of a tree.
 */
void BinaryTree::treeCreate(int start, int end) {
  if (start <= end) {

    int mid = (start + end) / 2;
    if (mid != root->data) {

      add(mid);
    }
    if (start != end) {
      if (end > 2) {

        treeCreate(start, mid - 1);
      }
      treeCreate(mid + 1, end);
    }
  }
}

/**
 * @brief Construct a new Binary Tree:: Binary Tree object
 *
 * @param copied The tree being copied.
 */
BinaryTree::BinaryTree(const BinaryTree &copied) {

  int start = 1;
  BinaryNode *n = copied.getRoot();
  int end = copyConstHelper(n);
  if (end != 0) {
    int mid = (end + start) / 2;

    this->root = new BinaryNode(mid);
    treeCreate(start, mid);
    treeCreate(mid + 1, end);

    // add threads
    treeThreads(this->root);

    for (int i = 1; i < end; i++) {
      if (!copied.contains(i)) {
        this->remove(i);
      }
    }
  } else {
    this->root = nullptr;
  }
}

/**
 * @brief This method is called by the copy constructor  and is used
 * during the process to ensure that the tree does not attempt to traverse to a
 * pointer that does not exist.
 *
 * @param treePtr
 * @return int
 */
int BinaryTree::copyConstHelper(BinaryNode *treePtr) {
  if (treePtr != nullptr) {
    while (treePtr->right != nullptr) {
      treePtr = treePtr->right;
    }
    return (treePtr->data);
  } else {
    return 0;
  }
}

/**
 * @brief Destroy the Binary Tree:: Binary Tree object using the clear method
 *
 */
BinaryTree::~BinaryTree() { clear(this->root); }
/**
 * @brief This method recursively goes through the tree and deletes each
 * node.
 *
 * @param subTreePtr the node and its children to be cleared.
 */
void BinaryTree::clear(BinaryNode *subTreePtr) {
  if (subTreePtr != nullptr) {
    if (subTreePtr->left != nullptr && !subTreePtr->leftThread) {
      clear(subTreePtr->left);
    }
    if (subTreePtr->right != nullptr && !subTreePtr->rightThread) {
      clear(subTreePtr->right);
    }
    subTreePtr->left = nullptr;
    subTreePtr->right = nullptr;
    delete subTreePtr;
  }
}

/**
 * @brief This method removes a value from the tree.
 *
 * @param value The value the tree is searched for.
 * @return true The value exists and was removed
 * @return false The value does not exist.
 */
bool BinaryTree::remove(int value) {
  if (!contains(value)) {
    return false;
  }
  return removeHelper(value, this->root, this->root);
}

// https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/ algorithm
// modified from geekfor geeks
/**
 * @brief A recursive method that assists the removal of a node.
 *
 * @param value The value being removed.
 * @param node The node currently being checked for its value.
 * @param parent The parent of the node being checked
 * @return true A node with the value was found and removed.
 * @return false There is no node with that value.
 */
bool BinaryTree::removeHelper(int value, BinaryNode *node, BinaryNode *parent) {
  if (value < node->data) {
    return removeHelper(value, node->left, node);
  } else if (value > node->data) {
    return removeHelper(value, node->right, node);
  } else {

    if (node->isLeaf()) {
      if (parent == node) {
        root = nullptr;
      }
      if (parent->right == node) {
        parent->right = node->right;
        parent->rightThread = node->rightThread;
      } else {
        parent->left = node->left;
        parent->leftThread = node->leftThread;
      }
      delete node;
    }
    // condition for only right child
    else if ((node->left == nullptr || node->leftThread) &&
             (node->right != nullptr && !node->rightThread)) {
      BinaryNode *nodeToBeDeleted = node->right;
      node->right = nodeToBeDeleted->right;
      node->rightThread = nodeToBeDeleted->rightThread;
      if (!nodeToBeDeleted->leftThread) {
        node->left = nodeToBeDeleted->left;
        BinaryNode *findThread = nodeToBeDeleted;
        while (!findThread->leftThread) {
          findThread = findThread->left;
        }
        findThread->leftThread = false;
        findThread->left = nullptr;
      } else {
        node->left = nullptr;
        node->leftThread = false;
      }
      node->data = nodeToBeDeleted->data;
      delete nodeToBeDeleted;
    }
    // conditional for only left child
    else if ((node->right == nullptr || node->rightThread) &&
             (node->left != nullptr && !node->leftThread)) {
      BinaryNode *nodeToBeDeleted = node->left;
      node->left = nodeToBeDeleted->left;
      node->leftThread = nodeToBeDeleted->leftThread;
      if (!nodeToBeDeleted->rightThread) {
        node->right = nodeToBeDeleted->right;
        BinaryNode *findThread = nodeToBeDeleted;
        while (!findThread->rightThread) {
          findThread = findThread->right;
        }
        findThread->rightThread = false;
        findThread->right = nullptr;
      } else {
        node->right = nullptr;
        node->rightThread = false;
      }
      node->data = nodeToBeDeleted->data;
      delete nodeToBeDeleted;
    }
    // if there are two children in right and left
    else {

      BinaryNode *subTreeParent = node;
      BinaryNode *subTreePtr = node->right;

      if (subTreePtr != nullptr) {
        if (!subTreePtr->leftThread && subTreePtr->left != nullptr) {

          while (!subTreePtr->leftThread && subTreePtr->left != nullptr) {
            subTreeParent = subTreePtr;
            subTreePtr = subTreePtr->left;
          }

          if (subTreePtr != nullptr) {
            node->data = subTreePtr->data;
          }

          if (subTreePtr->isLeaf()) {
            subTreeParent->left = nullptr;
          } else {
            // if right child only, sets parent->left to that branch
            subTreeParent->left = subTreePtr->right;
          }
        } else {
          node->data = subTreePtr->data;
          subTreeParent->right = subTreePtr->right;
          subTreeParent->rightThread = subTreePtr->rightThread;
        }
      }
      // now delete subTreePtr
      delete subTreePtr;
    }
  }
  return true;
}

/**
 * @brief This method adds an integer value to the tree if it is not already
 * in the tree. If the value already exists in the tree it will print the value
 *
 * @param value The integer value being added to the tree
 * @return true The value was added
 * @return false The value was not added because it already exists.
 */
bool BinaryTree::BinaryTree::add(int value) {
  if (root == nullptr) {
    root = new BinaryNode(value);
    return true;
  }

  if (contains(value)) {
    cout << value << endl;
    return false;
  }
  return addHelper(value, this->root);
}

/**
 * @brief This method assists the adding of an object.
 *
 * @param value The value being added.
 * @param node The node that is currently being traversed too.
 * @return true The value was added
 * @return false The value was not added.
 */
bool BinaryTree::addHelper(int value, BinaryNode *node) {
  if (value < node->data) {
    if (node->left != nullptr) {
      return addHelper(value, node->left);
    } else {
      BinaryNode *newNode = new BinaryNode(value);
      node->left = newNode;
    }
  }
  if (value > node->data) {
    if (node->right != nullptr) {
      return addHelper(value, node->right);
    } else {
      BinaryNode *newNode = new BinaryNode(value);
      node->right = newNode;
    }
  }
  return true;
}

/**
 * @brief Calls the method to check if the tree contains the given value.
 *
 * @param target The value being checked for.
 * @return true The node with the value exists.
 * @return false The node with the value doesn't exist.
 */
bool BinaryTree::contains(int target) const {
  return containsHelper(target, this->root);
}

/**
 * @brief This method checks the tree to see if the value is present.
 *
 * @param target The value being checked for.
 * @param node The node being checked.
 * @return true The value is in the tree
 * @return false The value is not in the tree.
 */
bool BinaryTree::containsHelper(int target, BinaryNode *node) const {
  if (node != nullptr) {

    if (target == node->data) {
      return true;
    }
    if (target > node->data && node->right != nullptr &&
        node->rightThread == false) {
      node = node->right;
      return containsHelper(target, node);
    }
    if (target < node->data && node->left != nullptr &&
        node->leftThread == false) {
      node = node->left;
      return containsHelper(target, node);
    }
  }
  return false;
}

/**
 * @brief This method
 *
 * @param treePtr The tree root
 */
void BinaryTree::treeThreads(BinaryNode *treePtr) {
  if (treePtr != nullptr) {
    if (treePtr->isLeaf()) {
      if (contains(treePtr->data + 1)) {
        treePtr->right = findNode(treePtr->data + 1, this->root);
        treePtr->rightThread = true;
      }
      if (contains(treePtr->data - 1)) {
        treePtr->left = findNode(treePtr->data - 1, this->root);
        treePtr->leftThread = true;
      }
      return;
    }

    if (treePtr->left != nullptr && !treePtr->leftThread) {
      treeThreads(treePtr->left);
    }

    if (treePtr->right == nullptr) {
      if (contains(treePtr->data + 1)) {
        treePtr->right = findNode(treePtr->data + 1, this->root);
        treePtr->rightThread = true;
      }
    }
    if (treePtr->left == nullptr) {
      if (contains(treePtr->data - 1)) {
        treePtr->left = findNode(treePtr->data - 1, this->root);
        treePtr->leftThread = true;
      }
    }
    if (treePtr->right != nullptr && !treePtr->rightThread) {
      treeThreads(treePtr->right);
    }
  }
}

/**
 * @brief This method searches the tree recursively for a node with the
 * value inputted.
 *
 * @param target The value being looked for.
 * @param treePtr The tree's point.
 * @return BinaryNode* The node with the value.
 */
BinaryNode *BinaryTree::findNode(int target, BinaryNode *treePtr) const {
  if (target < treePtr->data && treePtr->left != nullptr) {
    return findNode(target, treePtr->left);
  }
  if (target > treePtr->data && treePtr->left != nullptr) {
    return findNode(target, treePtr->right);
  }
  return treePtr;
}

/**
 * @brief Checks to see if the tree is empty.
 *
 * @return true The tree is empty.
 * @return false The tree is not empty.
 */
bool BinaryTree::isEmpty() const {
  if (this->root == nullptr) {
    return true;
  }
  return false;
}

// int BinaryTree::getHeight(BinaryNode* treePtr)
// {
//   if (treePtr == nullptr)
//       return 0;
//    else
//       return 1 + getHeight(treePtr–>getLeft() +
//                      getHeight(treePtr–>getRight());
// }

/**
 * @brief Returns the root of a BinaryTree
 *
 * @return BinaryNode* The root of the tree.
 */
BinaryNode *BinaryTree::getRoot() const { return this->root; }
