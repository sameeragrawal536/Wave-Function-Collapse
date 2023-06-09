#pragma once

#include "LinkedList.h"
#include "Structures.h"

class HashTable
{
private:
    // Length is the size of the Hash Table array.
    int length;
    int filled;
    
public:
    LinkedList** array;
    
    // Constructs the empty Hash Table object.
    // Array length is set to 13 by default.
    HashTable( int tableLength = 13 );

    bool contains(Pattern* pat);

    bool contains(Pattern* pat, int length);
    
    // Adds an item to the Hash Table.
    void insert(Pattern* key, Pattern* pat);

    void insert(int key, Pattern* pat);

    void operator=(HashTable h);
    
    // Returns an item from the Hash Table by key.
    // If the item isn't found, a null pointer is returned.
    LinkedList* get(Pattern* pat);

    LinkedList* get(int index);
    
    // Display the contents of the Hash Table to console window.
    void printTable();
    
    // Prints a histogram illustrating the Item distribution.
    void printHistogram();
    
    // Returns the number of locations in the Hash Table.
    int getLength();
    
    // Returns the number of Items in the Hash Table.
    int getNumberOfElements();
};