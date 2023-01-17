#include "List.h"
#include <stdbool.h>
#include <stdio.h>

// Constructors-Destructors ---------------------------------------------------
Node newNode(int x) {
    Node n = (Node) malloc(sizeof(NodeObj));
    n->data = x;
    n->next = NULL;
    n->prev = NULL;
    return n;
} 
List newList(void) {
    // Creates and returns a new empty List.
    List L = (List) malloc(sizeof(ListObj));
    L->cursorIndex = 0;
    L->length = 0;
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    return L;
}
void freeList(List* pL) {
    // Frees all heap memory associated with *pL, and sets
    // *pL to NULL.
    free(*pL);
    *pL = NULL;
}
// Access functions -----------------------------------------------------------
int length(List L) {
    // Returns the number of elements in L.
    return L->length;
}
int index(List L) {
    // Returns index of cursor element if defined, -1 otherwise.
    if (L->cursor) {
        return L->cursorIndex;
    }
}
int front(List L) {
    // Returns front element of L. Pre: length()>0
    if (length(L) > 0) {
        return L->front;
    }
    return -1;
}
int back(List L) {
    // Returns back element of L. Pre: length()>0
    if (length(L) > 0) {
        return L->back;
    }
    return -1;
}
int get(List L) {
    // Returns cursor element of L. Pre: length()>0, index()>=0
    if (length(L) > 0 && L->cursorIndex >= 0) {
        return L->cursor;
    }
}
bool equals(List A, List B); // Returns true iff Lists A and B are in same
 // state, and returns false otherwise.
// Manipulation procedures ----------------------------------------------------
void clear(List L) {
    // Resets L to its original empty state.
    L->cursorIndex = 0;
    L->length = 0;
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
}
void set(List L, int x) {
    // Overwrites the cursor element’s data with x.
    // Pre: length()>0, index()>=0
    if (length(L) > 0 && L->cursorIndex >= 0) {
        L->cursorIndex = x;
        L->cursor = L->front;
        for (int i = 0; i < x; i++) {
            L->cursor = L->cursor->next;
        }
    }
}
void moveFront(List L) {
    // If L is non-empty, sets cursor under the front element,
    // otherwise does nothing.
    if (length(L) > 0) {
        L->cursor = L->front;
        L->cursorIndex = 0;
    }
}
void moveBack(List L) {
    // If L is non-empty, sets cursor under the back element,
    // otherwise does nothing.
    if (length(L) > 0) {
        L->cursor = L->back;
        L->cursorIndex = length(L) - 1;
    }
}
void movePrev(List L) {
    // If cursor is defined and not at front, move cursor one
    // step toward the front of L; if cursor is defined and at
    // front, cursor becomes undefined; if cursor is undefined
    // do nothing
    if (L->cursor == NULL) {return;}
    if (L->cursorIndex == 0) {
        L->cursor = NULL;
        return;
    }
    L->cursorIndex--;
    L->cursor = L->cursor->prev;
}
void moveNext(List L) {
    // If cursor is defined and not at back, move cursor one
    // step toward the back of L; if cursor is defined and at
    // back, cursor becomes undefined; if cursor is undefined
    // do nothing
    if (L->cursor == NULL) {return;}
    if (L->cursorIndex == length(L) - 1) {
        L->cursor = NULL;
        return;
    }
    L->cursorIndex++;
    L->cursor = L->cursor->next;
}
void prepend(List L, int x) {
    // Insert new element into L. If L is non-empty,
    // insertion takes place before front element.
    Node n = newNode(x);
    L->length++;
    if (length(L) == 1) {
        L->front = n;
        return;
    }
    n->next = L->front;
    L->front->prev = n;
    L->front = n;
}
void append(List L, int x) {
    // Insert new element into L. If L is non-empty,
    // insertion takes place after back element.
    Node n = newNode(x);
    L->length++;
    if (length(L) == 1) {
        L->front = n;
        return;
    }
    n->prev = L->back;
    L->back->next = n;
    L->back = n;
}
void insertBefore(List L, int x) {
    // Insert new element before cursor.
    // Pre: length()>0, index()>=0
    if (length(L) > 0 && L->cursorIndex >= 0) {
        L->length++;
        Node n = newNode(x);
        if(L->cursorIndex == 0) {
            L->front = n;
        }
        else {
            L->cursor->prev->next = n;
            n->prev = L->cursor->prev;
        }
        L->cursor->prev = n;
        n->next = L->cursor;
        L->cursorIndex++;
    }
}
void insertAfter(List L, int x) {
    // Insert new element after cursor.
    // Pre: length()>0, index()>=0
    if (length(L) > 0 && L->cursorIndex >= 0) {
        L->length++;
        Node n = newNode(x);
        if(L->cursorIndex == length(L) - 1) {
            L->back = n;
        }
        else {
            L->cursor->next->prev = n;
            n->next = L->cursor->next;
        }
        L->cursor->next = n;
        n->prev = L->cursor;
    }
}
void deleteFront(List L) {
    // Delete the front element. Pre: length()>0
    if (length(L) > 0) {
        L->length--;
        if (length(L) == 1) {
            clear(L);
        }
        else {
            L->front = L->front->next;
            L->front->prev = NULL;
            L->cursorIndex--;
        }
    }
}
void deleteBack(List L) {
    // Delete the back element. Pre: length()>0
    if (length(L) > 0) {
        L->length--;
        if (length(L) == 1) {
            clear(L);
        }
        else {
            L->back = L->back->prev;
            L->back->next = NULL;
        }
    }
}
void delete(List L) {
    // Delete cursor element, making cursor undefined.
    // Pre: length()>0, index()>=0
    if (length(L) > 0 && L->cursorIndex >= 0) {
        L->cursor = NULL;
        L->cursorIndex = 0;
    }
}
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L) {
    // Prints to the file pointed to by out, a
    // string representation of L consisting
    // of a space separated sequence of integers,
    // with front on left.
    Node n = L->front;
    for (int i = 0; i < length(L); i++) {
        fprintf(out, "%d", n->data);
        n = n->next;
    }
}
List copyList(List L); // Returns a new List representing the same integer
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
