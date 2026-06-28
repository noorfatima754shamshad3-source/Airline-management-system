#include <iostream>
#include <string>
#include <conio.h>  // ya charater input laina ka lia ju hm na get_inpout function ma use hoa 
#include <cctype>   // toupper or tolower
#include <iomanip>
#include <windows.h>   // system function like sleep , clear screen 
#include <fstream>
using namespace std;
 
// coor codes hain predefined
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

string adminId = "a";
string adminPassword = "a";

void adminMenu();     // ju bi permisssions ya ju bi admin kr sakta ha es ko present krna ka lia lagaya ha
void passengerMenu(string userId); 
bool adminLogin();
bool passengerLogin(); 
void passengerSignup();
void addFlight(); 
void viewFlights();
void updateFlight();
void deleteFlight();
void addPassengerAdmin();
void viewPassengers();
void updatePassenger();
void deletePassenger();
void bookFlight(string userId);
void cancelReservation(string userId);
void viewAvailableFlights(); // ju app ka pass hain 
void personalReport(string userId);
void viewMyReservations(string userId);


// yhmaara validTIONS FUNCTIONS Hain
int integerInput();
string enterName();
string enterPhone();
string enterDate();
string enterTime();
bool isValidDate(string date);
bool isValidTime(string time);
bool isNumber(string str); 

int main() {
    system("cls");    // for clear screen 


    // sab sa pahla files add ki hain apni easyness ka lia   
    // ya es lia lagai ha jab kisi bii computer pat khola automatically three files create ho jay galti ka chance na rha
   
    ofstream f1("flights.txt", ios::app);  
    f1.close();
    ofstream f2("passengers.txt", ios::app);
    f2.close();
    ofstream f3("reservations.txt", ios::app);
    f3.close();
    
    int choice;
    
    while (true) {
        system("cls");
        cout << YELLOW;
        cout << "\n\n";
        cout << "\t\t\t\t\t\t==================================\n";
        cout << "\t\t\t\t\t\t     AIRLINE MANAGEMENT SYSTEM\n";
        cout << "\t\t\t\t\t\t==================================\n\n";
        cout << RESET;
        
        cout << "\t\t\t\t\t    " << "1. Admin Login" << "                " << "2. Passenger Login\n" ;
        cout << "\t\t\t\t\t    " << "3. View Flights" << "              " << "4. Passenger Sign Up\n" ;
        cout << "\t\t\t\t\t    " << "0." << RED << "EXIT\n" << RESET;
        
        cout << "\n\t\t\t\t\t\t" << "Enter choice: ";
        choice = integerInput();
        
        if (choice == 1) {
            if (adminLogin()) {
                adminMenu();
            }
        }
        else if (choice == 2) {
            passengerLogin();
        }
        else if (choice == 3) {
            viewFlights();
        }
        else if (choice == 4) {
            passengerSignup();
        }
        else if (choice == 0) {
            cout << "\n\n\t\t\t\t\t\tThank you! Goodbye " << endl;
            Sleep(2500);
            return 0;
        }
        else {
            cout << "\n\t\t\t\t\t\tInvalid choice......" << endl;
            Sleep(2500);
        }
    }
}

// ========== ADMIN LOGIN ==========
bool adminLogin() {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t  [------- ADMIN LOGIN -------]"<<endl;   
    cout << "\t\t\t\t\t\t*********************************\n\n" << RESET;
    
    string id, pass;
    cout << "\t\t\t\t\t\tEnter Admin ID: ";
    cin >> id;
    cout << "\t\t\t\t\t\tEnter Password: ";
    cin >> pass;
    cin.ignore();
    
    if (id == adminId && pass == adminPassword) {
        cout << "\n\t\t\t\t\t\tLogin successful!" << endl;
        Sleep(1000);
        return true;
    } else {
        cout << "\n\t\t\t\t\t\tInvalid admin....." << endl;
        Sleep(1500);
        return false;
    }
}

// passinger loginn
bool passengerLogin() {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- PASSENGER LOGIN -------]\n";
    cout << "\t\t\t\t\t\t******************************\n\n" << RESET;
    
    string userId, password;
    cout << "\t\t\t\t\t\tEnter User ID: ";
    getline(cin, userId);
    cout << "\t\t\t\t\t\tEnter Password: ";
    getline(cin, password);
    
    ifstream file("passengers.txt");
    string id, pass, name, phone;
    int bookings;
    double spent;
    
    while (file >> id >> pass >> name >> phone >> bookings >> spent) {
        if (id == userId && pass == password) {
            cout << "\n\t\t\t\t\t\tLogin Successful " << name << "!" << endl;
            Sleep(5000);
            file.close();
            passengerMenu(userId);
            return true;
        }
    }
    
    file.close();
    cout << "\n\t\t\t\t\t\tInvalid login......" << endl;
    Sleep(5000);
    return false;
}

