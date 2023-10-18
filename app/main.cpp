#include <stdio.h>
#include <ctime>
#include "myfunc.cpp"

int main() {
    // Создание объектов класса "Книга"
    Book* book1 = new Book("Title1", "Author1", "Publisher1", 1978);
    Book* book2 = new Book("Title2", "Author2", "Publisher2", 1985);

    // Создание объекта класса "Библиотека"
    Library library;

    library.add_book(book1);
    library.add_book(book2);

    time_t date1 = time(0) - 86400 * 20;
    library.reserve_book("Title1", date1);
    library.reserve_book("Title1", date1);

    vector<Book*> res = library.reserved_books();
    if (int(res.size()) > 0) {
        cout << "Found " << res.size() << " reserved books:" << endl;
        for (int i = 0; i < int(res.size()); i++) {
            res[i]->print();
            cout << endl;
        }
    } else {
        cout << "No reserved books found" << endl;
    }

    library.return_book("Title1");


    vector<Book*> books = library.find_books_by_author("Author2");
    if (int(books.size()) > 0) {
        cout << "Found " << books.size() << " books:" << endl;
        for (int i = 0; i < int(books.size()); i++) {
            books[i]->print();
            cout << endl;
        }
    } else {
        cout << "No books found" << endl;
    }

    return 0;
}
