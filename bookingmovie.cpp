#include <iostream>
#include <vector>
#include <string>

class Movie {
private:
    std::string title;
    std::string genre;
    int duration; // in minutes

public:
    Movie(const std::string& title, const std::string& genre, int duration)
        : title(title), genre(genre), duration(duration) {}

    std::string getTitle() const {
        return title;
    }

    std::string getGenre() const {
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
    std::string showTime;

public:
    Show(const Movie& movie, const CinemaHall& hall, const std::string& showTime)
        : movie(movie), hall(hall), showTime(showTime) {}

    Movie getMovie() const {
        return movie;
    }

    CinemaHall getCinemaHall() const {
        return hall;
    }

    std::string getShowTime() const {
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
    std::string name;
    std::string email;

public:
    Customer(const std::string& name, const std::string& email)
        : name(name), email(email) {}

    std::string getName() const {
        return name;
    }

    std::string getEmail() const {
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
    std::string paymentMethod;

public:
    Payment(double amount, const std::string& paymentMethod)
        : amount(amount), paymentMethod(paymentMethod) {}

    double getAmount() const {
        return amount;
    }

    std::string getPaymentMethod() const {
        return paymentMethod;
    }
};

class BookingSystem {
private:
    std::vector<Movie> movies;
    std::vector<CinemaHall> cinemaHalls;
    std::vector<Show> shows;
    std::vector<Booking> bookings;

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
            std::cout << "Seats not available." << std::endl;
            return Booking(Customer("", ""), Show(Movie("", "", 0), CinemaHall(0), ""), -1);
        }
    }

    void displayShows() {
        for (const auto& show : shows) {
            std::cout << "Movie: " << show.getMovie().getTitle() << ", Genre: " << show.getMovie().getGenre()
                      << ", Duration: " << show.getMovie().getDuration() << " mins"
                      << ", Hall: " << show.getCinemaHall().getAvailableSeats() << " seats available"
                      << ", Show Time: " << show.getShowTime() << std::endl;
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
    std::cout << "Available Shows:" << std::endl;
    bookingSystem.displayShows();

    // Simulate a booking
    Customer customer("John Doe", "john@example.com");
    int numSeatsToBook = 2;
    std::cout << "\nBooking " << numSeatsToBook << " seats for " << customer.getName() << std::endl;
    Booking booking = bookingSystem.bookTicket(customer, show1, numSeatsToBook);

    if (booking.getTicket().getSeatNumber() != -1) {
        std::cout << "Booking successful!" << std::endl;
        std::cout << "Movie: " << booking.getShow().getMovie().getTitle() << std::endl;
        std::cout << "Show Time: " << booking.getShow().getShowTime() << std::endl;
        std::cout << "Seat Number: " << booking.getTicket().getSeatNumber() << std::endl;
    }

    return 0;
}
