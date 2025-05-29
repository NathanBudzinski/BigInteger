

#include "BigInteger.h"
#include <gtest/gtest.h>

TEST(BigIntegerTest, DefaultConstructor) 
{
    BigInteger bigInt;
    EXPECT_EQ(bigInt.to_string(), "");
    EXPECT_FALSE(bigInt.is_negative());
    EXPECT_FALSE(bigInt.is_positive());
}

TEST(BigIntegerTest, StringConstructor) 
{
    BigInteger bigInt("12345");
    EXPECT_EQ(bigInt.to_string(), "12345");
    EXPECT_FALSE(bigInt.is_negative());
    EXPECT_TRUE(bigInt.is_positive());

    BigInteger zeroBigInt("0");
    EXPECT_EQ(zeroBigInt.to_string(), "0");
    EXPECT_FALSE(zeroBigInt.is_negative());
    EXPECT_FALSE(zeroBigInt.is_positive());

    BigInteger negBigInt("-12345");
    EXPECT_EQ(negBigInt.to_string(), "-12345");
    EXPECT_TRUE(negBigInt.is_negative());
    EXPECT_FALSE(negBigInt.is_positive());
}

TEST(BigIntegerTest, IntegerConstructor) 
{
    BigInteger bigInt(12345);
    EXPECT_EQ(bigInt.to_string(), "12345");
    EXPECT_FALSE(bigInt.is_negative());
    EXPECT_TRUE(bigInt.is_positive());

    BigInteger zeroBigInt(0);
    EXPECT_EQ(zeroBigInt.to_string(), "0");
    EXPECT_FALSE(zeroBigInt.is_negative());
    EXPECT_FALSE(zeroBigInt.is_positive());

    BigInteger negBigInt(-12345);
    EXPECT_EQ(negBigInt.to_string(), "-12345");
    EXPECT_TRUE(negBigInt.is_negative());
    EXPECT_FALSE(negBigInt.is_positive());
}

TEST(BigIntegerTest, CopyConstructor) 
{
    BigInteger original("12345");
    BigInteger copy(original);
    original = "-67890";
    EXPECT_EQ(copy.to_string(), "12345");
    EXPECT_FALSE(copy.is_negative());
    EXPECT_TRUE(copy.is_positive());
}

TEST(BigIntegerTest, AssignmentOperator) 
{
    BigInteger bigInt("12345");
    BigInteger assigned;
    assigned = bigInt;
    EXPECT_EQ(assigned.to_string(), "12345");
    EXPECT_FALSE(assigned.is_negative());
    EXPECT_TRUE(assigned.is_positive());

    BigInteger negBigInt("-67890");
    assigned = negBigInt;
    EXPECT_EQ(assigned.to_string(), "-67890");
    EXPECT_TRUE(assigned.is_negative());
    EXPECT_FALSE(assigned.is_positive());
}

TEST(BigIntegerTest, InvalidAssignment)
{
    BigInteger bigInt;
    EXPECT_THROW(bigInt = "--12345", std::invalid_argument);
    EXPECT_THROW(bigInt = "not_a_number", std::invalid_argument);
    EXPECT_THROW(bigInt = "12345abc", std::invalid_argument);

    EXPECT_THROW(BigInteger("--12345"), std::invalid_argument);
    EXPECT_THROW(BigInteger("not_a_number"), std::invalid_argument);
    EXPECT_THROW(BigInteger("12345abc"), std::invalid_argument);

    EXPECT_THROW(bigInt = "1234.12", std::invalid_argument);
    EXPECT_THROW(BigInteger("1234.12"), std::invalid_argument);
}

TEST(BigIntegerTest, UnaryMinus) 
{
    BigInteger bigInt("12345");
    BigInteger negBigInt = -bigInt;
    EXPECT_EQ(negBigInt.to_string(), "-12345");
    EXPECT_TRUE(negBigInt.is_negative());
    EXPECT_FALSE(negBigInt.is_positive());

    bigInt = -negBigInt;
    EXPECT_EQ(bigInt.to_string(), "12345");
    EXPECT_FALSE(bigInt.is_negative());
    EXPECT_TRUE(bigInt.is_positive());

    BigInteger zeroBigInt("0");
    BigInteger negZeroBigInt = -zeroBigInt;
    EXPECT_EQ(negZeroBigInt.to_string(), "0");
    EXPECT_FALSE(negZeroBigInt.is_negative());
    EXPECT_FALSE(negZeroBigInt.is_positive());
    
    BigInteger uninitBigInt;
    EXPECT_THROW(uninitBigInt = -uninitBigInt, std::invalid_argument);
}

TEST(BigIntegerTest, EqualityOperator)
{
    BigInteger a("12345");
    BigInteger b("12345");
    BigInteger c("67890");

    BigInteger negA("-12345");
    BigInteger negB("-12345");
    BigInteger negC("-67890");

    EXPECT_TRUE(a == a);
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(c == a);
    EXPECT_FALSE(a == negA);
    EXPECT_FALSE(negA == a);
    
    EXPECT_TRUE(negA == negA);
    EXPECT_TRUE(negA == negB);
    EXPECT_TRUE(negB == negA);
    EXPECT_FALSE(negA == negC);
    EXPECT_FALSE(negC == negA);

    BigInteger uninitBigInt;
    EXPECT_THROW(uninitBigInt == a, std::invalid_argument);
    EXPECT_THROW(a == uninitBigInt, std::invalid_argument);
    EXPECT_THROW(uninitBigInt == uninitBigInt, std::invalid_argument);
}

