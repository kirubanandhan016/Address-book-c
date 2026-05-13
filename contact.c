#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "validation.h"
#include <ctype.h>

// Initialize address book with zero contacts
void initialize(AddressBook *addressBook)
{
    // Set contact count to zero
    addressBook->contactCount = 0; // Initialize contact count to zero
}

// Create new contact with validation and duplicate checking
void createContact(AddressBook *addressBook)
{
    // Check if address book has reached maximum capacity
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        // Display error message if maximum capacity reached
        printf("Address book reached max contact\n"); // Check maximum capacity
        return;
    }

    // Get pointer to next available contact slot
    Contact *newContact = &addressBook->contacts[addressBook->contactCount]; // Get next available slot
    int i;

    char name[50];
    char phone[20];
    char email[50];

    // Name validation with 3 attempts
    for(i = 0; i < 3; i++)
    {
        printf("Enter the name: ");
        scanf(" %[^\n]", name);

        if(!validate_name(name))
        {
            printf("Invalid name. Try again\n");
            continue;
        }

        // Check for duplicate name
        int flag = 0;
        for(int j = 0; j < addressBook->contactCount; j++)
        {
            if(strcmp(addressBook->contacts[j].name, name) == 0)
            {
                printf("Name already available, save another name\n");
                flag = 1;
                break;
            }
        }

        if(flag) continue;
        break;
    }

    if(i == 3)
    {
        printf("Attempts finished\n");
        return;
    }

    // Phone validation with 3 attempts
    for(i = 0; i < 3; i++)
    {
        printf("Enter the phone: ");
        scanf("%19s", phone);

        if(!validate_phone(phone))
        {
            printf("Invalid phone number\n");
            continue;
        }

        // Check for duplicate phone
        int flag = 0;
        for(int j = 0; j < addressBook->contactCount; j++)
        {
            if(strcmp(addressBook->contacts[j].phone, phone) == 0)
            {
                printf("Phone number already exists\n");
                flag = 1;
                break;
            }
        }

        if(flag) continue;
        break;
    }

    if(i == 3)
    {
        printf("Invalid attempts\n");
        return;
    }

    // Email validation with 3 attempts
    for(i = 0; i < 3; i++)
    {
        printf("Enter the email: ");
        scanf("%49s", email);

        if(!validate_email(email))
        {
            printf("Invalid email retry\n");
            continue;
        }

        // Check for duplicate email
        int flag = 0;
        for(int j = 0; j < addressBook->contactCount; j++)
        {
            if(strcmp(addressBook->contacts[j].email, email) == 0)
            {
                printf("Email already exists\n");
                flag = 1;
                break;
            }
        }

        if(flag) continue;
        break;
    }

    if(i == 3)
    {
        printf("Invalid attempts\n");
        return;
    }

    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    strcpy(newContact->email, email);
    addressBook->contactCount++;

    printf("Contact successfully saved\n");
}

/* ---------------- SEARCH ---------------- */

// Search for contacts by name, phone, or email
void searchContact(AddressBook *addressBook)
{
    int choice;
    char key[50]; // Search term
    int found = 0; // Flag to track if contact is found

    printf("\nSearch Contact by:\n");
    printf("1.Name\n2.Phone\n3.Email\n");
    printf("Enter choice: ");
    scanf("%d", &choice); // Get search criteria

    printf("Enter search key: ");
    scanf(" %[^\n]", key); // Get search term

    // Search through all contacts
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        Contact c = addressBook->contacts[i];

        // Check if contact matches search criteria
        if((choice == 1 && strcmp(c.name, key) == 0) ||
           (choice == 2 && strcmp(c.phone, key) == 0) ||
           (choice == 3 && strcmp(c.email, key) == 0))
        {
            printf("\nContact Found:\n");
            printf("Name  : %s\n", c.name);
            printf("Phone : %s\n", c.phone);
            printf("Email : %s\n", c.email);
            found = 1; // Mark as found
        }
    }

    if(!found)
        printf("No matching contact found\n"); // Show message if no contact found
}

/* ---------------- EDIT ---------------- */

