// User SignUp Application

// Please select an option:
// 1: Add Record
// 2: Fetch Record
// 3: Quit

// Enter option: 1

// Add User. Please enter user name and age:
// Name: John Smith
// Age: 30

// User record added successfully.

// Please select an option:
// 1: Add Record
// 2: Fetch Record
// 3: Quit

// Enter option: 1

// Add User. Please enter user name and age:
// Name: Dave Jones
// Age: 21

// User record added successfully.

// Please select an option:
// 1: Add Record
// 2: Fetch Record
// 3: Quit

// Enter option: 2

// Please enter user ID:
// User ID: 0
// User Name: John Smith
// User Age: 30

// Please select an option:
// 1: Add Record
// 2: Fetch Record
// 3: Quit

// Enter option: 3

// Exit code: 0 (normal program termination)
#include <iostream>
#include <stdio.h>
#include <string>
#include <array>
#include <vector>

enum Option {
    ADD_RECORD = 1,
    FETCH_RECORD,
    QUIT,
    INVALID   
};

std::istream & operator >>(std::istream & instream,  Option& Opt)
{
    int int_Opt;
    instream >> int_Opt;
    Opt = Option(int_Opt);
    return instream;
}

class User {
    
    public:
        char id;
        std::string name;
        int age;
    
        User(char id, std::string name, int age) 
        {
            this->id = id;
            this->name = name;
            this->age = age;
        }   
        void fetch_user()
        {
            printf("User Name: %s\n", name.c_str());
            printf("User Age: %d\n", age);
        }
};

class UserDatabase {
    
    private:
        std::vector <User> users;

    public:
    
        void add_user() 
        {
            std::string name;
            int age;

            printf("\nAdd User. Please enter user name and age:\nName: ");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            std::getline(std::cin, name);

            printf("Age: ");
            while (true)
            {
                std::cin >> age;
                // Check if the input failed (e.g., due to non-numeric characters)
                if (std::cin.fail()) {
                    std::cout << "Invalid input. Please enter a valid number.\n";
                    std::cin.clear(); // Clear the error state
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the invalid input
                }
                else 
                {
                    // If no error, break out of loop
                    break;
                }
            }

            User user(users.size(), name, age);
            users.push_back(user);
            printf("\nUser record added successfully.\n");
        }   
        void fetch_user()
        { 
            int id;
            bool found = false;
            printf("\nPlease enter user ID:\nUser ID: ");
            std::cin >> id;
            for(int i = 0; i < users.size(); i++)
            {
                if(users[i].id == id)
                {
                    found = true;
                    users[i].fetch_user();
                    break;
                }
            }
            if(found == false)
            {
                printf("\nUser not found.\n");
            }
        }
};

class menu {

    public:
        std::array <std::string, 3> user_menu {"1. Add Record", "2. Fetch Record", "3. Quit"};
        void display_menu()
        {
            for(int i = 0; i < user_menu.size(); i++)
            {
                printf("%s \n", user_menu[i].c_str());
            }
        }
        Option get_user_option()
        {
            Option Opt;
            printf("\nEnter option: ");
            std::cin >> Opt;
            // Check if the input failed (e.g., due to non-numeric characters)
            if (std::cin.fail()) {
                std::cout << "Invalid input. Please enter a valid number.\n";
                std::cin.clear(); // Clear the error state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the invalid input
                return Option::INVALID;
            }
            else 
            {
                // If no error, return the selected option
                return Opt;
            }
        }
};

int main()
{
    menu user_menu;
    Option Opt = Option::QUIT;
    UserDatabase user_database;
    bool is_running = true;
    while (is_running == true)
    {
        printf("\nPlease select an option:\n");
        user_menu.display_menu();
        Opt = user_menu.get_user_option();
        switch (Opt)
        {
        case ADD_RECORD:
            user_database.add_user();
            break;
        case FETCH_RECORD:
            user_database.fetch_user();
            break;
        case QUIT:
            is_running = false;
            break;
        case INVALID:
            break;
        
        default:
            std::cout << "Invalid input. Please enter a valid Option.\n";
            break;
        }
    }


    return 0;
}