#include <iostream>
#include <cstdlib>
#include <string>
#include "database.h"
#include "user.h"
#include "userDatabase.h"

using namespace std;

int main()
{
    // Define Objects
    Database Database;
    UserDatabase UserDatabase;

    // Main Program Loop
    while (true)
    {
        int choice;
        cout << "1 - Patient\n";
        cout << "2 - Staff\n";
        cout << "3 - Exit\n\n";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        // Patinet Menu Tree
        case 1:
            cout << "1 - Login\n";
            cout << "2 - Register\n";
            cout << "3 - Exit\n\n";
            cin >> choice;
            switch (choice)
            {
            // Login
            case 1:
                // TODO: Make this menu a function to use after user registers
                // TODO: Authenticate User
                if (1 == 1) // if AUTH == TRUE
                {
                    cout << "1 - View Personal Detail\n";
                    cout << "2 - View Treatment & Cost\n";
                    cout << "3 - Exit\n\n";
                    cin >> choice;
                    switch (choice)
                    {
                    case 1:
                        // TODO: Output Patient Treatment
                    case 2:
                        // TODO: Output Patient Treatment Costs
                    case 3:
                        exit(0);
                    }
                }
            // Register
            case 2:
                // TODO: Create Patient
                // TODO: Output the patient auth menu
            case 3:
                exit(0);
            }
        // Staff Menu Tree
        case 2:
            cout << "1 - Doctor\n";
            cout << "2 - Nurse\n";
            cout << "3 - Pharmacist\n";
            cout << "4 - Exit\n\n";
            cin >> choice;

            switch (choice)
            {
            // Doctor / Nurse
            case 1 || 2:
                // TODO: Authenticate user
                if (1 == 1) // if AUTH == TRUE
                {
                    cout << "1 - View Patient Details";
                    cout << "2 - View Patient Treatment & Cost";
                    cout << "3 - View Data Analytics";
                    cout << "4 - Change Patient Medication";
                    cout << "5 - Exit";
                    cin >> choice;

                    switch (choice)
                    {
                    case 1:
                        // TODO: View Patient Details
                    case 2:
                        // TODO: View Patient Treatment & Cost
                    case 3:
                        // TODO: Output Data Analytics
                    case 4:
                        // TODO: Change Patient Medication
                    case 5:
                        exit(0);
                    }
                }
            // Pharmacist
            case 3:
                // TODO: Authenticate user
                if (1 == 1) // if AUTH == TRUE
                {
                    // TODO: View patient details
                }
            case 4:
                exit(0);
            }
        case 3:
            exit(0);
        }
    }

    return 0;
}