// Edit existing contact information
void editContact(AddressBook *addressBook)
{
    int choice, found = 0;
    char key[50]; // Search term to find contact

    printf("Edit by contact\n");
    printf("1.Name\n2.Phone\n3.Email\n");
    printf("Enter the choice: ");
    scanf("%d", &choice); // Get search criteria

    printf("Enter the key: ");
    scanf(" %[^\n]", key); // Get search term

    // Search for contact to edit
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        Contact *c = &addressBook->contacts[i];

        // Check if contact matches search criteria
        if((choice == 1 && strcmp(c->name, key) == 0) ||
           (choice == 2 && strcmp(c->phone, key) == 0) ||
           (choice == 3 && strcmp(c->email, key) == 0))
        {
            found = 1; // Mark contact as found

            printf("\nContact Found:\n");
            printf("1.Edit Name\n2.Edit Phone\n3.Edit Email\n");

            int editChoice;
            scanf("%d", &editChoice); // Get field to edit

            int attempts;

            if(editChoice == 1) // Edit name
            {
                for(attempts = 0; attempts < 3; attempts++)
                {
                    printf("Enter new name: ");
                    scanf(" %[^\n]", c->name);

                    if(validate_name(c->name))
                        break; // Exit if valid

                    printf("Invalid name\n");
                }
            }
            else if(editChoice == 2) // Edit phone
            {
                for(attempts = 0; attempts < 3; attempts++)
                {
                    printf("Enter new phone number: ");
                    scanf("%19s", c->phone);

                    if(validate_phone(c->phone))
                        break; // Exit if valid

                    // Show error if invalid
                    printf("Invalid phone number\n");
                }
            }
            else if(editChoice == 3) // Edit email
            {
                // Loop for 3 validation attempts
                for(attempts = 0; attempts < 3; attempts++)
                {
                    // Prompt user to enter new email
                    printf("Enter new email: ");
                    scanf("%49s", c->email);

                    // Validate email format
                    if(validate_email(c->email))
                        break; // Exit if valid

                    // Show error if invalid
                    printf("Invalid email\n");
                }
            }

            // Show success message
            printf("Contact updated successfully\n");
            return; // Exit after successful edit
        }
    }

    // Show message if contact not found
    if(!found)
        printf("Contact not found\n"); // Show message if no contact found
}

/* ---------------- DELETE ---------------- */

// Delete contact from address book
void deleteContact(AddressBook *addressBook)
{
    int choice, found = 0;
    char key[50]; // Search term to find contact

    // Display delete menu
    printf("\nDelete contact:\n");
    printf("1.Name\n2.Phone\n3.Email\n");

    // Get search criteria from user
    scanf("%d", &choice); // Get search criteria

    // Get search term from user
    printf("Enter the search key: ");
    scanf(" %[^\n]", key); // Get search term

    // Search for contact to delete
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        // Check if contact matches search criteria
        if((choice == 1 && strcmp(addressBook->contacts[i].name, key) == 0) ||
           (choice == 2 && strcmp(addressBook->contacts[i].phone, key) == 0) ||
           (choice == 3 && strcmp(addressBook->contacts[i].email, key) == 0))
        {
            found = 1; // Mark contact as found

            // Shift remaining contacts to fill the gap
            for(int j = i; j < addressBook->contactCount - 1; j++)
                addressBook->contacts[j] = addressBook->contacts[j+1];

            // Decrement contact counter
            addressBook->contactCount--; // Decrement contact counter

            // Show success message
            printf("Contact deleted\n");
            return; // Exit after successful deletion
        }
    }

    // Show message if contact not found
    if(!found)
        printf("Contact not found\n");
}

/* ---------------- LIST ---------------- */

// List all contacts with sorting options
void listContacts(AddressBook *addressBook, int sortchoice)
{
    // Check if address book is empty
    if(addressBook->contactCount == 0)
    {
        printf("\nNo contacts available in contacts\n"); // Check if address book is empty
        return;
    }

    // Temporary variable for swapping contacts
    Contact temp; // Temporary variable for swapping

    // Display sorting options
    printf("1.Name\n2.Phone\n3.Email\n");
    // Get sorting preference from user
    scanf("%d", &sortchoice); // Get sorting preference

    // Bubble sort algorithm to sort contacts
    for(int i = 0; i < addressBook->contactCount - 1; i++)
    {
        // Inner loop for bubble sort
        for(int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            // Variable for comparison result
            int cmp = 0;

            // Compare based on user's choice
            if(sortchoice == 1)
                cmp = strcmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name);
            else if(sortchoice == 2)
                cmp = strcmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone);
            else if(sortchoice == 3)
                cmp = strcmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email);

            // Swap if out of order
            if(cmp > 0)
            {
                // Perform swap operation
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }

    // Display contact list header
    printf("\n=========== CONTACT LIST ==========\n");

    // Display all sorted contacts
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        // Display contact number
        printf("\nContact %d\n", i + 1);
        // Display separator
        printf("-----------------------------\n");
        // Display contact details
        printf("Name  : %s\n", addressBook->contacts[i].name);
        printf("Phone : %s\n", addressBook->contacts[i].phone);
        printf("Email : %s\n", addressBook->contacts[i].email);
    }

    // Display list footer
    printf("\n===================================\n");
}