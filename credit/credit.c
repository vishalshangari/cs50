#include <stdio.h>
#include <cs50.h>

bool validate(long n);

int main(void)
{
    // Get credit card number
    long n = get_long("Number: ");
    
    // Check if credit card number is of valid format
    if (validate(n))
    {
        // Check what type of card
        if (n / 10000000000000 == 34 || n / 10000000000000 == 37)
        {
            printf("AMEX\n");
        }
        else if (n / 100000000000000 >= 51 && n / 100000000000000 <= 55)
        {
            printf("MASTERCARD\n");
        }
        else if (n / 1000000000000 == 4 || n / 1000000000000000 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    
}

bool validate(long n)
{
    // Set checksum total to 0
    int total = 0;
    
    // Loop through every other digit starting at second last
    for (long i = n, k = 1; i > 0; i = i / 10, k++)
    {
        // Check if digit is even place
        if (k % 2 == 0)
            if (i % 10 < 5)
            {
                total += (i % 10) * 2;
            }
            else
            {
                total += ((i % 10) * 2) % 10 + 1;
            }
        // Otherwise since odd place
        else
        {
            total += i % 10;
        }
    }
    
    //Check if modulo of total is 0 and return result
    if (total % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}