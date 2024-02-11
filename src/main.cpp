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
    // maybe add a while loop after the user logs in

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
                    // Output Patient Details
                    case 1:
                    {
                        Database.getPatientDetails(currentPatient.getPatientId());
                        Database.getPatientTreatments(currentPatient.getPatientId());
                        break;
                    }
                    // Output Patient Costs
                    case 2:
                    {
                        Database.getPatientCosts(currentPatient.getPatientId());
                        break;
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
                    // View Patient Details
                    case 1:
                    {
                        int patientId;
                        cout << "Enter patients ID: ";
                        cin >> patientId;
                        Database.getPatientDetails(patientId);
                        break;
                    }
                    // View Patient Treatment & Cost
                    case 2:
                    {
                        int patientId;
                        cout << "Enter patients ID: ";
                        cin >> patientId;
                        Database.getPatientTreatments(patientId);
                        Database.getPatientCosts(patientId);
                        break;
                    }
                    // Show Data Analytics
                    case 3:
                    {
                        cout << "1 - Average Age of Cancer Patients\n";
                        cout << "2 - Average Age of Diabetic Patients\n";
                        cout << "3 - Smoking Frequency of Cancer Patients\n";
                        cout << "4 - Exit\n\n";
                        cin >> choice;
                        cout << endl;

                        switch (choice)
                        {
                        // Average Age of Cancer Patients
						case 1:
                        {
						    Database.averageAgeOfCancerPatients();
							break;
						}
                        // Average Age of Diabetic Patients
						case 2:
                        {
						    Database.averageAgeOfDiabeticPatients();
							break;
                        }
                        // Smoking Frequency of Cancer Patients
						case 3:
                        {
						    Database.smokingFrequencyOfCancerPatients();
						    break;
						}
                        case 4:
						    exit(0);
                        }
                        break;
                    }
                    case 4:
                    {
                        // TODO: Change Patient Medication
                        int patientId;
                        cout << "Enter patients ID: ";
                        cin >> patientId;
                        Patient searchedPatient = Database.initialisePatient(patientId);

                        // Sort out condution numbers
                        if (searchedPatient.getCancer() == true)
                        {
                            cout << "1 - Change Cancer Medication\n";
                        }
                        if (searchedPatient.getDiabetes() == true)
                        {
							cout << "2 - Change Diabetes Medication\n";
						}
                        if (searchedPatient.getSmoker() == true)
                        {
                            cout << "3 - Change Smoking Medication\n";
                        }
                        cout << "4 - Exit\n\n";

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
                        cout << endl;
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
                        // View Patient Details
                        case 1:
                        {
                            // TODO: View Patient Details
                            break;
                        }
                        // View Patient Treatment & Cost
                        case 2:
                        {
                            // TODO: View Patient Treatment & Cost
                            break;
                        }
                        // View Data Analytics
                        case 3:
                        {
                            cout << "1 - Average Age of Cancer Patients\n";
                            cout << "2 - Average Age of Diabetic Patients\n";
                            cout << "3 - Smoking Frequency of Cancer Patients\n";
                            cout << "4 - Exit\n\n";
                            cin >> choice;
                            cout << endl;

                            switch (choice)
                            {
                            // Average Age of Cancer Patients
                            case 1:
                            {
                                Database.averageAgeOfCancerPatients();
                                break;
                            }
                            // Average Age of Diabetic Patients
                            case 2:
                            {
                                Database.averageAgeOfDiabeticPatients();
                                break;
                            }
                            // Smoking Frequency of Cancer Patients
                            case 3:
                            {
                                Database.smokingFrequencyOfCancerPatients();
                                break;
                            }
                            case 4:
                                exit(0);
                            }
                            break;
                        }
                        // Change Patient Medication
                        case 4:
                        {
                            // TODO: Change Patient Medication
                            break;
                        }
                        // Prescriptions and Treatments
                        case 5:
                        {
                            cout << "1 - View\n";
                            cout << "2 - Change\n";
                            cout << "3 - Exit\n\n";
                            cin >> choice;
                            cout << endl;

                            switch (choice)
                            {
                            // View Treatments
                            case 1:
                            {
                                // TODO: View Treatments
                                break;
                            }
                            // Change Treatments
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