
#include "BigInteger.h"
#include <algorithm>

bool is_numeric(const std::string& s) 
{
    if(!s.empty() && s[0] == '-')
    {
        return s.length() > 1 && std::all_of(s.begin() + 1, s.end(), ::isdigit);
    }
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

bool BigInteger::is_negative() const
{
    return negative;
}

bool BigInteger::is_positive() const
{
    return !negative && number != "0" && !number.empty();
}

BigInteger::BigInteger() 
    : number(), negative(false)
{
}

BigInteger::BigInteger(const std::string& num) 
{
    if (!is_numeric(num)) 
    {
        throw std::invalid_argument("Cannot assign non-numeric string to BigInteger");
    }
    if (num[0] == '-') 
    {
        negative = true;
        number = num.substr(1);
    } 
    else 
    {
        negative = false;
        number = num;
    }
}

BigInteger::BigInteger(const BigInteger& other) 
    : number(other.number), negative(other.negative)
{
}

BigInteger& BigInteger::operator=(const BigInteger& other) 
{
    if (this != &other) 
    {
        number = other.number;
        negative = other.negative;
    }
    return *this;
}

BigInteger& BigInteger::operator=(const std::string& num) 
{
    if (!is_numeric(num)) 
    {
        throw std::invalid_argument("Cannot assign non-numeric string to BigInteger");
    }
    if (num[0] == '-') 
    {
        negative = true;
        number = num.substr(1);
        return *this;
    } 
    negative = false;
    number = num;
    return *this;
}

BigInteger BigInteger::operator-() const 
{
    if (number.empty())
    {
        throw std::invalid_argument("Cannot negate an uninitialized BigInteger");
    }
    BigInteger result(*this);
    if (result.number != "0") 
    {
        result.negative = !result.negative;
    }
    return result;
}

BigInteger BigInteger::operator+(const BigInteger& other) const 
{
    std::string result;
    int i = number.length() - 1;
    int j = other.number.length() - 1;
    int carry = 0;
    while (i >= 0 || j >= 0 || carry) 
    {
        int digit1 = (i >= 0) ? number[i--] - '0' : 0;
        int digit2 = (j >= 0) ? other.number[j--] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        result.push_back((sum % 10) + '0');
        carry = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    return BigInteger(result);
}

BigInteger BigInteger::operator-(const BigInteger& other) const 
{
    // Implement subtraction logic here
    return BigInteger(); // Placeholder
}

BigInteger BigInteger::operator*(const BigInteger& other) const 
{
    // Implement multiplication logic here
    return BigInteger(); // Placeholder
}

BigInteger BigInteger::operator/(const BigInteger& other) const 
{
    // Implement division logic here
    return BigInteger(); // Placeholder
}

bool BigInteger::operator==(const BigInteger& other) const 
{
    if (number.empty() || other.number.empty()) 
    {
        throw std::invalid_argument("Cannot compare uninitialized BigInteger");
    }
    return (number == other.number) && (negative == other.negative);
}

bool BigInteger::operator!=(const BigInteger& other) const 
{
    return !(*this == other);
}

bool BigInteger::operator<(const BigInteger& other) const 
{
    if (number.empty() || other.number.empty()) 
    {
        throw std::invalid_argument("Cannot compare uninitialized BigInteger");
    }
    if (negative && !other.negative) 
    {
        return true;
    }
    if (!negative && other.negative) 
    {
        return false;
    }
    return number < other.number;
}

bool BigInteger::operator<=(const BigInteger& other) const 
{
    return (*this < other || *this == other);
}

bool BigInteger::operator>(const BigInteger& other) const 
{
    return !(*this <= other);
}

bool BigInteger::operator>=(const BigInteger& other) const 
{
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const BigInteger& bigInt) 
{
    if (bigInt.negative) 
    {
        os << '-';
    }
    os << bigInt.number;
    return os;
}

