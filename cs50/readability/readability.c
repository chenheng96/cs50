#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_words(string text);
int count_letters(string text);
int count_sentences(string text);

int main(void)
{
    string answer = get_string("Text: ");
    int letters = count_letters(answer);
    int words = count_words(answer);
    int sentences = count_sentences(answer);
    //printf("%s\n", answer);
    printf("%i letters\n", letters);
    printf("%i words\n", words);
    printf("%i sentences\n", sentences);
    float L = letters * 100.0 / words ;
    float S = sentences * 100.0 / words ;
    //printf("L: %f\n", L);
    //printf("S: %f\n", S);
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    //printf("%i grade\n", index);
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isupper(text[i]))
        {
            letters ++;
        }
        else if (islower(text[i]))
        {
            letters ++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 0;
    for (int j = 0, len = strlen(text); j < len; j++)
    {
        if (isspace(text[j]))
        {
            words ++;
        }
    }
    return words + 1;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int k = 0, len = strlen(text); k < len; k++)
    {
        if (text[k] == '.' || text[k] == '!' || text[k] == '?')
        {
            sentences ++;
        }
    }
    return sentences;
}