#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cstdint>
#include <iostream>
#include <algorithm>

template <typename C>
int sz(const C &c) { return static_cast<int>(c.size()); }

template <typename C>
int compare(C a, C b)
{
    int res = 1, i = 0, j = 0;

    if (sz(a) > sz(b))
    {
        return res;
    }
    if (sz(a) < sz(b))
    {
        return 0;
    }

    for (; i < sz(a) && j < sz(b); i++, j++)
    {
        if (a[i] != b[i])
        {
            res = a[i] > b[i];
            break;
        }
    }
    return res;
}

class BigInt
{
    friend std::ostream &operator<<(std::ostream &out, const BigInt &x);
    friend std::istream &operator>>(std::istream &inp, BigInt &x);
    friend BigInt operator+(const BigInt &a, const BigInt &b);
    friend BigInt operator-(const BigInt &a, const BigInt &b);
    friend BigInt operator*(const BigInt &a, const BigInt &b);

    friend BigInt operator/(const BigInt &a, const BigInt &b);
    friend BigInt operator%(const BigInt &a, const BigInt &b);
    friend int operator<(const BigInt &a, const BigInt &b);
    friend BigInt abs(const BigInt &a);
    friend BigInt operator++(BigInt &a);      // Prefix increment
    friend BigInt operator++(BigInt &a, int); // Postfix increment
    friend BigInt operator--(BigInt &a);      // Prefix decrement
    friend BigInt operator--(BigInt &a, int); // Postfix  decrement
    friend BigInt operator-(BigInt &a);
    friend BigInt operator+(BigInt &a);

    std::vector<long long> mDigits;
    int mIsNegative;

    static BigInt addAbsValues(const BigInt &a, const BigInt &b)
    {
        auto i = a.mDigits.rbegin();
        auto j = b.mDigits.rbegin();

        std::string out = "";

        int carry = 0;
        while (i != a.mDigits.rend() || j != b.mDigits.rend())
        {
            int sum = carry;
            if (i != a.mDigits.rend())
            {
                sum += (*i * a.mIsNegative);
                i++;
            }
            if (j != b.mDigits.rend())
            {
                sum += (*j * b.mIsNegative);
                j++;
            }
            if (sum < 0)
            {
                sum += 10;
                carry = -1;
                out += std::to_string(sum % 10);
                continue;
            }
            else
            {
                carry = sum / 10;
                out += std::to_string(sum % 10);
            }
        }
        if (carry)
        {
            out += std::to_string(carry);
        }
        std::reverse(out.begin(), out.end());

        return BigInt(out);
    }

public:
    explicit BigInt()
        : mIsNegative(1)
    {
        mDigits.push_back(0);
    }
    explicit BigInt(const std::string &n)
    {
        if (n.empty())
        {
            throw std::runtime_error("Empty string");
        }
        mIsNegative = n[0] == '-' ? -1 : 1;

        int nonZero = 0;
        for (int i = 0; i < sz(n); i++)
        {
            if ((n[i] == '-' || n[i] == '+') && i == 0)
            {
                continue;
            }
            if (!isdigit(n[i]))
            {
                throw std::runtime_error("Incorrect input " + n);
            }
            if (isdigit(n[i]) && n[i] != '0')
            {
                nonZero = 1;
            }
            if (nonZero)
            {
                mDigits.push_back((n[i] - '0'));
            }
        }
        if (!nonZero && n[0] == '0')
        {
            mDigits.push_back(0);
        }

        if (mDigits.empty())
        {
            throw std::runtime_error("Empty mDigits");
        }
    }
    BigInt(long long n)
        : BigInt(std::to_string(n))
    {
    }
};

std::ostream &operator<<(std::ostream &out, const BigInt &x)
{
    if (x.mIsNegative == -1)
    {
        out << "-";
    }
    for (auto digit : x.mDigits)
    {
        out << digit;
    }
    return out;
}

std::istream &operator>>(std::istream &inp, BigInt &x)
{
    std::string n;
    if (!(inp >> n))
    {
        return inp;
    }
    for (int i = 0; i < sz(n); i++)
    {
        if ((n[i] == '-' || n[i] == '+') && i == 0)
        {
            continue;
        }
        if (!isdigit(n[i]))
        {
            inp.setstate(std::ios_base::failbit);
            return inp;
        }
    }
    x = BigInt(n);

    return inp;
}

int operator<(const BigInt &a, const BigInt &b)
{
    if (a.mIsNegative < b.mIsNegative)
    {
        return 1;
    }
    else if (a.mIsNegative > b.mIsNegative)
    {
        return 0;
    }

    if (a.mIsNegative == 1 && b.mIsNegative == 1)
    {
        if (sz(a.mDigits) < sz(b.mDigits))
        {
            return 1;
        }
        else if (sz(a.mDigits) > sz(b.mDigits))
        {
            return 0;
        }
    }

    if (a.mIsNegative == -1 && b.mIsNegative == -1)
    {
        if (sz(a.mDigits) < sz(b.mDigits))
        {
            return 0;
        }
        else if (sz(a.mDigits) > sz(b.mDigits))
        {
            return 1;
        }
    }

    for (int i = 0; i < sz(a.mDigits) && i < sz(b.mDigits); i++)
    {
        if (a.mDigits[i] != b.mDigits[i])
        {
            if (a.mIsNegative == 1 && b.mIsNegative == 1)
            {
                return a.mDigits[i] < b.mDigits[i];
            }
            else
            {
                return !(a.mDigits[i] < b.mDigits[i]);
            }
        }
    }
    return 0;
}
int operator>(const BigInt &a, const BigInt &b)
{
    return b < a;
}

