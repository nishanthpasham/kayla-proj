// FILE: bintreetemplate.h
// IMPLEMENTS: The nine template functions of the second version of the binary
// tree toolkit (see bintree.h for documentation). Note that this file is not
// compiled on its own. Instead, this file is included by an include directive
// at the bottom of bintree.h.

#include <cassert>    // Provides assert
#include <iomanip>   // Provides setw
#include <iostream>  // Provides cout
#include <cstdlib>    // Provides NULL, size_t

using namespace std;

// Programming note: Some compilers require that the default argument is
// listed in the implementation as well as the prototype, so we have
// include the default arguments for create_node.
template <class Item>
BinaryTreeNode<Item>* create_node(
    const Item& entry,
    BinaryTreeNode<Item>* l_ptr,
    BinaryTreeNode<Item>* r_ptr
)
{
    BinaryTreeNode<Item>* result_ptr;

    result_ptr = new BinaryTreeNode<Item>;
    result_ptr->data  = entry;
    result_ptr->left  = l_ptr;
    result_ptr->right = r_ptr;

    return result_ptr;
}

template <class Item>
BinaryTreeNode<Item>* tree_copy(const BinaryTreeNode<Item>* root_ptr)
// Library facilities used: stdlib.h
{
    BinaryTreeNode<Item> *l_ptr;
    BinaryTreeNode<Item> *r_ptr;

    if (root_ptr == NULL)
        return NULL;
    else
    {
        l_ptr = tree_copy(root_ptr->left);
        r_ptr = tree_copy(root_ptr->right);
        return create_node(root_ptr->data, l_ptr, r_ptr);
    }
}

template <class Item>
void tree_clear(BinaryTreeNode<Item>*& root_ptr)
{
    if (root_ptr != NULL)
    {
        tree_clear(root_ptr->left);
        tree_clear(root_ptr->right);
        delete root_ptr;
        root_ptr = NULL;
    }
}

template <class Item>
bool is_leaf(const BinaryTreeNode<Item>& node)
{
    return (node.left == NULL) && (node.right == NULL);
}

template <class Process, class Item>
void inorder(Process f, BinaryTreeNode<Item>* node_ptr)
{
    if (node_ptr != NULL)
    {
        inorder(f, node_ptr->left);
        f(node_ptr->data);
        inorder(f, node_ptr->right);
    }
}

template <class Process, class Item>
void postorder(Process f, BinaryTreeNode<Item>* node_ptr)
{
    if (node_ptr != NULL)
    {
        postorder(f, node_ptr->left);
        postorder(f, node_ptr->right);
        f(node_ptr->data);
    }
}

template <class Process, class Item>
void preorder(Process f, BinaryTreeNode<Item>* node_ptr)
{
    if (node_ptr != NULL)
    {
        f(node_ptr->data);
        preorder(f, node_ptr->left);
        preorder(f, node_ptr->right);
    }
}

template <class Item>
size_t tree_size(const BinaryTreeNode<Item>* node_ptr)
// Library facilities used: stdlib.h
{
    if (node_ptr == NULL)
        return 0;
    else
        return 1 + tree_size(node_ptr->left) + tree_size(node_ptr->right);
}

//
//   template <class Item, class SizeType>
//   void printTreeAtDepth (BinaryTreeNode<Item>* node_ptr, SizeType depth)
//     Precondition: node_ptr is a pointer to a node in a binary
//     tree (or node_ptr may be NULL to indicate the empty tree).
//     If the pointer is NULL, then depth is expected to be 0.
//     If the pointer is not NULL, then depth is the depth of
//     the node pointed to by node_ptr.
//     Postcondition: If node_ptr is non-NULL, then the contents
//     of *node_ptr and all its descendants have been written
//     to cout with the << operator, using a backward in-order
//     traversal. Each node is indented 4 times its depth.
template <class Item, class SizeType>
void printTreeAtDepth (BinaryTreeNode<Item>* node_ptr, SizeType depth)
// Library facilities used: iomanip.h, iostream.h, stdlib.h
{
    if (node_ptr != NULL)
    {
        printTreeAtDepth (node_ptr->right, depth+1);
        cout << setw(4*depth) << ""; // Indent 4*depth spaces
        cout << node_ptr->data << endl;
        printTreeAtDepth (node_ptr->left, depth+1);
    }
}