TEST(BigIntegerTest, NotEqualOperator) 
{
    BigInteger a("12345");
    BigInteger b("67890");
    BigInteger c("12345");

    EXPECT_FALSE(a != a);
    EXPECT_FALSE(a != c);
    EXPECT_FALSE(c != a);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(b != a);
    
    BigInteger negA("-12345");
    BigInteger negB("-67890");
    BigInteger negC("-12345");

    EXPECT_FALSE(negA != negA);
    EXPECT_FALSE(negA != negC);
    EXPECT_FALSE(negC != negA);
    EXPECT_TRUE(negA != negB);
    EXPECT_TRUE(negB != negA);

    EXPECT_TRUE(a != negA);
    EXPECT_TRUE(negA != a);
    
    BigInteger uninitBigInt;
    EXPECT_THROW(uninitBigInt != a, std::invalid_argument);
    EXPECT_THROW(a != uninitBigInt, std::invalid_argument);
    EXPECT_THROW(uninitBigInt != uninitBigInt, std::invalid_argument);
}

TEST(BigIntegerTest, LessThanOperator) 
{
    BigInteger a("12345");
    BigInteger b("67890");
    BigInteger c("12345");

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(a < c);
    EXPECT_FALSE(b < a);
    EXPECT_FALSE(c < a);
    EXPECT_FALSE(a < a);

    BigInteger negA("-12345");
    BigInteger negB("-67890");
    BigInteger negC("-12345");

    EXPECT_TRUE(negA < negB);
    EXPECT_FALSE(negA < negC);
    EXPECT_FALSE(negB < negA);
    EXPECT_FALSE(negC < negA);
    EXPECT_FALSE(negA < negA);

    EXPECT_FALSE(a < negA);
    EXPECT_TRUE(negA < a);
    EXPECT_FALSE(b < negB);
    EXPECT_TRUE(negB < b);

    BigInteger uninitBigInt;
    EXPECT_THROW(uninitBigInt < a, std::invalid_argument);
    EXPECT_THROW(a < uninitBigInt, std::invalid_argument);
}

TEST(BigIntegerTest, LessThanEqualOperator) 
{
    BigInteger a("12345");
    BigInteger b("67890");
    BigInteger c("12345");

    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_FALSE(b <= a);
    EXPECT_TRUE(c <= a);
    EXPECT_TRUE(a <= a);

    BigInteger negA("-12345");
    BigInteger negB("-67890");
    BigInteger negC("-12345");

    EXPECT_TRUE(negA <= negB);
    EXPECT_TRUE(negA <= negC);
    EXPECT_FALSE(negB <= negA);
    EXPECT_TRUE(negC <= negA);
    EXPECT_TRUE(negA <= negA);

    EXPECT_FALSE(a <= negA);
    EXPECT_TRUE(negA <= a);
    EXPECT_FALSE(b <= negB);
    EXPECT_TRUE(negB <= b);

    BigInteger uninitBigInt;
    EXPECT_THROW(uninitBigInt <= a, std::invalid_argument);
    EXPECT_THROW(a <= uninitBigInt, std::invalid_argument);
}

TEST(BigIntegerTest, GreaterThanOperator) 
{
    BigInteger a("12345");
    BigInteger b("67890");
    BigInteger c("12345");

    EXPECT_FALSE(a > b);
    EXPECT_FALSE(a > c);
    EXPECT_TRUE(b > a);
    EXPECT_FALSE(c > a);
    EXPECT_FALSE(a > a);

    BigInteger negA("-12345");
    BigInteger negB("-67890");
    BigInteger negC("-12345");

    EXPECT_FALSE(negA > negB);
    EXPECT_FALSE(negA > negC);
    EXPECT_TRUE(negB > negA);
    EXPECT_FALSE(negC > negA);
    EXPECT_FALSE(negA > negA);

    EXPECT_TRUE(a > negA);
    EXPECT_FALSE(negA > a);
    EXPECT_TRUE(b > negB);
    EXPECT_FALSE(negB > b);

    BigInteger uninitBigInt;
    EXPECT_THROW(uninitBigInt > a, std::invalid_argument);
    EXPECT_THROW(a > uninitBigInt, std::invalid_argument);
}

TEST(BigIntegerTest, GreaterThanEqualOperator) 
{
    BigInteger a("12345");
    BigInteger b("67890");
    BigInteger c("12345");

    EXPECT_FALSE(a >= b);
    EXPECT_TRUE(a >= c);
    EXPECT_TRUE(b >= a);
    EXPECT_TRUE(c >= a);
    EXPECT_TRUE(a >= a);

    BigInteger negA("-12345");
    BigInteger negB("-67890");
    BigInteger negC("-12345");

    EXPECT_FALSE(negA >= negB);
    EXPECT_TRUE(negA >= negC);
    EXPECT_TRUE(negB >= negA);
    EXPECT_TRUE(negC >= negA);
    EXPECT_TRUE(negA >= negA);

    EXPECT_TRUE(a >= negA);
    EXPECT_FALSE(negA >= a);
    EXPECT_TRUE(b >= negB);
    EXPECT_FALSE(negB >= b);

    BigInteger uninitBigInt;
    EXPECT_THROW(uninitBigInt >= a, std::invalid_argument);
    EXPECT_THROW(a >= uninitBigInt, std::invalid_argument);
}


int main() 
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}