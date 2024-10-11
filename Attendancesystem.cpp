 #include <iostream>  // Input-Output Stream header file
#include <ctime>     // Time related functions header file
#include <map>       // Map data structure header file // map - store in the pair of keys and values 
#include <string>    // String data type header file
#include <cstdlib>   // Standard library for random number generation

using namespace std;  // Using standard namespace

// Function to get the current time in HH:MM:SS format
string getCurrentTime() {
    time_t now = time(0);  // Get the current time
    tm *ltm = localtime(&now);  // Convert the time to local time

    string hours = to_string(ltm->tm_hour);  // Convert the hour to a string
    string minutes = to_string(ltm->tm_min);  // Convert the minute to a string
    string seconds = to_string(ltm->tm_sec);  // Convert the second to a string

    return hours + ":" + minutes + ":" + seconds;  // Return the time in HH:MM:SS format
}

// Function to send an arrival message to a student's parents
void sendArrivalMessage(string studentName) {
    string currentTime = getCurrentTime();  // Get the current time
    cout << "Arrival message sent to " << studentName << "'s parents." << endl;
    cout << "Arrival Time: " << currentTime << endl;  // Display the arrival time
}

// Function to send an absent message to a student's parents
void sendAbsentMessage(string studentName) {
    cout << studentName << "'s has been removed from the system." << endl;
}

// Function to generate a 6-digit OTP
string generateOTP() {
    srand(time(0));  // Seed for random number generation
    string otp = "";
    for (int i = 0; i < 6; i++) {
        otp += (rand() % 10) + '0';  // Generate a random digit and append it to the OTP
    }
    return otp;
}

// Function to verify an OTP
bool verifyOTP(string otp, string enteredOtp) {
    return otp == enteredOtp;
}

// Function to check a student's code and update their attendance
void checkStudentCode(map<string, string>& studentCodes, string studentName, string enteredCode, map<string, bool>& attendance) {
    // Check if the student's code exists in the system
    if (studentCodes.find(studentName) != studentCodes.end()) {
        // Check if the entered code matches the student's code
        if (studentCodes[studentName] == enteredCode) {
            string otp = generateOTP();  // Generate an OTP
            cout << "OTP sent to your registered mobile number: " << otp << endl;
            string enteredOtp;
            cout << "Enter the OTP: ";
            cin >> enteredOtp;
            // Verify the OTP
            if (verifyOTP(otp, enteredOtp)) {
                sendArrivalMessage(studentName);  // Send an arrival message to the student's parents
                attendance[studentName] = true;  // Update the student's attendance
            } else {
                cout << "Incorrect OTP!" << endl;  // Display an error message for incorrect OTP
            }
        } else {
            cout << "Incorrect code!" << endl;  // Display an error message for incorrect code
        }
    } else {
        cout << "Student not registered!" << endl;  // Display an error message for unregistered student
    }
}

// Function to check a student's attendance and send an absent message if necessary
void checkAttendance(map<string, bool>& attendance, string studentName) {
    if (!attendance[studentName]) {
        sendAbsentMessage(studentName);  // Send an absent message to the student's parents
    } else {
        cout << studentName << " has checked in. No absent message will be sent/If you think there's an error in my details, please review them again."

 << endl;
    }
}

int main() {
    map<string, string> studentCodes;  // Map to store student codes
    map<string, bool> attendance;  // Map to store student attendance
    string studentName, enteredCode;

    // Assign student codes
    studentCodes["Atharva_Patankar"] = "123";
    studentCodes["Saqlain_Mirani"] = "654";
    studentCodes["Dia_Jhonsa"] = "678";
    studentCodes["Priyans_Gupta"] = "911";
    studentCodes["Honey_tolani"] = "911";

    // Initialize student attendance
    attendance["Atharva_Patankar"] = false;
    attendance["Saqlain_Mirani"] = false;
    attendance["Dia_Jhonsa"] = false;
    attendance["Priyans_Gupta"] = false;
    attendance["Honey_tolani"] = false;

    cout << "Enter your name: ";
    cin >> studentName;

    cout << "Enter your Bus code: ";
    cin >> enteredCode;

    checkStudentCode(studentCodes, studentName, enteredCode, attendance);  // Check the student's code and update their attendance
    checkAttendance(attendance, studentName);  // Check the student's attendance and send an absent message if necessary

    return 0;
}