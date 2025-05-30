
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

std::string add(const std::string& a, const std::string& b) 
{
    std::string result;
    int i = a.length() - 1;
    int j = b.length() - 1;
    int carry = 0;
    while (i >= 0 || j >= 0 || carry) 
    {
        int digit1 = (i >= 0) ? a[i--] - '0' : 0;
        int digit2 = (j >= 0) ? b[j--] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        result.push_back((sum % 10) + '0');
        carry = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string subtract(const std::string& a, const std::string& b) 
{
    std::vector<int> result(a.length());
    
    // Convert strings to digits
    for (unsigned int i = 0; i < a.length(); i++) 
    {
        result[i] = a[i] - '0';
    }
    
    // Perform subtraction
    for (unsigned int i = 0; i < b.length(); i++) 
    {
        int idx = a.length() - 1 - i;
        int digit2 = b[b.length() - 1 - i] - '0';
        
        if (result[idx] < digit2) {
            // Need to borrow
            int j = idx - 1;
            while (j >= 0 && result[j] == 0)
            {
                result[j] = 9;
                j--;
            }
            if (j >= 0) 
            {
                result[j]--;
            }
            result[idx] += 10;
        }
        result[idx] -= digit2;
    }
    
    // Convert back to string, removing leading zeros
    std::string final;
    bool leadingZeros = true;
    for (int digit : result) 
    {
        if (digit != 0) leadingZeros = false;
        if (!leadingZeros || final.length() > 0) 
        {
            final += digit + '0';
        }
    }
    
    return final.empty() ? "0" : final;
}

std::string multiply(const std::string& a, const std::string& b) 
{
    std::vector<int> result(a.length() + b.length(), 0);
    
    // Multiply each digit
    for (int i = a.length() - 1; i >= 0; i--) 
    {
        for (int j = b.length() - 1; j >= 0; j--) 
        {
            int digit1 = a[i] - '0';
            int digit2 = b[j] - '0';
            
            // Add to existing value at position
            int pos1 = i + j;
            int pos2 = i + j + 1;
            int product = digit1 * digit2 + result[pos2];
            
            result[pos2] = product % 10;
            result[pos1] += product / 10;
        }
    }
    
    // Convert to string, removing leading zeros
    std::string multiply_result;
    bool leadingZeros = true;
    
    for (int digit : result) 
    {
        if (digit != 0) 
        {
            leadingZeros = false;
        }
        if (!leadingZeros) 
        {
            multiply_result += (digit + '0');
        }
    }
    
    return multiply_result.empty() ? "0" : multiply_result;
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
    if (number.empty() || other.number.empty()) 
    {
        throw std::invalid_argument("Cannot add uninitialized BigInteger");
    }
    if (!negative && !other.negative) 
    {
        // Both positive
        return BigInteger(add(number, other.number));
    } 
    else if (negative && other.negative) 
    {
        // Both negative
        BigInteger result(add(number, other.number));
        result.negative = true;
        return result;
    } 
    else if (negative && !other.negative) 
    {
        // This is negative, other is positive
        if (-*this < other)
        {
            return BigInteger(subtract(other.number, number));
        }
        else if (*this == -other)
        {
            return BigInteger("0");
        }
        else 
        {
            BigInteger result(subtract(number, other.number));
            result.negative = true;
            return result;
        }
    } 
    else 
    {
        // This is positive, other is negative
        if (*this < -other) 
        {
            BigInteger result(subtract(other.number, number));
            result.negative = true;
            return result;
        } 
        else if (*this == -other) 
        {
            return BigInteger("0");
        } 
        else 
        {
            return BigInteger(subtract(number, other.number));
        }
    }
    throw std::invalid_argument("Invalid BigInteger state for addition");
}

BigInteger BigInteger::operator-(const BigInteger& other) const 
{
    return *this + -other;
}

BigInteger BigInteger::operator*(const BigInteger& other) const 
{
    BigInteger result(multiply(number, other.number));
    if ((is_positive() && other.is_positive()) || 
        (is_negative() && other.is_negative()))
    {
        return result;
    }
    result.negative = true;
    return result;
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



