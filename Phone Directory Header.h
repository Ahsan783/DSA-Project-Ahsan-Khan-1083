#ifndef PHONEDIRECTORY_H
#define PHONEDIRECTORY_H

#include "Contact.h"
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class PhoneDirectory {
private:
    unordered_map<string, vector<Contact*>> lastNameMap; 
    Contact* head;
    vector<Contact*> getAllContacts() const;
public:
    PhoneDirectory();
    void addContact(const string& firstName, const string& lastName,
                    const string& mobileNumber, const string& homeNumber,
                    const string& workNumber, const string& emailAddress,
                    const string& birthday);
    void displayContacts(const string& sortBy = "") const;
    void editContact(const string& firstName, const string& lastName, const string& newMobile,
                     const string& newHome, const string& newWork, const string& newEmail,
                     const string& newBirthday);
    void deleteContact(const string& firstName, const string& lastName);
    void searchContact(const string& query, const string& sortBy = "") const;
    ~PhoneDirectory();
};

#endif // PHONEDIRECTORY_H

