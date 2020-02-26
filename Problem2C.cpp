#include <iostream>
#include <vector>
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
    void insertRec(int n, Node *node) {
        //The only situation in which insertRec would be
        //called with NULL is when root is null (i.e. the
        //tree is empty) so we insert at root and return
        if (node == NULL) {
            root = (Node *) malloc(sizeof(Node));
            root->data = n;
            root->left = NULL;
            root->right = NULL;
            root->parent = NULL;
            return;
        }

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
            }
            //If there's already a node there, call insertRec on that node
            else {
                insertRec(n, node->left);
            }
        }
        //Else, it is greater than the current node so we look to the left
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
            }
            //If there's already a node there, call insertRec on that node
            else {
                insertRec(n, node->right);
            }
        }
    }

    void fillArray(Node *n, vector<int>::iterator &it) {
        if (n == NULL)
            return;
        
        fillArray(n->left, it);
        *it = n->data;
        it++;
        fillArray(n->right, it);
    }
public:
    //Constructor initializes the root pointer to NULL
    BST() {
        root = NULL;
    }

    //Public wrapper for insert function
    void insertValue(int n) {
        insertRec(n, root);
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

    void sort(vector<int> &array) {
        for (int i = 0; i < array.size(); i++) {
            insertValue(array[i]);
        }
        auto it = array.begin();
        fillArray(root, it);
    }
};

/*int main() {
    BST tree;
    vector<int> array = {1, 4, 0, 9, 6, 3, 2, 12};
    tree.sort(array);

    tree.printTree();

    for (int i = 0; i < 8; i++) {
        cout << array[i] << endl;
    }
}*/