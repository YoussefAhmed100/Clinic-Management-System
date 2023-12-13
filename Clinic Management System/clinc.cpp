#include <stdio.h>
#include <string.h>

// Define the structure for a patient
typedef struct
{
    int patientID;
    char name[50];
    int age;
} Patient;

// Define the structure for a doctor
typedef struct
{
    int doctorID;
    char name[50];
    char specialization[50];
} Doctor;

#define MAX_PATIENTS 100
#define MAX_DOCTORS 100

char patientDataPath[] = "patient_data.txt"; // File to store patient data
Patient patients[MAX_PATIENTS];
int numPatients = 0;

char doctorDataPath[] = "doctor_data.txt"; // File to store doctor data
Doctor doctors[MAX_DOCTORS];
int numDoctors = 0;

// Function prototypes
void readPatientDataFromFile(const char *filename);
void writePatientDataToFile(const char *filename);
void addPatient();
void updatePatient();
void deletePatient();
void searchPatient();
void displayAllPatients();
void managingPatientShowMainOption();
void managingDoctorShowMainOption();
void managingBookingShowMainOption();
void readDoctorDataFromFile(const char *filename);
void writeDoctorDataToFile(const char *filename);
void addDoctor();
void updateDoctor();
void deleteDoctor();
void searchDoctor();
void displayAllDoctors();

void showMainOption();

int main()
{
    showMainOption();
    return 0;
}

void showMainOption()
{
    int choice;

    do
    {
        printf("\n-------------------------\n");
        printf("Clinic Management System\n");
        printf("-------------------------\n");
        printf("1 - Manage Patient Data\n");
        printf("2 - Manage Doctor Data\n");
        printf("3 - Manage Bookings\n");
        printf("4 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            managingPatientShowMainOption();
            break;
        case 2:
            managingDoctorShowMainOption();
            break;
        case 3:
             managingBookingShowMainOption();
            break;
        case 4:
            writePatientDataToFile(patientDataPath);
            writeDoctorDataToFile(doctorDataPath);
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
            break;
        }
    } while (choice != 4);
}

void managingPatientShowMainOption()
{
    readPatientDataFromFile(patientDataPath);

    int choice;
    do
    {
        printf("\n-------------------------\n");
        printf("Patient Management System\n");
        printf("-------------------------\n");
        printf("1 - Add Patient\n");
        printf("2 - Update Patient\n");
        printf("3 - Delete Patient\n");
        printf("4 - Search Patient\n");
        printf("5 - Display All Patients\n");
        printf("6 - Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addPatient();
            break;
        case 2:
            updatePatient();
            break;
        case 3:
            deletePatient();
            break;
        case 4:
            searchPatient();
            break;
        case 5:
            displayAllPatients();
            break;
        case 6:
            writePatientDataToFile(patientDataPath);
            printf("Exiting the patient management system.\n");
            showMainOption();
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 6.\n");
            break;
        }
    } while (choice != 6);
}

void managingDoctorShowMainOption()
{
    readDoctorDataFromFile(doctorDataPath);

    int choice;
    do
    {
        printf("\n-------------------------\n");
        printf("Doctor Management System\n");
        printf("-------------------------\n");
        printf("1 - Add Doctor\n");
        printf("2 - Update Doctor\n");
        printf("3 - Delete Doctor\n");
        printf("4 - Search Doctor\n");
        printf("5 - Display All Doctors\n");
        printf("6 - Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addDoctor();
            break;
        case 2:
            updateDoctor();
            break;
        case 3:
            deleteDoctor();
            break;
        case 4:
            searchDoctor();
            break;
        case 5:
            displayAllDoctors();
            break;
        case 6:
            writeDoctorDataToFile(doctorDataPath);
            printf("Exiting the doctor management system.\n");
            showMainOption();
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 6.\n");
            break;
        }
    } while (choice != 6);
}

void readPatientDataFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("No existing patient data found.\n");
        return;
    }

    while (fscanf(file, "%d %s %d", &patients[numPatients].patientID, patients[numPatients].name, &patients[numPatients].age) == 3 && numPatients < MAX_PATIENTS)
    {
        numPatients++;
    }

    fclose(file);
}

void writePatientDataToFile(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening the patient data file for writing.\n");
        return;
    }

    for (int i = 0; i < numPatients; i++)
    {
        fprintf(file, "%d %s %d\n", patients[i].patientID, patients[i].name, patients[i].age);
    }

    fclose(file);
}

void addPatient()
{
    if (numPatients < MAX_PATIENTS)
    {
        printf("Enter patient ID: ");
        scanf("%d", &patients[numPatients].patientID);

        printf("Enter patient name: ");
        scanf("%s", patients[numPatients].name);

        printf("Enter patient age: ");
        scanf("%d", &patients[numPatients].age);

        numPatients++;

        printf("Patient added successfully.\n");
    }
    else
    {
        printf("Cannot add more patients. Array is full.\n");
    }
}

