/********************************************************************************* 
* Ryan Miller, rnmiller
* 2023 Winter CSE101 PA7 
* DictionaryTest.cpp 
* Test client for Dictionary ADT
* If no errors are raised and all memory is freed then Dictionary ADT worked correctly 
*********************************************************************************/ 

#include "Dictionary.h"
#include <assert.h>

int main() {
    Dictionary D = Dictionary();
    D.setValue("hi", 3);
    D.setValue("sup", 4);
    D.setValue("a", 5);
    assert(D.getValue("hi") == 3);
    assert(D.getValue("sup") == 4);
    D.begin();
    assert(D.currentKey() == "a");
    assert(D.currentVal() == 5);
    D.next();
    assert(D.currentKey() == "hi");
    assert(D.currentVal() == 3);
    D.next();
    assert(D.currentKey() == "sup");
    assert(D.currentVal() == 4);
    D.remove("hi");
    assert(D.size() == 2);
    assert(D.getValue("sup") == 4);
    assert(D.getValue("a") == 5);
    assert(D.contains("a"));
    D.clear();
    return 0;
}
