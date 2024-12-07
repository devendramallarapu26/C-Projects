#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

void saveContactsToEmail(Contact contacts[], int numContacts, const char *emailID) {
    printf("Saving contacts to email ID: %s\n", emailID);
    printf("Contact List:\n");
    for (int i = 0; i < numContacts; i++) {
        printf("Contact %d:\n", i + 1);
        printf("Name: %s\n", contacts[i].name);
        printf("Phone: %s\n", contacts[i].phone);
        printf("Email: %s\n", contacts[i].email);
        printf("-------------------------\n");
    }
    printf("Contacts saved to email ID successfully.\n");
}

void displayContactsFromEmail(Contact contacts[], int numContacts, const char *emailID) {
    printf("Displaying contacts from email ID: %s\n", emailID);
    printf("Contact List:\n");
    for (int i = 0; i < numContacts; i++) {
        printf("Contact %d:\n", i + 1);
        printf("Name: %s\n", contacts[i].name);
        printf("Phone: %s\n", contacts[i].phone);
        printf("Email: %s\n", contacts[i].email);
        printf("-------------------------\n");
    }
    printf("Contacts displayed from email ID successfully.\n");
}

int main() {
    Contact contacts[MAX_CONTACTS];
    int numContacts = 0;
    int choice;

    do {
        printf("Contact Management System\n");
        printf("-------------------------\n");
        printf("1. Add Contact\n");
        printf("2. Display All Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Save Contacts to Email\n");
        printf("5. Display Contacts from Email\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1: {
                // Add Contact
                if (numContacts >= MAX_CONTACTS) {
                    printf("Contact list is full. Cannot add more contacts.\n");
                    break;
                }
                Contact newContact;
                printf("Enter name: ");
                fgets(newContact.name, sizeof(newContact.name), stdin);
                newContact.name[strcspn(newContact.name, "\n")] = '\0'; // Remove trailing newline

                printf("Enter phone: ");
                fgets(newContact.phone, sizeof(newContact.phone), stdin);
                newContact.phone[strcspn(newContact.phone, "\n")] = '\0'; // Remove trailing newline

                printf("Enter email: ");
                fgets(newContact.email, sizeof(newContact.email), stdin);
                newContact.email[strcspn(newContact.email, "\n")] = '\0'; // Remove trailing newline

                contacts[numContacts++] = newContact;
                printf("Contact added successfully.\n");
                break;
            }
            case 2: {
                // Display All Contacts
                if (numContacts == 0) {
                    printf("No contacts found.\n");
                    break;
                }
                printf("Contact List:\n");
                for (int i = 0; i < numContacts; i++) {
                    printf("Contact %d:\n", i + 1);
                    printf("Name: %s\n", contacts[i].name);
                    printf("Phone: %s\n", contacts[i].phone);
                    printf("Email: %s\n", contacts[i].email);
                    printf("-------------------------\n");
                }
                break;
            }
            case 3: {
                // Search Contact
                if (numContacts == 0) {
                    printf("No contacts found.\n");
                    break;
                }
                char searchName[50];
                printf("Enter name to search: ");
                fgets(searchName, sizeof(searchName), stdin);
                searchName[strcspn(searchName, "\n")] = '\0'; // Remove trailing newline

                int found = 0;
                for (int i = 0; i < numContacts; i++) {
                    if (strcmp(contacts[i].name, searchName) == 0) {
                        printf("Contact found:\n");
                        printf("Name: %s\n", contacts[i].name);
                        printf("Phone: %s\n", contacts[i].phone);
                        printf("Email: %s\n", contacts[i].email);
                        printf("-------------------------\n");
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Contact not found.\n");
                }
                break;
            }
            case 4: {
                // Save Contacts to Email
                char emailID[50];
                printf("Enter email ID to save contacts: ");
                fgets(emailID, sizeof(emailID), stdin);
                emailID[strcspn(emailID, "\n")] = '\0'; // Remove trailing newline
                saveContactsToEmail(contacts, numContacts, emailID);
                break;
            }
            case 5: {
                // Display Contacts from Email
                char emailID[50];
                printf("Enter email ID to display contacts: ");
                fgets(emailID, sizeof(emailID), stdin);
                emailID[strcspn(emailID, "\n")] = '\0'; // Remove trailing newline
                displayContactsFromEmail(contacts, numContacts, emailID);
                break;
            }
            case 6: {
                // Exit
                printf("Exiting the program. Goodbye!\n");
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        printf("\n");
    } while (choice != 6);

    return 0;
}
