#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char    rotate(char c, int i);

int main(int argc, string argv[])
{
    int i = 0;
    int k = 0;
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    while (argv[1][i] != 0)
    {
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        i++;
    }
    int j = atoi(argv[1]);
    string s = get_string("plaintext: ");
    while (s[k] != 0)
    {
        s[k] = rotate(s[k], j);
        k++;
    }
    printf("ciphertext: %s\n", s);
}

char    rotate(char c, int i)
{
    if (isalpha(c))
    {
        c = c + (i % 26);
        if (!(isalpha(c)))
        {
            c = c - 26;
        }
    }
    return c;
}
