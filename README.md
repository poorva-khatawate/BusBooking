# Bus Booking System - Command-Line Interface (CLI) Project

## Introduction

The Bus Booking System is a command-line interface (CLI) application designed to streamline the process of booking bus tickets. Developed with a focus on simplicity and efficiency, this project automates key operations such as reservation management, ticket cancellation, and bus schedule tracking. The system is implemented using Object-Oriented Programming (OOP) principles, ensuring a modular and scalable codebase that is easy to maintain and extend.

## Key Components

1. **Bus Class**  
   Represents individual buses with attributes like bus number, bus route, total seats, and available seats. This class encapsulates all data and methods related to a specific bus.

2. **Ticket Class**  
   Manages ticket details, including passenger name, bus number, seat number, and booking status. This class handles the core functionality of ticket booking and cancellation.

3. **BookingManager Class**  
   Coordinates the booking process by interacting with the Bus and Ticket classes. It handles the allocation of seats, reservation status, and ensures that the system operates smoothly.

4. **User Interface**  
   A command-line interface that allows users to interact with the system, making reservations, canceling tickets, and viewing available buses and schedules.

5. **Exception Handling**  
   Ensures robust operation by managing potential errors such as invalid input, overbooking, and cancellation of non-existent reservations. The system gracefully handles exceptions, providing clear feedback to the user and maintaining system stability.

## System Flow

1. **User Input:**  
   The user interacts with the CLI to perform various actions, such as viewing available buses, booking tickets, or canceling reservations.

2. **Bus and Ticket Management:**  
   The system checks the availability of buses and seats based on user input. If seats are available, it proceeds with booking; otherwise, it informs the user about the unavailability.

3. **Booking Process:**  
   Upon successful booking, the system assigns a seat and generates a ticket. The details are stored and displayed to the user for confirmation.

4. **Cancellation Process:**  
   The user can cancel a reservation by providing the booking details. The system updates the status and releases the seat for future bookings.

5. **Exception Handling:**  
   The system monitors for any errors, such as invalid bus numbers or booking requests for full buses, and handles them appropriately by prompting the user with relevant messages.

## How This Project Helps

- **Resource-Friendly:**  
   Operates in a command-line environment, making it suitable for systems with limited resources or users who prefer text-based interfaces.

- **Scalability:**  
   The OOP-based structure allows for easy extension and modification, ensuring that the system can grow with future requirements.

- **Reliability:**  
   With built-in exception handling, the system ensures smooth and reliable operation even in cases of unexpected input or errors.

## Getting Started

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/poorva-khatawate/BusBooking.git

2. **Navigate to Project Directory.**
   ```bash
   cd BusBooking