//  PASSENGER SIGNUP
void passengerSignup() {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- PASSENGER SIGN UP -------]\n";
    cout << "\t\t\t\t\t\t********************************\n\n" << RESET;
    
    string userId, password, name, phone;
    
    cout << "\t\t\t\t\t\tEnter User ID: ";
    getline(cin, userId);
    
    cout << "\t\t\t\t\t\tEnter Password: ";
    getline(cin, password);
    
    cout << "\t\t\t\t\t\tEnter Name: ";
    name = enterName();
    
    cout << "\t\t\t\t\t\tEnter Phone (12 digits): ";
    phone = enterPhone();
    
    ofstream file("passengers.txt", ios::app);
    file << userId << " " << password << " " << name << " " 
         << phone << " 0 0.00" << endl;         // pahla 0 booking ka lia aur phor 0.00 ju passenger ka spent hoa ha
    file.close();
    
    cout << "\n\t\t\t\t\t\tSignup successful!" << endl;
    Sleep(2000);
}

//ADMIN MENU 
void adminMenu() {
    int choice;       // admin authority start from here 
    while (true) {
        system("cls");
        cout << YELLOW;
        cout << "\n\n\t\t\t\t\t\t     [------- ADMIN MENU -------]\n";
        cout << "\t\t\t\t\t\t***********************************\n\n" << RESET;
        
        cout << "\t\t\t\t\t    " << "1. Add Flight" << "                " << "2. View Flights\n" ;
        cout << "\t\t\t\t\t    " << "3. Update Flight"  << "             " << "4. Delete Flight\n" ;
        cout << "\t\t\t\t\t    " << "5. Add Passengers  "  << "          " << "6. View Passengers\n" ;
        cout << "\t\t\t\t\t    " << "7. Update Passenger"  << "          " << "8. Delete Passenger\n" ;
        cout << "\t\t\t\t\t    " << "0." <<  RED << "Logout\n\n" << RESET;
        
        cout << "\t\t\t\t\t\t    " << "Enter choice: ";
        choice = integerInput();  // ya function btata ha ka sirf integer  input hpo sakta aur kuch ni like !@#$%^&*
        
        if (choice == 1) {
            addFlight();
        }
        else if (choice == 2) {
            viewFlights();
        }
        else if (choice == 3) {
            updateFlight();
        }
        else if (choice == 4) {
            deleteFlight();
        }
        else if (choice == 5) {
            addPassengerAdmin();
        }
        else if (choice == 6) {
            viewPassengers();
        }
        else if (choice == 7) {
            updatePassenger();
        }
        else if (choice == 8) {
            deletePassenger();
        }
        else if (choice == 0) {
            cout << "\n\t\t\t\t\t\tLogging out..." << endl;
            Sleep(1000);
            return;
        }
        else {
            cout << "\n\t\t\t\t\t\tInvalid choice........" << endl;
            Sleep(1000);
        }
    }
}

// ========== PASSENGER MENU ==========
void passengerMenu(string userId) {
    int choice;
    
    while (true) {
        system("cls");
        cout << YELLOW;
        cout << "\n\n\t\t\t\t\t\t[------- PASSENGER MENU -------]\n";
        cout << "\t\t\t\t\t\t*******************************\n\n" << RESET;
        
        cout << "\t\t\t\t\t\t    " << "1. Book Flight\n" ;
        cout << "\t\t\t\t\t\t    " << "2. Cancel Reservation\n" ;
        cout << "\t\t\t\t\t\t    " << "3. View Available Flights\n" ;
        cout << "\t\t\t\t\t\t    " << "4. My Report\n" ;
        cout << "\t\t\t\t\t\t    " << "5. My Reservations\n" ;
        cout << "\t\t\t\t\t\t    " << "0." << RED << "Main Menu\n\n" << RESET;
        
        cout << "\t\t\t\t\t\t    " << "Enter choice: ";
        choice = integerInput();
        
        if (choice == 1) {
            bookFlight(userId);
        }
        else if (choice == 2) {
            cancelReservation(userId);
        }
        else if (choice == 3) {
            viewAvailableFlights();
        }
        else if (choice == 4) {
            personalReport(userId);
        }
        else if (choice == 5) {
            viewMyReservations(userId);
        }
        else if (choice == 0) {
            cout << "\n\t\t\t\t\t\tGoing to main Menu..." << endl;
            Sleep(1000);
            return;
        }
        else {
            cout << "\n\t\t\t\t\t\tInvalid choice!" << endl;
            Sleep(1000);
        }
    }
}

 //   FLIGHT FUNCTIONS
void addFlight() {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- ADD NEW FLIGHT -------]\n";
    cout << "\t\t\t\t\t\t*******************************\n\n" << RESET;
    
    string flightNo, departure, destination, date, time;
    int economySeats, businessSeats;
    double economyFare, businessFare;
    
    cout << "\t\t\t\t\t\tFlight Number: ";
    getline(cin, flightNo);
    
    cout << "\t\t\t\t\t\tDeparture City: ";
    getline(cin, departure);
    
    cout << "\t\t\t\t\t\tDestination City: ";
    getline(cin, destination);
    
    cout << "\t\t\t\t\t\tDate (DD-MM-YYYY): ";
    date = enterDate();
    
    cout << "\t\t\t\t\t\tTime (HH:MM): ";
    time = enterTime();
    
    cout << "\t\t\t\t\t\tEconomy Seats: ";
    economySeats = integerInput();
    cout << endl;
    cout << "\t\t\t\t\t\tBusiness Seats: ";
    businessSeats = integerInput();
    cout << endl;
    cout << "\t\t\t\t\t\tEconomy Fare : $ ";
    economyFare = integerInput();
    cout << endl;
    cout << "\t\t\t\t\t\tBusiness Fare: $ ";
    businessFare = integerInput();
    cout << endl;
    int totalSeats = economySeats + businessSeats;
    
    ofstream file("flights.txt", ios::app);
    file << flightNo << " " << departure << " " << destination << " " 
         << date << " " << time << " " << totalSeats << " " 
         << economySeats << " " << businessSeats << " " 
         << economyFare << " " << businessFare << endl;
    file.close();
    
    cout << "\n\t\t\t\t\t\tFlight added successfully!" << endl;
    Sleep(1500);
}

