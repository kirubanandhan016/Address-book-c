#include <stdio.h> // Standard input/output functions
#include<stdlib.h> // Memory allocation functions
#include "file.h" // Custom header for file operations

// Save all contacts to text file
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "w"); // Open file for writing

    if (fp == NULL)
    {
        printf("Error file\n"); // Check if file opened successfully
        return;
    }

    // Write each contact to file in CSV format
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp); // Close the file
}

// Load contacts from text file into memory
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "r"); // Open file for reading
    if (fp == NULL)
        return; // Exit if file doesn't exist

    // Read contacts from file until max capacity reached
    while (addressBook->contactCount < MAX_CONTACTS &&
           fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++; // Increment contact counter for each successful read
    }

    fclose(fp); // Close the file
}