template <class Item>
void printTree(BinaryTreeNode<Item>* node_ptr)
{
    printTreeAtDepth (node_ptr, 0);
}

template <class Item>
void insert (BinaryTreeNode<Item>* & root_ptr, Item Target) 
{
    insertRecursive(root_ptr, Target);
}

template <class Item>
void insertRecursive (BinaryTreeNode<Item>* node_ptr, Item Target) 
{
    /*
    Base case in the recursion. When you have reached a leaf node, 
    put the target item to the left of this leaf node if it is less 
    than or equal to the node value. 
    Else put it on the right.
    */
    if (is_leaf(node_ptr)){
        if (Target <= node_ptr->data) {
            node_ptr->left = Target;
        } else {
            node_ptr->right = Target;
        }
    }

    /*
    If the item to be inserted is less than or equal to the current node, 
    then the item needs to be inserted in the left sub tree. 
    Hence recurse to the left. 
    Else recurse to the right.
    */
    if (Target <= node_ptr->data) {
        return insertRecursive(node_ptr->left, Target);
    } else {
        return insertRecursive(node_ptr->right, Target);
    }
}

template <class Item>
BinaryTreeNode<Item>* reflect (const BinaryTreeNode<Item>* root_ptr) 
{
    reflectRecursive(root_ptr);
    return root_ptr;
}

template <class Item>
void reflectRecursive (BinaryTreeNode<Item>* node_ptr) 
{
    if (node_ptr != NULL) {
        // Swap left and right nodes.
        BinaryTreeNode<Item>* tmp = node_ptr->left;
        node_ptr->left = node_ptr->right;
        node_ptr->right = tmp;

        // Continue swapping down the tree
        reflectRecursive(node_ptr->left);
        reflectRecursive(node_ptr->right);
    }
}

template <class Item>
void remove (BinaryTreeNode<Item>* & root_ptr, Item Target)
{
    /* TODO: REMOVE THIS LINE BEFORE SUBMITTING ASSIGNMENT.
    Read the link below to understand the 3 cases for removing 
    an element from a BST.
    https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
    */

    // first find the parent of the target element
    BinaryTreeNode<Item>* parent = findParent(root_ptr, Target);
    if (parent == NULL) {
        // the root is the element to be removed.
        removeHelper(root_ptr);
    } else if (parent->left->data == Target) {
        removeHelper(parent->left);
    } else {
        removeHelper(parent->right);
    }
}

template <class Item>
void removeHelper(BinaryTreeNode<Item>* & node_ptr) {
    if (is_leaf(node_ptr)) 
    {
        // node to be deleted is a leaf node
        node_ptr = NULL;
    } else if (node_ptr->left == NULL)
    {
        // node to be deleted has one child on right
        node_ptr->data = node_ptr->right->data;
        node_ptr->right = NULL;
    } else if (node_ptr->right == NULL) 
    {
        // node to be deleted has one child on left
        node_ptr->data = node_ptr->left->data;
        node_ptr->left = NULL;
    } else {
        // node to be deleted has two children. Then find the inorder successor.
        BinaryTreeNode<Item>* successor = findInOrderSuccessor(node_ptr);
        
        // copy successor's data 
        node_ptr->data = successor->data; 

        // delete the successor
        successor = NULL;
    }
}

template <class Item>
BinaryTreeNode<Item>* findInOrderSuccessor (BinaryTreeNode<Item>* & node_ptr) {
    if (node_ptr == NULL) {
        return NULL;
    }

    BinaryTreeNode<Item>* curr_ptr = node_ptr->right;
    while (curr_ptr->left != NULL) {
        curr_ptr = curr_ptr->left;
    }

    return curr_ptr;
}

template <class Item>
BinaryTreeNode<Item>* findParent (BinaryTreeNode<Item>* & node_ptr, Item Target)
{
    if (node_ptr->data == Target) {
        // Target is the root
        return NULL;
    }
    else if (node_ptr->left->data == Target || node_ptr->right->data == Target) {
        return node_ptr;
    } else if (node_ptr->data > Target)
    {
        return findParent(node_ptr->left, Target);
    } else {
        return findParent(node_ptr->right, Target);
    }
    
}