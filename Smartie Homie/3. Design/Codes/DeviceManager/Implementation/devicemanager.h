#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#define idle 0
#define active 1
#define controlDevice 2
#define management 3

#define off 0
#define on 1

using namespace std;

void ClearScreen()
{
    cout << string(100, '\n');
}

class user
{
    std::string userName;
    char gender;
    int dayOfBirth, monthOfBirth, yearOfBirth, userAge, userUID;

public:
    int currentDate, currentMonth, currentYear;

    void getUserName()
    {
        std::cout << "What would you like me to call you?: ";
        usleep(500);
        getline(std::cin, userName);
        std::cout << "Hey, " << userName << "! Nice to meet you!" << std::endl;
    }

    void getGender()
    {
        std::cout << "What is your gender? (M/F): ";
        usleep(500);
        std::cin >> gender;
        cin.ignore();
        while (gender != 'M' && gender != 'F')
        {
            std::cout << "Sorry, invalid input. Please try again (M/F): ";
            std::cin >> gender;
            cin.ignore();
        }
    }

    void getCurrentDate()
    {
        time_t t = time(NULL);
        tm *timePtr = localtime(&t);
        currentDate = timePtr->tm_mon + 1;
        currentMonth = timePtr->tm_mday;
        currentYear = timePtr->tm_year + 1900;
    }

    void getUserDoB()
    {
        int response = 0;
        std::string confirmation;
        std::cout << "Lastly, what is your date of birth? (dd mm yyyy + strictly only integers): ";
        std::cin >> dayOfBirth >> monthOfBirth >> yearOfBirth;
        cin.ignore();

        while (!response)
        {
            if (dayOfBirth <= 0 || dayOfBirth > 31 || monthOfBirth <= 0 || monthOfBirth > 12) // If unusual date
            {
                std::cout << "Invalid date, please try again (dd mm yyyy): ";
                std::cin >> dayOfBirth >> monthOfBirth >> yearOfBirth;
                cin.ignore();
            }

            else if (monthOfBirth == 2 && dayOfBirth > 29) //If Feb and date is greater than 29
            {
                std::cout << "There are only 29 days in Feb, try again (dd mm yyyy): ";
                std::cin >> dayOfBirth >> monthOfBirth >> yearOfBirth;
                cin.ignore();
            }

            else if (monthOfBirth < 8 && monthOfBirth % 2 == 0 && dayOfBirth > 30) //If before August and date is greater than 30 on even month
            {
                std::cout << "Invalid date, please try again (dd mm yyyy): ";
                std::cin >> dayOfBirth >> monthOfBirth >> yearOfBirth;
                cin.ignore();
            }

            else if (monthOfBirth > 8 && monthOfBirth % 2 == 1 && dayOfBirth > 30) //If after August and date is greater than 30 on even odd
            {
                std::cout << "Invalid date, please try again (dd mm yyyy): ";
                std::cin >> dayOfBirth >> monthOfBirth >> yearOfBirth;
                cin.ignore();
            }

            else if (yearOfBirth < 1920) //If year of birth is 1920
            {
                std::cout << "A bit too old for this device, Old timer. Try again (minimum 1920) (dd mm yyyy): ";
                std::cin >> dayOfBirth >> monthOfBirth >> yearOfBirth;
                cin.ignore();
            }

            else if (yearOfBirth > currentYear) //If age is less than 10 years old
            {
                std::cout << "Yeah, no, please enter a valid date (dd mm yyyy): ";
                std::cin >> dayOfBirth >> monthOfBirth >> yearOfBirth;
                cin.ignore();
            }

            else if (yearOfBirth > currentYear - 10) //If age is less than 10 years old
            {
                std::cout << "I think you are too young for this, kid. Try again (minimum 10 years old) (dd mm yyyy): ";
                std::cin >> dayOfBirth >> monthOfBirth >> yearOfBirth;
                cin.ignore();
            }

            else
            {
                std::cout << "Is your birthday on " << dayOfBirth << "." << monthOfBirth << "." << yearOfBirth << "? (y for yes, everything else is no): ";
                getline(cin, confirmation);
                if (confirmation == "y")
                {
                    std::cout << "Thank you!" << std::endl;
                    break;
                }
                else
                {
                    std::cout << "Please try again, enter your date of birth (dd mm yyyy): ";
                    std::cin >> dayOfBirth >> monthOfBirth >> yearOfBirth;
                    cin.ignore();
                    continue;
                }
            }
        }
    }

    void convertDoB2Age()
    {
        userAge = currentYear - yearOfBirth;
        if (currentMonth > monthOfBirth)
            userAge = userAge - 1;
        else if (currentDate > dayOfBirth && currentMonth == monthOfBirth)
            userAge = userAge - 1;
    }

