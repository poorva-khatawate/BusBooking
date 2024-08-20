#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <unordered_map>
using namespace std;
// Forward declarations
class Passenger;
class schedule;
class Seat;
class Bus;
class ticket;
class payment;
class UPIPayment;
class CardPayment;
class busSystem;

// User class for registration and login
class User {
private:
    string username;
    string password;

public:
    User(string u, string p) : username(u), password(p) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
};


class UserSystem {
private:
    unordered_map<string, User*> users;
    User* loggedInUser;

    UserSystem() : loggedInUser(nullptr) {}

public:
    static UserSystem& getInstance() {
        static UserSystem instance;
        return instance;
    }

    void registerUser(const string& username, const string& password) {
        if (users.find(username) != users.end()) {
            throw runtime_error("User already exists.");
        }
        users[username] = new User(username, password);
        cout << "User registered successfully.\n";
    }

    bool loginUser(const string& username, const string& password) {
        if (users.find(username) != users.end() && users[username]->getPassword() == password) {
            loggedInUser = users[username];
            cout << "Login successful.\n";
            return true;
        }
        cout << "Invalid username or password.\n";
        return false;
    }

    User* getLoggedInUser() const {
        return loggedInUser;
    }

    void logoutUser() {
        loggedInUser = nullptr;
        cout << "Logged out successfully.\n";
    }
};

class schedule
{
    public: string from;
             string to;
             string timing;
             public:
    schedule(){}
    schedule(string From,string To,string Time)
    {
        from=From;
        to=To;
        timing=Time;
    }
};


class Seat
{
    private: int seatNo;
             bool isbooked;
            Passenger* passenger; // A pointer to the passenger who booked this seat

    public:
            Seat() : seatNo(0), isbooked(false), passenger(nullptr) {}
            Seat(int sno) : seatNo(sno), isbooked(false), passenger(nullptr) {}

            bool isSeatBooked() {
                return isbooked;
            }

        void bookSeat(Passenger* p) {
            isbooked = true;
            passenger = p;
        }


    Passenger* getPassenger() {
        return passenger;
    }

    int getSeatNumber() {
        return seatNo;
    }
      void cancelSeatBooking() {
        if (isbooked) {
            isbooked = false;
            passenger = nullptr;
            cout << "Seat booking canceled successfully." << endl;
        } else {
            cout << "Seat is not booked, so cannot cancel." << endl;
        }
    }

};

class Bus
{
    private: int busNo;
             string type;
             int no_of_seats;
             float ticketprice;
             Seat* seats[14]; // Array of seats in the bus
    public: schedule busSchedule;

        public:
        Bus(){}
        Bus(int bno,string Type,int nseats,float price,schedule s):busSchedule(s)
        {
            busNo=bno;
            type=Type;
            no_of_seats=nseats;
            ticketprice=price;
             for (int i = 0; i < 14; ++i) {
            seats[i] = new Seat(i + 1);
             }
        }

        ~Bus() {
        for (int i = 0; i < 20; ++i) {
            delete seats[i];
        }
    }
    int getBusNumber()
     {
         return busNo;
      }
    string getFrom()
     {
          return busSchedule.from;
      }
    string getTo()
    {
        return busSchedule.to;
    }
    string getTime()
    {
        return busSchedule.timing;
    }
    float getTicketPrice()
    {
        return ticketprice;
    }
    string getType()
    {
        return type;
    }
    Seat* getSeat(int seatNumber) {
        if (seatNumber >= 1 && seatNumber <= 14) {
            return seats[seatNumber - 1];
        }
        return nullptr;
    }


    int getAvailableSeats() {
        int count = 0;
        for (int i = 0; i < 14; i++) {
            if (!seats[i]->isSeatBooked()) {
                ++count;
            }
        }
        return count;
    }

    void viewPassengerList() {
        cout << "Passenger List for Bus " << busNo << ":\n";
        for (int i = 0; i < 14; i++) {
            Seat* seat = seats[i];
            if (seat->isSeatBooked())
                {
                cout << "Seat Number: " << seat->getSeatNumber() << ", Booked by Passenger\n";
            }
        }
        cout << endl;
    }
};



