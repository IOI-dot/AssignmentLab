#include <queue> //For Queue
#include <vector> //For Vectors
#include <ctime> //For simulating patient waiting
#include <cstdlib> //For rand() an srand() functions
#include <iostream>
#include <stdexcept> //For the errors displayed
#include "Patient.cpp"
using namespace std;
class Queue_System {
private:
    queue<Patient> urgentQueue;
    queue<Patient> normalQueue;
    double total_served; 
    double total_waiting; 
    int time; //Time which will get decrimnted every minute 
 
public:
    Queue_System() {
        total_served = 0;
        total_waiting = 0;
        time = 0;  // Start with time = 0 (Midnight or the start of the simulation)
    }
    void Check_time(int n) {
        time = n;
    }
    int GetTime() {
        return time;
    }
    // Add a patient to either urgent or normal queue
    void Add_Patient(Patient& patient) {
        try {
            // Check if the patient ID is valid
            if (!patient.Check_ID(patient.Get_ID())) {
                throw invalid_argument("Invalid patient ID format. Must be a 14-digit number.");
            }

            // Add the patient to the appropriate queue
            if (patient.isUrgent()) {
                urgentQueue.push(patient);
            }
            else {
                normalQueue.push(patient);
            }

        }
        catch (const invalid_argument& e) {
            cerr << "Error adding patient: " << e.what() << endl;
        }
        catch (const exception& e) {
            cerr << "Unexpected error: " << e.what() << endl;
        }
    }
    // Serve a limited number of patients, giving priority to urgent ones
    void Serve_All(int num) {
        int patient_served = 0;
        // Try serving urgent patients first
        try {
            if(time==0){
                while (patient_served < num && !urgentQueue.empty()) {
                    Patient current = urgentQueue.front();
                    Serve_One(current);
                    urgentQueue.pop();
                    patient_served ++;
                }
            }
        }
        catch (out_of_range& e) {
            cerr << "Error, Out of Bounds" << e.what() << endl;
        }

        // Then serve normal patients
        try{
            if(time==0){
                while (patient_served < num && !normalQueue.empty()) {
                    Patient current = normalQueue.front();
                    Serve_One(current);
                    normalQueue.pop();
                    patient_served++;
                }
            }
        }
        catch (out_of_range& e) {
            cerr << "Error, Out of Bounds." << e.what() << endl;
        }
    }

    // Serve one patient, incrementing the served counter 
    void Serve_One(Patient& patient) {
        total_served++; // Increment total served patients
        cout << "Served Patient ID: " << patient.Get_ID() << " | Arrival time: " << patient.getArrivalTime() << " | Gender: " << patient.Get_Gender() <<" | Status: "<<(patient.isUrgent() ? " Urguent " :" Normal " )<< endl;
    }

    // Advance time by one minute (called each cycle)
    void advance_Time() {
        time--; // time by 1 minute
        total_waiting++;
    }

    // Display the current status of the queues and patient statistics
    void Status(int num) {
        int urguentsize = urgentQueue.size();
        int  normalsize = normalQueue.size();
            cout << "Urgent Queue: " << (urguentsize-num>=0 ? urguentsize-num: 0)<< " patients \n";
            if (normalsize - num > 0) {
                cout << "Normal Queue: " << (urguentsize - num <= 0 ? normalsize - num + urguentsize : normalsize) << " patients \n";
            }
            else {
                cout << "Normal Queue: " << 0 << " patients \n";
            }
            cout << "Serving right now " << (num >= normalsize ? normalsize : num) << endl;
            cout << "Total Served: " << (total_served < 0 ? 0 : total_served) << "\n";
            cout << "Average Waiting Time: " << (total_served > 0 ? total_waiting / total_served : total_waiting) << " minutes.\n";
        
    }
    void fStatus() {
        cout << "Urgent Queue: " << urgentQueue.size() << " patients waiting.\n";
        cout << "Normal Queue: " << normalQueue.size() << " patients waiting.\n";
        cout << "Total Served: " << total_served << "\n";
        cout << "Average Waiting Time: " << (total_served > 0 ? total_waiting / total_served : total_waiting) << " minutes.\n";
    }
};
