#include <functional>
#include <iostream>
#include <cstdlib>
#include <string>
#include "accessLevel.hpp"
#include "database.hpp"
#include "hashing.hpp"
#include "utils.hpp"
#include "user.hpp"

using namespace std;

int main()
{
    // Instantiate Object(s)
    Database Database;

    // TODO: non essential but fix program loop
    // patient has to continue to login to use menu more than once

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
        // Patient Menu Tree
        case 1:
        {
            cout << "1 - Login\n";
            cout << "2 - Register\n";
            cout << "3 - Exit\n\n";
            cin >> choice;
            cout << endl;
            switch (choice)
            {
            // Login
            case 1:
            {
                int userId = Database.authenticateUser();
                if (userId != -1)
                {
                    Patient currentPatient = Database.initialisePatient(userId);
                    cout << endl;
                    cout << "1 - View Personal Details\n";
                    cout << "2 - View Treatment & Cost\n";
                    cout << "3 - Exit\n\n";
                    cin >> choice;
                    cout << endl;
                    switch (choice)
                    {
                    case 1:
                    {
<<<<<<< Updated upstream
                        Database.getPatientDetails(currentPatient.getPatientId());
                        Database.getPatientTreatments(currentPatient.getPatientId());
                        break;
                    }
                    case 2:
                    {
                        Database.getPatientCosts(currentPatient.getPatientId());
                        break;
=======
                        // Output Patient Details & Treatment
                        Database.getPatientDetails(Patient.getPatientId());
                        Database.getPatientTreatments(Patient.getPatientId());
                    }
                    case 2:
                    {
                        // Output Patient Costs
                        Database.getPatientCosts(Patient.getPatientId());
>>>>>>> Stashed changes
                    }
                    case 3:
                        exit(0);
                    }
                }
                break;
            }
            // Register
            case 2:
            {
                string username, password;
                cout << "Username: ";
                cin >> username;
                password = Utils::checkPasswordMatch();

                size_t hashedPassword = Hashing::hashPassword(password);

                string firstname, lastname;
                int age;
                cout << "Firstname: ";
                cin >> firstname;
                cout << "Lastname: ";
                cin >> lastname;
                cout << "Age: ";
                cin >> age;
                cout << endl;

                char hasCancer, hasDiabetes, isSmoker;
                int diabetesType, cancerStage, smokingQuantity;
                cout << "Please answer with 'y' or 'n'\n\n";
                cout << "Do you have Cancer? ";
                cin >> hasCancer;
                cout << endl;
                if (hasCancer == 'y')
                {
                    cout << "1 - Stage 1\n";
                    cout << "2 - Stage 2\n";
                    cout << "3 - Stage 3\n";
                    cout << "4 - Stage 4\n\n";
                    cin >> cancerStage;
                    cout << endl;
                }
                cout << "Do you have Diabetes? ";
                cin >> hasDiabetes;
                cout << endl;
                if (hasDiabetes == 'y')
                {
                    cout << "1 - Type 1\n";
                    cout << "2 - Type 2\n\n";
                    cin >> diabetesType;
                    cout << endl;
                }
                cout << "Do you smoke? ";
                cin >> isSmoker;
                cout << endl;
                if (isSmoker == 'y')
                {
                    cout << "1 - 1 pack a month\n";
                    cout << "2 - 1 pack a week\n";
                    cout << "3 - 1 pack a day\n\n";
                    cin >> smokingQuantity;
                    cout << endl;
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

                Patient newPatient(username, hashedPassword, firstname, lastname,
                    age, cancer, cancerStage,
                    diabetes, diabetesType,
                    smoker, smokingQuantity,
                    previouslyCancerous, previouslySmoked);

                Database.createPatient(newPatient);
                break;
            }
            case 3:
                exit(0);
            }
            break;
        }
        // Staff Menu Tree
        case 2:
        {
            cout << "1 - Doctor\n";
            cout << "2 - Nurse\n";
            cout << "3 - Pharmacist\n";
            cout << "4 - Exit\n\n";
            cin >> choice;
            cout << endl;
            switch (choice)
            {
            // Doctor
            case 1:
            {
                __fallthrough;
            }
            // Nurse
            case 2:
            {
                int userId = Database.authenticateUser();
                if (userId != -1)
                {
                    User currentUser = Database.initialiseStaff(userId);
                    cout << endl;
                    cout << "1 - View Patient Details\n";
                    cout << "2 - View Patient Treatment & Cost\n";
                    cout << "3 - View Data Analytics\n";
                    cout << "4 - Change Patient Medication\n";
                    cout << "5 - Create Staff Accounts\n";
                    cout << "6 - Exit\n\n";
                    cin >> choice;
                    cout << endl;

                    switch (choice)
                    {
                    case 1:
                    {
                        // TODO: Search for Patient
                        
                        // ask for patient username
                        // search for patient
                        // initialise patient

                        // use: Database.getPatientDetails(Patient.getPatientId());
                        break;
                    }
                    case 2:
                    {
                        // TODO: View Patient Treatment & Cost
                        // TODO: Search for Patient

                        // ask for patient username
                        // search for patient
                        // initialise patient

                        //use Database.getPatientDetails(Patient.getPatientId());
                        //use Database.getPatientTreatments(Patient.getPatientId());
                        break;
                    }
                    case 3:
                    {
                        // TODO: Output Data Analytics
                        break;
                    }
                    case 4:
                    {
                        // TODO: Change Patient Medication
                        break;
                    }
                    // Register Doctor/Nurse
                    case 5:
                    {
                        AccessLevel accessLevel = AccessLevel::DOCTOR;
                        string username, password;
                        cout << "Username: ";
                        cin >> username;
                        password = Utils::checkPasswordMatch();
                        
                        size_t hashedPassword = Hashing::hashPassword(password);

                        User newStaff(username, hashedPassword, accessLevel);

                        Database.createStaff(newStaff);
                        break;
                    }
                    case 6:
                        exit(0);
                    }
                }
                break;
            }
            // Pharmacist
            case 3:
            {
                int userId = Database.authenticateUser();
                if (userId != -1)
                {
                    User currentUser = Database.initialiseStaff(userId);
                    if (currentUser.getAccessLevel() == AccessLevel::PHARMACIST)
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
                        {
                            // TODO: View Patient Details
                            break;
                        }
                        case 2:
                        {
                            // TODO: View Patient Treatment & Cost
                            break;
                        }
                        case 3:
                        {
                            // TODO: Output Data Analytics
                            break;
                        }
                        case 4:
                        {
                            // TODO: Change Patient Medication
                            break;
                        }
                        case 5:
                        {
                            cout << "1 - View\n";
                            cout << "2 - Change\n";
                            cout << "3 - Exit\n\n";
                            cin >> choice;
                            cout << endl;
                            switch (choice)
                            {
                            case 1:
                            {
                                // TODO: View Treatments
                                break;
                            }
                            case 2:
                            {
                                // TODO: Change Treatments
                                break;
                            }
                            case 3:
                                exit(0);
                            }
                            break;
                        }
                        case 6:
                            exit(0);
                        }
                    }
                    else
                    {
                        cout << endl;
                        cout << "You are not a Pharmacist\n\n";
                        exit(0);
                    }
                }
                break;
            }
            case 4:
                exit(0);
            }
            break;
        }
        case 3:
            exit(0);
        }
    }
    return 0;
}