class Passenger
{
    private: string name;
             string phoneno;
             string gender;
             int age;
             int ticketNumber;
    public:
        Passenger(){}
        Passenger(string n,string ph,string g,int Age)
        {
            name=n;
            phoneno=ph;
            gender=g;
            age=Age;
        }
        void setTicketNumber(int ticketNo) {
        ticketNumber = ticketNo;
         }

        int getTicketNumber()
        {
            return ticketNumber;
        }
        string getName()  { return name; }
        string getGender() { return gender; }
        string getContact(){return phoneno; }
        int getAge() {return age;}

   void bookSeat(Bus* bus, Seat* seat) {
    seat->bookSeat(this); // Passing the current passenger object
    cout << "Seat booked successfully for Passenger: " << name << endl;
    }


};

class ticket
{
    private: int ticketNo;
             Bus* bus;
             Seat* seat;
    public:
        ticket(){}
        ticket(int ticketNO, Bus* Bus, Seat* Seat)
        : ticketNo(ticketNO), bus(Bus), seat(Seat) {}

    int getTicketNumber()
     {
         return ticketNo;
     }
    Bus* getBus()
     {
        return bus;
     }
    Seat* getSeat()
     {
         return seat;
     }

};

class payment{
    public:
        payment(){}
    virtual void processPayment(double amount) = 0;
    virtual ~payment() {}
};

class UPIPayment : public payment {
    private: string UPId;
    public: UPIPayment()
    {
        UPId="";
    }

    void processPayment(double amount) {
        cout<<"Enter UPI ID\n";
        cin>>UPId;
        cout << "Processing UPI Id "<<UPId<<" with payment of Rs." << amount << endl;
    }
};

class CardPayment : public payment {
    private: int cardNo;
    public:
        CardPayment()
        {
            cardNo=0;
        }

    void processPayment(double amount) {
        cout<<"Enter Card Number"<<endl;
        cin>>cardNo;
        cout << "Processing Card payment of Rs." << amount << endl;

    }
};

 class NoBusesFoundException : public exception
     {
      public:
      const char* what() const throw ()
       {
        return "No buses found for the specified route.";
        }
    };

 class NoTicketFoundException : public exception
     {
      public:
      const char* what() const throw ()
       {
        return "Invalid Ticket Number.\n";
        }
    };


class busSystem
{
    Bus* buses[15];
    int busCount;
    int ticketCounter;

    busSystem() : busCount(0), ticketCounter(1) {}

public:

    static busSystem& getInstance() {
        static busSystem instance;
        return instance;
    }

    void addBus(Bus* bus) {
        if (busCount < 15) {
            buses[busCount++] = bus;
        }
    }

    Bus* getBus(int busNumber) {
        if (busNumber < 1 || busNumber > busCount) {
            return nullptr;
        }
        return buses[busNumber - 1];
    }

