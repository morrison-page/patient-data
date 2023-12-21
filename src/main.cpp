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
        cout << "2 - Staff\n\n";
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
            case 1:
                // TODO: Authenticate User
                switch (choice)
                {
                case 1:
                    cout << "1 - View Treatment\n";
                    cout << "2 - View Treatment Cost\n";
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
            case 2:
                // TODO: Create Patient
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
            case 1:

            case 2:

            case 3:

            case 4:
                exit(0);
            }

        }
    }

    return 0;
}