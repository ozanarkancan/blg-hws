#include "BigUnsignedInt.h"
#include <iostream>

using namespace std;

BigUnsignedInt::BigUnsignedInt(unsigned int number)
{
    digits.push_back(number);//Push given number as digit[0]
}

BigUnsignedInt::BigUnsignedInt(const BigUnsignedInt& otherBigInt)
{
    deque<unsigned int> temporaryDigits = otherBigInt.getDigits();//Get digits
    for(unsigned int i = 0; i < temporaryDigits.size(); i++)//Copy each one
        digits.push_back(temporaryDigits[i]);
}

BigUnsignedInt::BigUnsignedInt(int numberOfDigits)
{
    for(unsigned int i = 0; i < (unsigned int)numberOfDigits; i++)//digits[0] = 0, digits[1] = 0, ... digits[numberOfDigits - 1] = 0
        digits.push_back(0);//Push numberOfDigits time zero
}

BigUnsignedInt::~BigUnsignedInt()
{
    digits.clear();//Clear all digits
}

deque<unsigned int> BigUnsignedInt::getDigits() const
{
    return digits;//Return copy of digits
}

BigUnsignedInt& BigUnsignedInt::operator+=(const BigUnsignedInt& bigIntRightSide)//Performs full adder
{
    deque<unsigned int> tempDigits = bigIntRightSide.getDigits();//Get copy of digits
    unsigned int lengthOfThis = this->digits.size();
    unsigned int lengthOfOther = tempDigits.size();

    uint64_t currentCarry = 0;
    uint64_t currentDigitsTotal = 0;

    if(lengthOfThis >= lengthOfOther)//make this + other
    {
        for(unsigned int i = 0; i < lengthOfOther; i++)
        {
            currentDigitsTotal = (uint64_t)this->digits[i] + (uint64_t)tempDigits[i] + currentCarry;//Add two digits with carry
            currentCarry = currentDigitsTotal >= base ? 1 : 0;//Determine if there is a carry
            this->digits[i] = (uint64_t)modForUnsignedLong(currentDigitsTotal, base);//Set digit i
        }

        if(currentCarry == 1)//While there is a carry add digit i with carry
        {
            for(unsigned int i = lengthOfOther; i < lengthOfThis; i++)
            {
                if(currentCarry == 0)
                    break;
                currentDigitsTotal = (uint64_t)this->digits[i] + currentCarry;//Add digit i with carry
                currentCarry = currentDigitsTotal >= base ? 1 : 0;//Determine if there is a carry
                this->digits[i] = (unsigned int)modForUnsignedLong(currentDigitsTotal, base);//Set digit i
            }
            if(currentCarry == 1)//Extend with 1
                this->digits.push_back(1);
        }
    }
    else//make other + this as mentioned above
    {
        for(unsigned int i = 0; i < lengthOfThis; i++)
        {
            currentDigitsTotal = (uint64_t)this->digits[i] + (uint64_t)tempDigits[i] + currentCarry;
            currentCarry = currentDigitsTotal >= base ? 1 : 0;
            this->digits[i] = (unsigned int)(currentDigitsTotal % base);
        }

        if(currentCarry == 1)
        {
            for(unsigned int i = lengthOfThis; i < lengthOfOther; i++)
            {
                if(currentCarry == 0)
                    break;
                currentDigitsTotal = (uint64_t)tempDigits[i] + currentCarry;
                currentCarry = currentDigitsTotal >= base ? 1 : 0;
                this->digits.push_back((unsigned int)modForUnsignedLong(currentDigitsTotal, base));
            }
            if(currentCarry == 1)
                this->digits.push_back(1);
        }
    }

    return *this; // Return this object
}

const BigUnsignedInt& BigUnsignedInt::operator+(const BigUnsignedInt& bigIntRightSide) const
{
    BigUnsignedInt* result = new BigUnsignedInt(*this);//Create copy of this object
    *result += bigIntRightSide;//Add other to copy of this
    return *result;//Return result
}