void updatePatient()
{
    int targetID;
    printf("Enter patient ID to update: ");
    scanf("%d", &targetID);

    int found = 0;
    for (int i = 0; i < numPatients; i++)
    {
        if (patients[i].patientID == targetID)
        {
            printf("Enter new name: ");
            scanf("%s", patients[i].name);

            printf("Enter new age: ");
            scanf("%d", &patients[i].age);

            found = 1;
            printf("Patient updated successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Patient ID not found.\n");
    }
}

void deletePatient()
{
    int targetID;
    printf("Enter patient ID to delete: ");
    scanf("%d", &targetID);

    int found = 0;
    for (int i = 0; i < numPatients; i++)
    {
        if (patients[i].patientID == targetID)
        {
            found = 1;
            for (int j = i; j < numPatients - 1; j++)
            {
                patients[j] = patients[j + 1];
            }
            numPatients--;
            printf("Patient deleted successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Patient ID not found.\n");
    }
}

void searchPatient()
{
    int targetID;
    printf("Enter patient ID to search: ");
    scanf("%d", &targetID);

    int found = 0;
    for (int i = 0; i < numPatients; i++)
    {
        if (patients[i].patientID == targetID)
        {
            found = 1;
            printf("Patient found:\n");
            printf("ID: %d, Name: %s, Age: %d\n", patients[i].patientID, patients[i].name, patients[i].age);
            break;
        }
    }

    if (!found)
    {
        printf("Patient ID not found.\n");
    }
}

void displayAllPatients()
{
    if (numPatients == 0)
    {
        printf("No patients to display.\n");
        return;
    }

    printf("Patient Records:\n");
    for (int i = 0; i < numPatients; i++)
    {
        printf("ID: %d, Name: %s, Age: %d\n", patients[i].patientID, patients[i].name, patients[i].age);
    }
}

void readDoctorDataFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("No existing doctor data found.\n");
        return;
    }

    while (fscanf(file, "%d %s %s", &doctors[numDoctors].doctorID, doctors[numDoctors].name, doctors[numDoctors].specialization) == 3 && numDoctors < MAX_DOCTORS)
    {
        numDoctors++;
    }

    fclose(file);
}

void writeDoctorDataToFile(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening the doctor data file for writing.\n");
        return;
    }

    for (int i = 0; i < numDoctors; i++)
    {
        fprintf(file, "%d %s %s\n", doctors[i].doctorID, doctors[i].name, doctors[i].specialization);
    }

    fclose(file);
}

void addDoctor()
{
    if (numDoctors < MAX_DOCTORS)
    {
        printf("Enter doctor ID: ");
        scanf("%d", &doctors[numDoctors].doctorID);

        printf("Enter doctor name: ");
        scanf("%s", doctors[numDoctors].name);

        printf("Enter doctor specialization: ");
        scanf("%s", doctors[numDoctors].specialization);

        numDoctors++;

        printf("Doctor added successfully.\n");
    }
    else
    {
        printf("Cannot add more doctors. Array is full.\n");
    }
}

void updateDoctor()
{
    int targetID;
    printf("Enter doctor ID to update: ");
    scanf("%d", &targetID);

    int found = 0;
    for (int i = 0; i < numDoctors; i++)
    {
        if (doctors[i].doctorID == targetID)
        {
            printf("Enter new name: ");
            scanf("%s", doctors[i].name);

            printf("Enter new specialization: "); // Fixed the missing quotation mark here
            scanf("%s", doctors[i].specialization);

            found = 1;
            printf("Doctor updated successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Doctor ID not found.\n");
    }
}
void deleteDoctor()
{
    int targetID;
    printf("Enter doctor ID to delete: ");
    scanf("%d", &targetID);

    int found = 0;
    for (int i = 0; i < numDoctors; i++)
    {
        if (doctors[i].doctorID == targetID)
        {
            found = 1;
            for (int j = i; j < numDoctors - 1; j++)
            {
                doctors[j] = doctors[j + 1];
            }
            numDoctors--;
            printf("Doctor deleted successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Doctor ID not found.\n");
    }
}

void searchDoctor()
{
    int targetID;
    printf("Enter doctor ID to search: ");
    scanf("%d", &targetID);

    int found = 0;
    for (int i = 0; i < numDoctors; i++)
    {
        if (doctors[i].doctorID == targetID)
        {
            found = 1;
            printf("Doctor found:\n");
            printf("ID: %d, Name: %s, Specialization: %s\n", doctors[i].doctorID, doctors[i].name, doctors[i].specialization);
            break;
        }
    }

    if (!found)
    {
        printf("Doctor ID not found.\n");
    }
}

void displayAllDoctors()
{
    if (numDoctors == 0)
    {
        printf("No doctors to display.\n");
        return;
    }

    printf("Doctor Records:\n");
    for (int i = 0; i < numDoctors; i++)
    {
        printf("ID: %d, Name: %s, Specialization: %s\n", doctors[i].doctorID, doctors[i].name, doctors[i].specialization);
    }
}
// Define the structure for a booking
typedef struct
{
    int bookingID;
    int patientID;
    int doctorID;
    // Add more fields as needed
} Booking;

#define MAX_BOOKINGS 100
Booking bookings[MAX_BOOKINGS];
int numBookings = 0;

char bookingDataPath[] = "booking_data.txt"; // File to store booking data

// Function prototypes for booking management
void readBookingDataFromFile(const char *filename);
void writeBookingDataToFile(const char *filename);
void addBooking();
void updateBooking();
void deleteBooking();
void searchBooking();
void displayAllBookings();

void readBookingDataFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("No existing booking data found.\n");
        return;
    }

    while (fscanf(file, "%d %d %d", &bookings[numBookings].bookingID, &bookings[numBookings].patientID, &bookings[numBookings].doctorID) == 3 && numBookings < MAX_BOOKINGS)
    {
        // Read additional fields as needed
        numBookings++;
    }

    fclose(file);
}

