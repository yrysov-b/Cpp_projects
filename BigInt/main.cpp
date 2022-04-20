#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest/doctest.h"

#include "sstream"
#include "string"
#include "BigInt.hpp"
using namespace std;

TEST_CASE("BigInt : default constructor")
{
    BigInt a;

    ostringstream sout;
    sout << a;

    REQUIRE(sout.str() == "0");
}

TEST_CASE("BigInt : constructor with integer and string")
{
    ostringstream sout;

    SUBCASE("Test with 1234")
    {
        BigInt a(1234);
        sout << a;
        REQUIRE(sout.str() == "1234");
    }
    SUBCASE("Test with 1234")
    {
        BigInt a("-7");
        sout << a;
        REQUIRE(sout.str() == "-7");
    }
    SUBCASE("Test with 5")
    {
        BigInt a("5");
        sout << a;
        REQUIRE(sout.str() == "5");
    }
    SUBCASE("Test with 7")
    {
        BigInt a("7");
        sout << a;
        REQUIRE(sout.str() == "7");
    }
    SUBCASE("Test with 0")
    {
        BigInt a("0");
        sout << a;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("Test with 123")
    {
        BigInt a("123");
        sout << a;
        REQUIRE(sout.str() == "123");
    }

    SUBCASE("Test with -233333333")
    {
        BigInt a("-233333333");
        sout << a;
        REQUIRE(sout.str() == "-233333333");
    }

    SUBCASE("Test with 111111111111111111")
    {
        BigInt a("111111111111111111");
        sout << a;
        REQUIRE(sout.str() == "111111111111111111");
    }
    SUBCASE("Test with +111111111111111111")
    {
        BigInt a("+111111111111111111");
        sout << a;
        REQUIRE(sout.str() == "111111111111111111");
    }
    SUBCASE("Test with: ")
    {
        REQUIRE_THROWS_AS(BigInt a("");, runtime_error);
    }
    SUBCASE("Test with s")
    {
        REQUIRE_THROWS_AS(BigInt a("s");, runtime_error);
    }
    SUBCASE("Test with 0001")
    {
        BigInt a("0001");
        sout << a;
        REQUIRE(sout.str() == "1");
    }
    SUBCASE("Test with -000")
    {
        REQUIRE_THROWS_AS(BigInt a("-000");, runtime_error);
    }
}

TEST_CASE("BigInt : input operator >>")
{

    SUBCASE("Test with: 111111111111111111")
    {
        istringstream sinp("111111111111111111");
        BigInt a;

        sinp >> a;
        ostringstream sout;
        sout << a;
        REQUIRE(sout.str() == "111111111111111111");
    }

    SUBCASE("Test with: huuge number ")
    {
        istringstream sinp("huuge number");
        BigInt a;

        sinp >> a;
        REQUIRE(sinp.fail());

        ostringstream sout;
        sout << a;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("Test with: -12312321321331312312 ")
    {
        istringstream sinp("-12312321321331312312");
        BigInt a;

        sinp >> a;

        ostringstream sout;
        sout << a;
        REQUIRE(sout.str() == "-12312321321331312312");
    }

    SUBCASE("Test with: -123123213213---31312312 ")
    {
        istringstream sinp("-123123213213---31312312");
        BigInt a;

        sinp >> a;
        REQUIRE(sinp.fail());

        ostringstream sout;
        sout << a;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("Test with: space ")
    {
        istringstream sinp("    ");
        BigInt a;

        sinp >> a;
        REQUIRE(sinp.fail());

        ostringstream sout;
        sout << a;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("Test with: 1234 313 ")
    {
        istringstream sinp("1234 313");
        BigInt a;
        int x;

        sinp >> a >> x;

        ostringstream sout;
        sout << a;
        REQUIRE(sout.str() == "1234");
        REQUIRE(x == 313);
    }
}

TEST_CASE("BigInt : addition")
{
    ostringstream sout;

    SUBCASE("11111 + 11111")
    {
        BigInt a(11111);
        BigInt b(11111);

        sout << a + b;
        REQUIRE(sout.str() == "22222");
    }
    SUBCASE("-11111 +(-11111)")
    {
        BigInt a(-11111);
        BigInt b(-11111);

        sout << a + b;
        REQUIRE(sout.str() == "-22222");
    }

    SUBCASE("11111 + (-10000)")
    {
        BigInt a(11111);
        BigInt b(-11110);

        sout << a + b;
        REQUIRE(sout.str() == "1");
    }
    SUBCASE("11111 + (-11112)")
    {
        BigInt a(11111);
        BigInt b(-11112);

        sout << a + b;
        REQUIRE(sout.str() == "-1");
    }

    SUBCASE("-11111 + (11112)")
    {
        BigInt a(-11111);
        BigInt b(11112);

        sout << a + b;
        REQUIRE(sout.str() == "1");
    }

    SUBCASE("-11111 + (11110)")
    {
        BigInt a(-11111);
        BigInt b(11110);

        sout << a + b;
        REQUIRE(sout.str() == "-1");
    }
    SUBCASE("100 + (1)")
    {
        BigInt a(100);
        BigInt b(1);

        sout << a + b;
        REQUIRE(sout.str() == "101");
    }
    SUBCASE("10000000000000000000000000000000000000000000000000000 + (-1)")
    {
        BigInt a("10000000000000000000000000000000000000000000000000000");
        BigInt b(-1);

        sout << a + b;
        REQUIRE(sout.str() == "9999999999999999999999999999999999999999999999999999");
    }
    SUBCASE("-10000000000000000000000000000000000000000000000000000 + (1)")
    {
        BigInt a("-10000000000000000000000000000000000000000000000000000");
        BigInt b(1);

        sout << a + b;
        REQUIRE(sout.str() == "-9999999999999999999999999999999999999999999999999999");
    }
    SUBCASE("1 -10000000000000000000000000000000000000000000000000000 ")
    {
        BigInt a(1);
        BigInt b("-10000000000000000000000000000000000000000000000000000");

        sout << a + b;
        REQUIRE(sout.str() == "-9999999999999999999999999999999999999999999999999999");
    }
    SUBCASE(" 10000000000000000000000000000000000000000000000000001 -10000000000000000000000000000000000000000000000000000 ")
    {
        BigInt a("10000000000000000000000000000000000000000000000000001");
        BigInt b("-10000000000000000000000000000000000000000000000000000");

        sout << a + b;
        REQUIRE(sout.str() == "1");
    }
}

TEST_CASE("BigInt : subtraction")
{
    ostringstream sout;

    SUBCASE("1000 - 10")
    {
        BigInt a(1000);
        BigInt b(10);

        sout << a - b;
        REQUIRE(sout.str() == "990");
    }
    SUBCASE("-1000 - (-999)")
    {
        BigInt a(-1000);
        BigInt b(-999);

        sout << a - b;
        REQUIRE(sout.str() == "-1");
    }
    SUBCASE("17 - 38)")
    {
        BigInt a(17);
        BigInt b(38);

        sout << a - b;
        REQUIRE(sout.str() == "-21");
    }
    SUBCASE("1 - 1)")
    {
        BigInt a(1);
        BigInt b(1);

        sout << a - b;
        REQUIRE(sout.str() == "0");
    }
    SUBCASE("-89 -(-98))")
    {
        BigInt a(-89);
        BigInt b(-98);

        sout << a - b;
        REQUIRE(sout.str() == "9");
    }

    // SUBCASE("Ultimate test from professor Shostak: 1 million test")
    // {
    //     for (int i = -100; i <= 900; i++)
    //     {
    //         BigInt a(i);
    //         for (int j = -100; j <= 900; j++)
    //         {
    //             int sum = i - j;
    //             cout << i << " " << j << "\n";
    //             BigInt b(j);
    //             ostringstream sout1;
    //             sout1 << a - b;
    //             CHECK(sout1.str() == std::to_string(sum));
    //         }
    // }
    //  }
    SUBCASE("empty")
    {
        BigInt a;
        BigInt b;

        sout << a - b;
        REQUIRE(sout.str() == "0");
    }
    SUBCASE("-1000 - (-10)")
    {
        BigInt a(-1000);
        BigInt b(-10);

        sout << a - b;
        REQUIRE(sout.str() == "-990");
    }
    SUBCASE("1000 - (-10)")
    {
        BigInt a(1000);
        BigInt b(-10);

        sout << a - b;
        REQUIRE(sout.str() == "1010");
    }
    SUBCASE("-1000 - (10)")
    {
        BigInt a(-1000);
        BigInt b(10);

        sout << a - b;
        REQUIRE(sout.str() == "-1010");
    }
    SUBCASE(" 10000000000000000000000000000000000000000000000000001 -10000000000000000000000000000000000000000000000000000 ")
    {
        BigInt a("10000000000000000000000000000000000000000000000000001");
        BigInt b("10000000000000000000000000000000000000000000000000000");

        sout << a - b;
        REQUIRE(sout.str() == "1");
    }
    SUBCASE(" 10000000000000000000000000000000000000000000000000001 -1 ")
    {
        BigInt a("10000000000000000000000000000000000000000000000000001");
        BigInt b(1);

        sout << a - b;
        REQUIRE(sout.str() == "10000000000000000000000000000000000000000000000000000");
    }
}

TEST_CASE("BigInt : multiplication")
{
    ostringstream sout;

    SUBCASE("123 * 11")
    {
        BigInt a(123);
        BigInt b(11);

        sout << a * b;
        REQUIRE(sout.str() == "1353");
    }
    SUBCASE("5 * 7")
    {
        BigInt a("5");
        BigInt b("7");

        sout << a * b;

        REQUIRE(sout.str() == "35");
    }
    SUBCASE("5 * 7")
    {
        BigInt a(5);
        BigInt b(7);

        sout << a * b;

        REQUIRE(sout.str() == "35");
    }
    SUBCASE("123 * 10")
    {
        BigInt a(123);
        BigInt b(10);

        sout << a * b;
        REQUIRE(sout.str() == "1230");
    }
    SUBCASE("11111 * 11111")
    {
        BigInt a(11111);
        BigInt b(11111);

        sout << a * b;
        REQUIRE(sout.str() == "123454321");
    }
    SUBCASE("-11111 * -11111")
    {
        BigInt a(-11111);
        BigInt b(-11111);

        sout << a * b;
        REQUIRE(sout.str() == "123454321");
    }
    SUBCASE("-11111 * 11111")
    {
        BigInt a(-11111);
        BigInt b(11111);

        sout << a * b;
        REQUIRE(sout.str() == "-123454321");
    }
    SUBCASE("11111 * -11111")
    {
        BigInt a(11111);
        BigInt b(-11111);

        sout << a * b;
        REQUIRE(sout.str() == "-123454321");
    }
    SUBCASE("11111 * -11111")
    {
        BigInt a("11111");
        BigInt b(-11111);

        sout << a * b;
        REQUIRE(sout.str() == "-123454321");
    }
    SUBCASE("11111111111111111111111111111111 * 11111111111111111111111111111111")
    {
        BigInt a("11111111111111111111111111111111");
        BigInt b("11111111111111111111111111111111");

        sout << a * b;
        REQUIRE(sout.str() == "123456790123456790123456790123454320987654320987654320987654321");
    }
}

TEST_CASE("BigInt : self-operands")
{
    ostringstream sout;

    SUBCASE("123 = 123 - 13")
    {
        BigInt a(123);
        BigInt b(13);

        a -= b;
        sout << a;
        REQUIRE(sout.str() == "110");
    }
    SUBCASE("123 = 123 + 7")
    {
        BigInt a(123);
        BigInt b(7);

        a += b;
        sout << a;
        REQUIRE(sout.str() == "130");
    }
}

TEST_CASE("BigInt : division")
{
    ostringstream sout;

    SUBCASE("100/-10")
    {
        BigInt a(100);
        BigInt b(-10);

        sout << a / b;
        REQUIRE(sout.str() == "-10");
    }
    SUBCASE("1/1")
    {
        BigInt a(1);
        BigInt b(1);

        sout << a / b;
        REQUIRE(sout.str() == "1");
    }
    SUBCASE("100/-10")
    {
        BigInt a("100");
        BigInt b("-10");

        sout << a / b;
        REQUIRE(sout.str() == "-10");
    }

    SUBCASE("120 / 10")
    {
        BigInt a(120);
        BigInt b(10);

        sout << a / b;
        REQUIRE(sout.str() == "12");
    }

    SUBCASE("1000000000000000000000000000000000000 / 10")
    {
        BigInt a("100000000000000000000000000000000000000000000000000000000");
        BigInt b(10);

        sout << a / b;
        REQUIRE(sout.str() == "10000000000000000000000000000000000000000000000000000000");
    }
    SUBCASE("10/1000000000000000000000000000000000000 ")
    {
        BigInt a(10);
        BigInt b("100000000000000000000000000000000000000000000000000000000");

        sout << a / b;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("10/11")
    {
        BigInt a(10);
        BigInt b(11);

        sout << a / b;
        REQUIRE(sout.str() == "0");
    }
    SUBCASE("1000000000000000000000000000000000000 / -10")
    {
        BigInt a("100000000000000000000000000000000000000000000000000000000");
        BigInt b(-10);

        sout << a / b;
        REQUIRE(sout.str() == "-10000000000000000000000000000000000000000000000000000000");
    }
    SUBCASE("-1000000000000000000000000000000000000 / -10")
    {
        BigInt a("-100000000000000000000000000000000000000000000000000000000");
        BigInt b(-10);

        sout << a / b;
        REQUIRE(sout.str() == "10000000000000000000000000000000000000000000000000000000");
    }
    SUBCASE("-1000000000000000000000000000000000000 / 10")
    {
        BigInt a("-100000000000000000000000000000000000000000000000000000000");
        BigInt b(10);

        sout << a / b;
        REQUIRE(sout.str() == "-10000000000000000000000000000000000000000000000000000000");
    }
    SUBCASE("0 / 10")
    {
        BigInt a("0");
        BigInt b(10);

        sout << a / b;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("Multi range ")
    {
        for (int i = 200; i < 1000; i++)
        {
            for (int j = 1; j < 100; j++)
            {
                BigInt a(i);
                BigInt b(j);
                sout << (a * b);
                REQUIRE(sout.str() == std::to_string(i * j));
                sout.str("");
            }
        }
    }
    SUBCASE("1200 / 10")
    {
        BigInt a(1200);
        BigInt b(10);

        sout << a / b;
        REQUIRE(sout.str() == "120");
    }
}

TEST_CASE("BigInt : remainder")
{
    ostringstream sout;
    SUBCASE("12000000 % 10")
    {
        BigInt a(12000000);
        BigInt b(10);

        sout << a % b;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("120000001 % 3")
    {
        BigInt a(12000001);
        BigInt b(3);

        sout << a % b;
        REQUIRE(sout.str() == "1");
    }
    SUBCASE("-10 % 3")
    {
        BigInt a(-10);
        BigInt b(3);

        sout << a % b;
        REQUIRE(sout.str() == "-1");
    }

    SUBCASE("-10 % -3")
    {
        BigInt a(-10);
        BigInt b(-3);

        sout << a % b;
        REQUIRE(sout.str() == "-1");
    }

    SUBCASE("42342342424312312321331321242432312 % 42342342424312312321331321242432311 ")
    {
        BigInt a("42342342424312312321331321242432312");
        BigInt b("42342342424312312321331321242432311");

        sout << a % b;
        REQUIRE(sout.str() == "1");
    }
    SUBCASE("-42342342424312312321331321242432312 % 42342342424312312321331321242432311 ")
    {
        BigInt a("-42342342424312312321331321242432312");
        BigInt b("42342342424312312321331321242432311");

        sout << a % b;
        REQUIRE(sout.str() == "-1");
    }
}

TEST_CASE("BigInt : comparison")
{

    SUBCASE("120 < 10")
    {
        BigInt a(120);
        BigInt b(10);

        REQUIRE(b < a);
    }
    SUBCASE("-120 < -120")
    {
        BigInt a(-120);
        BigInt b(-120);

        REQUIRE((a < b) == 0);
    }

    SUBCASE("120 > 10")
    {
        BigInt a(120);
        BigInt b(10);

        REQUIRE(a > b);
    }
    SUBCASE("-120 > -10")
    {
        BigInt a(-120);
        BigInt b(-10);

        REQUIRE((a > b) == 0);
    }

    SUBCASE("120 == 120")
    {
        BigInt a("120");
        BigInt b("120");

        REQUIRE(a == b);
    }
    SUBCASE("-120 == -120")
    {
        BigInt a("-120");
        BigInt b("-120");

        REQUIRE((a < b) == 0);
        REQUIRE((a > b) == 0);
        REQUIRE(a == b);
    }
    SUBCASE("120 != 12")
    {
        BigInt a(120);
        BigInt b(12);

        REQUIRE((a < b) == 0);
        REQUIRE(a > b);
        REQUIRE(a != b);
    }
    SUBCASE("120 <= 121")
    {
        BigInt a(120);
        BigInt b(121);

        REQUIRE(a <= b);
    }

    SUBCASE("120 >= 100")
    {
        BigInt a(120);
        BigInt b(100);

        REQUIRE(a >= b);
    }
    SUBCASE("100 >= 100")
    {
        BigInt a(100);
        BigInt b(100);

        REQUIRE(a >= b);
    }
    SUBCASE("100 <= 100")
    {
        BigInt a(100);
        BigInt b(100);

        REQUIRE(a <= b);
    }
}

TEST_CASE("BigInt : operators  ")
{
    ostringstream sout;

    SUBCASE("+=")
    {
        BigInt a(1000000000);
        a += 1;
        sout << a;

        REQUIRE(sout.str() == "1000000001");
    }
    SUBCASE("-=")
    {
        BigInt a(1000000001);
        a -= 1;
        sout << a;

        REQUIRE(sout.str() == "1000000000");
    }
    SUBCASE("*=")
    {
        BigInt a("11111111111111111111111111111111");

        a *= a;

        sout << a;
        REQUIRE(sout.str() == "123456790123456790123456790123454320987654320987654320987654321");
    }
    SUBCASE("/=")
    {
        BigInt a("-100000000000000000000000000000000000000000000000000000000");
        a /= 10;

        sout << a;
        REQUIRE(sout.str() == "-10000000000000000000000000000000000000000000000000000000");
    }
    SUBCASE("%=")
    {
        BigInt a("-100000000000000000000000000000000000000000000000000000000");
        a %= 10;

        sout << a;
        REQUIRE(sout.str() == "0");
    }
    SUBCASE("++ prefix")
    {
        BigInt a("100000000000000000000000000000000000000000000000000000000");

        sout << ++a;
        REQUIRE(sout.str() == "100000000000000000000000000000000000000000000000000000001");
    }
    SUBCASE("++ postfix")
    {
        BigInt a("100000000000000000000000000000000000000000000000000000000");

        sout << a++;
        REQUIRE(sout.str() == "100000000000000000000000000000000000000000000000000000000");
    }
    SUBCASE("-- prefix")
    {
        BigInt a("100000000000000000000000000000000000000000000000000000001");

        sout << --a;
        REQUIRE(sout.str() == "100000000000000000000000000000000000000000000000000000000");
    }
    SUBCASE("-- postfix")
    {
        BigInt a("100000000000000000000000000000000000000000000000000000001");

        sout << a--;
        REQUIRE(sout.str() == "100000000000000000000000000000000000000000000000000000001");
    }
    SUBCASE("- unary")
    {
        BigInt a("100000000000000000000000000000000000000000000000000000000");

        sout << -a;
        REQUIRE(sout.str() == "-100000000000000000000000000000000000000000000000000000000");
    }
    SUBCASE("+ unary")
    {
        BigInt a("100000000000000000000000000000000000000000000000000000000");

        sout << +a;
        REQUIRE(sout.str() == "100000000000000000000000000000000000000000000000000000000");
    }
}