BigUnsignedInt& BigUnsignedInt::operator-=(const BigUnsignedInt& bigIntRightSide)
{
    deque<unsigned int> tempDigits = bigIntRightSide.getDigits();//Get copy of digits
    unsigned int lengthOfThis = this->digits.size();
    unsigned int lengthOfOther = tempDigits.size();

    int64_t currentCarry = 0;
    int64_t currentDigitsTotal = 0;

    if(lengthOfThis >= lengthOfOther)
    {
        for(unsigned int i = 0; i < lengthOfOther; i++)
        {
            currentDigitsTotal = (int64_t)this->digits[i] - (int64_t)tempDigits[i] + currentCarry; //Subtract digits and add carry
            if(currentDigitsTotal < 0)//If total is less than zero there is a barrow
            {
                currentCarry = -1;//Set carry -1
                this->digits[i] = (unsigned int)modForUnsignedLong(currentDigitsTotal, base);//Find pozitive modulo and set digit i
            }
            else
            {
                currentCarry = 0;//Set carry 0
                this->digits[i] = (unsigned int)modForUnsignedLong(currentDigitsTotal, base);//Set digit i
            }
        }

        if(currentCarry == -1)//While there is a barrow add digit i with carry
        {
            for(unsigned int i = lengthOfOther; i < lengthOfThis; i++)
            {
                if(currentCarry == 0)
                    break;
                currentDigitsTotal = (int64_t)this->digits[i] + currentCarry;//Add digit i with carry

                if(currentDigitsTotal < 0)
                {
                    currentCarry = -1;//Set carry -1
                    this->digits[i] = (unsigned int)modForUnsignedLong(currentDigitsTotal, base);//Find pozitive modulo and set digit i
                }
                else
                {
                    currentCarry = 0;//Set carry 0
                    this->digits[i] = (unsigned int)modForUnsignedLong(currentDigitsTotal, base);
                }
            }
            if(currentCarry == -1)//There is still barrow so result is negative
                throw "Overflow at subtraction!";
            else//Clear unnecessary 0 digits from most significant to least significant
            {
                for(unsigned int i = lengthOfThis - 1; i > 0; i--)//Leave one digit as 0 to represent number zero
                {
                    if(this->digits[i] == 0)
                        this->digits.pop_back();
                    else
                        break;
                }
            }
        }
    }
    else//number1 < number2 : Result is negative
    {
        throw "Overflow at subtraction!";
    }

    return *this; // Return this object
}

const BigUnsignedInt& BigUnsignedInt::operator-(const BigUnsignedInt& bigIntRightSide) const
{
    BigUnsignedInt* result = new BigUnsignedInt(*this);//Create copy of this object
    *result -= bigIntRightSide;//Subtract other from copy of this
    return *result;
}

BigUnsignedInt& BigUnsignedInt::operator=(const BigUnsignedInt& bigIntRightSide)
{
    if(this == &bigIntRightSide)//Check same object
        return *this;
    else
    {
        this->digits.clear();//Clear digits
        deque<unsigned int> temporaryDigits = bigIntRightSide.getDigits();//Get copy of digits
        for(unsigned int i = 0; i < temporaryDigits.size(); i++)//Push new digits
            this->digits.push_back(temporaryDigits[i]);
        return *this;
    }
}

bool BigUnsignedInt::operator==(const BigUnsignedInt& bigIntRightSide) const
{
    unsigned int lengthOfThis = this->digits.size();

    deque<unsigned int> tempDigits = bigIntRightSide.getDigits();
    unsigned int lengthOfOther = tempDigits.size();

    if(lengthOfThis != lengthOfOther)//Check size
        return false;
    else
    {
        for(int i = lengthOfThis - 1; i >= 0; i--)//Check all digits
            if(this->digits[i] != tempDigits[i])
                return false;

        return true;//Both numbers are equal
    }
}

bool BigUnsignedInt::operator<(const BigUnsignedInt& bigIntRightSide) const
{
    unsigned int lengthOfThis = this->digits.size();

    deque<unsigned int> tempDigits = bigIntRightSide.getDigits();
    unsigned int lengthOfOther = tempDigits.size();

    if(lengthOfThis < lengthOfOther)//number1 < number2
        return true;
    else
    {
        if(lengthOfThis > lengthOfOther)//number2 < number1
            return false;
        else//Number of digits are equal
        {
            for(int i = lengthOfThis - 1; i >= 0; i--)//Check each digits
            {
                if(this->digits[i] < tempDigits[i])//number1 < number2
                    return true;
                else if(this->digits[i] > tempDigits[i])//number2 < number1
                    return false;
            }
            return false;//Two number are equal
        }
    }
}

bool BigUnsignedInt::operator<=(const BigUnsignedInt& bigIntRightSide) const
{
    return (*this < bigIntRightSide || *this == bigIntRightSide);
}

