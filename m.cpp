#include <string>
#include <regex> // A library perfect for the ID checking
#include <iostream>
using namespace std;
class Patient {
private:
	string ID;
	char Gender;
	string arrival_time;
	bool is_urguent;
public:
	//Constructor
	Patient(string id, char g, string arr, bool urg) {
		if (!Check_ID(id)) {
			throw invalid_argument("Invalid ID format. ID must be exactly 14 digits.");
		}
		if (g != 'M' && g != 'F') {
			throw invalid_argument("Invalid Gender. Must be 'M' (Male) or 'F' (Female).");
		}

		ID = id;
		Gender = g;
		arrival_time = arr;
		is_urguent = urg;
	}
	bool Check_ID(string ID) {
		regex pattern(R"(\d{14})"); //Checks if the ID is 14 digits wide
		return regex_match(ID, pattern);
	}
	string Get_ID() {
		return ID;
	}
	char Get_Gender() { return Gender; }
	string getArrivalTime(){ return arrival_time; }
	bool isUrgent() { return is_urguent; }
};