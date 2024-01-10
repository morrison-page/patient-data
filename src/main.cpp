#include <functional>
#include <iostream>
#include <cstdlib>
#include <string>
#include "database.hpp"
#include "hashing.hpp"
#include "user.hpp"
#include "accessLevel.hpp"

using namespace std;

int main()
{
    // Instantiate Objects
    Database Database;
    Hashing Hashing;

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
            {             
                // TODO: Create Patient
                string username, password, passwordCheck;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
                cout << "Password again: ";
                cin >> passwordCheck;
                // TODO: add error checking

                size_t hashedPassword = Hashing.hashPassword(password);

                string firstname, lastname;
                cout << "Firstname: ";
                cin >> firstname;
                cout << "Lastname: ";
                cin >> lastname;
                cout << endl;

                char hasCancer, hasDiabetes, isSmoker;
                int diabetesType, cancerStage, smokingQuantity;
                cout << "Please answer with 'y' or 'n'\n\n";
                cout << "Do you have Cancer? ";
                cin >> hasCancer;
                if (hasCancer == 'y')
                {
                    cout << "1 - Stage 1\n";
                    cout << "2 - Stage 2\n";
                    cout << "3 - Stage 3\n";
                    cout << "4 - Stage 4\n\n";
                    cin >> cancerStage;
                }
                cout << "Do you have Diabetes? ";
                cin >> hasDiabetes;
                if (hasDiabetes == 'y')
                {
                    cout << "1 - Type 1\n";
                    cout << "2 - Type 2\n\n";
                    cin >> diabetesType;
                }
                cout << "Do you smoke? ";
                cin >> isSmoker;
                if (isSmoker == 'y')
                {
                    cout << "1 - 1 pack a month\n";
                    cout << "2 - 1 pack a week\n";
                    cout << "3 - 1 pack a day\n\n";
                    cin >> smokingQuantity;
                }
                char hasSmoked, hadCancer;
                cout << "Previously had Cancer: ";
                cin >> hadCancer;
                cout << "Previously Smoked: ";
                cin >> hasSmoked;
                cout << endl;
                
                bool cancer = (hasCancer == 'y');
                bool diabetes = (hasDiabetes == 'y');
                bool smoker = (isSmoker == 'y');
                bool previouslyCancerous = (hadCancer == 'y');
                bool previouslySmoked = (hasSmoked == 'y');

                Patient Patient(username, hashedPassword, firstname, lastname,
                    cancer, cancerStage,
                    diabetes, diabetesType,
                    smoker, smokingQuantity,
                    previouslyCancerous, previouslySmoked);

                Database.createPatient(Patient);
            }
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