bool BigUnsignedInt::operator>(const BigUnsignedInt& bigIntRightSide) const
{
    return !(*this <= bigIntRightSide);
}

bool BigUnsignedInt::operator>=(const BigUnsignedInt& bigIntRightSide) const
{
    return !(*this < bigIntRightSide);
}

const BigUnsignedInt& BigUnsignedInt::operator*(const BigUnsignedInt& bigIntRightSide)
{
    unsigned int lengthOfThis = this->digits.size();//m

    deque<unsigned int> digitsOfRightSide = bigIntRightSide.getDigits();//Get copy of digits
    unsigned int lengthOfOther = digitsOfRightSide.size();//n
    int numberOfDigitsOfResult = (int)(lengthOfThis + lengthOfOther);//Number of digits of result is m + n

    BigUnsignedInt* result = new BigUnsignedInt(numberOfDigitsOfResult);//Create m + n digits as zero
    deque<unsigned int> digitsOfResult = result->getDigits();//Get digits

    for(int j = 0; j < lengthOfOther; j++)//Make elementery school multiplication
    {
        if(digitsOfRightSide[j] != 0)//If multiplier is zero set result zero
        {
            uint64_t currentCarry = 0;
            uint64_t currentTotal = 0;

            for(int i = 0; i < lengthOfThis; i++)
            {
                //Multiply digits and add carry and result digit[i]
                currentTotal = (uint64_t)this->digits[i] * (uint64_t)digitsOfRightSide[j] + (uint64_t)digitsOfResult[i + j] + currentCarry;
                digitsOfResult[i + j] = (unsigned int)modForUnsignedLong(currentTotal, base);//Set digit
                currentCarry = divisionForUnsignedLong(currentTotal, base);//Set carry
            }

            digitsOfResult[lengthOfThis + j] = (unsigned int)currentCarry;//Set digit
        }
    }

    //Clear unnecessary zero digits from higher digits
    for(unsigned int i = numberOfDigitsOfResult - 1; i > 0; i--)//Leave one digit as 0 to represent number zero
    {
        if(digitsOfResult[i] == 0)
        {
            digitsOfResult.pop_back();
            numberOfDigitsOfResult--;
        }
        else
            break;
    }

    result->setDigits(digitsOfResult);//Set all digits

    return *result;
}

const BigUnsignedInt& BigUnsignedInt::operator/(const BigUnsignedInt& bigIntRightSide)
{
    if(bigIntRightSide == 0)//Zero division
        throw "Exception: Zero division!";

    BigUnsignedInt* result = new BigUnsignedInt((unsigned int)0);
    BigUnsignedInt copyOfThis = BigUnsignedInt(*this);//Copy of this
    BigUnsignedInt copyOfOther = bigIntRightSide;//Copy of right side object

    while(copyOfThis >= copyOfOther)//Find how many other is in this
    {
        *result += 1;//Increment one result
        copyOfThis -= copyOfOther;//Decrease copy of this
    }

    return *result;//Return result
}


/*
*All operator overloading with unsigned int type create BigUnsigned int from unsigned int number
*and perform operation
*/
BigUnsignedInt& BigUnsignedInt::operator+=(const unsigned int& intRightSide)//Performs full adder
{
    BigUnsignedInt bigIntFromUnsignedInt = BigUnsignedInt(intRightSide);
    *this += bigIntFromUnsignedInt;

    return *this ; // Return this object
}

const BigUnsignedInt& BigUnsignedInt::operator+(const unsigned int& intRightSide) const
{
    BigUnsignedInt* result = new BigUnsignedInt(*this);//Create copy of this object
    BigUnsignedInt bigIntFromUnsignedInt = BigUnsignedInt(intRightSide);
    *result += bigIntFromUnsignedInt;
    return *result;
}

BigUnsignedInt& BigUnsignedInt::operator-=(const unsigned int& intRightSide)
{
    BigUnsignedInt bigIntFromUnsignedInt = BigUnsignedInt(intRightSide);
    *this -= bigIntFromUnsignedInt;
    return *this; // Return this object
}

const BigUnsignedInt& BigUnsignedInt::operator-(const unsigned int& intRightSide) const
{
    BigUnsignedInt* result = new BigUnsignedInt(*this);//Create copy of this object
    BigUnsignedInt bigIntFromUnsignedInt = BigUnsignedInt(intRightSide);
    *result -= bigIntFromUnsignedInt;
    return *result;
}

