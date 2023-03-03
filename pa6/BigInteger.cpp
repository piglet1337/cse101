/********************************************************************************* 
* Ryan Miller, rnmiller
* 2023 Winter CSE101 PA6 
* BigInteger.cpp 
* BigInteger ADT Module 
*********************************************************************************/

#include "BigInteger.h"
#include <stdexcept>

const int power = 9;
const ListElement base = 1000000000;

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
}


// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    if (s.length() == 0) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    int stop = 0;
    switch (s[0]) {
        case '-':
            if (s.length() == 1) {
                throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            }
            stop = 1;
            signum = -1;
            break;
        case '+':
            if (s.length() == 1) {
                throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            }
            signum = 1;
            stop = 1;
            break;
        default:
            signum = 1;
            break;
    }
    for (ListElement scalar = 1, value = 0, i = s.length() - 1; i >= stop; i--) {
        if (s[i] < '0' || s[i] > '9') {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
        value += scalar * (s[i] - '0');
        scalar *= 10;
        if (scalar == base) {
            digits.insertAfter(value);
            scalar = 1;
            value = 0;
        }
        else if (i == stop) {
            digits.insertAfter(value);
        }
    }
    for (digits.moveFront(); digits.peekNext() == 0; ) {
        digits.eraseAfter();
    }
}


// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    signum = N.sign();
    digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is negative, 
// positive or 0, respectively.
int BigInteger::sign() const {
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    if (signum < N.signum) {return -1;}
    if (signum > N.signum) {return 1;}
    List copy = List(digits);
    List nCopy = List(N.digits);
    copy.moveFront();
    nCopy.moveFront();
    for (int i = 0; i < copy.length() - nCopy.length(); i++) {
        if (copy.peekNext() > 0) {return 1;}
        copy.moveNext();
    }
    for (int i = 0; i < nCopy.length() - copy.length(); i++) {
        if (nCopy.peekNext() > 0) {return -1;}
        nCopy.moveNext();
    }
    while (copy.position() < copy.length()) {
        if (copy.peekNext() > nCopy.peekNext()) {return 1;}
        if (copy.peekNext() < nCopy.peekNext()) {return -1;}
        copy.moveNext();
        nCopy.moveNext();
    }
    return 0;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    signum = 0;
    digits = List();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    signum *= -1;
}


// BigInteger Arithmetic operations ----------------------------------------


static List addition(List A, List B) {
    List sum = List();
    A.moveBack();
    B.moveBack();
    long carry = 0;
    while (A.position() > 0 || B.position() > 0) {
        long aNum = 0;
        long bNum = 0;
        if (A.position() != 0) {aNum = A.peekPrev();}
        if (B.position() != 0) {bNum = B.peekPrev();}
        long result = aNum + bNum + carry;
        carry = 0;
        sum.insertAfter(result % base);
        if (result > base) {carry = 1;}
        if (A.position() > 0) {A.movePrev();}
        if (B.position() > 0) {B.movePrev();}
    }
    return sum;
}

static List subtraction(List A, List B) {
    List sum = List();
    A.moveBack();
    B.moveBack();
    long carry = 0;
    while (A.position() > 0 || B.position() > 0) {
        long aNum = 0;
        long bNum = 0;
        if (A.position() != 0) {aNum = A.peekPrev();}
        if (B.position() != 0) {bNum = B.peekPrev();}
        long result = aNum - bNum - carry;
        carry = 0;
        if (result < 0) {
            result += base;
            carry = 1;
        }
        sum.insertAfter(result);
        if (A.position() > 0) {A.movePrev();}
        if (B.position() > 0) {B.movePrev();}
    }
    for (sum.moveFront(); sum.peekNext() == 0; ) {
        sum.eraseAfter();
    }
    return sum;
}
// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger sum = BigInteger();
    List copy = List(digits);
    List nCopy = List(N.digits);
    if (signum == N.signum) {
        sum.digits = addition(copy, nCopy);
        sum.signum = signum;
        return sum;
    }
    if (signum == 0) {
        sum.digits = nCopy;
        sum.signum = N.signum;
        return sum;
    }
    if (N.signum == 0) {
        sum.digits = copy;
        sum.signum = signum;
        return sum;
    }
    if (signum == 1 && N.signum == -1) {
        BigInteger temp = BigInteger(N);
        temp.negate();
        if (compare(temp) == 1) {
            sum.digits = subtraction(copy, nCopy);
            sum.signum = 1;
        }
        if (compare(temp) == -1) {
            sum.digits = subtraction(nCopy, copy);
            sum.signum = -1;
        }
        if (compare(temp) == 0) {
            sum.signum = 0;
        }
        return sum;
    }
    if (signum == -1 && N.signum == 1) {
        BigInteger temp = BigInteger(N);
        temp.negate();
        if (compare(temp) == 1) {
            sum.digits = subtraction(copy, nCopy);
            sum.signum = -1;
        }
        if (compare(temp) == -1) {
            sum.digits = subtraction(nCopy, copy);
            sum.signum = 1;
        }
        if (compare(temp) == 0) {
            sum.signum = 0;
        }
        return sum;
    }
    return sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger temp = BigInteger(N);
    temp.negate();
    return add(temp);
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger product;
    product.signum = signum * N.signum;
    if (product.signum == 0) {
        return product;
    }
    List copy = List(digits);
    List nCopy = List(N.digits);
    for (nCopy.moveBack(); nCopy.position() > 0; nCopy.movePrev()) {
        List temp;
        for (int i = 0; i < nCopy.length() - nCopy.position(); i++) {
            temp.insertAfter(0);
        }
        long carry = 0;
        for (copy.moveBack(); copy.position() > 0; copy.movePrev()) {
            long result = nCopy.peekPrev() * copy.peekPrev() + carry;
            carry = 0;
            if (result > base) {
                carry = result / base;
                result = result%base;
            }
            temp.insertAfter(result);
        }
        if (carry) {temp.insertAfter(carry);}
        product.digits = addition(product.digits, temp);
    }
    return product;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    if (signum == 0) {
        return "0";
    }
    std::string strRep = "";
    if (signum == -1) {
        strRep += "-";
    }
    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        std::string number = std::to_string(digits.peekNext());
        int length = number.length();
        for (int i = 0; i < power-length && digits.position() != 0; i++) {
            number = "0" + number;
        }
        strRep += number;
    }
    return strRep;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 0) {return true;}
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == -1) {return true;}
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) <= 0) {return true;}
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1) {return true;}
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) >= 0) {return true;}
    return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.mult(B);
    return A;
}