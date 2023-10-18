#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class Book {
protected:
    string title;
    string author;
    string publisher;
    int year;
    bool reserved = false;
    time_t reserveDay;
    time_t returnDay;

    int calculate_fine(){
        time_t difference = difftime(returnDay, reserveDay);
        int daysDiff = difference / 86400;
        int fine = 0;
        if (daysDiff > 14){
            fine = (daysDiff - 14) * 5;
        }
        return fine;
    }

public:
    Book(string title, string author, string publisher, int year) {
        this->title = title;
        this->author = author;
        this->publisher = publisher;
        this->year = year;
    }

    void reserve_B(time_t date){
        this->reserveDay = date;
        this->reserved = true;
    }

    int return_B(){
        this->returnDay = time(0);
        this->reserved = false;
        return calculate_fine();
    }

    string get_title() {
        return title;
    }

    string get_author() {
        return author;
    }

    int get_year() {
        return year;
    }

    bool is_reserved(){
        return reserved;
    }

    virtual void print() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Publisher: " << publisher << endl;
        cout << "Year: " << year << endl;
    }
};

class Library {
protected:
    vector<Book*> books;

    Book* find_book_by_title(string title){
        for (int i = 0; i < int(books.size()); i++) {
            if (books[i]->get_title() == title) {
                return books[i];
            }
        }
        return nullptr;
    }

public:
    void add_book(Book* book) {
        books.push_back(book);
    }

    vector<Book*> find_books_by_author(string author){
        vector<Book*> result;
        for (int i = 0; i < int(books.size()); i++) {
            if (books[i]->get_author() == author) {
                result.push_back(books[i]);
            }
        }
        return result;
    }

    void reserve_book (string title, time_t date){
        Book* foundBook = find_book_by_title(title);

        if(foundBook == nullptr){
            cout << "There is no books like this" << endl;
        }
        else if(foundBook->is_reserved()){
            cout << "Book already reserved" << endl;
        }
        else{
            foundBook->reserve_B(date);
        }
    }

    void return_book (string title){
        Book* foundBook = find_book_by_title(title);
        if(foundBook == nullptr){
            cout << "There is no book like this reserved" << endl;
        }else{
            int fine = foundBook->return_B();
            if (fine == 0){
                cout << "No need to pay fine" << endl;
            }
            else{
                cout << "You have to pay " << fine << " rubles" << endl;
            }
        }
    }

    void remove_book_by_title(string title) {
        for (int i = 0; i < int(books.size()); i++) {
            if (books[i]->get_title() == title) {
                books.erase(books.begin() + i);
            }
        }
    }

    vector<Book*> reserved_books(){
        vector<Book*> result;
        for(int i = 0; i < int(books.size()); i++){
            if(books[i]->is_reserved() == true){
                result.push_back(books[i]);
            }
        }
        return result;
    }

    void print_books() {
        for (int i = 0; i < int(books.size()); i++) {
            books[i]->print();
            cout << endl;
        }
    }
};
