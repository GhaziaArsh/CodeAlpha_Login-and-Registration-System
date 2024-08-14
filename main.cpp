#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

class User
{private:
    string username;
    string password;


    void validateInput(const string& input, const string& fieldName)
    {
        if (input.empty())
        {
            throw invalid_argument(fieldName + " cannot be empty.");
        }
    }

public:
    User(const string& uname, const string& pwd)
    {
        validateInput(uname, "Username");
        validateInput(pwd, "Password");
        username = uname;
        password = pwd;
    }

    void registerUser() const
    {
        if (userExists())
        {
            cout << "Error: Username already exists. Please choose a different username." << endl;
            return;
        }
        ofstream file(username + ".txt");
        if (!file) {
            cout << "Error: Unable to create user file. Please try again later." << endl;
            return;
        }
        file << username << endl;
        file << password << endl;
        file.close();
        cout << "Registration successful!" << endl;
    }
    bool loginUser() const
     {
        if (!userExists())
        {
            cout << "Error: User does not exist. Please register first." << endl;
            return false;
        }
        string storedUsername, storedPassword;
        ifstream file(username + ".txt");
        if (file.is_open())
        {
            getline(file, storedUsername);
            getline(file, storedPassword);
            file.close();
            if (storedUsername == username && storedPassword == password)
            {
                return true;
            } else {
                cout << "Error: Incorrect password." << endl;
                return false;
            }
        } else {
            cout << "Error: Unable to open user file. Please try again later." << endl;
            return false;
        }
    }

private:

    bool userExists() const {
        ifstream file(username + ".txt");
        return file.good();
    }
};

void displayMenu() {
    cout << "Welcome to the User Management System" << endl;
    cout << "-------------------------------------" << endl;
    cout << "-------------------------------------" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "-------------------------------------" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Choose an option: ";
}

int main()
{
    int choice;
    string uname, pwd;

    do {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter username: ";
                cin >> uname;
                cout << "Enter password: ";
                cin >> pwd;

                try {
                    User newUser(uname, pwd);
                    newUser.registerUser();
                } catch (const invalid_argument& e)
                {
                    cout << "Error: " << e.what() << endl;
                }
                break;

            case 2:
                cout << "Enter username: ";
                cin >> uname;
                cout << "Enter password: ";
                cin >> pwd;

                try {
                    User existingUser(uname, pwd);
                    if (existingUser.loginUser())
                    {
                        cout << "Login successful!" << endl;
                    }
                } catch (const invalid_argument& e)
                {
                    cout << "Error: " << e.what() << endl;
                }
                break;

            case 3:
                cout << "Thank you for using the User Management System. Goodbye!" << endl;
                break;

            default:
                cout << "Error: Invalid choice. Please try again." << endl;
                break;
        }

    }
    while (choice != 3);

    return 0;
}
