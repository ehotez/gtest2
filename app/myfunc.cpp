#include <iostream>
#include <vector>
#include <ctime>

class Book {

private:
    std::string title;
    std::string author;
    std::string publisher;
    int year;
    bool reserved = false;
    time_t reserveDay;
    time_t returnDay;

protected:

    int calculate_fine() const{
        time_t difference = int(difftime(returnDay, reserveDay));
        int daysDiff = int(difference / 86400);
        int fine = 0;
        if (daysDiff > 14){
            fine = (daysDiff - 14) * 5;
        }
        return fine;
    }

public:
    Book(const std::string& title, const std::string& author, const std::string& publisher, int year)
        : title(title), author(author), publisher(publisher), year(year) {
    }

    void reserve_B(time_t date){
        this->reserveDay = date;
        this->reserved = true;
    }

    int return_B(){
        this->returnDay = time(nullptr);
        this->reserved = false;
        return calculate_fine();
    }

    std::string get_title() const{
        return title;
    }

    std::string get_author() const{
        return author;
    }

    int get_year() const{
        return year;
    }

    bool is_reserved() const{
        return reserved;
    }

    void print_book() {
        std::cout << "Title: " << title << std::endl;
        std::cout << "Author: " << author << std::endl;
        std::cout << "Publisher: " << publisher << std::endl;
        std::cout << "Year: " << year << std::endl;
    }
};

class Library {
private:
    std::vector<Book*> books;

protected:
    Book* find_book_by_title(const std::string& title){
        for(Book* book: books) {
            if (book->get_title() == title) {
                return book;
            }
        }
        return nullptr;
    }

public:
    void add_book(Book* book) {
        books.push_back(book);
    }

    std::vector<Book*> find_books_by_author(const std::string& author){
        std::vector<Book*> result;
        for(Book* book: books) {
            if (book->get_author() == author) {
                result.push_back(book);
            }
        }
        return result;
    }

    void reserve_book (const std::string& title, time_t date){
        Book* foundBook = find_book_by_title(title);

        if(foundBook == nullptr){
           std::cout << "There is no books like this" << std::endl;
        }
        else if(foundBook->is_reserved()){
            std::cout << "Book already reserved" << std::endl;
        }
        else{
            foundBook->reserve_B(date);
        }
    }

    void return_book (const std::string& title){
        Book* foundBook = find_book_by_title(title);
        if(foundBook == nullptr){
            std::cout << "There is no book like this reserved" << std::endl;
        }else{
            int fine = foundBook->return_B();
            if (fine == 0){
                std::cout << "No need to pay fine" << std::endl;
            }
            else{
                std::cout << "You have to pay " << fine << " rubles" << std::endl;
            }
        }
    }

    void remove_book_by_title(const std::string& title) {
        for (auto it = books.begin(); it != books.end(); ) {
            if ((*it)->get_title() == title) {
                it = books.erase(it);
            } else {
                ++it;
            }
        }
    }

    std::vector<Book*> reserved_books() const{
        std::vector<Book*> result;
        for(Book* book: books){
            if(book->is_reserved() == true){
                result.push_back(book);
            }
        }
        return result;
    }

    void print_books() const{
        for(Book* book: books) {
            book->print_book();
            std::cout << std::endl;
        }
    }
};
