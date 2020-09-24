#include <stdlib.h>
#include <stdio.h>


int main (int argc, char* argv[])
{

FILE *dictptr = fopen(argv[1], "r");

    if (dictptr == NULL)
    {
        return 0;
    }

    char *word = malloc(45 * sizeof(char) + 1);

    while(fscanf(dictptr, "%s", word) != EOF)
    {
        printf("%s", word);
    }

}