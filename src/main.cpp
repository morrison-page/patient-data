#include <functional>
#include <iostream>
#include <cstdlib>
#include <string>
#include "database.h"
#include "hashing.h"
#include "user.h"
#include "accessLevel.h"
#include "userDatabase.h"

using namespace std;

int main()
{
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
            cout << endl;
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
                    cout << endl;
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
                string username, password;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
                
                size_t hashedPassword = Hashing::hashPassword(password);

                User User(username, hashedPassword, AccessLevel::PATIENT);

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
            cout << endl;
            switch (choice)
            {
            // Doctor / Nurse
            case 1 || 2:
                // TODO: Authenticate user
                if (1 == 1) // if AUTH == TRUE
                {
                    cout << "1 - View Patient Details\n";
                    cout << "2 - View Patient Treatment & Cost\n";
                    cout << "3 - View Data Analytics\n";
                    cout << "4 - Change Patient Medication\n";
                    cout << "5 - Exit\n\n";
                    cin >> choice;
                    cout << endl;
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
                    cout << "1 - View Patient Details\n";
                    cout << "2 - View Patient Treatment & Cost\n";
                    cout << "3 - View Data Analytics\n";
                    cout << "4 - Change Patient Medication\n";
                    cout << "5 - Prescriptions and Treatments\n";
                    cout << "6 - Exit\n\n";
                    cin >> choice;
                    cout << endl;
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
                        cout << "1 - View\n";
                        cout << "2 - Change\n";
                        cout << "3 - Exit\n\n";
                        cin >> choice;
                        cout << endl;
                        switch (choice)
                        {
                        case 1:
                            // TODO: View Treatments
                        case 2:
                            // TODO: Change Treatments
                        case 3:
                            exit(0);
                        }
                    case 6:
                        exit(0);
                    }
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