    int findBusNumber(int busNumber) {
        for (int i = 0; i < busCount; ++i) {
            if (buses[i]->getBusNumber() == busNumber) {
                return i;
            }
        }
        return -1; // Bus number not found
    }

//displaying the bus details and availabilty
void viewBusDetails()
    {
        cout << "===============================================================" << endl;
        cout << "Bus Details and Availability" << endl;
        cout << "===========================" << endl;
        cout << left << setw(10) << "Bus No" << setw(15) << "From" << setw(15) << "To" << setw(11) << "Available Seats" <<setw(30)<<" Timing "<< endl;
        cout << "-----------------------------------------------------------" << endl;

        for (int i = 0; i < busCount; ++i) {
            Bus* bus = buses[i];
            cout << left << setw(10) << bus->getBusNumber() << setw(15) << bus->getFrom() << setw(15) << bus->getTo() << setw(15) << bus->getAvailableSeats()
            <<setw(30)<<bus->getTime() << endl;
        }
        cout << "================================================================" << endl;
     }


//finding the busues for the given route
    bool findBusesByRoute(const string& from, const string& to)
     {
        if (busCount == 0) {
        cout << "No buses available in the system." << endl;
        throw runtime_error("No buses available.");
        }
        bool found = false;

        cout << "-------------------------------------------------------------------------------------------------------" << endl;
        cout << "Bus Number | From        | To          | Time       | Available Seats | Type            |      Ticket Price" << endl;
        cout << "-------------------------------------------------------------------------------------------------------" << endl;

        for (int i = 0; i < busCount; ++i) {
            Bus* bus = buses[i];
            if (bus->getFrom() == from && bus->getTo() == to) {
                found = true;
                cout << setw(4) << right << bus->getBusNumber() << setw(9) << " | ";
                cout << setw(12) << left << bus->getFrom() << " | ";
                cout << setw(12) << left << bus->getTo() << " | ";
                cout << setw(10) << left << bus->getTime() << " | ";
                cout << setw(15) << right << bus->getAvailableSeats() << " | ";
                cout << setw(10) << left << bus->getType() << " | ";
                cout << setw(10) << right << bus->getTicketPrice() << endl;
        }
    }
    cout << "---------------------------------------------------------------------------------------" << endl;

    if (!found) {
        throw NoBusesFoundException();
        return false;
    }
    return true;
  }


//displays the seat to be selected as rows
void selectSeat(int busNumber)
 {
    int busIndex = findBusNumber(busNumber);
    if (busIndex == -1)
        {
        throw invalid_argument("Invalid bus number!");
        return;
        }

    Bus* bus = buses[busIndex];
    cout << "Bus Number: " << bus->getBusNumber() << endl;
    cout << "Available Seats: " << bus->getAvailableSeats() << " out of 14" << endl;
    cout << "Seats: ";
    for (int seatNumber = 1; seatNumber <= 14; ++seatNumber) {
        Seat* seat = bus->getSeat(seatNumber);
        char availability = seat->isSeatBooked() ? 'B' : 'N';
        cout << seatNumber << availability << " ";

        if (seatNumber % 2 == 0) {
            cout << endl << "       ";
        }
    }
    cout << endl << endl;
}



//find the seats for the given route
    bool findBusesByRouteWithSeats(const string& from, const string& to)
    {
    bool found = false;
    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << "Bus Number | From        | To          | Time        | Type      | Ticket Price" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < busCount; ++i) {
        Bus* bus = buses[i];
        if (bus->getFrom() == from && bus->getTo() == to) {
            found = true;
            cout << setw(10) << bus->getBusNumber() << " | ";
            cout << setw(12) << bus->getFrom() << " | ";
            cout << setw(12) << bus->getTo() << " | ";
            cout << setw(10) << bus->getTime() << " | ";
            cout << setw(10) << bus->getType() << " | ";
            cout << setw(8) << bus->getTicketPrice() << endl<<endl;

            int availableSeats = 0;
            cout << "Seats: ";
            for (int seatNumber = 1; seatNumber <= 14; ++seatNumber) {
                Seat* seat = bus->getSeat(seatNumber);
                char availability = seat->isSeatBooked() ? 'B' : 'N';
                cout << seatNumber << availability <<setw(3)<< " ";

                // Add a line break for better readability
                if (seatNumber % 7 == 0) {
                    cout << endl << "       ";
                }

                if (!seat->isSeatBooked()) {
                    availableSeats++;
                }
            }
            cout << endl << "Available Seats: " << availableSeats << endl;
            cout << "---------------------------------------------------------------------------------------" << endl<<endl;
        }
    }

    if (!found) {
        throw NoBusesFoundException();
        return false;
    }
    return true;
}

//get ticketnumber from the list
ticket *getTicketByNumber(int ticketNumber)
{
    for (int i = 0; i < busCount; ++i) {
        Bus *bus = buses[i];
        for (int j = 0; j < 14; ++j) {
            Seat *seat = bus->getSeat(j + 1);
            if (seat->isSeatBooked() && seat->getPassenger()->getTicketNumber() == ticketNumber) {
                return new ticket(ticketNumber, bus, seat);
            }
        }
    }
    throw NoTicketFoundException();
}

