// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned N = 24342394;

// Number of words loaded into dictionary
int wordcount = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char check_word[strlen(word)];
    strcpy(check_word, word);

    for (int i = 0; check_word[i] != '\0'; i++)
    {
        check_word[i] = tolower(check_word[i]);
    }

    int index = hash(check_word);

    if (table[index] != NULL)
    {
        for (node* nodeptr = table[index]; nodeptr != NULL; nodeptr = nodeptr->next)
        {
            if (strcmp(nodeptr->word, check_word) == 0)
            {
                return true;
            }
        }
    }
    return false;

}

// Hashes word to a number
// Using the famous djb2 hash function
unsigned int hash(const char *word)
{
    int hash = 0;
    int n;

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))
            n = word[i] - 'a' + 1;
        else
            n = 27;

        hash = ((hash << 3) + n) % N;
    }

    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dictptr = fopen(dictionary, "r");

    if (dictptr == NULL)
    {
        return false;
    }

    char *word = malloc(LENGTH * sizeof(char) + 1);

    while(fscanf(dictptr, "%s", word) != EOF)
    {
        if (!add_to_hash_table(word))
            return false;
        wordcount++;
    }

    free(word);
    fclose(dictptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (wordcount == 0)
        return 0;
    else
        return wordcount;
}

void free_nodes(node *n);

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *np;
        while ((np = table[i]) != NULL)
        {
            table[i] = table[i]->next;
            free(np);
        }
    }
    return true;
}

// Adds word of dictionary to hash table
bool add_to_hash_table(char *word)
{
    node *np = malloc(sizeof(node));

    if (np == NULL)
    {
        return false;
    }

    unsigned hashval;

    hashval = hash(word);
    strcpy(np->word, word);
    np->next = table[hashval];
    table[hashval] = np;

    return true;
}

void free_nodes(node *n)
{

}