    void assignUserID()
    {
        userUID = 1560000 + rand() % 1500;
        std::cout << "Your unique identifier is: " << userUID << std::endl;
    }

    std::string returnUserName()
    {
        return userName;
    }

    user()
    {
        std::cout << "Creating your account!" << std::endl;
        //constructor
    }
};

class device
{
    int deviceUID, status = off;
    std::string deviceName;

public:
    void getDeviceName()
    {
        std::cout << "What would you like me to call this device?: ";
        std::cin >> deviceName;
        cin.ignore();
    }

    void assignDeviceID()
    {
        deviceUID = 1540000 + rand() % 1500;
        std::cout << deviceName << "'s unique identifier is: " << deviceUID << std::endl;
    }

    void deviceSwitch()
    {
        status = !status;
    }

    device()
    {
        std::cout << "Creating a new device!" << std::endl;
        //constructor
    }

    std::string returnDeviceName()
    {
        return deviceName;
    }

    int returnDeviceStatus()
    {
        return status;
    }
};

void addNewUser(std::vector<user> &userList, int &userCount)
{
    userList.push_back(user());
    usleep(2000);
    ClearScreen();
    userCount = userList.size();
    int i = userList.size() - 1;
    userList[i].getUserName();
    userList[i].getGender();
    userList[i].getCurrentDate();
    userList[i].getUserDoB();
    userList[i].convertDoB2Age();
    userList[i].assignUserID();
    usleep(1000);
    std::cout << "Account created successfully!" << std::endl;
    usleep(2000);
    ClearScreen();
}

void addNewDevice(std::vector<device> &deviceList, int &deviceCount)
{
    deviceList.push_back(device());
    usleep(2000);
    ClearScreen();
    deviceCount = deviceList.size();
    int i = deviceList.size() - 1;
    deviceList[i].getDeviceName();
    deviceList[i].assignDeviceID();
    usleep(1000);
    std::cout << "Device added successfully!" << std::endl;
    usleep(2000);
    ClearScreen();
}

void welcomeScreen(int &initialSetup, std::vector<user> &userList, int &userCount)
{
    if (!initialSetup)
    {
        ClearScreen();
        std::cout << "________________________________________________" << std::endl;
        std::cout << "           Welcome to Stella system             " << std::endl;
        std::cout << "________________________________________________\n\n";
        usleep(2000);
        std::cout << "Looks like it is your first time here. Let's start with setting you up." << std::endl;
        usleep(2000);
        ClearScreen();
        addNewUser(userList, userCount);
        initialSetup = 1;
        ClearScreen();
    }
    else
    {
        ClearScreen();
        std::cout << "________________________________________________" << std::endl;
        std::cout << "         Welcome back to Stella system          " << std::endl;
        std::cout << "________________________________________________\n\n";
        usleep(4000);
        ClearScreen();
    }
}

void waitForActivation(std::string &activation, int &state, int &devicePower)
{
    ClearScreen();
    cout << "****************************************************************" << endl;
    cout << "Idle mode - Activate using 'Wake up, Stella' or turn off using 'Power Off': ";
    getline(cin, activation);
    if (activation == "Wake up, Stella")
    {
        cout << "I am up!" << endl;
        usleep(2000);
        ClearScreen();
        state = active;
    }
    if (activation == "Power Off")
    {
        cout << "Good night!" << endl;
        usleep(2000);
        ClearScreen();
        devicePower = off;
    }
    else
    {
        ClearScreen();
    }
}

void loginUser(int &loginStatus, std::vector<user> userList, int &loggedInUser, int &state, int &devicePower, std::string &loggedInUserName)
{
    if (!loginStatus)
    {
        cout << "****************************************************************" << endl;
        cout << "Greetings, user! Please specify your name.\nYou can also return to idle using 'Idle' or turn off the device using 'Power Off': ";
        std::string response;
        getline(cin, response);
        for (int i = 0; i < userList.size(); i++)
        {
            if (response == "Power Off")
            {
                cout << "Good night!" << endl;
                usleep(2000);
                ClearScreen();
                devicePower = off;
                break;
            }
            else if (response == "Idle")
            {
                state = idle;
                cout << "I'll just take a nap then." << endl;
                usleep(2000);
                ClearScreen();
                break;
            }
            else if (response == userList[i].returnUserName())
            {
                loggedInUserName = userList[i].returnUserName();
                loggedInUser = i;
                loginStatus = 1;
                cout << "Logged in successfully!" << endl;
                usleep(2000);
                ClearScreen();
                break;
            }
            else if (i == userList.size() - 1)
            {
                cout << "No user found with such name. Please try again." << endl;
                usleep(2000);
                ClearScreen();
                break;
            }
        }
    }
}

