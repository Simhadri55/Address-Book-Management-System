/*Documentation
Name        :T Simhadri
Date        :04/07/2025
Description :Address Book project
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

//validtion function for number
int is_validnumber(AddressBook *addressBook, char *number)
{
    int i = 0;

    // Check if the number has exactly 10 digits
    while (number[i] != '\0')
    {
        if (number[i] < '0' || number[i] > '9') // Check if each char is digit or not
            return 0;
        i++;
    }

    if (i != 10) //number must conatins 10 numbers
        return 0;

    return 1;
}
int is_validemail(AddressBook *addressBook, char *mail)
{
    int i=0,len=strlen(mail),count=0;
    //email must contain minimum 7 characters
    if(len<7)
        return 0;

    // email should have only one '@'
    for(i = 0; i < len;i++)
    {
        if(mail[i]=='@')
        {
            count++;
        }
    }
    if(count>1)
        return 0;
    //checking for '.'
    for (i = 0; mail[i] != '\0';i++)
    {
        if ((mail[i]) == '.' && (mail[i + 1]) == '.')
            return 0;
    }

    //checking '@' and ".com" 
    if (strchr(mail, '@') && strstr(mail, ".com"))
    {
        i = 0;
        while (mail[i] == '@')
        {
            if(!isalnum(mail[i-1]) || !isalnum(mail[i+1]))
            {
                return 0;
            }
            i++;
        }
        //checking for .com is present at last or not
        char *ch = strstr(mail,".com"); 
        if(strcmp(ch, ".com")!=0)
            return 0;
        for (i = 0; i < len;i++)
        {
            if((mail[i]==' ') || (isupper(mail[i]))) //checking for space and uppercase alphabets
                return 0;
        }
    }
    else 
        return 0;
    return 1;
}

// Search contact
void search_name(AddressBook *addressBook)
{
    int i, found = 0;
    char new_name[20];

    while(!found)
    {
        printf("Enter the contact name: ");
        scanf(" %[^\n]", new_name); // Reads input with spaces

        // Searching for all contacts with matching name
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, new_name) == 0)
            {
                printf("\nContact %d:\n", found + 1);
                printf("Name     : %s\n", addressBook->contacts[i].name);
                printf("Contact  : %s\n", addressBook->contacts[i].phone);
                printf("Email-ID : %s\n", addressBook->contacts[i].email);
                found++;
            }
        }
        // If no match found
        if (found == 0)
        {
            printf("Contact not found, enter correct name\n");
        }
    }
}
void search_number(AddressBook *addressBook)
{
    int i, found = 0;
    char number[20];

    int ret = 0;
    while (!ret)
    {
        printf("Enter the contact number: ");
        scanf(" %[^\n]", number);

        ret = is_validnumber(addressBook, number); // number validation
        // Searching for all contacts with matching numbers
        if (ret)
        {
            for (i = 0; i < addressBook->contactCount; i++)
            {
                //comparing the entered number with existed contacts
                if (strcmp(addressBook->contacts[i].phone, number) == 0)
                {
                    printf("\nContact %d:\n", found + 1);
                    printf("Name     : %s\n", addressBook->contacts[i].name);
                    printf("Contact  : %s\n", addressBook->contacts[i].phone);
                    printf("Email-ID : %s\n", addressBook->contacts[i].email);
                    found++;
                    break;
                }
            }
        }
        if (!ret)
            printf("Invalid number!\n"); //if number is invalid
    }
    // If no match found
    if (found == 0)
    {
        printf("Contact not found\n");
    }
}

void search_email(AddressBook *addressBook)
{
    int i, found = 0;
    char mail[50];

    int ret = 0;
    while (!ret)
    {
        printf("Enter the Email-ID: ");
        scanf(" %[^\n]", mail);
        ret = is_validemail(addressBook, mail); //validating the mail
        if (ret)
        {
            // Searching for all contacts with matching email
            for (i = 0; i < addressBook->contactCount; i++)
            {
                //comparing the given mail with existed contacts
                if (strcmp(addressBook->contacts[i].email, mail) == 0)
                {
                    printf("\nContact %d:\n", found + 1);
                    printf("Name     : %s\n", addressBook->contacts[i].name);
                    printf("Contact  : %s\n", addressBook->contacts[i].phone);
                    printf("Email-ID : %s\n", addressBook->contacts[i].email);
                    found++;
                    break;
                }
            }
        }
        if (!ret)
            printf("Invalid Email-ID!\n");
    }
    // If no match found
    if (found == 0)
    {
        printf("Contact not found\n");
    }
}

//  Editing the contact
void search_by_name(AddressBook *addressBook, int flag)
{
    int i, count = 0;
    char new_name[20];
    int name_index[MAX_CONTACTS];

    while (1)
    {
        printf("Enter the contact name: ");
        scanf(" %[^\n]", new_name); 

        count = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            //Comparing the new_name with existed Contacts
            if (strcmp(addressBook->contacts[i].name, new_name) == 0)
                name_index[count++] = i;
        }

        if (count == 0)
        {
            printf("Invalid Name! or Contact name not found.\n");
            continue;
        }
        else
        {
            if (flag) //flag==1
            {
                edit_contact(addressBook, name_index, count);
                break;
            }
            else //flag==0
            {
                delete_contact(addressBook, name_index, count);
                break;
            }
        }
    }
}

void search_by_number(AddressBook *addressBook, int flag)
{
    int i, count = 0;
    char new_number[20];
    int number_index[5];

    while (1)
    {
        printf("Enter the contact number: ");
        scanf(" %[^\n]", new_number);

        // validation function for new_number
        if (!is_validnumber(addressBook, new_number))
        {
            printf("Invalid number format!\n");
            continue; //skips remaining instructions
        }

        count = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            //comapring the new number with existed contacts
            if (strcmp(addressBook->contacts[i].phone, new_number) == 0)
                number_index[count++] = i;
        }

        if (count == 0)
        {
            printf("Contact number not found.\n");
            continue;
        }
        else
        {
            if (flag) //flag==1
            {
                edit_contact(addressBook, number_index, count);
                break;
            }
            else //flag==0
            {
                delete_contact(addressBook, number_index, count);
                break;
            }
        }
    }
}

void search_by_email(AddressBook *addressBook, int flag)
{
    int i, count = 0;
    char new_email[50];
    int email_index[MAX_CONTACTS];

    while (1)
    {
        printf("Enter the contact email: ");
        scanf(" %[^\n]", new_email);

        // validation function for email
        if (!is_validemail(addressBook, new_email))
        {
            printf("Invalid email format!\n");
            continue;
        }

        count = 0;
        for (i = 0; i < addressBook->contactCount; i++)
        {
            //Comparing the new email with existed contact emails
            if (strcmp(addressBook->contacts[i].email, new_email) == 0)
                email_index[count++] = i;
        }

        if (count == 0)
        {
            printf("Contact email not found.\n");
            continue;
        }
        else
        {
            if (flag) //flag==1
            {
                edit_contact(addressBook, email_index, count);
                break;
            }
            else //flag==0
            {
                delete_contact(addressBook, email_index, count);
                break;
            }
        }
    }
}

// Editing the contact
void edit_contact(AddressBook *addressBook, int *index, int count)
{
    int i, ret = 0, choice = 0, select = 1, selected_index = 0;
    char edit_name[30], edit_number[15], edit_email[40];

    printf("\nThese are the matched contacts:\n");
    for (i = 0; i < count; i++)
    {
        //printing the matched contacts
        printf("\nContact %d:\n", i + 1);
        printf("Name     : %s\n", addressBook->contacts[index[i]].name);
        printf("Contact  : %s\n", addressBook->contacts[index[i]].phone);
        printf("Email-ID : %s\n", addressBook->contacts[index[i]].email);
    }

    if (count > 1)
    {
        while (1)
        { 
            printf("\nSelect one contact to edit 1 to %d and 0 for menu : ", count);
            scanf("%d", &select);

            if (select >= 1 && select <= count) //number between 1 and count
                break;
            else if(select==0)
                return;
            else
                printf("\nInvalid selection!\n");
        }
    }

    selected_index = index[select - 1]; // Exact index (arr index starts from 0)

    while (!ret)
    {
        printf("\nSelect choice to edit:\n");
        printf("1. Name\n2. Number\n3. Email\n4. Back to Menu\nEnter your choice: \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            printf("Enter the new name: ");
            scanf(" %[^\n]", edit_name);
            strcpy(addressBook->contacts[selected_index].name, edit_name); //copyiong the new name with existed name
            ret = 1;
            break;
        }
        case 2:
        {
            while (1)
            {
                printf("Enter the new contact number : ");
                scanf(" %[^\n]", edit_number);

                // validation function for number
                if (!is_validnumber(addressBook, edit_number))
                {
                    printf("Invalid number format!\n");
                    continue;
                }
                // Checking for duplicate numbers
                if (!(is_duplicate_number(addressBook, edit_number)))
                {
                    strcpy(addressBook->contacts[selected_index].phone, edit_number); //Copying the new number with existed number
                    ret = 1;
                    break;
                }
                else
                    printf("\nNumber already existed!\n");
            }
            break;
        }
        case 3:
        {
            while (1)
            {
                printf("Enter the new Email-ID: ");
                scanf(" %[^\n]", edit_email);

                //validating the email
                if (!is_validemail(addressBook, edit_email))
                {
                    printf("Invalid email format!\n");
                    continue;
                }

                // Checking for duplicates
                if (!(is_duplicate_email(addressBook, edit_email)))
                {
                    strcpy(addressBook->contacts[selected_index].email, edit_email);//Copying the new email with existed email
                    ret = 1;
                    break;
                }
                else
                    printf("\nEmail-ID already existed!\n");
            }
            break;
        }
        case 4:
            printf("Existing...\n");
            return;
        default:
            printf("Invalid choice!\n");
        }
    }

    // Displaying the edited contact
    printf("\nSuccessfully edited contact\n");
    printf("Name     : %s\n", addressBook->contacts[selected_index].name);
    printf("Contact  : %s\n", addressBook->contacts[selected_index].phone);
    printf("Email-ID : %s\n", addressBook->contacts[selected_index].email);
}

// Delete contact function
void delete_contact(AddressBook *addressBook, int *index, int count)
{
    int i, select = 1, selected_index = 0;

    printf("\nThese are the matched contacts:\n");
    for (i = 0; i < count; i++)
    {
        printf("\nContact %d:\n", i + 1);
        printf("Name     : %s\n", addressBook->contacts[index[i]].name);
        printf("Contact  : %s\n", addressBook->contacts[index[i]].phone);
        printf("Email-ID : %s\n", addressBook->contacts[index[i]].email);
    }

    // until a valid selection loop will iterating
    while (1)
    {
        printf("\nSelect one contact to delete 1 to %d and 0 for back to menu : ", count);
        scanf("%d", &select);

        if (select >= 1 && select <= count) //number between 1 and count
            break;
        else if(select==0)
            return;
        else
            printf("Invalid selection! Please try again.\n");
    }

    selected_index = index[select - 1];

    // Shifting the contacts to the left to overwrite the selected contact
    for (i = selected_index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1]; 
    }

    addressBook->contactCount--;

    printf("\nSuccessfully deleted the selected contact\n");
}

// Duplicate funtion for number
int is_duplicate_number(AddressBook *addressBook, char *number)
{
    int i;
    for (i = 0; i < addressBook->contactCount; i++) //upto no of contactCount
    {
        if (strcmp(addressBook->contacts[i].phone, number) == 0) //comparing for duplicates
        {
            return 1;
        }
    }
    return 0;
}

int is_duplicate_email(AddressBook *addressBook, char *email)
{
    int i;
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0) //comparing
        {
            return 1;
        }
    }
    return 0;
}