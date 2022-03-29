#include <stdio.h>
#include <cs50.h>

int main(void)

{
    //Prompt user for height
    int height = 0;
    do
    {
        height = get_int("What is the height? (1-8)\n");
    }
    while (height < 1 || height > 8);

    //Print the pyramid
    for (int i = 0; i < height; i++)
    {
        for (int k = height; k > i + 1; k--)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}