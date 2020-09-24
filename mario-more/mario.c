#include <stdio.h>
#include <cs50.h>

void printChars(int j, string str);

int main(void) 
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    
    // Interate by row i, through height n
    for (int i = 1; i <= n; i++)
    {
        printChars(n - i, " ");
        
        //Print left #s
        printChars(i, "#");
        
        //Print spaces in the middle
        printChars(2, " ");
        
        //Print right #s
        printChars(i, "#");
        
        //Print newline
        printf("\n");
        
    }
}

void printChars(int j, string str)
{
    for (int i = 0; i < j; i++)
    {
        printf("%s", str);
    }
}
