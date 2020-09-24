#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get user's name
    string name = get_string("What is your name?\n");
    
    //Print user's name
    printf("hello, %s\n", name);
}