#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //prompt user for 16 digits
    long answer = get_long("Number: ");

    //validate whether it is credit card
    long answerdivideby10 = answer / 10;
    long productsdigit = 0;
    long productsdigit2 = 0;
    long products = 0;
    long sumproductsdigits = 0;
    long sum = 0;
    long sumdigits = 0;
    long answer2 = answer;


    for (long i = 0; i < 15; i++)
    {
        products = answerdivideby10 % 10 * 2;
        answerdivideby10 = answerdivideby10 / 100;
        productsdigit = products % 10;
        productsdigit2 = products / 10 % 10;
        sumproductsdigits = sumproductsdigits + productsdigit + productsdigit2;
        sum = answer2 % 10;
        answer2 = answer2 / 100;
        sumdigits = sumdigits + sum;
    }
    long valid = sumproductsdigits + sumdigits;

    //amex 15 digits, starts with 34 or 37
    if ((floor(answer / (10000000000000)) == 34 || floor(answer / (10000000000000)) == 37) && answer / (10000000000000) < 100
        && ((valid % 10) == 0))
    {
        printf("AMEX\n");
    }
    //master 16 digits, starts with 51,52,53,54 or 55
    else if ((floor(answer / (100000000000000)) == 51 || floor(answer / (100000000000000)) == 52
              || floor(answer / (100000000000000)) == 53
              || floor(answer / (100000000000000)) == 54 || round(answer / (100000000000000)) == 55) && answer / (100000000000000) < 100
             && ((valid % 10) == 0))
    {
        printf("MASTERCARD\n");
    }
    //visa 13 or 16 digits, starts with 4
    else if ((floor(answer / (1000000000000)) == 4 && answer / (100000000000) < 100 && ((valid % 10) == 0))
             || ((floor(answer / (1000000000000000)) == 4)
                 && answer / (100000000000000) < 100 && ((valid % 10) == 0)))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
