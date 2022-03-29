#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int x;
    do
    {
        x = get_int("What is the start size?\n");
    }
    while (x < 9);
    
    
    // TODO: Prompt for end size
    int y;
    do
    {
        y = get_int("What is the end size?\n");
    }
    while (y < x);
    
    
    // TODO: Calculate number of years until we reach threshold
    int n = 0;
    do
    {
        x = x + (x / 3) - (x / 4);
        n++;
    }
    while (x < y);
    
    // TODO: Print number of years
    printf("Years: %i\n", n);
}