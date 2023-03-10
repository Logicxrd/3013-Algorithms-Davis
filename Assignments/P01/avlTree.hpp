//#include "AvlTree.h"
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;

struct TreeNode {
    int value;
    string data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    int avlValue;
};

class AvlTree {

private:

    string str_value;

    TreeNode* root;
    int avlValue(TreeNode* nodePtr);
    void computeAvlValues(TreeNode*& nodePtr);
    void deleteNode(int, TreeNode*&);
    void dodumpTree(TreeNode* nodePtr);
    int height(TreeNode* nodePtr);
    void insertNode(TreeNode*&, TreeNode*&);
    void makeDeletion(TreeNode*& nodePtr);
    bool rightHeavy(TreeNode* nodePtr);
    bool leftHeavy(TreeNode* nodePtr);
    void rotateLeft(TreeNode*& nodePtr);
    void rotateRight(TreeNode*& nodePtr);
    void deleteString(string, TreeNode*&);
    void dodumpStringTree(TreeNode* nodePtr);
    void insertStringNode(TreeNode*&, TreeNode*&);

public:
    AvlTree();
    AvlTree(string data);
    ~AvlTree();

    void dumpTree();
    void dumpStringTree();
    void insert(int);
    void remove(int);
    void search(int, ofstream&);
    void insertStr(string);
    void removeStr(string);
    void searchStr(string, ofstream&);
    int treeHeight();
};

void AvlTree::remove(int num) { deleteNode(num, root); };

void AvlTree::removeStr(string data) { deleteString(data, root); };


void AvlTree::dumpTree() {
    cout << "---------------------------------" << endl;
    cout << "Root:   " << root << "\n";
    dodumpTree(root);
};

void AvlTree::dumpStringTree() {
    cout << "---------------------------------" << endl;
    cout << "Root:   " << root << "\n";
    dodumpStringTree(root);
};

AvlTree::AvlTree(string data) {
    root = NULL;
    str_value = data;
}

AvlTree::AvlTree() {
    root = NULL;
}

AvlTree::~AvlTree() {
}

//************************************************************************
// Method Name: insertNode
//
// Private
//
// Purpose: Creates a new node and assigns the passed int value to it. Subsequently
//          calls insert to actually travers the binary tree and link the node in
//          proper location.
//
// Arguments: reference to root, and a reference to a new node
//
// Returns: Nothing.
//*************************************************************************
void AvlTree::insertNode(TreeNode*& nodePtr, TreeNode*& newNode) {

    if (nodePtr == NULL) {
        nodePtr = newNode;
    }
    else if (newNode->value <= nodePtr->value) {
        newNode->parent = nodePtr;
        insertNode(nodePtr->left, newNode);

    }
    else {
        newNode->parent = nodePtr;
        insertNode(nodePtr->right, newNode);
    }
}

//************************************************************************
// Method Name: insert
//
// Public
//
// Purpose: Creates a new node and assigns the passed in value to it. Subsequently
//          calls insert to actually travers the binary tree and link the node in
//          proper location.
//
// Arguments: integer to be placed in binary tree.
//
// Returns: Nothing.
//*************************************************************************
void AvlTree::insert(int num) {
    TreeNode* newNode;

    newNode = new TreeNode;
    newNode->value = num;
    newNode->avlValue = 0;
    newNode->left = newNode->right = NULL;
    newNode->parent = NULL;
    insertNode(root, newNode);
    computeAvlValues(root);
}

//************************************************************************
// Method Name: insertStr
//
// Public
//
// Purpose: Creates a new node and assigns the passed in value to it. Subsequently
//          calls insert to actually travers the binary tree and link the node in
//          proper location.
//
// Arguments: integer to be placed in binary tree.
//
// Returns: Nothing.
//*************************************************************************
void AvlTree::insertStr(string moreData) {
    TreeNode* newNode;

    newNode = new TreeNode;
    newNode->data = moreData;
    newNode->avlValue = 0;
    newNode->left = newNode->right = NULL;
    newNode->parent = NULL;
    insertStringNode(root, newNode);
    computeAvlValues(root);
}

//************************************************************************
// Method Name: insertStringNode
//
// Private
//
// Purpose: Creates a new node and assigns the passed string value to it. Subsequently
//          calls insert to actually travers the binary tree and link the node in
//          proper location.
//
// Arguments: reference of type string to root, and a reference to a new node
//
// Returns: Nothing.
//*************************************************************************
void AvlTree::insertStringNode(TreeNode*& nodePtr, TreeNode*& newNode) {

    if (nodePtr == NULL) {
        nodePtr = newNode;
    }
    else if (newNode->data <= nodePtr->data) {
        newNode->parent = nodePtr;
        insertStringNode(nodePtr->left, newNode);

    }
    else {
        newNode->parent = nodePtr;
        insertStringNode(nodePtr->right, newNode);
    }
}



