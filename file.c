/*Documentation
Name        :T Simhadri
Date        :04/07/2025
Description :Address Book project
*/
#include <stdio.h>      
#include "file.h"          
#include "contact.h"        

// This function saves contacts into a CSV file
void saveContactsToFile(AddressBook *addressBook)
{
    // Open the file to write
    FILE *fptr = fopen("contacts.csv", "w");
    if (fptr == NULL)
    {
        // Show error if file can't open
        fprintf(stderr, "Cannot open the file for writing\n");
        return;
    }

    // Write all contacts one by one
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,  
                addressBook->contacts[i].phone,  
                addressBook->contacts[i].email); 
    }

    // Close the file after saving
    fclose(fptr);
}

// This function reads contacts from a CSV file
void loadContactsFromFile(AddressBook *addressBook)
{
    // Open the file to read
    FILE *fptr = fopen("contacts.csv", "r");
    if (fptr == NULL)
    {
        // Show error if file can't open
        fprintf(stderr, "Cannot open the file for reading\n");
        return;
    }

    int i = 0; // Counter for contacts
    // Read contacts one by one
    while (i < MAX_CONTACTS)
    {
        // Read name, phone, and email from the file
        int ret = fscanf(fptr, "%99[^,],%19[^,],%99[^\n]\n",
                         addressBook->contacts[i].name,
                         addressBook->contacts[i].phone,
                         addressBook->contacts[i].email);

        // Stop if data is not correct
        if (ret != 3)
        {
            break;
        }

        i++; // Next contact
    }

    // Save total contacts count
    addressBook->contactCount = i;

    // Close the file after reading
    fclose(fptr);
}
