
#include <iostream>
#include <string>

class BigInteger
{
    private:
        std::string number;
        bool negative = false;
        friend bool is_numeric(const std::string& s);

    public:
        BigInteger();
        BigInteger(const std::string& num);
        
        template<typename T, typename = typename std::enable_if_t<std::is_integral<T>::value>>
        BigInteger(const T num)
        {
            if (num < 0) 
            {
                negative = true;
                number = std::to_string(-num);
            } 
            else 
            {
                negative = false;
                number = std::to_string(num);
            }
        }

        BigInteger(const BigInteger& other);
        BigInteger& operator=(const BigInteger& other);
        BigInteger& operator=(const std::string& num);

        template<typename T, typename = typename std::enable_if_t<std::is_integral<T>::value>>
        BigInteger& operator=(const T num) 
        {
            if (num < 0) 
            {
                negative = true;
                number = std::to_string(-num);
            }
            else 
            {
                negative = false;
                number = std::to_string(num);
            }
            return *this;
        }

        std::string to_string() const 
        {
            return (negative ? "-" : "") + number;
        }

        bool is_negative() const;

        bool is_positive() const;
        

        BigInteger& operator+=(const BigInteger& other);
        BigInteger& operator-=(const BigInteger& other);
        BigInteger& operator*=(const BigInteger& other);
        BigInteger& operator/=(const BigInteger& other);
        BigInteger& operator%=(const BigInteger& other);
        BigInteger operator-() const; // Unary minus

        BigInteger operator+(const BigInteger& other) const;
        BigInteger operator-(const BigInteger& other) const;
        BigInteger operator*(const BigInteger& other) const;
        BigInteger operator/(const BigInteger& other) const;

        bool operator==(const BigInteger& other) const;
        bool operator!=(const BigInteger& other) const;
        bool operator<(const BigInteger& other) const;
        bool operator<=(const BigInteger& other) const;
        bool operator>(const BigInteger& other) const;
        bool operator>=(const BigInteger& other) const;

        friend std::ostream& operator<<(std::ostream& os, const BigInteger& bigInt);

        friend std::string add(const std::string& a, const std::string& b);
        friend std::string subtract(const std::string& a, const std::string& b);
        friend std::string multiply(const std::string& a, const std::string& b);
        friend std::string divide(const std::string& a, const std::string& b);
        friend std::string mod(const std::string& a, const std::string& b);
};