//************************************************************************
// Method Name: search
//
// Public
//
// Purpose: Traverses a binary tree looking for a key value
//
// Arguments: integer to look for, output stream
//
// Returns: number of comparisons made before finding node
//*************************************************************************
void AvlTree::search(int num, ofstream& o) {
    TreeNode* nodePtr = root;

    int comparisons = 1;

    while (nodePtr) {
        if (nodePtr->value == num)
        {
            cout << "Found within ";
            cout << comparisons << " comparisons" << endl;
            o << "Found within ";
            o << comparisons << " comparisons" << endl;
            break;
        }
        else if (num < nodePtr->value)
        {
            comparisons++;
            nodePtr = nodePtr->left;
        }
        else
        {
            comparisons++;
            nodePtr = nodePtr->right;
        }
    }

}

//************************************************************************
// Method Name: searchStr
//
// Public
//
// Purpose: Traverses a binary tree looking for a key value
//
// Arguments: string to look for, output stream
//
// Returns: number of  comparisons made before finding node
//*************************************************************************
void AvlTree::searchStr(string moreData, ofstream& o) {
    TreeNode* nodePtr = root;

    int comparisons = 1;

    while (nodePtr) {
        if (nodePtr->data == moreData)
        {
            cout << "Record found!" << endl;
            cout << "Found after ";
            cout << comparisons << " comparisons..." << endl;
            o << "Record found!" << endl;
            o << "Found after ";
            o << comparisons << " comparisons..." << endl;
            break;
        }
        else if (moreData < nodePtr->data)
        {
            nodePtr = nodePtr->left;
            comparisons++;
        }
        else
        {
            nodePtr = nodePtr->right;
            comparisons++;
        }
    }

}

//************************************************************************
// Method Name: deleteNode
//
// Private
//
// Purpose: Traverses a binary tree looking for a key value to mark for
//          deletion (could be merged with search).
//
// Arguments: key to delete, nodePtr of the start of the tree (root , subroot, etc.)
//
// Returns: void
//*************************************************************************
void AvlTree::deleteNode(int num, TreeNode*& nodePtr) {
    if (nodePtr) {
        if (num < nodePtr->value)
            deleteNode(num, nodePtr->left);
        else if (num > nodePtr->value)
            deleteNode(num, nodePtr->right);
        else if (nodePtr->value == num)
            makeDeletion(nodePtr);
    }
    else {
        cout << "Value does not exist!" << endl;
    }
}

//************************************************************************
// Method Name: deleteString
//
// Private
//
// Purpose: Traverses a binary tree looking for a key value to mark for
//          deletion (could be merged with search).
//
// Arguments: key to delete, nodePtr of the start of the tree (root , subroot, etc.)
//
// Returns: void
//*************************************************************************
void AvlTree::deleteString(string moreData, TreeNode*& nodePtr) {
    if (nodePtr) {
        if (moreData < nodePtr->data)
            deleteString(moreData, nodePtr->left);
        else if (moreData > nodePtr->data)
            deleteString(moreData, nodePtr->right);
        else if (nodePtr->data == moreData)
            makeDeletion(nodePtr);
    }
    else {
        cout << "Value does not exist!" << endl;
    }
}

//************************************************************************
// Method Name: makeDeletion
//
// Private
//
// Purpose: Actually removes a node from a tree by pointer manipulation and
//          frees the memory
//
// Arguments: address of node to be deleted
//
// Returns: void
//*************************************************************************
void AvlTree::makeDeletion(TreeNode*& nodePtr) {
    TreeNode* tempNodePtr;

    if (nodePtr == NULL)
        cout << "Cannot delete empty node.\n";
    else if (nodePtr->right == NULL) {

        tempNodePtr = nodePtr;
        nodePtr = nodePtr->left;
        delete tempNodePtr;

    }
    else if (nodePtr->left == NULL) {

        tempNodePtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempNodePtr;

    }
    else {
        tempNodePtr = nodePtr->right;
        while (tempNodePtr->left)
            tempNodePtr = tempNodePtr->left;
        tempNodePtr->left = nodePtr->left;
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempNodePtr;
    }
    computeAvlValues(root);
}

//************************************************************************
// Method Name: height
//
// Private
//
// Purpose: Actually removes a node from a tree by pointer manipulation and
//          frees the memory
//
// Arguments: address of the root of the tree (or subtree)
//
// Returns: void
//*************************************************************************
int AvlTree::height(TreeNode* nodePtr) {
    int left_height = 0;
    int right_height = 0;
    if (nodePtr == NULL)
        return 0;
    else {
        left_height = height(nodePtr->left);
        right_height = height(nodePtr->right);
    }
    if (left_height > right_height)
        return 1 + left_height;
    else
        return 1 + right_height;
}

