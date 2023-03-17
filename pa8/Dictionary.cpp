/********************************************************************************* 
* Ryan Miller, rnmiller
* 2023 Winter CSE101 PA8 
* Dictionary.cpp 
* Dictionary ADT Module 
*********************************************************************************/
#include "Dictionary.h"
#define BLACK 1
#define RED 0

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R == nil) {return;}
    inOrderString(s, R->left);
    s += R->key + " : " + std::to_string(R->val) + "\n";
    inOrderString(s, R->right);
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R == nil) {return;}
    s += R->key + "\n";
    preOrderString(s, R->left);
    preOrderString(s, R->right);
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R == nil) {return;}
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
    if (R == nil) {return;}
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    delete R;
    R = nil;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil) {return nil;}
    if (R->key == k) {return R;}
    if (R->key < k) {
        return search(R->right, k);
    }
    return search(R->left, k);
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R == nil) {return nil;}
    if (R->left == nil) {return R;}
    return findMin(R->left);
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R == nil) {return nil;}
    if (R->right == nil) {return R;}
    return findMax(R->right);
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N == nil) {return nil;}
    return N->right;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N == nil) {return nil;}
    return N->left;
}

// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
    Node* y = N->right;
    N->right = y->left;
    if (y->left != nil) {
        y->left->parent = N;
    }
    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->left) {
        N->parent->left = y;
    } else {
        N->parent->right = y;
    }
    y->left = N;
    N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N) {
    Node* x = N->left;
    N->left = x->right;
    if (x->right != nil) {
        x->right->parent = N;
    }
    x->parent = N->parent;
    if (N->parent == nil) {
        root = x;
    } else if (N == N->parent->left) {
        N->parent->left = x;
    } else {
        N->parent->right = x;
    }
    x->right = N;
    N->parent = x;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {
    while (N->parent != nil && N->parent->color == RED) {
        if (N->parent == N->parent->parent->left) {
            Node* y = N->parent->parent->right;
            if (y != nil && y->color == RED) {
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if (N == N->parent->right) {
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        } else {
            Node* y = N->parent->parent->left;
            if (y != nil && y->color == RED) {
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if (N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nil) {
        v->parent = u->parent;
    }
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
    if (N == nil) {return;}
    while (N != root && N->color) {
        if (N == N->parent->left) {
            Node* w = N->parent->right;
            if (!w->color) {
                w->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if (w->left->color && w->right->color) {
                w->color = RED;
                N = N->parent;
            } else {
                if (w->right->color) {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(w);
                    w = N->parent->right;
                }
                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }
        } else {
            Node* w = N->parent->left;
            if (!w->color) {
                w->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                w = N->parent->left;
            }
            if (w->right->color && w->left->color) {
                w->color = RED;
                N = N->parent;
            } else {
                if (w->left->color) {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                w->color = N->parent->color;
                N->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {
    Node* y = N;
    Node* x;
    int y_original_color = y->color;
    if (N->left == NULL) {
        x = N->right;
        RB_Transplant(N, N->right);
    } else if (N->right == NULL) {
        x = N->left;
        RB_Transplant(N, N->left);
    } else {
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == N) {
            if (x != nil) {
                x->parent = y;
            }
        } else {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    delete N;
    if (y_original_color == BLACK) {
        RB_DeleteFixUp(x);
    }
}

// Class Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}
   
// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
    nil = nullptr;
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
    nil = nullptr;
    root = nil;
    current = root;
    num_pairs = 0;
    preOrderCopy(D.root, findMax(D.root));
}

// Destructor
Dictionary::~Dictionary() {
    postOrderDelete(root);
}


// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    Node* n = search(root, k);
    return (n != nil);
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    if (!contains(k)) {
        throw std::logic_error("Dictionary: getValue(): key \""+k+"\" does not exist");
    }
    Node* n = search(root, k);
    return n->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
    return (current != nil);
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
    if (current == nil) {
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    if (current == nil) {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    postOrderDelete(root);
    nil = nullptr;
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    Node* n = search(root, k);
    if (n != nil) {
        n->val = v;
        return;
    }
    num_pairs++;
    Node *z = new Node(k, v);
    Node *y = nil;
    Node *x = root;
    while (x != nil) {
        y = x;
        if (k < x->key) {
            x = x->left;
            continue;
        }
        x = x->right;
    }
    z->parent = y;
    if (y == nil) {
        root = z;
    }
    else if (k < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->color = RED;
    RB_InsertFixUp(z);
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    Node *N = search(root, k);
    if (N == nil) {
        throw std::logic_error("Dictionary: remove(): key \""+k+"\" does not exist");
    }
    if (N == current) {current = nil;}
    num_pairs--;
    RB_Delete(N);
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
    current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
    current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if (current == nil) {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    if (current == findMax(root)) {
        current = nil;
        return;
    }
    if (current->right != nil) {
        current = findMin(current->right);
        return;
    }
    Node *temp = current->parent;
    while (temp->key < current->key) {
        temp = temp->parent;
    }
    current = temp;
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if (current == nil) {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    if (current == findMin(root)) {
        current = nil;
        return;
    }
    if (current->left != nil) {
        current = findMax(current->left);
        return;
    }
    Node *temp = current->parent;
    while (temp->key > current->key) {
        temp = temp->parent;
    }
    current = temp;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
    return (to_string() == D.to_string());
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
    nil = NULL;
    root = nil;
    current = root;
    num_pairs = 0;
    preOrderCopy(D.root, findMax(D.root));
    return *this;
}