BigUnsignedInt& BigUnsignedInt::operator=(const unsigned int& intRightSide)
{
    this->digits.clear();//Clear digits
    this->digits.push_back(intRightSide);//Pushes given number
    return *this;
}

bool BigUnsignedInt::operator==(const unsigned int& intRightSide) const
{
    BigUnsignedInt bigIntFromUnsignedInt = BigUnsignedInt(intRightSide);
    return (*this == bigIntFromUnsignedInt);
}

bool BigUnsignedInt::operator<(const unsigned int& intRightSide) const
{
    BigUnsignedInt bigIntFromUnsignedInt = BigUnsignedInt(intRightSide);
    return (*this < bigIntFromUnsignedInt);
}

bool BigUnsignedInt::operator<=(const unsigned int& intRightSide) const
{
    BigUnsignedInt bigIntFromUnsignedInt = BigUnsignedInt(intRightSide);
    return (*this <= bigIntFromUnsignedInt);
}

bool BigUnsignedInt::operator>(const unsigned int& intRightSide) const
{
    BigUnsignedInt bigIntFromUnsignedInt = BigUnsignedInt(intRightSide);
    return (*this > bigIntFromUnsignedInt);
}

bool BigUnsignedInt::operator>=(const unsigned int& intRightSide) const
{
    BigUnsignedInt bigIntFromUnsignedInt = BigUnsignedInt(intRightSide);
    return (*this >= bigIntFromUnsignedInt);
}

const BigUnsignedInt& BigUnsignedInt::operator*(const unsigned int& intRightSide)
{
    BigUnsignedInt* result = new BigUnsignedInt(*this);
    BigUnsignedInt bigIntFromUnsignedInt = BigUnsignedInt(intRightSide);

    *result = *result * bigIntFromUnsignedInt;

    return *result;
}

const BigUnsignedInt& BigUnsignedInt::operator/(const unsigned int& intRightSide)
{
    BigUnsignedInt* result = new BigUnsignedInt(*this);
    BigUnsignedInt bigIntFromUnsignedInt = BigUnsignedInt(intRightSide);

    *result = *result / bigIntFromUnsignedInt;

    return *result;
}

unsigned int BigUnsignedInt::getBinaryLengthOfNumber(unsigned int number)
{
    unsigned int length = 0;

    do
    {
        number = number >> 1;//Shift right
        length++;//Increase length
    }while(number != 0);//If number is zero break loop

    return length;//Return length
}

unsigned int BigUnsignedInt::getBinaryLength()
{
    unsigned int length = 0;
    unsigned int numberOfDigits = this->digits.size();

    //Length equals 2^32 * (number of digits - 1) + length of most significant digit
    length = (numberOfDigits - 1) * 32 + getBinaryLengthOfNumber(this->digits[numberOfDigits - 1]);

    return length;
}

void BigUnsignedInt::setDigits(deque<unsigned int>& digits)
{
    this->digits.clear();//Clear digits
    for(int i = 0; i < digits.size(); i++)
        this->digits.push_back(digits[i]);//Set digit
}

void BigUnsignedInt::setDigit(unsigned int index, unsigned int value)
{
    this->digits[index] = value;//Set digit
}

void BigUnsignedInt::printDigits()
{
    for(int i = this->digits.size() - 1; i >= 0; i--)//Print digits
        cout << this->digits[i] << " ";
    cout << endl;
}

unsigned long BigUnsignedInt::modForUnsignedLong(uint64_t number, uint64_t radix)
{
    if(number >= 0)
    {
        while(number >= radix)
            number -= radix;//Find modulo
    }
    else
    {
        while(number < 0)
            number += radix;//Find modulo
    }
    return number;
}

unsigned long BigUnsignedInt::divisionForUnsignedLong(uint64_t number1, uint64_t number2)
{
    unsigned long result = 0;
    while(number1 >= number2)
    {
        number1 -= number2;
        result++;
    }
    return result;
}

BigUnsignedInt BigUnsignedInt::powerOfBase(unsigned int pow)//Calculates power of a big unsigned int
{
    BigUnsignedInt result = BigUnsignedInt(*this);//Create copy of this
    for(unsigned int i = 1; i < pow; i++)//Calculate power
        result <<= 1;
    return result;//Return result;
}