//************************************************************************
// Method Name: treeHeight
//
// Public
//
// Purpose: Public method to call the private height method
//
// Arguments: none
//
// Returns: void
//*************************************************************************
int AvlTree::treeHeight() {
    return height(root);
}

//************************************************************************
// Method Name: avlValue
//
// Private
//
// Purpose: Private method to calculate the avl value of a node.
//
// Arguments: address of a node
//
// Returns: void
//*************************************************************************
int AvlTree::avlValue(TreeNode* nodePtr) {
    return height(nodePtr->right) - height(nodePtr->left);
}

//************************************************************************
// Method Name: computeAvlValues
//
// Private
//
// Purpose: Private method to calculate the avl values of the entire tree.
//
// Arguments: address of a node
//
// Returns: void
//*************************************************************************
void AvlTree::computeAvlValues(TreeNode*& nodePtr) {
    if (nodePtr) {
        computeAvlValues(nodePtr->left);
        computeAvlValues(nodePtr->right);
        nodePtr->avlValue = avlValue(nodePtr);
        if (nodePtr->avlValue > 1) {
            rotateLeft(nodePtr);
        }
        else if (nodePtr->avlValue < -1) {
            rotateRight(nodePtr);
        }
    }
}

//************************************************************************
// Method Name: rotateLeft
//
// Private
//
// Purpose: Private method to perform a left rotation from a given position in a tree
//
// Arguments: address of a node
//
// Returns: void
//*************************************************************************
void AvlTree::rotateLeft(TreeNode*& SubRoot) {

    if (leftHeavy(SubRoot->right)) {
        rotateRight(SubRoot->right);
    }

    TreeNode* Temp;

    Temp = SubRoot->right;
    SubRoot->right = Temp->left;
    Temp->left = SubRoot;
    SubRoot = Temp;

    computeAvlValues(SubRoot);
}

//************************************************************************
// Method Name: rotateLeft
//
// Private
//
// Purpose: Private method to perform a right rotation from a given position in a tree
//
// Arguments: address of a node
//
// Returns: void
//*************************************************************************
void AvlTree::rotateRight(TreeNode*& SubRoot) {
    if (rightHeavy(SubRoot->left)) {
        rotateLeft(SubRoot->left);
    }

    TreeNode* Temp;

    Temp = SubRoot->left;
    SubRoot->left = Temp->right;
    Temp->right = SubRoot;
    SubRoot = Temp;

    computeAvlValues(SubRoot);
}

//************************************************************************
// Method Name: dodumpTree
//
// Private
//
// Purpose: Private method to show the basic pointer structure of the tree.
//          Initially written to help with debugging.
//
// Arguments: address of a node
//
// Returns: void
// Outputs: tree information
//*************************************************************************
void AvlTree::dodumpTree(TreeNode* nodePtr) {
    if (nodePtr) {
        cout << "Add:    " << nodePtr << "\n"
            << "Parent->" << nodePtr->parent << "\n"
            << "Val:    " << nodePtr->value << "\n"
            << "Avl:    " << nodePtr->avlValue << "\n"
            << "Left->  " << nodePtr->left << "\n"
            << "Right-> " << nodePtr->right << "\n\n";

        dodumpTree(nodePtr->left);
        dodumpTree(nodePtr->right);
    }
}


//************************************************************************
// Method Name: dodumpStringTree
//
// Private
//
// Purpose: Private method to show the basic pointer structure of the tree.
//          Initially written to help with debugging.
//
// Arguments: address of a node
//
// Returns: void
// Outputs: tree information
//*************************************************************************
void AvlTree::dodumpStringTree(TreeNode* nodePtr) {
    if (nodePtr) {
        cout << "Add:    " << nodePtr << "\n"
            << "Parent->" << nodePtr->parent << "\n"
            << "Val:    " << nodePtr->data << "\n"
            << "Avl:    " << nodePtr->avlValue << "\n"
            << "Left->  " << nodePtr->left << "\n"
            << "Right-> " << nodePtr->right << "\n\n";

        dodumpStringTree(nodePtr->left);
        dodumpStringTree(nodePtr->right);
    }
}

//************************************************************************
// Method Name: leftHeavy,rightHeavy
//
// Private
//
// Purpose: Compares the subtrees of a node to see which is taller
//
// Arguments: address of a node
//
// Returns: true if (left/right) heavy
//
//*************************************************************************
bool AvlTree::leftHeavy(TreeNode* nodePtr) {
    return height(nodePtr->left) > height(nodePtr->right);
}

bool AvlTree::rightHeavy(TreeNode* nodePtr) {
    return height(nodePtr->right) > height(nodePtr->left);
}

/**
 *
 */