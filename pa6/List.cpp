/********************************************************************************* 
* Ryan Miller, rnmiller
* 2023 Winter CSE101 PA6 
* List.cpp 
* List ADT Module 
*********************************************************************************/

#include "List.h"

// Node constructor
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    Node* N = L.frontDummy->next;
    while (N != L.backDummy) {
        insertBefore(N->data);
        N = N->next;
    }
}

// Destructor
List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if (length() == 0) {
        throw std::length_error("List: front(): empty list");
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if (length() == 0) {
        throw std::length_error("List: back(): empty list");
    }
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if (position() >= length()) {
        throw std::range_error("List: peekNext(): cursor at end");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if (position() <= 0) {
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    moveFront();
    while (num_elements > 0) {
        eraseAfter();
    }
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = num_elements;
}

// moveNext
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
    if (position() >= length()) {
        throw std::range_error("List: moveNext(): cursor at back");
    }
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
    if (position() <= 0) {
        throw std::range_error("List: movePrev(): cursor at front");
    }
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    Node *n = new Node(x);
    n->prev = beforeCursor;
    n->next = afterCursor;
    afterCursor->prev = n;
    beforeCursor->next = n;
    afterCursor = n;
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    Node *n = new Node(x);
    n->prev = beforeCursor;
    n->next = afterCursor;
    afterCursor->prev = n;
    beforeCursor->next = n;
    beforeCursor = n;
    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    if (position() >= length()) {
        throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    if (position() <= 0) {
        throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    if (position() >= length()) {
        throw std::range_error("List: eraseAfter(): cursor at back");
    }
    Node *n = afterCursor;
    afterCursor = n->next;
    afterCursor->prev = n->prev;
    beforeCursor->next = afterCursor;
    delete n;
    num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    if (position() <= 0) {
        throw std::range_error("List: eraseBefore(): cursor at front");
    }
    Node *n = beforeCursor;
    beforeCursor = n->prev;
    beforeCursor->next = n->next;
    afterCursor->prev = beforeCursor;
    delete n;
    num_elements--;
    pos_cursor--;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
    while (afterCursor != backDummy) {
        moveNext();
        if (beforeCursor->data == x) {return position();}
    }
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    while (beforeCursor != frontDummy) {
        movePrev();
        if (afterCursor->data == x) {return position();}
    }
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    Node *before = beforeCursor;
    Node *after = afterCursor;
    int pos = pos_cursor;
    Node *currentBefore = frontDummy;
    Node *currentAfter = frontDummy->next;
    for (int i = 0; i < length(); i++) {
        beforeCursor = currentBefore = currentAfter;
        afterCursor = currentAfter = currentAfter->next;
        pos_cursor = i+1;
        int target = beforeCursor->data;
        while (true) {
            int result = findNext(target);
            if (result == -1) {break;}
            if (result == pos) {before = before->prev;}
            if (result == pos+1) {after = after->next;}
            if (result <= pos) {pos--;}
            if (result == i+2) {currentAfter = currentAfter->next;}
            eraseBefore();
        }
    }
    beforeCursor = before;
    afterCursor = after;
    pos_cursor = pos;
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List copy = List(L);
    copy.moveFront();
    Node* N = backDummy->prev;
    while (N != frontDummy) {
        copy.insertAfter(N->data);
        N = N->prev;
    }
    return copy;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    std::string stringRep = "(";
    Node *n = frontDummy->next;
    stringRep += std::to_string(n->data);
    n = n->next;
    while (n != backDummy) {
        stringRep += ", ";
        stringRep += std::to_string(n->data);
        n = n->next;
    }
    stringRep += ")";
    return stringRep;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    Node* nodeR = R.frontDummy->next;
    Node* nodeL = frontDummy->next;
    while (nodeR != R.backDummy || nodeL != backDummy) {
        if (nodeL->data != nodeR->data) {return false;}
        nodeL = nodeL->next;
        nodeR = nodeR->next;
    }
    return true;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
    clear();
    Node* N = L.frontDummy->next;
    Node* before = frontDummy;
    Node* after = backDummy;
    while (N != L.backDummy) {
        insertBefore(N->data);
        if (N == L.beforeCursor) {
            before = beforeCursor;
            after = afterCursor;
        }
        N = N->next;
    }
    beforeCursor = before;
    afterCursor = after;
    pos_cursor = L.pos_cursor;
    return *this;
}
