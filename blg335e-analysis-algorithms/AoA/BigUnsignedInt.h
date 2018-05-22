#ifndef BIGUNSIGNEDINT_H
#define BIGUNSIGNEDINT_H

#include <deque>
#include <string>
#include <limits.h>
#include <math.h>
#include <stdint.h>

#define base (uint64_t)UINT_MAX + 1 //define base as 2^32

using namespace std;

class BigUnsignedInt
{
    private:
        deque<unsigned int> digits;//Represents digits
        unsigned int getBinaryLengthOfNumber(unsigned int number);//Finds binary length of an unsigned int number.
        unsigned long modForUnsignedLong(uint64_t number, uint64_t radix);//There is a problem default / operation on unsigned long type, implements that operation
        unsigned long divisionForUnsignedLong(uint64_t number1, uint64_t number2);//There is a problem default % on unsigned long type, implements that operation
        BigUnsignedInt powerOfBase(unsigned int pow);

    public:
        BigUnsignedInt(unsigned int number);//Creates object that has one digit as number
        BigUnsignedInt(const BigUnsignedInt& otherBigInt);//Copy constructor
        BigUnsignedInt(int numberOfDigits);//Creates object that has specified digits as all of them zero
        ~BigUnsignedInt();//Deconstructor
        deque<unsigned int> getDigits() const;//Returns digits
        //Operator overloadings
        const BigUnsignedInt& operator+(const BigUnsignedInt& bigIntRightSide) const;
        BigUnsignedInt& operator+=(const BigUnsignedInt& bigIntRightSide);
        const BigUnsignedInt& operator-(const BigUnsignedInt& bigIntRightSide) const;
        BigUnsignedInt& operator-=(const BigUnsignedInt& bigIntRightSide);
        BigUnsignedInt& operator=(const BigUnsignedInt& bigIntRightSide);
        bool operator==(const BigUnsignedInt& bigIntRightSide) const;
        bool operator<(const BigUnsignedInt& bigIntRightSide) const;
        bool operator<=(const BigUnsignedInt& bigIntRightSide) const;
        bool operator>(const BigUnsignedInt& bigIntRightSide) const;
        bool operator>=(const BigUnsignedInt& bigIntRightSide) const;
        const BigUnsignedInt& operator*(const BigUnsignedInt& bigIntRightSide);
        const BigUnsignedInt& operator/(const BigUnsignedInt& bigIntRightSide);
        const BigUnsignedInt& operator+(const unsigned int& intRightSide) const;
        BigUnsignedInt& operator+=(const unsigned int& intRightSide);
        const BigUnsignedInt& operator-(const unsigned int& intRightSide) const;
        BigUnsignedInt& operator-=(const unsigned int& intRightSide);
        BigUnsignedInt& operator=(const unsigned int& intRightSide);
        bool operator==(const unsigned int& intRightSide) const;
        bool operator<(const unsigned int& intRightSide) const;
        bool operator<=(const unsigned int& intRightSide) const;
        bool operator>(const unsigned int& bigIntRightSide) const;
        bool operator>=(const unsigned int& bigIntRightSide) const;
        const BigUnsignedInt& operator*(const unsigned int& intRightSide);
        const BigUnsignedInt& operator/(const unsigned int& intRightSide);
        BigUnsignedInt operator<<=(unsigned int number);

        unsigned int getBinaryLength();//Returns binary length of number
        void setDigits(deque<unsigned int>& digits);//Sets digits
        void setDigit(unsigned int index, unsigned int value);//Set specified digit
        void printDigits();//Prints digits
        BigUnsignedInt karatsuba(BigUnsignedInt bigIntRightSide);
        void addExtraZeroDigitToMostSignificantBit();
        BigUnsignedInt fastDivision(BigUnsignedInt bigIntRightSide);

};

ostream& operator<< (std::ostream &out, BigUnsignedInt &bigInt);
#endif // BIGUNSIGNEDINT_H