//print ticket details
void printTicketDetails(int ticketNumber)
 {
        ticket* t = getTicketByNumber(ticketNumber);
        cout << "===========================" << endl;
        cout << "Ticket Number: " << t->getTicketNumber() << endl;
        cout << "Bus Number: " << t->getBus()->getBusNumber() << endl;
        cout << "From: " << t->getBus()->getFrom() << ", To: " << t->getBus()->getTo() << endl;
        cout << "Time: "<<t->getBus()->getTime()<<endl;
        cout << "Seat Number: " << t->getSeat()->getSeatNumber() << endl;
        cout << "Passenger Name: " << t->getSeat()->getPassenger()->getName() << endl;
        cout << "Contact No.: " << t->getSeat()->getPassenger()->getContact() << endl;
        cout << "Age.: " << t->getSeat()->getPassenger()->getAge() << endl;
        cout << "Gender.: " << t->getSeat()->getPassenger()->getGender() << endl;
        cout << "===========================" << endl;

}

//booking a seat
void bookSeatForTicket(int busNumber, int numSeats)
   {
    if (UserSystem::getInstance().getLoggedInUser() == nullptr) {
            cout << "Please log in to book seats.\n";
            return;
        }
        int busIndex = findBusNumber(busNumber);
        if (busIndex == -1) {
           throw invalid_argument("Invalid bus number!");
        }


        Bus* bus = buses[busIndex];
         if (numSeats > bus->getAvailableSeats())
            {
                cout << "Sorry, only " << bus->getAvailableSeats() << " seats are available for this bus." << endl;
            return;
            }
    int arr[14],cnt=-1;
    for (int i = 0; i < numSeats; i++) {
        int seatNumber;
        cout << "Enter Seat Number " << i + 1 << ": ";
        cin >> seatNumber;

        Seat* seat = bus->getSeat(seatNumber);
        if (!seat) {
            cout << "Invalid seat number " << seatNumber << ". Please try again." << endl;
            --i;
            continue;
        }

        if (seat->isSeatBooked()) {
            cout << "Seat " << seatNumber << " is already booked. Please select another seat." << endl;
            --i;
            continue;
        }
        cout<<endl;

        cout << "Enter Passenger"<<i+1<<" Name for Seat " << seatNumber << ": ";
        cin.ignore();
        string name;
        getline(cin, name);
        cout << "Enter Contact Number for Seat " << seatNumber << ": ";
        string contact;
        cin >> contact;
        cout << "Enter Gender for Seat " << seatNumber << ": ";
        string gender;
        cin >> gender;
        cout << "Enter Age for Seat " << seatNumber << ": ";
        int age;
        cin >> age;

        Passenger* passenger = new Passenger(name, contact, gender, age);
        int ticketNumber = ticketCounter++;
        arr[++cnt]=ticketNumber;

        passenger->setTicketNumber(ticketNumber);
        seat->bookSeat(passenger);
        cout << "Seat " << seatNumber << " selected successfully for Passenger: " << name << endl<<endl;
    }
      int paymentChoice;
            do {
                cout << "Select Payment Mode:\n";
                cout << "1. UPI Payment\n";
                cout << "2. Card Payment\n";
                cin >> paymentChoice;
                if (paymentChoice != 1 && paymentChoice != 2)
                    {
                    cout << "Invalid payment option! Please select 1 for UPI Payment or 2 for Card Payment." << endl;
                    }
            } while (paymentChoice != 1 && paymentChoice != 2);

            payment* paymentMode;
            if (paymentChoice == 1) {
                paymentMode = new UPIPayment();
            } else {
                paymentMode = new CardPayment();
            }

            // Process payment
            double ticketPrice = bus->getTicketPrice();
            double price=numSeats*ticketPrice;
            char ch;
            cout<<"Enter * to proceed to pay "<<price<<" amt\n";
            cin>>ch;
            if(ch=='*')
            {
            paymentMode->processPayment(price);
            delete paymentMode; // Free the allocated memory
            cout<<"Payment successful and "<< numSeats<<" Seats booked\n"<<endl;
            cout<<"Ticket Details\n";
            for(int j=0;j<numSeats;j++)
            {
                printTicketDetails(arr[j]);
            }
            }
            else
                throw("Booking unsuccessful.\n");

}

