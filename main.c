#include<stdio.h>// For input/output functions
#include"contact.h"// User-defined header for address book
#include<ctype.h> // For character handling functions
int main() 
{
    int choice, sortchoice;// Initialize sortchoice 
    AddressBook addressBook;// Structure to store contacts

    initialize(&addressBook); //intialize address book

    do 
    {
        // Display main menu options to user
        printf("\n\t\t\t------------Address Book Menu-------------\t\t\t\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");

        printf("Enter your choice: ");//    Read user  choice
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);//create contact & add contact details
                break;
            case 2:
                searchContact(&addressBook);//search already created contact to search contact details
                break;
            case 3:
                editContact(&addressBook);// Edit contact deatails
                break;
            case 4:
                deleteContact(&addressBook);// remove contact from the choice
                break;
            case 5:
                listContacts(&addressBook, sortchoice);//Display contact 
                break;
            case 6:
                printf("Saving and Exiting...\n");// save the data's
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");//wrong input
        }
    } while (choice != 6);
    
    return 0;//End of program
}