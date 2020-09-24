#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    //If less/more than 2 args, return error and usage description
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //Set key reference to user input second arg
    string key = argv[1];

    //Set keyLength to length of key input
    int keyLength = strlen(key);


    //Check if string is 26 characters
    if (keyLength != 26)
    {
        printf("Your key is not 26 characters in length.\n");
        return 1;
    }

    for (int i = 0; i < keyLength; i++)
    {
        //Check for non-alphabetic characters
        if (!isalpha(key[i]))
        {
            printf("Your key contains non-alphabetic characters.\n");
            return 1;
        }

        for (int j = i + 1; j < keyLength; j++)
        {
            if (key[i] == key[j])
            {
                printf("Your key contains duplicates.\n");
                return 1;
            }
        }
    }

    string plain = get_string("plaintext: ");
    int plainLength = strlen(plain);
    char cipher[strlen(plain)];

    printf("ciphertext: ");

    for (int k = 0; k < plainLength; k++)
    {
        //Check for non-alphabetic characters
        if (!isalpha(plain[k]))
        {
            cipher[k] = plain[k];
            printf("%c", cipher[k]);
        }
        else if (isupper(plain[k]))
        {
            int position = plain[k] - 65;
            cipher[k] = toupper(key[position]);
            printf("%c", cipher[k]);
        }
        else if (islower(plain[k]))
        {
            int position = plain[k] - 97;
            cipher[k] = tolower(key[position]);
            printf("%c", cipher[k]);
        }
    }

    //Pring ending newline and return 0
    printf("\n");
    return 0;
}