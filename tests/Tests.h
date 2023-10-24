#ifndef TESTS_H
#define TESTS_H

#include <gtest/gtest.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

extern "C" {
#include "myfunc.cpp"
}

//Книга забронирована
TEST(BookTest, BookCanBeReserved) {
    Book book("Title", "Author", "Publisher", 2023);
    time_t reserveDate = time(nullptr);
    book.reserve_B(reserveDate); // Книга зарезервированна
    ASSERT_TRUE(book.is_reserved());
}

//Книга возвращена с просроком
TEST(BookTest, BookReturnedWithFine) {
    Book book("Title", "Author", "Publisher", 2023);
    time_t reserveDate = time(nullptr) - (15 * 86400); // 15 дней
    book.reserve_B(reserveDate);
    book.return_B();
    ASSERT_FALSE(book.is_reserved()); // Книга возвращена с просроком в 1 день
    ASSERT_EQ(book.return_B(), 5);  // Штраф 5 рублей
}

//Книга возвращена вовремя
TEST(BookTest, BookReturnedInTime) {
    Book book("Title", "Author", "Publisher", 2023);
    time_t reserveDate = time(nullptr) - (10 * 86400); // 10 дней
    book.reserve_B(reserveDate);
    book.return_B();
    ASSERT_FALSE(book.is_reserved()); // Книга возвращена во время
    ASSERT_EQ(book.return_B(), 0);  // Штраф 0
}

//Тестирование всех get методов
TEST(BookTest, GettersTest) {
    Book book("Title", "Author", "Publisher", 2023);
    ASSERT_EQ(book.get_title(), "Title");
    ASSERT_EQ(book.get_author(), "Author");
    ASSERT_EQ(book.get_year(), 2023);
    ASSERT_EQ(book.is_reserved(), false);
}

//Тестирование вывода информации о книге
TEST(BookTest, Print) {
    Book book("Title1", "Author1", "Publisher1", 1978);
    testing::internal::CaptureStdout();
    book.print_book();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Title: Title1\nAuthor: Author1\nPublisher: Publisher1\nYear: 1978\n");
}

//В библиотеку можно добавить и найти книгу
TEST(LibraryTest, LibraryCanAddAndFindBooks) {
    Library library;
    Book book1("Title1", "Author1", "Publisher1", 2022);
    Book book2("Title2", "Author2", "Publisher2", 2023);

    library.add_book(&book1);
    library.add_book(&book2);

    ASSERT_EQ(library.find_books_by_author("Author2")[0]->get_author(), "Author2");
}

//В библиотеке можно забронировать книгу
TEST(LibraryTest, LibraryCanReserveBooks) {
    Library library;
    Book book("Title", "Author", "Publisher", 2023);
    time_t reserveDate = time(nullptr) - 1;
    library.add_book(&book);
    library.reserve_book("Title", reserveDate);
    ASSERT_TRUE(book.is_reserved());

}

//В библиотеке можно вернуть книгу
TEST(LibraryTest, LibraryCanReturnBooks) {
    Library library;
    Book book("Title", "Author", "Publisher", 2023);
    time_t reserveDate = time(nullptr) - 1;
    library.add_book(&book);
    library.reserve_book("Title", reserveDate);
    ASSERT_TRUE(book.is_reserved());
    library.return_book("Title");
    ASSERT_FALSE(book.is_reserved());
}

//В библиотеке нельзя вернуть книгу не из этой библиотеки
TEST(LibraryTest, LibraryCannotReturnUnknownBook) {
    Library library;
    Book book("Title", "Author", "Publisher", 2023);
    time_t reserveDate = time(nullptr) - 1;
    library.add_book(&book);
    testing::internal::CaptureStdout();
    library.reserve_book("Title1", reserveDate);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Unknown book\n");

}

//В библиотеке нельзя забронировать уже забронированную книгу
TEST(LibraryTest, LibraryCannotTakeReservedBook) {
    Library library;
    Book book("Title", "Author", "Publisher", 2023);
    time_t reserveDate = time(nullptr) - 1;
    library.add_book(&book);
    testing::internal::CaptureStdout();
    library.reserve_book("Title", reserveDate);
    library.reserve_book("Title", reserveDate);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Book already reserved\n");
}


//Из библиотеки можно удалить книгу
TEST(LibraryTest, RemoveFromLibrary) {
    Library library;
    Book book("Title", "Author", "Publisher", 2023);
    library.add_book(&book);
    library.remove_book_by_title("Title");
    ASSERT_EQ(library.find_books_by_author("Author").size(), 0);
}

//В библиотеке можно посмотреть список забронированных книг
TEST(LibraryTest, ReservedBooksInLibrary) {
    Library library;
    Book book1("Title1", "Author1", "Publisher1", 2023);
    Book book2("Title2", "Author2", "Publisher2", 2023);
    library.add_book(&book1);
    time_t date = time(nullptr);
    library.reserve_book("Title1", date);
    ASSERT_EQ(library.reserved_books().size(), 1);
}

//Поиск похожих книг по одному слову
TEST(LibraryTest, SimilarBooksByOneWord) {
    Library library;

    library.add_book(new Book("The Catcher in the Rye", "J.D. Salinger","Publisher", 1984));
    library.add_book(new Book("To Kill a Mockingbird", "Harper Lee","Publisher", 1984));
    library.add_book(new Book("The Great Gatsby", "F. Scott Fitzgerald","Publisher", 1984));
    library.add_book(new Book("1984", "George Orwell","Publisher", 1984));

    std::string search_title = "Mockingbird";
    std::vector<Book*> books = library.similar_books(search_title);
    testing::internal::CaptureStdout();
    for(const Book* book: books){
        std::cout << book->get_title() << std::endl;
    }
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To Kill a Mockingbird\n");

}

//Поиск похожих книг по нескольким словам
TEST(LibraryTest, SimilarBooksByWords) {

    Library library;

    library.add_book(new Book("The Catcher in the Rye", "J.D. Salinger","Publisher", 1984));
    library.add_book(new Book("To Kill a Mockingbird", "Harper Lee","Publisher", 1984));
    library.add_book(new Book("The Great Gatsby", "F. Scott Fitzgerald","Publisher", 1984));
    library.add_book(new Book("1984", "George Orwell","Publisher", 1984));

    std::string search_title = "Mockingbird great rye";
    std::vector<Book*> books = library.similar_books(search_title);
    testing::internal::CaptureStdout();
    for(const Book* book: books){
        std::cout << book->get_title() << std::endl;
    }
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "The Catcher in the Rye\nTo Kill a Mockingbird\nThe Great Gatsby\n");

}

//Поиск похожих книг в независимости от регистра букв
TEST(LibraryTest, SimilarBooksUpperCase) {
    Library library;

    library.add_book(new Book("The Catcher in the Rye", "J.D. Salinger","Publisher", 1984));
    library.add_book(new Book("To Kill a Mockingbird", "Harper Lee","Publisher", 1984));
    library.add_book(new Book("The Great Gatsby", "F. Scott Fitzgerald","Publisher", 1984));
    library.add_book(new Book("1984", "George Orwell","Publisher", 1984));

    std::string search_title = "GaTSbY";
    std::vector<Book*> books = library.similar_books(search_title);
    testing::internal::CaptureStdout();
    for(const Book* book: books){
        std::cout << book->get_title() << std::endl;
    }
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "The Great Gatsby\n");
}

#endif // TESTS_H