void viewFlights() {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- ALL FLIGHTS -------]\n";
    cout << "\t\t\t\t\t\t***************************\n\n" << RESET;
    
    ifstream file("flights.txt");
    if (!file) {
        cout << "\t\t\t\t\t\tNo flights found!\n";
        Sleep(2300);
        return;
    }
    
    cout << "\t-------------------------------------------------------------------------------------------------\n";
    cout << "\t" << left << setw(12) << "Flight" << setw(15) << "Departure"<< setw(15) << "Destination" << setw(12) << "Date"
         << setw(10) << "Time" << setw(8) << "Eco" << setw(8) << "Bus" << setw(10) << "Eco Fare" << setw(10) << "Bus Fare" << endl;
    cout << "\t-------------------------------------------------------------------------------------------------\n";
    
    string flightNo, departure, destination, date, time;
    int totalSeats, economySeats, businessSeats;
    double economyFare, businessFare;
    
    while (file >> flightNo >> departure >> destination >> date >> time 
          >> totalSeats >> economySeats >> businessSeats 
          >> economyFare >> businessFare) {
        cout << "\t" << left << setw(12) << flightNo<< setw(15) << departure << setw(15) << destination << setw(12) << date
             << setw(10) << time << setw(8) << economySeats << setw(8) << businessSeats << "$" << setw(9) << fixed << setprecision(2) << economyFare << "$" << setw(9) << businessFare << endl;
    }
    
    file.close();
    // cout << "\n\t\t\t\t\t\tDisplaying all flights..." << endl;
    Sleep(5000);
}                       //  view flight koi bi kr sakta ha ya sign up or login ka bina wala bi

//  UPDATE FLIGHT 
void updateFlight() {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- UPDATE FLIGHT -------]\n";
    cout << "\t\t\t\t\t\t*****************************\n\n" << RESET;
    
    cout << "\t\t\t\t\t\tFlight Number: ";
    string flightNo;
    getline(cin, flightNo);
    
    ifstream inFile("flights.txt");
    if (!inFile) {
        cout << "\n\t\t\t\t\t\tNo flights in database!\n";
        Sleep(1500);
        return;
    }
    
    ofstream tempFile("temp.txt");   // write ka lia temporary
    bool found = false;
    
    // Read from file directly
    string fNo, departure, destination, date, time;
    int totalSeats, economySeats, businessSeats;
    double economyFare, businessFare;
    
    while (inFile >> fNo >> departure >> destination >> date >> time 
           >> totalSeats >> economySeats >> businessSeats 
           >> economyFare >> businessFare) {
        
        if (fNo == flightNo) {
            found = true;
            
            cout << "\n\t\t\t\t\t\tCurrent Details:\n";
            cout << "\t\t\t\t\t\tDeparture: " << departure << endl;
            cout << "\t\t\t\t\t\tDestination: " << destination << endl;
            cout << "\t\t\t\t\t\tDate: " << date << endl;
            cout << "\t\t\t\t\t\t Departure Time: " << time << endl;
            cout << "\t\t\t\t\t\tEconomy Seats: " << economySeats << endl;
            cout << "\t\t\t\t\t\tBusiness Seats: " << businessSeats << endl;
            cout << "\t\t\t\t\t\tEconomy Fare: $" << economyFare << endl;
            cout << "\t\t\t\t\t\tBusiness Fare: $" << businessFare << endl;
            
            cout << "\n\t\t\t\t\t\tEnter new details:\n";
            
            cout << "\t\t\t\t\t\tNew Departure City: ";
            getline(cin, departure);
            
            cout << "\t\t\t\t\t\tNew Destination City: ";
            getline(cin, destination);
            
            cout << "\t\t\t\t\t\tNew Date (DD-MM-YYYY): ";
            date = enterDate();   // ya vaidate date ka lia 
            
            cout << "\t\t\t\t\t\tNew Time (HH:MM): ";
            getline(cin, time);
            
            cout << "\t\t\t\t\t\tNew Economy Seats: ";
            economySeats = integerInput();
            
            cout << "\t\t\t\t\t\tNew Business Seats: ";
            businessSeats = integerInput();
            
            cout << "\t\t\t\t\t\tNew Economy Fare: ";
            economyFare = integerInput();
            
            cout << "\t\t\t\t\t\tNew Business Fare: ";
            businessFare = integerInput();
            
            totalSeats = economySeats + businessSeats;
            
            tempFile << fNo << " " << departure << " " << destination << " " 
                     << date << " " << time << " " << totalSeats << " " 
                     << economySeats << " " << businessSeats << " " 
                     << economyFare << " " << businessFare << endl;
            break;
        } else {
            tempFile << fNo << " " << departure << " " << destination << " " 
                     << date << " " << time << " " << totalSeats << " " 
                     << economySeats << " " << businessSeats << " " 
                     << economyFare << " " << businessFare << endl;
        }
    }
    
    inFile.close();
    tempFile.close();
    
    if (found) {
        remove("flights.txt");
        rename("temp.txt", "flights.txt");
        cout << "\n\t\t\t\t\t\tFlight updated successfully......." << endl;

    } else {
        remove("temp.txt");
        cout << "\n\t\t\t\t\t\tFlight not found!" << endl;
    }
    Sleep(1500);
}

