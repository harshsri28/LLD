#include <bits/stdc++.h>
using namespace std;

class Movie {
private:
     string title;
     string genre;
    int duration; // in minutes

public:
    Movie(const  string& title, const  string& genre, int duration)
        : title(title), genre(genre), duration(duration) {}

     string getTitle() const {
        return title;
    }

     string getGenre() const {
        return genre;
    }

    int getDuration() const {
        return duration;
    }
};

class CinemaHall {
private:
    int capacity;
    int availableSeats;

public:
    CinemaHall(int capacity) : capacity(capacity), availableSeats(capacity) {}

    int getAvailableSeats() const {
        return availableSeats;
    }

    bool bookSeats(int numSeats) {
        if (numSeats <= availableSeats) {
            availableSeats -= numSeats;
            return true;
        }
        return false;
    }
};

class Show {
private:
    Movie movie;
    CinemaHall hall;
     string showTime;

public:
    Show(const Movie& movie, const CinemaHall& hall, const  string& showTime)
        : movie(movie), hall(hall), showTime(showTime) {}

    Movie getMovie() const {
        return movie;
    }

    CinemaHall getCinemaHall() const {
        return hall;
    }

     string getShowTime() const {
        return showTime;
    }
};

class Ticket {
private:
    Show show;
    int seatNumber;

public:
    Ticket(const Show& show, int seatNumber) : show(show), seatNumber(seatNumber) {}

    Show getShow() const {
        return show;
    }

    int getSeatNumber() const {
        return seatNumber;
    }
};

class Customer {
private:
     string name;
     string email;

public:
    Customer(const  string& name, const  string& email)
        : name(name), email(email) {}

     string getName() const {
        return name;
    }

     string getEmail() const {
        return email;
    }
};

class Booking {
private:
    Customer customer;
    Show show;
    Ticket ticket;

public:
    Booking(const Customer& customer, const Show& show, int seatNumber)
        : customer(customer), show(show), ticket(show, seatNumber) {}

    Customer getCustomer() const {
        return customer;
    }

    Show getShow() const {
        return show;
    }

    Ticket getTicket() const {
        return ticket;
    }
};

class Payment {
private:
    double amount;
     string paymentMethod;

public:
    Payment(double amount, const  string& paymentMethod)
        : amount(amount), paymentMethod(paymentMethod) {}

    double getAmount() const {
        return amount;
    }

     string getPaymentMethod() const {
        return paymentMethod;
    }
};

class BookingSystem {
private:
     vector<Movie> movies;
     vector<CinemaHall> cinemaHalls;
     vector<Show> shows;
     vector<Booking> bookings;

public:
    void addMovie(const Movie& movie) {
        movies.push_back(movie);
    }

    void addCinemaHall(const CinemaHall& hall) {
        cinemaHalls.push_back(hall);
    }

    void addShow(const Show& show) {
        shows.push_back(show);
    }

    Booking bookTicket(const Customer& customer, const Show& show, int numSeats) {
        int hallIndex = 0; // For simplicity, assuming one hall for a show
        CinemaHall& hall = cinemaHalls[hallIndex];

        if (hall.bookSeats(numSeats)) {
            Booking booking(customer, show, hall.getAvailableSeats() + 1 - numSeats);
            bookings.push_back(booking);
            return booking;
        } else {
             cout << "Seats not available." <<  endl;
            return Booking(Customer("", ""), Show(Movie("", "", 0), CinemaHall(0), ""), -1);
        }
    }

    void displayShows() {
        for (const auto& show : shows) {
             cout << "Movie: " << show.getMovie().getTitle() << ", Genre: " << show.getMovie().getGenre()
                      << ", Duration: " << show.getMovie().getDuration() << " mins"
                      << ", Hall: " << show.getCinemaHall().getAvailableSeats() << " seats available"
                      << ", Show Time: " << show.getShowTime() <<  endl;
        }
    }
};

int main() {
    BookingSystem bookingSystem;

    Movie movie1("Inception", "Sci-Fi", 148);
    Movie movie2("The Dark Knight", "Action", 152);
    CinemaHall hall1(100);
     CinemaHall hall2(80);

    // Add movies and cinema halls to the booking system
    bookingSystem.addMovie(movie1);
    bookingSystem.addMovie(movie2);
    bookingSystem.addCinemaHall(hall1);
    bookingSystem.addCinemaHall(hall2);

    // Create shows for the movies in the halls
    Show show1(movie1, hall1, "2023-10-15 18:00");
    Show show2(movie2, hall2, "2023-10-15 20:00");

    // Add shows to the booking system
    bookingSystem.addShow(show1);
    bookingSystem.addShow(show2);

    // Display available shows
     cout << "Available Shows:" <<  endl;
    bookingSystem.displayShows();

    // Simulate a booking
    Customer customer("John Doe", "john@example.com");
    int numSeatsToBook = 2;
     cout << "\nBooking " << numSeatsToBook << " seats for " << customer.getName() <<  endl;
    Booking booking = bookingSystem.bookTicket(customer, show1, numSeatsToBook);

    if (booking.getTicket().getSeatNumber() != -1) {
         cout << "Booking successful!" <<  endl;
         cout << "Movie: " << booking.getShow().getMovie().getTitle() <<  endl;
         cout << "Show Time: " << booking.getShow().getShowTime() <<  endl;
         cout << "Seat Number: " << booking.getTicket().getSeatNumber() <<  endl;
    }

    return 0;
}
