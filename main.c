/*Documentation
Name        :T Simhadri
Date        :04/07/2025
Description :Address Book project
*/
#include "contact.h"
#include "file.h"

int main() 
{
    int choice;

    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
	//addressBook.contactCount = 0;

	do 
    {
	printf("\nAddress Book Menu:\n");
	printf("1. Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. Save and Exit\n");
	printf("Enter your choice: ");
	if (scanf("%d", &choice) != 1)
	{
		printf("\nInvalid selection! \n");

		// Clear the invalid characters from the input buffer(flush)
		while (getchar() != '\n'); // clear until newline
			continue;
	}

	switch (choice) 
	{
	    case 1:
			createContact(&addressBook); //create an contact
			break;
	    case 2:
			searchContact(&addressBook); //search the matched contacts
			break;
	    case 3:
			editContact(&addressBook); //edit the select contact
			break;
	    case 4:
			deleteContact(&addressBook); //delete the selected contact
			break;
	    case 5:
			listContacts(&addressBook); // list all the contacts
			break;
	    case 6:
			printf("Saving and Exiting...\n");
			saveContactsToFile(&addressBook);
			saveAndExit(&addressBook);
			break;
	    default:
			printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 6); 

    //cleanup(); // Cleanup any resources before exiting
    return 0;
}
