#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
using namespace std;
struct Vehicle
{
    string regNo;
    string owner;
    string type;
};

struct Area
{
    string name;
    int vehicleCount;
};

struct Signal 
{
    string color;
    int greenTime;
};

struct Challan 
{
    int id;
    string vehicleRegNo;
    string owner;
    string violationType;
    int fineAmount;
};
const int MAX_VEHICLES = 20;
const int MAX_CHALLANS = 50;
Vehicle vehicles[MAX_VEHICLES];
int vCount = 0;
Area areas[3] = 
{
    {"F-6 Markaz", 0},
    {"Blue Area", 0},
    {"Zero Point", 0}
};
Signal signals[3];
Challan challans[MAX_CHALLANS];
int cCount = 0;
void menu();
void registerVehicle();
void showVehicles();
void trafficStatus();
void smartSignalControl();
void emergencyDetection();
void showSignalStatus();
void generateChallan();
void checkChallans();
string generateRegNo();
int main() 
{
    srand(time(0));
    int choice;
    do {
        menu();
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1: registerVehicle(); break;
        case 2: showVehicles(); break;
        case 3: trafficStatus(); break;
        case 4: smartSignalControl(); break;
        case 5: emergencyDetection(); break;
        case 6: showSignalStatus(); break;
        case 7: generateChallan(); break;
        case 8: checkChallans(); break;
        case 0: cout << "Exiting system...\n"; break;
        default: cout << "Invalid choice!\n";
        }
        if (choice != 0) 
        {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 0);
    return 0;
}
void menu()
{
    cout << "\n===== SMART TRAFFIC MANAGEMENT SYSTEM =====\n";
    cout << "1. Register Vehicle (Auto Registration No)\n";
    cout << "2. Show Registered Vehicles\n";
    cout << "3. Check Traffic Status\n";
    cout << "4. Smart Signal Control\n";
    cout << "5. Emergency Vehicle Detection\n";
    cout << "6. Show Current Signal Status\n";
    cout << "7. Generate E-Challan\n";
    cout << "8. Check Your Challans\n";
    cout << "0. Exit\n";
}
string generateRegNo()
{
    return "ISB-" + to_string(1000 + vCount);
}
void registerVehicle() {
    if (vCount >= MAX_VEHICLES)
    {
        cout << "Vehicle limit reached!\n";
        return;
    }
    vehicles[vCount].regNo = generateRegNo();
    cout << "Owner Name: ";
    cin.ignore();
    getline(cin, vehicles[vCount].owner);
    cout << "Vehicle Type (Car/Bike): ";
    cin >> vehicles[vCount].type;
    cout << "Vehicle Registered Successfully!\n";
    cout << "Generated Registration Number: "
        << vehicles[vCount].regNo << endl;
    vCount++;
}
void showVehicles() 
{
    if (vCount == 0) 
    {
        cout << "No vehicles registered.\n";
        return;
    }
    cout << "\nRegistered Vehicles:\n";
    for (int i = 0; i < vCount; i++)
    {
        cout << vehicles[i].regNo << " | "
            << vehicles[i].owner << " | "
            << vehicles[i].type << endl;
    }
}
void trafficStatus()
{
    cout << "\nLive Traffic Status:\n";

    for (int i = 0; i < 3; i++) 
    
    {
        areas[i].vehicleCount = rand() % 30 + 5;
        cout << areas[i].name << " : "
            << areas[i].vehicleCount << " vehicles\n";
    }
}
void smartSignalControl() {
    cout << "\nSmart Signal Control:\n";

    for (int i = 0; i < 3; i++)
    {
        if (signals[i].color == "Green" && signals[i].greenTime == 60)
            continue;
        if (areas[i].vehicleCount > 20)
        {
            signals[i].color = "Green";
            signals[i].greenTime = 45;
        }
        else 
        {
            signals[i].color = "Green";
            signals[i].greenTime = 30;
        }
        cout << areas[i].name << " | "
            << signals[i].color
            << " | Green Time: "
            << signals[i].greenTime << "s\n";
    }
}
void emergencyDetection() 
{
    string emergencyTypes[3] = { "Ambulance", "Fire Brigade", "Police" };
    int areaIndex = rand() % 3;
    int typeIndex = rand() % 3;
    cout << "\n?? EMERGENCY VEHICLE DETECTED!\n";
    cout << "Type: " << emergencyTypes[typeIndex] << endl;
    cout << "Location: " << areas[areaIndex].name << endl;
    for (int i = 0; i < 3; i++)
    {
        signals[i].color = "Red";
        signals[i].greenTime = 0;
    }
    signals[areaIndex].color = "Green";
    signals[areaIndex].greenTime = 60;

    cout << "Action Taken: Signal at "
        << areas[areaIndex].name
        << " turned GREEN for emergency clearance.\n";
}
void showSignalStatus()
{
    cout << "\nCurrent Signal Status:\n";
    cout << left << setw(20) << "Area"
        << setw(10) << "Color"
        << setw(12) << "Green Time"
        << setw(15) << "Vehicles" << endl;
    cout << string(57, '-') << endl;
    for (int i = 0; i < 3; i++) 
    {
        cout << left << setw(20) << areas[i].name
            << setw(10) << signals[i].color
            << setw(12) << signals[i].greenTime
            << setw(15) << areas[i].vehicleCount << endl;
    }
}
void generateChallan() 
{
    if (cCount >= MAX_CHALLANS)
    {
        cout << "Maximum challans reached!\n";
        return;
    }
    string reg;
    cout << "Enter Vehicle Registration Number: ";
    cin >> reg;
    bool found = false;
    string ownerName;
    for (int i = 0; i < vCount; i++) 
    {
        if (vehicles[i].regNo == reg) 
        {
            found = true;
            ownerName = vehicles[i].owner;
            break;
        }
    }
    if (!found) 
    {
        cout << "Vehicle not found!\n";
        return;
    }
    cout << "Select Violation Type:\n";
    cout << "1. Signal Break (1000)\n2. Overspeed (1500)\n3. Parking (800)\n4. No Helmet (500)\n";
    int v;
    cin >> v;
    string type;
    int fine;
    switch (v) 
    {
    case 1: type = "Signal Break"; fine = 1000; break;
    case 2: type = "Overspeed"; fine = 1500; break;
    case 3: type = "Parking"; fine = 800; break;
    case 4: type = "No Helmet"; fine = 500; break;
    default: type = "Signal Break"; fine = 1000;
    }
    challans[cCount].id = cCount + 1;
    challans[cCount].vehicleRegNo = reg;
    challans[cCount].owner = ownerName;
    challans[cCount].violationType = type;
    challans[cCount].fineAmount = fine;
    cout << "Challan Generated! ID: " << challans[cCount].id
        << " | Type: " << type << " | Fine: " << fine << endl;
    cCount++;
}
void checkChallans() 
{
    string owner;
    cout << "Enter your Name: ";
    cin.ignore();
    getline(cin, owner);
    bool found = false;
    cout << "\nChallans for " << owner << ":\n";
    for (int i = 0; i < cCount; i++)
    {
        if (challans[i].owner == owner) 
        {
            found = true;
            cout << "ID: " << challans[i].id
                << " | Vehicle: " << challans[i].vehicleRegNo
                << " | Violation: " << challans[i].violationType
                << " | Fine: " << challans[i].fineAmount << endl;
        }
    }
    if (!found) 
    {
        cout << "No challans found for " << owner << ".\n";
    }
}