void chooseCommand(int &loginStatus, int &state, std::string loggedInUserName, int &devicePower)
{
    if (loginStatus)
    {
        std::string response;
        cout << "****************************************************************" << endl;
        cout << "Home\n\n";
        cout << "So " << loggedInUserName << ", how may I help you?" << endl;
        cout << "     1. Control devices" << endl;
        cout << "     2. Settings and management" << endl;
        cout << "     3. Return to idle" << endl;
        cout << "     4. Turn off device" << endl;
        cout << "     5. Logout\n\n";
        cout << "Please choose from the list above: ";
        getline(cin, response);
        usleep(100);
        if (response == "1")
        {
            state = controlDevice;
            ClearScreen();
        }
        else if (response == "2")
        {
            state = management;
            ClearScreen();
        }
        else if (response == "3")
        {
            state = idle;
            cout << "Then I'll head back to my nap. Call me when you need." << endl;
            usleep(3000);
        }
        else if (response == "4")
        {
            devicePower = off;
            cout << "Good night!" << endl;
            usleep(2000);
        }
        else if (response == "5")
        {
            loginStatus = 0;
            cout << "See you, " << loggedInUserName << ". Come back whenever you need me." << endl;
            loginStatus = 0;
            usleep(3000);
            ClearScreen();
        }
        else
        {
            cout << "Inserting obligatory 'Ha Ha Ha!', please choose from list." << endl;
            usleep(3000);
            ClearScreen();
        }
    }
}

void chooseDevice(std::vector<device> deviceList, int deviceCount, int &chosenDevice, int &state, int &success)
{
    success = 0;
    cout << "****************************************************************" << endl;
    cout << "Device control\n\n";
    if (deviceCount != 0)
    {
        cout << "Your devices list:" << endl;
        for (int i = 0; i < deviceCount; i++)
        {
            cout << "     " << i << ". " << deviceList[i].returnDeviceName() << endl;
        }
        cout << "     " << deviceCount << ". Return" << endl; //Last option (return) always == device count
        cout << "\nPlease choose from the list above (strictly no letters): ";

        cin >> chosenDevice;
        cin.ignore();

        if (chosenDevice < deviceCount && chosenDevice >= 0)
        {
            success = 1;
        }
        else if (chosenDevice == deviceCount)
        {
            state = active;
            ClearScreen();
        }
        else
        {
            cout << "Invalid input! Try again." << endl;
            usleep(1000);
            chosenDevice = deviceCount + 1;
            ClearScreen();
        }
    }

    else
    {
        cout << "You have added no device. Returning to home." << endl;
        usleep(100);
        state = active;
        usleep(2000);
        ClearScreen();
    }
}

void deviceControl(std::vector<device> &deviceList, int deviceCount, int chosenDevice, int success)
{
    if (success)
    {
        std::string input;
        int stat;
        stat = deviceList[chosenDevice].returnDeviceStatus();
        cout << "The current chosen device is " << deviceList[chosenDevice].returnDeviceName() << "." << endl;
        cout << "Device status: ";
        if (stat)
        {
            cout << "ON" << endl;
            cout << "\nWould you like to turn it off (y for yes or any other key for no): ";
            getline(cin, input);
            if (input == "y")
            {
                deviceList[chosenDevice].deviceSwitch();
                cout << "The device has been turned off" << endl;
            }
            else
            {
                cout << "Ok, it is staying on." << endl;
            }
        }
        else
        {
            cout << "OFF" << endl;
            cout << "\nWould you like to turn it on (y for yes or any other key for no): ";
            getline(cin, input);
            if (input == "y")
            {
                deviceList[chosenDevice].deviceSwitch();
                cout << "The device has been turned on" << endl;
            }
            else
            {
                cout << "Ok, it is off." << endl;
            }
        }
        usleep(2000);
        ClearScreen();
    }
}

void chooseManagementFunction(std::string &mode, int &state)
{
    cout << "****************************************************************" << endl;
    cout << "Settings and management\n\n";
    cout << "     1. Add a new user" << endl;
    cout << "     2. Add a new device" << endl;
    cout << "     3. Return" << endl;
    cout << "\nPlease choose from the list above: ";
    getline(cin, mode);
    usleep(100);
    if (mode == "3")
    {
        state = active;
        ClearScreen();
    }
    if (mode != "1" && mode != "2" && mode != "3")
    {
        cout << "Invalid option." << endl;
        usleep(2000);
        ClearScreen();
    }
}

void managementMode(std::string mode, std::vector<user> &userList, int &userCount, std::vector<device> &deviceList, int &deviceCount)
{
    ClearScreen();
    if (mode == "1")
        addNewUser(userList, userCount);
    if (mode == "2")
        addNewDevice(deviceList, deviceCount);
}

#endif