void deleteFlight() {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- DELETE FLIGHT -------]\n";
    cout << "\t\t\t\t\t\t*****************************\n\n" << RESET;
    
    cout << "\t\t\t\t\t\tFlight Number: ";
    string flightNo;
    getline(cin, flightNo);
    
    ifstream inFile("flights.txt");
    if (!inFile) {
        cout << "\n\t\t\t\t\t\tNo flights in database!\n";
        Sleep(1500);
        return;
    }
    
    ofstream tempFile("temp.txt");
    bool found = false;
    
    // Read each flight directly
    string fNo, departure, destination, date, time;
    int totalSeats, economySeats, businessSeats;
    double economyFare, businessFare;
    
    while (inFile >> fNo >> departure >> destination >> date >> time 
           >> totalSeats >> economySeats >> businessSeats 
           >> economyFare >> businessFare) {
        
        if (fNo == flightNo) {
            found = true;  // Skip this flight (don't write to temp file)
        } else {
            // Write all other flights to temp file
            tempFile << fNo << " " << departure << " " << destination << " " 
                     << date << " " << time << " " << totalSeats << " " 
                     << economySeats << " " << businessSeats << " " 
                     << economyFare << " " << businessFare << endl;
        }
    }
    
    inFile.close();
    tempFile.close();
    
    if (found) {
        remove("flights.txt");
        rename("temp.txt", "flights.txt");
        cout << "\n\t\t\t\t\t\tFlight deleted successfully!" << endl;
    } else {
        remove("temp.txt");   /// remove string ka funtion haaa 
        cout << "\n\t\t\t\t\t\tFlight not found..........." << endl;
    }
    Sleep(2500);
}

// PASSENGER FUNCTION
void addPassengerAdmin() {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- ADD PASSENGER(S) -------]\n";
    cout << "\t\t\t\t\t\t******************************\n\n" << RESET;
    
    cout << "\t\t\t\t\t\tHow many passengers? ";
    int count = integerInput();
    
    for (int i = 0; i < count; i++) {
        cout << "\n\t\t\t\t\t\t--- Passenger " << i+1 << " ---\n";
        
        string userId, password, name, phone;
        
        cout << "\t\t\t\t\t\tUser ID: ";
        getline(cin, userId);
        
        cout << "\t\t\t\t\t\tPassword: ";
        getline(cin, password);
        
        cout << "\t\t\t\t\t\tName: ";
        name = enterName();
        
        cout << "\t\t\t\t\t\tPhone (12 digits): ";
        phone = enterPhone();
        
        ofstream file("passengers.txt", ios::app);
        file << userId << " " << password << " " << name << " " 
             << phone << " 0 0.00" << endl;
        file.close();
        
        cout << "\t\t\t\t\t\tAdded: " << userId << endl;
    }
   
    cout << "\n\t\t\t\t\t\tAll passengers added!" << endl;
    Sleep(2000);
}

void viewPassengers() {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- ALL PASSENGERS -------]\n";
    cout << "\t\t\t\t\t\t*****************************\n\n" << RESET;
    
    ifstream file("passengers.txt");
    if (!file) {
        cout << "\t\t\t\t\t\tNo passengers found........\n";
        Sleep(2000);
        return;
    }
    
    cout << "\t------------------------------------------------------------------------------------------\n";
    cout << "\t" << left << setw(15) << "User ID"
         << setw(25) << "Name"
         << setw(20) << "Phone"
         << setw(10) << "Bookings"
         << setw(15) << "Total Spent" << endl;
    cout << "\t------------------------------------------------------------------------------------------\n";
    
    string userId, password, name, phone;
    int bookings;
    double spent;
    
    while (file >> userId >> password >> name >> phone >> bookings >> spent) {
        cout << "\t" << left << setw(15) << userId
             << setw(25) << name
             << setw(20) << phone
             << setw(10) << bookings
             << "$" << setw(14) << fixed << setprecision(2) << spent << endl;
    }
    
    file.close();
    Sleep(5000);
}

