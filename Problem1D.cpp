#include <iostream>
#include <queue>

using namespace std;

class BST {
private:
    //Node struct for internal representation purposes
    struct Node {
        //Value held in the node
        int data;

        //Pointer to left child
        Node *left;

        //Pointer to right child
        Node *right;

        //Pointer to parent
        Node *parent;
    };
    typedef struct Node Node;

    //Pointer to root node
    Node *root;

    //Checks if node has no children
    bool isChildless(Node *n) {
        return (!n->left) && (!n->right);
    }

    //Inserts value n into the tree
    void insertIter(int n) {
        //Edge case where tree is empty
        if (root == NULL) {
            root = (Node *) malloc(sizeof(Node));
            root->data = n;
            root->left = NULL;
            root->right = NULL;
            root->parent = NULL;
            return;
        }

        Node *node = root;

        //Iterate until we find a leaf
        while (true) {
            //if n is less than (or equal to) the current node, look to the left
            if (n <= node->data) {
                //If the current node has no left child, insert new node to the left
                if (node->left == NULL) {
                    //allocate a new node and initalize it
                    Node *newNode = (Node *) malloc(sizeof(Node));
                    newNode->data = n;
                    newNode->left = NULL;
                    newNode->right = NULL;
                    newNode->parent = node;

                    node->left = newNode;  

                    break;      
                }
                else {
                    node = node->left;
                }
            }
            //Else, it is greater than the current node so we look to the right
            else {
                //If the current node has no right child, insert new node to the right
                if (node->right == NULL) {
                    //allocate a new node and initalize it
                    Node *newNode = (Node *) malloc(sizeof(Node));
                    newNode->data = n;
                    newNode->left = NULL;
                    newNode->right = NULL;
                    newNode->parent = node;

                    node->right = newNode; 

                    break;       
                }
                else {
                    node = node->right;
                }
            }
        }
    }

    //helper function that figures out whether
    //oldNode is the left or right child of it's parent
    //and replaces the appropriate pointer in the parent
    //with newNode
    void replaceNode(Node *oldNode, Node *newNode) {
        if (oldNode->parent->left == oldNode) {
            oldNode->parent->left = newNode;
        }
        else if (oldNode->parent->right == oldNode) {
            oldNode->parent->right = newNode;
        }
    }

    //Finds the first node with value n and deletes it
    void deleteIter(int n) {
        //Covers case where tree is empty
        if (root == NULL)
            return;
        
        //Covers case where we are deleting root
        if (root->data == n) {
            //If root is childless, set to NULL and return
            if (isChildless(root)) {
                delete root;
                root = NULL;
                return;
            }

            //If root only has a right child, just shift it up
            if (root->right && (!root->left)) {
                Node *oldRoot = root;
                root = root->right;
                root->parent = NULL;
                delete oldRoot;
                return;
            }

            //If root only has a left child, just shift it up
            if ((!root->right) && root->left) {
                Node *oldRoot = root;
                root = root->left;
                root->parent = NULL;
                delete oldRoot;
                return;
            }

            //By looking for the previous and next at the same time
            //We lower the chance of a worst case scenario
            Node *prev = root->left;
            //Edge case for when we find the previous value immediately
            if (!prev->right) {
                prev->right = root->right;
                delete root;
                root = prev;
                root->parent = NULL;
                return;
            }

            Node *next = root->right;
            //Edge case for when we find the next value immediately
            if (!next->left) {
                next->left = root->left;
                delete root;
                root = next;
                root->parent = NULL;
                return;
            }

            while (prev->right && next->left) {
                prev = prev->right;
                next = next->left;
            }

            if (!prev->right) {
                prev->parent->right = prev->left;
                root->data = prev->data;
                delete prev;
                return;
            }
            else { //!next->left
                next->parent->left = next->right;
                root->data = next->data;
                delete next;
                return;
            }
        }

        Node *node = root;

        while (true) {
            if (n < node->data) {
                node = node->left;
            }
            else if (n > node->data) {
                node = node->right;
            }
            else { //MATCH
                //If node is childless, just delete it
                if (isChildless(node)) {
                    replaceNode(node, NULL);
                    delete node;
                    return;
                }

                //If node only has a right child, just shift it up
                if (node->right && (!node->left)) {
                    replaceNode(node, node->right);
                    delete node;
                    return;
                }

                //If node only has a left child, just shift it up
                if ((!node->right) && node->left) {
                    replaceNode(node, node->left);
                    delete node;
                    return;
                }

                //By looking for the previous and next at the same time
                //We lower the chance of a worst case scenario
                Node *prev = node->left;
                //Edge case for when we find the previous value immediately
                if (!prev->right) {
                    prev->right = node->right;
                    replaceNode(node, prev);
                    delete node;
                    return;
                }

                Node *next = node->right;
                //Edge case for when we find the next value immediately
                if (!next->left) {
                    next->left = node->left;
                    replaceNode(node, next);
                    delete node;
                    return;
                }

                while (prev->right && next->left) {
                    prev = prev->right;
                    next = next->left;
                }

                if (!prev->right) {
                    node->data = prev->data;
                    replaceNode(prev,prev->left);
                    delete prev;
                }
                else { //!next->left
                    node->data = next->data;
                    replaceNode(next, next->right);
                    delete next;
                }
            }
        }
    }

