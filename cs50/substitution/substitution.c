#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string    substitute(string s, string t);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Please input alphabets only.\n");
            return 1;
        }
    }
    int a = 0;
    int b;
    while (argv[1][a] != 0)
    {
        b = a + 1;
        while (argv[1][b] != 0)
        {
            if (argv[1][a] == argv[1][b])
            {
                printf("Dupliucate alphabets.\n");
                return 1;
            }
            b++;
        }
        a++;
    }
    string s = get_string("plaintext : ");
    string q = substitute(s, argv[1]);
    printf("ciphertext: %s\n", q);
    return 0;
}

string    substitute(string s, string t)
{
    int i = 0;
    while (s[i] != 0)
    {
        while (isalpha(s[i]) != 0)
        {
            int j = 0;
            if (isupper(s[i]) == 0)
            {
                while (t[j] != 0)
                {
                    t[j] = tolower(t[j]);
                    j++;
                }
                j = 0;
                s[i] = t[s[i] - 'a'];
            }
            else if (islower(s[i]) == 0)
            {
                while (t[j] != 0)
                {
                    t[j] = toupper(t[j]);
                    j++;
                }
                j = 0;
                s[i] = t[s[i] - 'A'];
            }
            i++;
        }
        i++;
    }
    return s;
}