void updatePassenger() {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- UPDATE PASSENGER -------]\n";
    cout << "\t\t\t\t\t\t*******************************\n\n" << RESET;
    
    cout << "\t\t\t\t\t\tUser ID: ";
    string userId;
    getline(cin, userId);
    
    ifstream inFile("passengers.txt");
    if (!inFile) {
        cout << "\n\t\t\t\t\t\tNo passengers in database!\n";
        Sleep(1500);
        return;
    }
    
    ofstream tempFile("temp.txt");
    bool found = false;
    
    // Read each passenger directly
    string id, pass, name, phone;
    int bookings;
    double spent;
    
    while (inFile >> id >> pass >> name >> phone >> bookings >> spent) {   
        
        if (id == userId) {


            found = true;
            
            cout << "\n\t\t\t\t\t\tCurrent Name: " << name << endl;
            cout << "\t\t\t\t\t\tCurrent Phone: " << phone << endl;
            
            cout << "\n\t\t\t\t\t\tEnter new details:\n";
            cout << "\t\t\t\t\t\tNew Name: ";
            name = enterName();

            cout << "\t\t\t\t\t\tNew Phone: ";
            phone = enterPhone();
            
            cout << "\t\t\t\t\t\tNew Password: ";
            getline(cin, pass);
            
            tempFile << id << " " << pass << " " << name << " " 
                    << phone << " " << bookings << " " << fixed << setprecision(2) << spent << endl;
        } else {   
            // temporary file ko remove krna ka lia

            tempFile << id << " " << pass << " " << name << " " 
                    << phone << " " << bookings << " " << fixed << setprecision(2) << spent << endl;
        }
    }
    
    inFile.close();
    tempFile.close();
    
    if (found) {
        remove("passengers.txt");
        rename("temp.txt","passengers.txt");
        cout << "\n\t\t\t\t\t\tPassenger updated successfully....." << endl;
    } else {
        remove("temp.txt");
        cout << "\n\t\t\t\t\t\tPassenger not found!" << endl;
    }
    Sleep(2500);
}

void deletePassenger() 
{
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- DELETE PASSENGER -------]\n";
    cout << "\t\t\t\t\t\t*******************************\n\n" << RESET;
    
    cout << "\t\t\t\t\t\tUser ID: ";
    string userId;
    getline(cin, userId);
    
    ifstream inFile("passengers.txt");
    if (!inFile) {
        cout << "\n\t\t\t\t\t\tNo passengers in database!\n";
        Sleep(1500);
        return;
    }
    
    ofstream tempFile("temp.txt");
    bool found = false;
    
    // Read each passenger directly
    string id, pass, name, phone;
    int bookings;
    double spent;
    
    while (inFile >> id >> pass >> name >> phone >> bookings >> spent) {
        
        if (id == userId) {
            found = true;  // Skip this passenger don't write to temp file
        } else {
            // Write all other passengers to temp file
            tempFile << id << " " << pass << " " << name << " " 
                    << phone << " " << bookings << " " << fixed << setprecision(2) << spent << endl;
        }
    }
    
    inFile.close();
    tempFile.close();
    
    if (found) {
        remove("passengers.txt");
        rename("temp.txt", "passengers.txt");
        cout << "\n\t\t\t\t\t\tPassenger deleted successfully!" << endl;
    } else {
        remove("temp.txt");
        cout << "\n\t\t\t\t\t\tPassenger not found!" << endl;
    }
    Sleep(1500);
}
// book flight
void bookFlight(string userId) {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- BOOK A FLIGHT -------]\n";
    cout << "\t\t\t\t\t\t*****************************\n\n" << RESET;
    
    viewAvailableFlights();
    
    cout << "\n\t\t\t\t\t\tFlight Number: ";
    string flightNo;
    getline(cin, flightNo);
    
    ifstream fFile("flights.txt");
    if (!fFile) {
        cout << "\n\t\t\t\t\t\tNo flights available!\n";
        Sleep(1500);
        return;
    }
    
    string fNo, departure, destination, date, time;
    int totalSeats, economySeats, businessSeats;
    double economyFare, businessFare;
    bool found = false;
    
    // Find the flight
    while (fFile >> fNo >> departure >> destination >> date >> time 
          >> totalSeats >> economySeats >> businessSeats 
          >> economyFare >> businessFare) {
        if (fNo == flightNo) {
            found = true;
            break;
        }
    }
    fFile.close();
    
    if (!found) {
        cout << "\n\t\t\t\t\t\tFlight not found.........\n";
        Sleep(1500);
        return;
    }
    
    // Show seat options
    cout << "\t\t\t\t\t\t" << "1. Economy ($" << (int)economyFare << ")\n";
    cout << "\t\t\t\t\t\t" << "2. Business ($" << (int)businessFare << ")\n";
    cout << "\t\t\t\t\t\t" << "Choice: ";
    int seatType = integerInput();
    
    while(seatType != 1 && seatType != 2) {
        cout << "\n\t\t\t\t\t\tInvalid choice!\n";
        Sleep(2500);
        return;
    }
    
                   // Set seat type details
    int maxSeats;
    double fare;
    string typeName;
    
    if (seatType == 1) {
        maxSeats = economySeats;
        fare = economyFare;
        typeName = "Economy";
    } else {
        maxSeats = businessSeats;
        fare = businessFare;
        typeName = "Business";
    }
    
    if (maxSeats <= 0) {
        cout << "\n\t\t\t\t\t\tNo seats available in this class!\n";
        Sleep(1500);
        return;
    }
    
    // Get number of seats
    cout << "\t\t\t\t\t\tNumber of Seats (1-" << maxSeats << "): ";
    int seats = integerInput();
    
    if (seats < 1 || seats > maxSeats) {
        cout << "\n\t\t\t\t\t\tInvalid number of seats!\n";
        Sleep(2500);
        return;
    }
    
    double totalFare = fare * seats;
    
    // Update flight seats
    ifstream inFile("flights.txt");
    ofstream temp("temp.txt");
    
    while (inFile >> fNo >> departure >> destination >> date >> time 
          >> totalSeats >> economySeats >> businessSeats 
          >> economyFare >> businessFare) {
        if (fNo == flightNo) {
            if (seatType == 1) {
                economySeats -= seats;
            } else {
                businessSeats -= seats;
            }
            totalSeats = economySeats + businessSeats;
        }
        temp << fNo << " " << departure << " " << destination << " " 
             << date << " " << time << " " << totalSeats << " " 
             << economySeats << " " << businessSeats << " " 
             << economyFare << " " << businessFare << endl;
    }
    inFile.close();
    temp.close();
    remove("flights.txt");
    rename("temp.txt", "flights.txt");
    
    // Create reservation ID
    string resId = "RES" + userId; // reaservation id
    
    // Add reservation
    ofstream res("reservations.txt", ios::app);
    res << resId << " " << userId << " " << flightNo << " " 
        << date << " " << seats << " " 
        << typeName << " " << totalFare << endl;
    res.close();
    
    // Update passenger bookings and spending
    ifstream pFile("passengers.txt");
    ofstream pTemp("ptemp.txt");
    string pId, pass, pname, pphone;
    int pbookings;
    double pspent;
    
    while (pFile >> pId >> pass >> pname >> pphone >> pbookings >> pspent) {
        if (pId == userId) {
            pbookings++;   // passenger ki booking +1
            pspent += totalFare;
        }
        pTemp << pId << " " << pass << " " << pname << " " 
              << pphone << " " << pbookings << " " << fixed << setprecision(2) << pspent << endl;
    }
    pFile.close();
    pTemp.close();
    remove("passengers.txt");
    rename("ptemp.txt", "passengers.txt");
    
    cout << "\n\n\t\t\t\t\t\tBooking confirmed!" << endl;
    cout << "\t\t\t\t\t\tReservation ID: " << resId << endl;
    cout << "\t\t\t\t\t\tTotal: $" << totalFare << endl;
    Sleep(3000);
}

