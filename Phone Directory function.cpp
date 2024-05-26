#include "Phone Directory Header.h"
#include <iostream>
#include <algorithm>

PhoneDirectory::PhoneDirectory() : head(NULL) {}

vector<Contact*> PhoneDirectory::getAllContacts() const {
    vector<Contact*> contacts;
    Contact* current = head;
    while (current != NULL) {
        contacts.push_back(current);
        current = current->next;
    }
    return contacts;
}

void PhoneDirectory::addContact(const string& firstName, const string& lastName,
                                const string& mobileNumber, const string& homeNumber,
                                const string& workNumber, const string& emailAddress,
                                const string& birthday) {
    Contact* newContact = new Contact(firstName, lastName, mobileNumber, homeNumber, workNumber, emailAddress, birthday);
    if (head == NULL) {
        head = newContact;
    } else {
        Contact* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newContact;
    }
    // Update the last name hash table
    lastNameMap[lastName].push_back(newContact);
}

// Function to display all contacts in the directory
void PhoneDirectory::displayContacts(const string& sortBy) const {
    if (head == NULL) {
        cout << "There are no contacts in the directory." << endl;
        return;
    }

    vector<Contact*> contacts = getAllContacts();

    if (sortBy == "name") {
        sort(contacts.begin(), contacts.end(), [](Contact* a, Contact* b) {
            return a->getFirstName() + " " + a->getLastName() < b->getFirstName() + " " + b->getLastName();
        });
    } else if (sortBy == "mobile") {
        sort(contacts.begin(), contacts.end(), [](Contact* a, Contact* b) {
            return a->getMobileNumber() < b->getMobileNumber();
        });
    } else if (sortBy == "home") {
        sort(contacts.begin(), contacts.end(), [](Contact* a, Contact* b) {
            return a->getHomeNumber() < b->getHomeNumber();
        });
    } else if (sortBy == "work") {
        sort(contacts.begin(), contacts.end(), [](Contact* a, Contact* b) {
            return a->getWorkNumber() < b->getWorkNumber();
        });
    }

    for (Contact* contact : contacts) {
        cout << "Name: " << contact->getFirstName() << " " << contact->getLastName() << endl;
        cout << "Mobile Number: " << contact->getMobileNumber() << endl;
        cout << "Home Number: " << contact->getHomeNumber() << endl;
        cout << "Work Number: " << contact->getWorkNumber() << endl;
        cout << "Email Address: " << contact->getEmailAddress() << endl;
        cout << "Birthday: " << contact->getBirthday() << endl; // Display birthday
        cout << endl;
    }
}

// Function to find a contact by name and edit its information
void PhoneDirectory::editContact(const string& firstName, const string& lastName, const string& newMobile,
                                 const string& newHome, const string& newWork, const string& newEmail,
                                 const string& newBirthday) {
    Contact* current = head;
    while (current != NULL) {
        if (current->getFirstName() == firstName && current->getLastName() == lastName) {
            current->setMobileNumber(newMobile);
            current->setHomeNumber(newHome);
            current->setWorkNumber(newWork);
            current->setEmailAddress(newEmail);
            current->setBirthday(newBirthday);
            cout << "Contact updated successfully!" << endl;
            return;
        }
        current = current->next;
    }
    cout << "Contact not found!" << endl;
}

// Function to delete a contact by name
void PhoneDirectory::deleteContact(const string& firstName, const string& lastName) {
    if (head == NULL) {
        cout << "Contact not found!" << endl;
        return;
    }

    if (head->getFirstName() == firstName && head->getLastName() == lastName) {
        Contact* temp = head;
        head = head->next;
        delete temp;
        cout << "Contact deleted successfully!" << endl;
        return;
    }

    Contact* current = head;
    while (current->next != NULL) {
        if (current->next->getFirstName() == firstName && current->next->getLastName() == lastName) {
            Contact* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Contact deleted successfully!" << endl;
            return;
        }
        current = current->next;
    }
    cout << "Contact not found!" << endl;
}

// Function to search for a contact by name or phone number
void PhoneDirectory::searchContact(const string& query, const string& sortBy) const {
    vector<Contact*> results;
    // Search by last name from the hash table
    auto it = lastNameMap.find(query);
    if (it != lastNameMap.end()) {
        results.insert(results.end(), it->second.begin(), it->second.end());
    }
    // Search by first name and phone numbers
    Contact* current = head;
    while (current != NULL) {
        if (current->getFirstName() == query || current->getMobileNumber() == query ||
            current->getHomeNumber() == query || current->getWorkNumber() == query) {
            results.push_back(current);
        }
        current = current->next;
    }

    if (sortBy == "name") {
        sort(results.begin(), results.end(), [](Contact* a, Contact* b) {
            return a->getFirstName() + " " + a->getLastName() < b->getFirstName() + " " + b->getLastName();
        });
    } else if (sortBy == "mobile") {
        sort(results.begin(), results.end(), [](Contact* a, Contact* b) {
            return a->getMobileNumber() < b->getMobileNumber();
        });
    } else if (sortBy == "home") {
        sort(results.begin(), results.end(), [](Contact* a, Contact* b) {
            return a->getHomeNumber() < b->getHomeNumber();
        });
    } else if (sortBy == "work") {
        sort(results.begin(), results.end(), [](Contact* a, Contact* b) {
            return a->getWorkNumber() < b->getWorkNumber();
        });
    }

    if (!results.empty()) {
        cout << "Search results:" << endl;
        for (Contact* contact : results) {
            cout << "Name: " << contact->getFirstName() << " " << contact->getLastName() << endl;
            cout << "Mobile Number: " << contact->getMobileNumber() << endl;
            cout << "Home Number: " << contact->getHomeNumber() << endl;
            cout << "Work Number: " << contact->getWorkNumber() << endl;
            cout << "Email Address: " << contact->getEmailAddress() << endl;
            cout << "Birthday: " << contact->getBirthday() << endl; // Display birthday
            cout << endl;
        }
    } else {
        cout << "Contact not found!" << endl;
    }
}

// Destructor to free memory
PhoneDirectory::~PhoneDirectory() {
    Contact* current = head;
    while (current != NULL) {
        Contact* next = current->next;
        delete current;
        current = next;
    }
}