// Function to write booking data to a file
void writeBookingDataToFile(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening the booking data file for writing.\n");
        return;
    }

    for (int i = 0; i < numBookings; i++)
    {
        fprintf(file, "%d %d %d\n", bookings[i].bookingID, bookings[i].patientID, bookings[i].doctorID);
        // Write additional fields as needed
    }

    fclose(file);
}

 

void managingBookingShowMainOption()
{
    readBookingDataFromFile(bookingDataPath);

    int choice;
    do
    {
        printf("\n-------------------------\n");
        printf("Booking Management System\n");
        printf("-------------------------\n");
        printf("1 - Add Booking\n");
        printf("2 - Update Booking\n");
        printf("3 - Delete Booking\n");
        printf("4 - Search Booking\n");
        printf("5 - Display All Bookings\n");
        printf("6 - Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBooking();
            break;
        case 2:
            updateBooking();
            break;
        case 3:
            deleteBooking();
            break;
        case 4:
            searchBooking();
            break;
        case 5:
            displayAllBookings();
            break;
        case 6:
            writeBookingDataToFile(bookingDataPath);
            printf("Exiting the booking management system.\n");
            showMainOption();
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 6.\n");
            break;
        }
    } while (choice != 6);
}

void addBooking()
{
    if (numBookings < MAX_BOOKINGS)
    {
        printf("Enter booking ID: ");
        scanf("%d", &bookings[numBookings].bookingID);

        printf("Enter patient ID: ");
        scanf("%d", &bookings[numBookings].patientID);

        printf("Enter doctor ID: ");
        scanf("%d", &bookings[numBookings].doctorID);

        // Add more fields as needed

        numBookings++;

        printf("Booking added successfully.\n");
    }
    else
    {
        printf("Cannot add more bookings. Array is full.\n");
    }
}

void updateBooking()
{
    int targetID;
    printf("Enter booking ID to update: ");
    scanf("%d", &targetID);

    int found = 0;
    for (int i = 0; i < numBookings; i++)
    {
        if (bookings[i].bookingID == targetID)
        {
            // You can update other fields as needed
            printf("Enter new patient ID: ");
            scanf("%d", &bookings[i].patientID);

            printf("Enter new doctor ID: ");
            scanf("%d", &bookings[i].doctorID);

            // Update other fields as needed

            found = 1;
            printf("Booking updated successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Booking ID not found.\n");
    }
}

void deleteBooking()
{
    int targetID;
    printf("Enter booking ID to delete: ");
    scanf("%d", &targetID);

    int found = 0;
    for (int i = 0; i < numBookings; i++)
    {
        if (bookings[i].bookingID == targetID)
        {
            found = 1;
            for (int j = i; j < numBookings - 1; j++)
            {
                bookings[j] = bookings[j + 1];
            }
            numBookings--;
            printf("Booking deleted successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Booking ID not found.\n");
    }
}

void searchBooking()
{
    int targetID;
    printf("Enter booking ID to search: ");
    scanf("%d", &targetID);

    int found = 0;
    for (int i = 0; i < numBookings; i++)
    {
        if (bookings[i].bookingID == targetID)
        {
            found = 1;
            printf("Booking found:\n");
            printf("Booking ID: %d, Patient ID: %d, Doctor ID: %d\n", bookings[i].bookingID, bookings[i].patientID, bookings[i].doctorID);
            // Print other fields as needed
            break;
        }
    }

    if (!found)
    {
        printf("Booking ID not found.\n");
    }
}

void displayAllBookings()
{
    if (numBookings == 0)
    {
        printf("No bookings to display.\n");
        return;
    }

    printf("Booking Records:\n");
    for (int i = 0; i < numBookings; i++)
    {
        printf("Booking ID: %d, Patient ID: %d, Doctor ID: %d\n", bookings[i].bookingID, bookings[i].patientID, bookings[i].doctorID);
        // Print other fields as needed
    }
}