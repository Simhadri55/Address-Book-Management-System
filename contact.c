/*Documentation
Name        :T Simhadri
Date        :04/07/2025
Description :Address Book project
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook)
{
    int i;
    /* Define the logic for print the contacts */
    printf("\nThere are %d contacts :\n", addressBook->contactCount);
    for (i = 0; i < addressBook->contactCount; i++)
    {
        printf("\nContact %d :\n", i + 1);
        printf("Name     : %s\n", addressBook->contacts[i].name);
        printf("Contact  : %s\n", addressBook->contacts[i].phone);
        printf("Email-ID : %s\n", addressBook->contacts[i].email);
    }
    // printf("%s\n", addressBook->contacts[addressBook->contactCount].name);
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
     loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address book is full.\n");
        return;
    }
    // Read the name from the user
    printf("Enter the contact name: ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);

    char number[20];
    int i, ret = 0;
    while (!ret)
    {
        // Read the contact
        printf("Enter the contact number: ");
        scanf(" %s", number);
        // - Check whether the count is 10 or not
        // - Check all 10 characters are digits or not.
        // - Check the given number is already exist or not
        ret = is_validnumber(addressBook, number); 
        if (ret)
        {
            // Check for duplicate number 
            if (is_duplicate_number(addressBook, number))
            {
                ret = 0;
            }
        }
        if (!ret)
            printf("Invalid mobile number or already existed!\n");
    }

    // storing the number
    strcpy(addressBook->contacts[addressBook->contactCount].phone, number);

    char mail[50];

    // - Check whether char - @ and .com is present or not
    ret = 0;
    while (!ret)
    {
        // Read the email ID
        printf("Enter the Email-ID: ");
        scanf("  %[^\n]", mail);
        ret = is_validemail(addressBook, mail);
        if (ret)
        {
            // Check for duplicate email if return true
            if (is_duplicate_email(addressBook, mail))
            {
                ret = 0;
            }
        }
        if (!ret)
            printf("Invalid Email-ID or already existed!\n");
    }

    // storing the email-ID
    strcpy(addressBook->contacts[addressBook->contactCount].email, mail);

    // Increment the contact count.
    addressBook->contactCount++;
    printf("\nSuccessfully created a contact\n");
}

void searchContact(AddressBook *addressBook)
{
    int choice = 0;
    printf("Select one to search \n");
    printf("1. Name\n");
    printf("2. Number\n");
    printf("3. Email\n");
    printf("4. Back to Menu\n");
    while(1)
    {
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid selection! \n");

                // Clear the invalid characters from the input buffer
            while (getchar() != '\n'); // clear until newline
                continue;
        }

        switch (choice)
        {
        case 1:
            search_name(addressBook);
            return;
        case 2:
            search_number(addressBook);
            return;
        case 3:
            search_email(addressBook);
            return;
        case 4:
            printf("Existing...\n");
            return;
        default:
            printf("Invalid choice!");
        }
    }
}

void editContact(AddressBook *addressBook)
{
    int choice = 0;
    printf("Select one to search \n");
    printf("1. Name\n");
    printf("2. Number\n");
    printf("3. Email\n");
    printf("4. Bact to Menu\n");
    while(1)
    {
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
		{
			printf("\nInvalid selection! \n");

			// Clear the invalid characters from the input buffer
			while (getchar() != '\n'); // clear until newline
			continue;
		}

        switch (choice)
        {
        case 1:
            search_by_name(addressBook, 1);
            return;
        case 2:
            search_by_number(addressBook, 1);
            return;
        case 3:
            search_by_email(addressBook, 1);
            return;
        case 4:
            printf("Existing...\n");
            return;
        default:
            printf("Invalid choice!");
        }
    }
}

void deleteContact(AddressBook *addressBook)
{
    int choice = 0;
    printf("Select one to search \n");
    printf("1. Name\n");
    printf("2. Number\n");
    printf("3. Email\n");
    printf("4. Back to Menu\n");
    while(1)
    {
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
		{
			printf("\nInvalid selection! \n");

			// Clear the invalid characters from the input buffer
			while (getchar() != '\n')
				; // clear until newline
			continue;
		}

        switch (choice)
        {
        case 1:
            search_by_name(addressBook, 0);
            return;
        case 2:
            search_by_number(addressBook, 0);
            return;
        case 3:
            search_by_email(addressBook, 0);
            return;
        case 4:
            printf("Existing...\n");
            return;
        default:
            printf("Invalid choice!");
        }
    }
}
