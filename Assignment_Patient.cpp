#include "Queue.cpp"
#include <iostream>
#include <cstdlib>//For rand()
#include <ctime>// For time()
using namespace std;
vector<Patient> generatePatients(int count) {
    srand(static_cast<unsigned int>(time(0))); // Seed for randomization
    vector<Patient> patients;

    try {
        bool types[] = { 0, 1 };
        char genders[] = { 'M', 'F' };
        int currentHour = 0; // Starting hour
        int currentMinute = 0; // Starting minute

        // Loop to generate patient data
        for (int i = 0; i < count; i++) {
            // Generate random ID (14 digits)
            std::string id = "28";
            for (int j = 0; j < 12; ++j) {
                id += to_string(rand() % 10);  // Append a random digit
            }

            // Generate random gender
            char gender = genders[rand() % 2];

            // Generate random arrival time (HH:MM format)
            int hour = rand() % 24;       // Random hour (0-23)
            int minute = rand() % 60;     // Random minute (0-59)
            string arrivalTime = (hour < 10 ? "0" : "") + to_string(hour) + ":" +
                (minute < 10 ? "0" : "") + to_string(minute);

            // Generate random type (urgent or normal)
            bool type = types[rand() % 2];

            // Create and added patient to the vector
            patients.emplace_back(id, gender, arrivalTime, type);
        }
    }

    catch (const bad_alloc& e) {
        cerr << "Memory allocation failed while creating patients: " << e.what() << endl;
    }
    catch (const invalid_argument& e) {
        cerr << "Invalid data encountered while creating a patient: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Unexpected error while generating patients: " << e.what() << endl;
    }

    return patients;
}
// Helper function to convert HH:MM string to total minutes
int timeToMinutes(const string& time) {
    int hours = stoi(time.substr(0, 2)); // Extract hours
    int minutes = stoi(time.substr(3, 2)); // Extract minutes
    return hours * 60 + minutes; // Total minutes since midnight
}

bool compareByArrivalTime( Patient& a,  Patient& b) {
    return timeToMinutes(a.getArrivalTime()) < timeToMinutes(b.getArrivalTime());
}
int main() {


    int patientCount;
    cout <<"Enter scenario (simple=100, moderate=300, crowded=700): ";
    cin >> patientCount;

    std::vector<Patient> patients = generatePatients(patientCount);
    // Sort the patients by their arrival time
    sort(patients.begin(), patients.end(), compareByArrivalTime);
    Queue_System queueSystem;

    for (auto& patient : patients) {
        queueSystem.Add_Patient(patient);
    }
    int N =0;
    int timee;
    N = 5 + rand() % 6;
    while (patientCount>0) {
        timee = 1 + rand() % 10;
        queueSystem.Check_time(timee);
        while (queueSystem.GetTime() >= 0) {
            queueSystem.Serve_All(N);
            queueSystem.advance_Time();
            if (queueSystem.GetTime() < 0) {
                N = 5 + rand() % 6;
                if (N >= patientCount) {
                    N = patientCount;
                }
            }
            queueSystem.Status(N);
            cout << "Press Enter to advance time by 1 minute...";
            cin.ignore();  // Clear the newline character
            cin.get();  // Wait for user to press Enter
  
        }
        patientCount -= N;
    }  
    cout << "Final Status:" << endl;
    queueSystem.fStatus();
    return 0;
}