    //Helper function the gets the node that contains n
    //Returns null if value not found
    Node *getNode(int n) {
        Node *node = root;

        while (node != NULL && node->data != n) {
            if (n < node->data)
                node = node->left;
            else
                node = node->right;
        }

        return node;
    }

    //Helper function for case where node has
    //no right subtree
    int findNextRecUp(Node *node) {
        //if is left child
        if (node->parent->left == node) {
            return node->parent->data;
        }
        else {
            return findNextRecUp(node->parent);
        }
    }

    //Given a value in the tree,n, returns the next highest value
    //in the tree
    int findNextIter(int n) {
        //First we have to find the node that contains n
        Node *node = getNode(n);

        if (node->right) {
            node = node->right;
            while (node->left)
                node = node->left;
            return node->data;
        }
        else {
            while (node->parent->left != node)
                node = node->parent;
            return node->parent->data;
        }
    }

    //Given a value in the tree,n, returns the next lowest value
    //in the tree
    int findPrevIter(int n) {
        //First we have to find the node that contains n
        Node *node = getNode(n);

        if (node->left) {
            node = node->left;
            while (node->right)
                node = node->right;
            return node->data;
        }
        else {
            while (node->parent->right != node)
                node = node->parent;
            return node->parent->data;
        }
    }

    int findMaxIter() {
        Node *node = root;

        while (node->right)
            node = node->right;
        
        return node->data;
    }

    int findMinIter() {
        Node *node = root;

        while (node->left)
            node = node->left;
        
        return node->data;
    }

public:
    //Constructor initializes the root pointer to NULL
    BST() {
        root = NULL;
    }

    //Public wrapper for insert function
    void insertValue(int n) {
        insertIter(n);
    }

    //Public wrapper for delete function
    void deleteValue(int n) {
        deleteIter(n);
    }

    //Public wrapper for findNext function
    int findNext(int n) {
        return findNextIter(n);
    }

    //Public wrapper for findPrev function
    int findPrev(int n) {
        return findPrevIter(n);
    }

    //Public wrapper for findMax function
    int findMax() {
        return findMaxIter();
    }

    //Public wrapper for findMin function
    int findMin() {
        return findMinIter();
    }

    //Prints tree for debug purposes
    void printTree() {
        if (root == NULL) {
            cout << "Empty tree" << endl;
            return;
        }

        queue<Node*> q;
        //Push root onto queue for zeroth level
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            cout << "Level " << level << endl;
            //Pre-get size so that we only process the nodes on the current level
            int size = q.size();
            //Output values for current level
            for (int i = 0; i < size; i++) {
                Node *n = q.front();
                q.pop();
                cout << "\tNode: " << n->data;
                if (n->left) {
                    cout << "\tLeft: " << n->left->data;
                    q.push(n->left);
                }
                else
                    cout << "\tLeft: NULL";
                if (n->right) {
                    cout << "\tRight: " << n->right->data;
                    q.push(n->right);
                }
                else
                    cout << "\tRight: NULL";
                cout << endl;
            }
            level++;
        }
    }
};

/*int main() {
    BST tree;
    tree.insertValue(4);
    tree.insertValue(2);
    tree.insertValue(6);
    tree.insertValue(1);
    tree.insertValue(3);
    tree.insertValue(5);
    tree.insertValue(7);
    tree.printTree();
    cout << endl;
    tree.deleteValue(2);
    tree.printTree();
    /*
    for (int i = 1; i < 7; i++) {
        cout << i << " is followed by " << tree.findNext(i) << endl;
    }

    cout << "Max: " << tree.findMax() << endl;
    cout << "Min: " << tree.findMin() << endl;*/

    /*tree.insertValue(1);
    tree.insertValue(-2);
    tree.insertValue(-1);
    tree.insertValue(0);
    tree.insertValue(3);
    tree.insertValue(2);
    
    
    tree.printTree();
    cout << endl;
    tree.deleteValue(-2);
    tree.printTree();*/
//}
