/********************************************************************************* 
* Ryan Miller, rnmiller
* 2023 Winter CSE101 PA7 
* Dictionary.cpp 
* Dictionary ADT Module 
*********************************************************************************/
#include "Dictionary.h"


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
    Node* left = search(R->left, k);
    Node* right = search(R->right, k);
    if (left != nil) {return left;}
    if (right != nil) {return right;}
    return nil;
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
    if (root == nil) {
        root = new Node(k, v);
        root->left = nil;
        root->right = nil;
        root->parent = nil;
        return;
    }
    Node *cursor = root;
    Node *newNode = new Node(k, v);
    newNode->left = nil;
    newNode->right = nil;
    while (true) {
        if (cursor->key < k) {
            if (cursor->right == nil) {
                cursor->right = newNode;
                newNode->parent = cursor;
                return;
            }
            cursor = cursor->right;
            continue;
        }
        if (cursor->left == nil) {
            cursor->left = newNode;
            newNode->parent = cursor;
            return;
        }
        cursor = cursor->left;
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    if (!contains(k)) {
        throw std::logic_error("Dictionary: remove(): key \""+k+"\" does not exist");
    }
    Node* n = search(root, k);
    if (n == current) {current = nil;}
    num_pairs--;
    //if node is leaf
    if (n->left == nil && n->right == nil) {
        if (n == root) {
            root = nil;
            delete n;
            return;
        }
        if (n->parent->key < n->key) {
            n->parent->right = nil;
        }
        else {
            n->parent->left = nil;
        }
        delete n;
        return;
    }
    //if node has one child
    if (n->left == nil && n->right != nil) {
        if (n == root) {
            root = n->right;
            root->parent = nil;
            delete n;
            return;
        }
        if (n->parent->key < n->key) {
            n->parent->right = n->right;
            n->right->parent = n->parent;
            delete n;
            return;
        }
        n->parent->left = n->right;
        n->right->parent = n->parent;
        delete n;
        return;
    }
    if (n->left != nil && n->right == nil) {
        if (n == root) {
            root = n->left;
            root->parent = nil;
            delete n;
            return;
        }
        if (n->parent->key < n->key) {
            n->parent->right = n->left;
            n->left->parent = n->parent;
            delete n;
            return;
        }
        n->parent->left = n->left;
        n->left->parent = n->parent;
        delete n;
        return;
    }
    //if node has two children
    Node *temp = findMin(n->right);
    if (temp->parent->key < temp->key) {
        temp->parent->right = temp->right;
    }
    else {
        temp->parent->left = temp->right;
    }
    temp->left = n->left;
    temp->right = n->right;
    if (temp->left != nil) {
        temp->left->parent = temp;
    }
    if (temp->right != nil) {
        temp->right->parent = temp;
    }
    temp->parent = n->parent;
    if (n == root) {
        root = temp;
        delete n;
        return;
    }
    if (n->parent->key < n->key) {
        n->parent->right = temp;
        delete n;
        return;
    }
    n->parent->left = temp;
    delete n;
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