int operator==(const BigInt &a, const BigInt &b)
{
    return (!(a < b) && !(b < a));
}

int operator!=(const BigInt &a, const BigInt &b)
{
    return !(a == b);
}

int operator<=(const BigInt &a, const BigInt &b)
{
    return (a < b || a == b);
}

int operator>=(const BigInt &a, const BigInt &b)
{
    return (b < a || b == a);
}

BigInt operator+(const BigInt &a, const BigInt &b)
{
    if (a.mIsNegative == b.mIsNegative) // if both are negative/ positive, just add
    {
        BigInt a1 = a, b1 = b;

        a1.mIsNegative = 1;
        b1.mIsNegative = 1;

        BigInt t = a1.addAbsValues(a1, b1);
        t.mIsNegative = a.mIsNegative;

        return t;
    }
    else
    {
        BigInt a1, b1;
        if (a.mIsNegative == 1 && b.mIsNegative == -1)
        {
            a1 = a;
            b1 = b;
        }
        else
        {
            a1 = b;
            b1 = a;
        }

        if (compare(a1.mDigits, b1.mDigits))
        {
            return a.addAbsValues(a1, b1);
        }
        else
        {
            BigInt tA = a1, tB = b1;

            tA.mIsNegative = b1.mIsNegative;
            tB.mIsNegative = a1.mIsNegative;

            BigInt res = a1.addAbsValues(tB, tA);
            res.mIsNegative = res.mIsNegative * (-1);

            return res;
        }
    }
}
BigInt abs(const BigInt &a)
{
    BigInt absA = a;
    absA.mIsNegative = 1;
    return absA;
}

BigInt operator-(const BigInt &a, const BigInt &b)
{
    BigInt b1 = b;
    b1.mIsNegative = -b1.mIsNegative;

    return (a + b1);
}

void operator+=(BigInt &a, const BigInt &b)
{
    a = a + b;
}

void operator-=(BigInt &a, const BigInt &b)
{
    a = a - b;
}

BigInt operator*(const BigInt &a, const BigInt &b)
{
    BigInt result;
    result.mDigits.resize(sz(a.mDigits) + sz(b.mDigits));

    if (a == BigInt() || b == BigInt()) // multiplication by zero
    {
        return BigInt();
    }

    const std::vector<long long> &x = (abs(a) > abs(b) ? a.mDigits : b.mDigits);
    const std::vector<long long> &y = (abs(a) < abs(b) ? a.mDigits : b.mDigits);

    int shift = 0, end = sz(result.mDigits) - 1;
    for (int i = sz(y) - 1; i >= 0; i--, shift++) // multiplication process
    {
        int index = shift;
        for (int j = sz(x) - 1; j >= 0; j--, index++)
        {
            int sum = y[i] * x[j];

            result.mDigits[end - index] += sum;
        }
    }
    for (int i = sz(result.mDigits) - 1; i > 0; i--) // handling carries
    {
        int carry = result.mDigits[i] / 10;
        result.mDigits[i] %= 10;
        result.mDigits[i - 1] += carry;
    }

    if (result.mDigits.front() == 0) // deleting zeroes
    {
        result.mDigits.erase(result.mDigits.begin());
    }

    if (a.mIsNegative != b.mIsNegative)
    {
        result.mIsNegative = -1;
    }
    return result;
}

BigInt operator/(const BigInt &a, const BigInt &b)
{
    std::string value = "", ans = "0";

    BigInt divisor = b;
    divisor.mIsNegative = 1;

    if (divisor.mDigits[0] == 0)
    {
        throw std::runtime_error("Devision by zero");
    }

    int i = 0, end = sz(a.mDigits);
    for (; i < end && i < sz(b.mDigits); i++) // init of dividor
    {
        value += std::to_string(a.mDigits[i]);
    }
    --i;
    while (i < end)
    {
        BigInt temp(value);

        int q = 0;
        while (temp >= divisor) // number of divents
        {
            temp -= divisor;
            q++;
        }
        ans += std::to_string(q);

        value = "";
        for (int j = 0; j < sz(temp.mDigits); j++) // rest remainder from substraction
        {
            value += std::to_string(temp.mDigits[j]);
        }
        ++i;
        if (i < end)
            value += std::to_string(a.mDigits[i]);
    }

    BigInt result(ans);

    if (a.mIsNegative != b.mIsNegative)
    {
        result.mIsNegative = -1;
    }

    return result;
}

BigInt operator%(const BigInt &a, const BigInt &b)
{

    return a - ((a / b) * b);
}

void operator/=(BigInt &a, const BigInt &b)
{
    a = a / b;
}

void operator*=(BigInt &a, const BigInt &b)
{
    a = a * b;
}

void operator%=(BigInt &a, const BigInt &b)
{
    a = a % b;
}

BigInt operator++(BigInt &a)
{
    a += BigInt(1);
    return a;
}

BigInt operator++(BigInt &a, int)
{
    BigInt temp = a;
    ++a;
    return temp;
}

BigInt operator--(BigInt &a)
{
    a -= BigInt(1);
    return a;
}

BigInt operator--(BigInt &a, int)
{
    BigInt temp = a;
    --a;
    return temp;
}

BigInt operator-(BigInt &a)
{
    a.mIsNegative *= -1;
    return a;
}

BigInt operator+(BigInt &a)
{
    return a;
}