//cancel booking
void cancelBookingByTicketNumber(int ticketNumber)
{
       char cancelChoice;
        for (int i = 0; i < busCount; ++i)
            {
            Bus* bus = buses[i];
            for (int j = 0; j < 14; ++j)
                {
                Seat* seat = bus->getSeat(j + 1);
                Passenger* passenger = seat->getPassenger();
                if (passenger && passenger->getTicketNumber() == ticketNumber) {
                    cout << "Do you want to cancel the booking? (Y/N): ";
                    cin >> cancelChoice;
                    if (cancelChoice == 'Y' || cancelChoice == 'y') {
                        seat->cancelSeatBooking();
                        cout << "Ticket " << ticketNumber << " canceled successfully for Passenger: " << passenger->getName()<<" and 50% refund initiated " << endl;
                    } else {
                        cout << "Booking for Ticket " << ticketNumber << " is not canceled.\n";
                    }
                    return;
                }
            }
        }
        throw invalid_argument("Ticket not found or already canceled.");
}

//view passengers list for the bus
void viewPassengerListByBus(int busNumber) {
    int busIndex = findBusNumber(busNumber);
    if (busIndex == -1) {
        throw invalid_argument("Invalid bus number!");
    }

    Bus* bus = buses[busIndex];
    cout << "Passenger List for Bus " << bus->getBusNumber() << ":\n";
    bool passengerFound = false;

    for (int i = 0; i < 14; i++) {
        Seat* seat = bus->getSeat(i + 1);
        if (seat->isSeatBooked()) {
            Passenger* passenger = seat->getPassenger();
            cout << "Ticket Number: " << passenger->getTicketNumber() << endl;
            cout << "Passenger Name: " << passenger->getName() << endl;
            cout << "Seat Number: " << seat->getSeatNumber() << endl;
            cout << "-----------------------------" << endl;
            passengerFound = true;
        }
    }

    if (!passengerFound) {
        throw runtime_error("No passengers found for the specified bus.");
    }

}

};



void displayMenu() {
    cout << "Choose an option:" << endl;
    cout<<" --------------------------------------------------"<<endl;
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. View all available buses" << endl;
    cout << "4. Find buses by route" << endl;
    cout << "5. Book a seat" << endl;
    cout << "6. Check ticket status" << endl;
    cout << "7. Cancel booking" << endl;
    cout << "8. View bus details and passengers list on board" << endl;
    cout << "9.Logout\n";
    cout << "10. Exit" << endl;
    cout<<" --------------------------------------------------"<<endl<<endl;
}

