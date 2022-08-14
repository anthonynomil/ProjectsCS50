#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask what credit card number to check
    long number = get_long("Number: ");

    // Divide the credit card number by 10 so the last number will be our digit
    long a = number / 1000000000000000;
    long b = number / 100000000000000;
    long c = number / 10000000000000;
    long d = number / 1000000000000;
    long e = number / 100000000000;
    long f = number / 10000000000;
    long g = number / 1000000000;
    long h = number / 100000000;
    long i = number / 10000000;
    long j = number / 1000000;
    long k = number / 100000;
    long l = number / 10000;
    long m = number / 1000;
    long n = number / 100;
    long o = number / 10;
    long p = number % 10;

    // Initialize variables for the double digits later on
    long r = 0;
    long s = 0;
    long t = 0;
    long u = 0;
    long v = 0;
    long w = 0;
    long x = 0;
    long y = 0;
    long z = 0;

    // Initialize the variables for the type of card
    bool visa = false;
    bool masterc = false;
    bool amerexp = false;

    //Remove the number before and multiply it by 10 to get a single digit
    o -= n * 10;
    n -= m * 10;
    m -= l * 10;
    l -= k * 10;
    k -= j * 10;
    j -= i * 10;
    i -= h * 10;
    h -= g * 10;
    g -= f * 10;
    f -= e * 10;
    e -= d * 10;
    d -= c * 10;
    c -= b * 10;
    b -= a * 10;

    // Check if the card is an American express
    if (a == 0 && b == 3 && (c == 7 || c == 4))
    {
        amerexp = true;
    }

    // Check if the card is a Visa
    else if ((a == 4) || (a == 0 && b == 0 && c == 0 && d == 4))
    {
        visa = true;
    }

    // Check if the card is a MasterCard
    else if (a == 5 && (b >= 1 && b <= 5))
    {
        masterc = true;
    }

    // Every other digit and multiply it by 2
    a *= 2;
    c *= 2;
    e *= 2;
    g *= 2;
    i *= 2;
    k *= 2;
    m *= 2;
    o *= 2;

    // Checking if a number is > 9 and if the number is higher than this make it two single digit numbers
    if (a > 9)
    {
        r = a % 10;
        a /= 10;
    }
    if (c > 9)
    {
        s = c % 10;
        c /= 10;
    }
    if (e > 9)
    {
        t = e % 10;
        e /= 10;
    }
    if (g > 9)
    {
        u = g % 10;
        g /= 10;
    }
    if (i > 9)
    {
        v = i % 10;
        i /= 10;
    }
    if (k > 9)
    {
        w = k % 10;
        k /= 10;
    }
    if (m > 9)
    {
        x = m % 10;
        m /= 10;
    }
    if (o > 9)
    {
        y = o % 10;
        o /= 10;
    }

    // Add every credit card digit together
    z = a + c + e + g + i + k + m + o + r + s + t + u + v + w + x + y;

    // Add the rest of the credit card numbers
    z = z + b + d + f + h + j + l + n + p;

    // Check what type of card it is and whether it's valid or not
    if (z % 10 == 0)
    {
        if (amerexp == true)
        {
            printf("AMEX\n");
        }
        else if (visa == true)
        {
            printf("VISA\n");
        }
        else if (masterc == true)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}