void viewAvailableFlights() {
    system("cls");
    cout << YELLOW;
       cout << "\n\n\t\t\t\t\t\t[------- AVAILABLE FLIGHTS -------]\n";
    cout << "\t\t\t\t\t\t*********************************\n\n" << RESET;
    
    ifstream file("flights.txt");
    if (!file) {
           cout << "\t\t\t\t\t\tNo flights available.......\n";
             Sleep(2500);
        return;
    }
    
    cout << "\t--------------------------------------------------------------------------------------------------------------\n";
    cout << "\t" << left << setw(12) << "Flight" 
         << setw(15) << "Departure"
         << setw(15) << "Destination"
         << setw(12) << "Date"
         << setw(10) << "Time"
         << setw(8) << "Eco"
         << setw(8) << "Bus"
         << setw(10) << "Eco Fare"
         << setw(10) << "Bus Fare" << endl;
    cout << "\t--------------------------------------------------------------------------------------------------------------\n";
    
    string flightNo, departure, destination, date, time;
    int totalSeats, economySeats, businessSeats;
    double economyFare, businessFare;
    bool found = false;
    
    while (file >> flightNo >> departure >> destination >> date >> time 
          >> totalSeats >> economySeats >> businessSeats 
          >> economyFare >> businessFare) {
        if (totalSeats > 0) {
            found = true;
            cout << "\t" << left << setw(12) << flightNo
                 << setw(15) << departure
                 << setw(15) << destination
                 << setw(12) << date
                 << setw(10) << time
                   << setw(8) << economySeats
                 << setw(8) << businessSeats
                 << "$" << setw(9) << fixed << setprecision(2) << economyFare
                 << "$" << setw(9) << businessFare << endl;
        }
    }
    
    file.close();
    
      if (!found) {
         cout << "\n\t\t\t\t\t\tNo flights available........" << endl;
    }
    
    Sleep(2000);
}