BigUnsignedInt BigUnsignedInt::operator<<=(unsigned int number)
{
    for(unsigned int i = 0; i < number; i++)//Shift number to left specified times
        this->digits.push_front((unsigned int) 0);
    return *this;
}

//Add extra zero bit
//Method used int karasutba to make equal length of two multipland
void BigUnsignedInt::addExtraZeroDigitToMostSignificantBit()
{
    this->digits.push_back((unsigned int)0);//
}

BigUnsignedInt BigUnsignedInt::karatsuba(BigUnsignedInt bigIntRightSide)
{
    unsigned int lengthOfThis = this->digits.size();
    unsigned int lengthOfOther = bigIntRightSide.getDigits().size();

    if(lengthOfThis == 1 || lengthOfOther == 1)
        return *this * bigIntRightSide;
    else
    {
        BigUnsignedInt bigUnsignedIntBase = BigUnsignedInt((unsigned int)UINT_MAX);
        bigUnsignedIntBase += 1; //2^32 as bigUnsignedInt base

        if(lengthOfThis < lengthOfOther)//Check size
        {
            for(unsigned int i = 0; i < lengthOfOther - lengthOfThis; i++)
                this->addExtraZeroDigitToMostSignificantBit();
            lengthOfThis = lengthOfOther;
        }
        else if(lengthOfOther < lengthOfThis)
        {
            for(unsigned int i = 0; i < lengthOfThis - lengthOfOther; i++)
                bigIntRightSide.addExtraZeroDigitToMostSignificantBit();
            lengthOfThis = lengthOfOther;
        }

        deque<unsigned int> digitsOfRightSide = bigIntRightSide.getDigits();//Get copy of digits

        BigUnsignedInt xLow = BigUnsignedInt((int)ceil(lengthOfThis / 2));//Create xLow with empty digits
        for(unsigned int i = 0; i < ceil(lengthOfThis / 2); i++)//Set digits
            xLow.setDigit(i, this->digits[i]);

        BigUnsignedInt xHigh = BigUnsignedInt((int)(lengthOfThis - ceil(lengthOfThis / 2)));//Create xHigh with empty digits
        for(unsigned int i = (unsigned int)ceil(lengthOfThis / 2); i < lengthOfThis; i++)//Set digits
            xHigh.setDigit((unsigned int)(i - ceil(lengthOfThis / 2)), this->digits[i]);

        BigUnsignedInt yLow = BigUnsignedInt((int)ceil(lengthOfOther / 2));//Create yLow with empty digits
        for(unsigned int i = 0; i < ceil(lengthOfOther / 2); i++)//Set digits
            yLow.setDigit(i, digitsOfRightSide[i]);

        BigUnsignedInt yHigh = BigUnsignedInt((int)(lengthOfThis - ceil(lengthOfOther / 2)));//Create yHigh with empty digits
        for(unsigned int i = (unsigned int)ceil(lengthOfOther / 2); i < lengthOfOther; i++)//Set digits
            yHigh.setDigit((unsigned int)(i - ceil(lengthOfOther / 2)), digitsOfRightSide[i]);

        BigUnsignedInt a = xHigh.karatsuba(yHigh);
        BigUnsignedInt d = xLow.karatsuba(yLow);
        BigUnsignedInt temp = xHigh + xLow;
        BigUnsignedInt e = temp.karatsuba(yHigh + yLow) - a - d;

        BigUnsignedInt result = a * bigUnsignedIntBase.powerOfBase(lengthOfThis) + e * bigUnsignedIntBase.powerOfBase(lengthOfThis / 2)+ d;
        return bigUnsignedIntBase;
    }
}

BigUnsignedInt BigUnsignedInt::fastDivision(BigUnsignedInt bigIntRightSide)
{
    deque<unsigned int> digitsOfThis = this->getDigits();//Get copy of digits
    deque<unsigned int> digitsOfRightsSide = bigIntRightSide.getDigits();//Get copy of digits
    if(digitsOfRightsSide.size() == 1 && digitsOfThis.size() == 1)
        return BigUnsignedInt(digitsOfThis[0] / digitsOfRightsSide[0]);
    else
        return *this / bigIntRightSide;
}

ostream& operator<< (std::ostream &out, BigUnsignedInt &bigInt)
{
    uint64_t total = 0;
    deque<unsigned int> digits = bigInt.getDigits();
    for(unsigned int i = 0; i < digits.size(); i++)//Calculate actual value
        total += digits[i] * powl(base, i);
    out << total;//Print it
    return out;
}

