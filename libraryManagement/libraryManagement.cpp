#include <bits/stdc++.h>
using namespace std;

class Book {
private:
    string title, author;
    bool availabilityStatus;
    queue<string> last10Order;

public:
    Book(string title, string author, bool availabilityStatus) 
        : title(title), author(author), availabilityStatus(availabilityStatus) {}

    void setAvailabilityStatus(bool status) {
        availabilityStatus = status;
    }

    bool getAvailabilityStatus() {
        return availabilityStatus;
    }

    string getTitle() {
        return title;
    }

    string getAuthorName() {
        return author;
    }

    void addMemberToQueue(string memberName) {
        if (last10Order.size() >= 10) last10Order.pop();
        last10Order.push(memberName);
    }

    queue<string> getLast10Order() {
        return last10Order;
    }
    
     bool operator<(const Book& other) const {
        return tie(title, author) < tie(other.title, other.author);
    }

    bool operator==(const Book& other) const {
        return tie(title, author) == tie(other.title, other.author);
    }
    

};

class Member {
private:
    int id;
    map<Book, bool> borrowedBooks;
    string memberName;
    queue<Book> last10Order;

public:
    Member(int id, string memberName) : id(id), memberName(memberName) {}

    void addBookToQueue(Book& book) {
        if (last10Order.size() >= 10) last10Order.pop();
        last10Order.push(book);
    }

    queue<Book> getLast10Order() {
        return last10Order;
    }

    string getMemberName() {
        return memberName;
    }

    void borrowBook(Book& book) {
        if(book.getAvailabilityStatus() ==  false){
          cout<<"book is not available\n";
        }
        if (borrowedBooks.find(book) != borrowedBooks.end()) {
            cout << "Book already borrowed by the user\n";
            return;
        }
        borrowedBooks[book] = true;
        book.setAvailabilityStatus(false);
    }

    void unBorrowBook(Book& book) {
        if (borrowedBooks.find(book) == borrowedBooks.end()) {
            cout << "Book not borrowed\n";
            return;
        }
        borrowedBooks.erase(book);
        book.setAvailabilityStatus(true);
    }

    int getBorrowedBookCount() {
        return borrowedBooks.size();
    }
};

class Library {
private:
    vector<Book> libraryBooks;
    vector<Member> libraryMembers;

public:
    void addBookInLibrary(Book& book) {
        libraryBooks.push_back(book);
    }

    vector<Book> getLibraryBooks() {
        return libraryBooks;
    }

    void addMemberInLibrary(Member& member) {
        libraryMembers.push_back(member);
    }

    vector<Member> getLibraryMembers() {
        return libraryMembers;
    }

    void borrowBook(Book& book, Member& member) {
        member.borrowBook(book);
        member.addBookToQueue(book);
    }

    void unBorrowBook(Book& book, Member& member) {
        member.unBorrowBook(book);
    }

    queue<Book> getMemberBookHistory(Member& member) {
        return member.getLast10Order();
    }
};

int main(){
  Book b1("hdsjhfjsd book", "John Doe", true);
  Member M1(1, "sdfsdfd");
  
  Member M2(2, "fsdfsdfds");
  
  Library library;
  library.addBookInLibrary(b1);
  library.addMemberInLibrary(M1);
  
  library.borrowBook(b1, M1);
  cout << "Borrowed book count: " << M1.getBorrowedBookCount() << "\n";

  library.unBorrowBook(b1, M1);
  cout << "Borrowed book count: " << M1.getBorrowedBookCount() << "\n";
  
}