// RESERVATION FUNCTIONS
void cancelReservation(string userId) {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- CANCEL RESERVATION -------]\n";
    cout << "\t\t\t\t\t\t**********************************\n\n" << RESET;
    
    // Show user's reservations
    ifstream resFile("reservations.txt");
    bool hasReservations = false;
    
    cout << "\t\t\t\t\t\tYour Reservations:\n";
    cout << "\t----------------------------------------------------------------------------------------\n";
    cout << "\t" << left << setw(12) << "Res ID"
         << setw(12) << "Flight"
         << setw(12) << "Date"
         << setw(10) << "Seats"
         << setw(12) << "Type"
         << setw(15) << "Total" << endl;
    cout << "\t----------------------------------------------------------------------------------------\n";
    
    string resId, uId, flightNo, date, seatType;
    int seats;
    double totalFare;
    
       while (resFile >> resId >> uId >> flightNo >> date >> seats >> seatType >> totalFare) {
        if (uId == userId) {
            hasReservations = true;
            cout << "\t" << left << setw(12) << resId
                 << setw(12) << flightNo
                 << setw(12) << date
                 << setw(10) << seats
                 << setw(12) << seatType
                 << "$" << setw(14) << fixed << setprecision(2) << totalFare << endl;
        }
    }
    resFile.close();
    
    if (!hasReservations) {
        cout << "\t\t\t\t\t\tNo reservations found......\n";
        Sleep(2500);
        return;
    }
    
      cout << "\n\t\t\t\t\t\tEnter Reservation ID to cancel: ";
    string cancelId;
    getline(cin, cancelId);
    
    // Delete reservation from file
    ifstream inRes("reservations.txt");
    ofstream tempRes("temp_res.txt");   // temporary file ha for reservations jis ma ha passengers na ju ki hA

    bool found = false;
    string cancelFlightNo;
    int cancelSeats = 0;
      string cancelSeatType;
    double cancelTotalFare = 0;
    
    while (inRes >> resId >> uId >> flightNo >> date >> seats >> seatType >> totalFare) {
        if (resId == cancelId && uId == userId) {
            found = true;
            cancelFlightNo = flightNo;
            cancelSeats = seats;
             cancelSeatType = seatType;
            cancelTotalFare = totalFare;
            // Don't write this reservation deleting it
        } else {
            tempRes << resId << " " << uId << " " << flightNo << " " 
                   << date << " " << seats << " " << seatType << " " << totalFare << endl;
        }
    }
    inRes.close();
    tempRes.close();
    
    if (!found) {
        remove("temp_res.txt");
        cout << "\n\t\t\t\t\t\tReservation not found!" << endl;
        Sleep(2500);
        return;
    }
    
    remove("reservations.txt");
    rename("temp_res.txt", "reservations.txt");
    
    // Return seats to flight
    ifstream inFlight("flights.txt");
    ofstream tempFlight("temp_flight.txt");
    string fNo, departure, dest, fdate, ftime;
    int tSeats, eSeats, bSeats;
    double eFare, bFare;
    
    while (inFlight >> fNo >> departure >> dest >> fdate >> ftime 
          >> tSeats >> eSeats >> bSeats >> eFare >> bFare) {
        if (fNo == cancelFlightNo) {
            if (cancelSeatType == "Economy") {
                eSeats += cancelSeats;
            } else {
                bSeats += cancelSeats;
            }
            tSeats = eSeats + bSeats;
        }
        tempFlight << fNo << " " << departure << " " << dest << " " 
                  << fdate << " " << ftime << " " << tSeats << " " 
                  << eSeats << " " << bSeats << " " 
                  << eFare << " " << bFare << endl;
    }
    inFlight.close();
    tempFlight.close();
    
    remove("flights.txt");
    rename("temp_flight.txt", "flights.txt");
    
    // Update passenger bookings and spending
    ifstream pFile("passengers.txt");
    ofstream pTemp("ptemp2.txt");
    string pId, pass, pname, pphone;
    int pbookings;
    double pspent;
    
    while (pFile >> pId >> pass >> pname >> pphone >> pbookings >> pspent) {
        if (pId == userId) {
            pbookings--;
            pspent -= cancelTotalFare;
            if (pbookings < 0) pbookings = 0;
            if (pspent < 0) pspent = 0;
        }
        pTemp << pId << " " << pass << " " << pname << " " 
              << pphone << " " << pbookings << " " << fixed << setprecision(2) << pspent << endl;
    }
    pFile.close();
    pTemp.close();
    remove("passengers.txt");
    rename("ptemp2.txt", "passengers.txt");
    
    cout << "\n\t\t\t\t\t\tReservation cancelled successfully......" << endl;
    Sleep(2000);
}

/// REPORT FUNCTIONS
void personalReport(string userId) {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- PERSONAL REPORT -------]\n";
    cout << "\t\t\t\t\t\t*******************************\n\n" << RESET;
    
    // Get passenger info
    ifstream pFile("passengers.txt");
    if (!pFile) {
        cout << "\t\t\t\t\t\tNo passenger data found!\n";
        Sleep(2000);
        return;
    }
    
    string id, pass, name, phone;
    int bookings;
    double spent;
    bool found = false;
    
    while (pFile >> id >> pass >> name >> phone >> bookings >> spent) {
        if (id == userId) {
            found = true;
            cout << "\t\t\t\t\t\tName: " << name << endl;
            cout << "\t\t\t\t\t\tPhone: " << phone << endl;
            cout << "\t\t\t\t\t\tTotal Bookings: " << bookings << endl;
            cout << "\t\t\t\t\t\tTotal Spent: $" << fixed << setprecision(2) << spent << endl;
            break;
        }
    }
    pFile.close();
    
    if (!found) {
        cout << "\t\t\t\t\t\tPassenger not found!" << endl;
        Sleep(2500);
        return;
    }
    
    // Show reservation history
    cout << "\n\t\t\t\t\t\tReservation History: \n";
    cout << "\t----------------------------------------------------------------------------------------\n";
    cout << "\t" << left << setw(12) << "Res ID"
         << setw(12) << "Flight"
         << setw(12) << "Date"
         << setw(10) << "Seats"
         << setw(12) << "Type"
         << setw(15) << "Total" << endl;
    cout << "\t----------------------------------------------------------------------------------------\n";
    
    ifstream resFile("reservations.txt");
    if (!resFile) {
        cout << "\t\t\t\t\t\tNo reservation data!\n";
        Sleep(2500);
        return;
    }
    
    string resId, uId, flightNo, date, seatType;
    int seats;
    double totalFare;
    int totalReservations = 0;
    
    while (resFile >> resId >> uId >> flightNo >> date >> seats >> seatType >> totalFare) {
        if (uId == userId) {
            totalReservations = totalReservations + 1;
            cout << "\t" << left << setw(12) << resId
                 << setw(12) << flightNo
                 << setw(12) << date
                 << setw(10) << seats
                 << setw(12) << seatType
                 << "$" << setw(14) << fixed << setprecision(2) << totalFare << endl;
        }
    }
    resFile.close();
    
    cout << "\n\t\t\t\t\t\tTotal Reservations: " << totalReservations << endl;
    Sleep(4000);
}