int main()
{
    busSystem& BusSystem = busSystem::getInstance();
    UserSystem& UserSys = UserSystem::getInstance();
    int busNumber,numseats,ticketNumber;
    string from,to;
    schedule s1("Mumbai","Pune","10:15");
    schedule s2("Mumbai","Bangalore","17:30");
    schedule s3("Mumbai","Bangalore","19:30");
    schedule s4("Mumbai","Pune","19:30");
    schedule s5("Bangalore","Pune","20:10");
    schedule s6("Pune","Bangalore","17:30");
    schedule s7("Pune","Bangalore","21:14");
    schedule s8("Bangalore","Pune","16:30");
    schedule s9("Bangalore","Mumbai","14:50");
    schedule s10("Pune","Delhi","16:30");
    schedule s11("Pune","Jaipur","08:30");
    schedule s12("Hubli","Mumbai","22:30");
    schedule s13("Panjim","Mumbai","12:30");
    schedule s14("Hubli","Bangalore","15:30");
    schedule s15("Bangalore","Mumbai","14:30");

    Bus busesToAdd[] = {
    Bus(5066,"A/C sleeper",14,1800,s1),
    Bus(3755,"A/C seater",14,1600,s2),
    Bus(1001,"A/C sleeper",14,2000,s3),
    Bus(2344,"Non-A/C sleeper",14,1700,s4),
    Bus(6767,"A/C sleeper",14,1800,s5),
    Bus(9090,"A/C seater",14,1400,s6),
    Bus(1991,"A/C semi-sleeper",14,1600,s7),
    Bus(7776,"Non-A/C sleeper",14,1200,s8),
    Bus(3066,"A/C semi-sleeper",14,1400,s9),
    Bus(6960,"Non A/C sleeper",14,1700,s10),
    Bus(5434,"Non A/C sleeper",14,2000,s11),
    Bus(1534,"A/C seater",14,1350,s12),
    Bus(9593,"Non A/C sleeper",14,1280,s13),
    Bus(4113,"Non A/C semi-sleeper",14,1890,s14),
    Bus(8813,"A/C semi-sleeper",14,1780,s15),
    };
    int numBusesToAdd = sizeof(busesToAdd) / sizeof(busesToAdd[0]);

    for (int i = 0; i < numBusesToAdd; ++i) {
        BusSystem.addBus(&busesToAdd[i]);
    }

    cout << "------------------------------------------------------" << endl;
    cout << "                Welcome to Redbus              " << endl;
    cout << "------------------------------------------------------" << endl;
    int choice;

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
         case 1: { // Register
            string username, password;
            cout << "Enter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;
            try {
                UserSys.registerUser(username, password);
            } catch (const runtime_error& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        }

        case 2: { // Login
            string username, password;
            cout << "Enter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;
            UserSys.loginUser(username, password);
            break;
        }
        case 3: // See availability of buses
            BusSystem.viewBusDetails();
            break;

        case 4: try{ // Find buses by route
            cout<<"Enter from city\n";
            cin>>from;
            cout<<"Enter to city\n";
            cin>>to;
            cout<<"Buses available for this route are\n";
            BusSystem.findBusesByRouteWithSeats(from,to);
            }
            catch(const runtime_error& e)
            {
                cout<<"Error: "<<e.what()<<endl;
            }
            catch(const NoBusesFoundException& ex)
            {
                cout<<"Error: "<<ex.what()<<endl;
            }
             break;


        case 5: // Book a seat
               try{
            cout<<"Enter from city\n";
            cin>>from;
            cout<<"Enter to city\n";
            cin>>to;
            cout<<"Buses available for this route are\n";
            if(BusSystem.findBusesByRoute(from,to))
            {
            cout << "Enter Bus Number: ";
            cin >> busNumber;
            BusSystem.selectSeat(busNumber);
            cout<<"Enter the Number of seats you want to book\n";
            cin>>numseats;
            if(numseats<=0)
                throw out_of_range("Invalid Number of seats\n");
            BusSystem.bookSeatForTicket(busNumber,numseats);
            //cout << "Ticket Details:\n";
           // BusSystem.printTicketDetails(t);
            }
            }
            catch(const out_of_range& e)
            {
                cout<<"Error: "<<e.what()<<endl;
            }
            catch(const NoBusesFoundException& ex)
            {
                cout<<"Error: "<<ex.what()<<endl;
            }
            catch(const invalid_argument& e)
            {
                cout<<"Error: "<<e.what()<<endl;
            }
            catch(const char* msg)
            {
                cout<<msg<<endl;
            }
            break;

        case 6: try{ // Check ticket status
            int ticketNumber;
                cout << "Enter Ticket Number: ";
                cin >> ticketNumber;
                BusSystem.printTicketDetails(ticketNumber);
                printf("TICKET CONFIRMED\n");
                }
                catch(const NoTicketFoundException& e)
                {
                    cout<<"Error: "<<e.what()<<endl;
                }
                break;

        case 7: try{
                cout<<"Enter the Ticket number\n";
                cin>>ticketNumber;

                BusSystem.cancelBookingByTicketNumber(ticketNumber);
                }
                catch(const invalid_argument& e)
                {
                    cout<<"Error: "<<e.what()<<endl;
                }
                break;

        case 8: // View bus details along with the list of passengers
                try{
            cout << "Enter Bus Number: ";
            cin >> busNumber;
            BusSystem.viewPassengerListByBus(busNumber);
            }
            catch(const invalid_argument& e)
            {
                cout<<"Error: "<<e.what()<<endl;
            }
            catch(const runtime_error& e)
            {
                cout<<"Error: "<<e.what()<<endl;
            }

            break;
        case 9: { // Logout
            UserSys.logoutUser();
            break;
        }
        case 10: // Exit from the app
            cout << "Exiting the app. Thank you!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 10);

    return 0;
}
