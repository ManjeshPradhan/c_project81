# ✈️ Airplane Ticket Booking System

Welcome to the **Airplane Ticket Booking System**, a console-based C program that lets you **sign up**, **log in**, **choose flights**, **book seats**, and **make payments** — all with a simple and colorful interface! 🎉

---

## 🚀 Features

- **User Signup & Login:** Secure email and password validation with personal and bank details storage  
- **Flight Selection:** Choose from 10 popular airports across Nepal 🇳🇵  
- **Interactive Seat Layout:** Visual seat map showing available (🟢) and booked (❌) seats  
- **Flexible Seat Booking:** Book up to 10 seats per transaction with easy input format (e.g., `1A 2B`)  
- **Payment Processing:** Use saved bank details or enter new payment info for hassle-free checkout 💳  
- **Automatic Ticket Generation:** Receive a detailed ticket with flight info, seat numbers, date, and time 🎫  
- **Persistent Storage:** User info and seat bookings saved in files for session continuity  
- **User-Friendly Console UI:** Color-coded outputs and typewriter effects for an engaging experience 🎨  

---

## 🛫 Airports Covered

| #  | Airport Name                                   | Location    |
|-----|-----------------------------------------------|-------------|
| 1   | Tribhuvan International Airport (TIA)        | Kathmandu   |
| 2   | Pokhara International Airport (PIA)           | Pokhara     |
| 3   | Gautam Buddha International Airport (GBIA)    | Bhairahawa  |
| 4   | Janakpur Airport (JNA)                         | Janakpur    |
| 5   | Biratnagar Airport (BIR)                       | Biratnagar  |
| 6   | Nepalgunj Airport (KEP)                        | Nepalgunj   |
| 7   | Dhangadhi Airport (DHI)                        | Dhangadhi   |
| 8   | Simara Airport (SIF)                           | Simara      |
| 9   | Bharatpur Airport (BHR)                        | Bharatpur   |
| 10  | Bhadrapur Airport (BDP)                        | Jhapa       |

---

## 🛠️ How to Use

1. **Compile the program:**  
   ```bash
   gcc -o booking_system booking_system.c
Run the executable:

bash
Copy
Edit
./booking_system
Follow the on-screen menu:

Signup: Create your account with email and password

Login: Access your account

Exit: Quit the program

After logging in:

Choose departure and arrival airports

Set your flight time (24-hour format)

View available seats in a clear layout

Book your preferred seats by typing seat numbers (e.g., 1A 2B 3C)

Make payment using saved account or enter new payment details

Get your ticket:

View your detailed ticket with flight info, booking details, and ticket number

📂 Data Storage
database.txt: Stores all user credentials, personal info, and bank details securely in plain text

seats.txt: Tracks seat availability and bookings to maintain the latest seat map

🎨 Code Highlights
Input Validation: Ensures email format and password strength

Console Colors & Effects: Uses ANSI codes for colors and a typewriter effect for enhanced UX

Randomized Ticket Numbers: Unique ticket generation for every booking

Persistent Booking Data: Saves and loads seat status from files

Supports Up to 10 Seats per Booking: Convenient batch booking for groups

💡 Future Improvements
Encrypt stored passwords and sensitive data

Add real database support (e.g., SQLite, MySQL)

Implement GUI or web interface for easier access

Expand payment methods with integration to popular platforms

Add flight schedules and dynamic seat availability

📜 License
This project is created for educational purposes and is open to enhancements and learning.