void viewMyReservations(string userId) {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- MY RESERVATIONS -------]\n";
    cout << "\t\t\t\t\t\t*******************************\n\n" << RESET;
    
    ifstream resFile("reservations.txt");
    if (!resFile) {
        cout << "\t\t\t\t\t\tNo reservations found!\n";
        Sleep(2000);
        return;
    }
    
    bool hasReservations = false;
    
    cout << "\t----------------------------------------------------------------------------------------\n";
    cout << "\t" << left << setw(12) << "Res ID"
         << setw(12) << "Flight"
         << setw(12) << "Date"
         << setw(10) << "Seats"
         << setw(12) << "Type"
         << setw(15) << "Total" << endl;
    cout << "\t----------------------------------------------------------------------------------------\n";
    
    string resId, uId, flightNo, date, seatType;
    int seats;
    double totalFare;
    
    while (resFile >> resId >> uId >> flightNo >> date >> seats >> seatType >> totalFare) {
        if (uId == userId) {
            hasReservations = true;
            cout << "\t" << left << setw(12) << resId
                 << setw(12) << flightNo
                 << setw(12) << date
                 << setw(10) << seats
                 << setw(12) << seatType
                 << "$" << setw(14) << fixed << setprecision(2) << totalFare << endl;
        }
    }
    resFile.close();
    
    if (!hasReservations) {
        cout << "\t\t\t\t\t\tNo reservations found....\n";
    }
    Sleep(4000);
}

//         VALIDATION FUNCTIONS 
bool isNumber(string str) {
    if (str.empty()) return false;
    for (int i = 0; i < str.length(); i++) {      //AB,C not allowed
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}

bool isValidDate(string date) {
    if (date.length() != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;
    
    string day = date.substr(0, 2); // 0 index par jao aur waha sa zero  index aur one index wala utha luuu

    string month = date.substr(3, 2); // 3 index pa r jao aur 2 index uthao integer ka
    string year = date.substr(6, 4);
    
    if (!isNumber(day) || !isNumber(month) || !isNumber(year)) return false;
    
    int d = stoi(day);
    int m = stoi(month);
    int y = stoi(year);
    
    if (d < 1 || d > 31) return false;
    if (m < 1 || m > 12) return false;
    if (y < 2024 || y > 2030) return false;
    
    return true;
}

bool isValidTime(string time) {
    if (time.length() != 5) return false; // 07:09 ya 5 length
    if (time[2] != ':') return false;
    
    string hour = time.substr(0, 2);  // .SUBSTR  ya index bnata ha input ka
    string minute = time.substr(3, 2);
    
    if (!isNumber(hour) || !isNumber(minute)) return false;
    
    int h = stoi(hour);
    int m = stoi(minute);
    
    if (h < 0 || h > 23) return false;
    if (m < 0 || m > 59) return false;
    
    return true;
}

int integerInput()
{
    int input = 0;
    char ch = 0;
    int count = 0;

    while(true)
    {
        ch = _getch();
        bool valid = false;
        if(count > 0 && ch == 13){
            break;
        }
        if (ch == 8 && count > 0) {
            input /= 10;
            count--;
            cout << "\b \b";  // for remove one charater on the left side 
            continue;
        }
        if((ch >= '0' && ch <='9')){
            count++;
            valid = true;
        }
        if(ch == 32){
            valid = false;
        }
        
        if(valid){
            int digit = ch - 48;                             // ya inteer ko ak series of integer ma convert krta ha
            input = (input * 10) + digit;
            cout << ch;
        }
    }
    return input;
}

string enterName() {   
    string name;
    while (true) {
        getline(cin, name);
        if (name.length() > 0) {
            bool valid = true;
            for (int i = 0; i < name.length(); i++) {
                char c = name[i];
                if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ' || c == '-')) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                return name;
            }
        }
        cout << "Invalid name Please enter letters, spaces or hyphens only: ";
    }
}

string enterPhone() {
    string phone;
    while (true) {
        getline(cin, phone);
        if (phone.length() == 12) {
            bool valid = true;
            for (int i = 0; i < phone.length(); i++) {
                if (phone[i] < '0' || phone[i] > '9') {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                return phone;
            }
        }
        cout << "Invalid phone Please enter exactly 12 digits: ";
    }
}

string enterDate() {
    string date;
    while (true) {
        getline(cin, date);
        if (isValidDate(date)) {
            return date;
        }
        cout << "Invalid date format! Please use DD-MM-YYYY format.\n";
        cout << "Enter date (DD-MM-YYYY): ";
    }
}

string enterTime() {
    string time;
    while (true) {
        getline(cin, time);
        if (isValidTime(time)) {
            return time;
        }
        cout << "Invalid time format Please use HH:MM format (24-hour).\n";
        cout << "Enter time (HH:MM): ";
    }
}