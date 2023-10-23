#ifndef TESTS_H
#define TESTS_H

#include <gtest/gtest.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

extern "C" {
#include "myfunc.cpp"
}

TEST(BookTest, BookCanBeReserved) {
    Book book("Title", "Author", "Publisher", 2023);
    time_t reserveDate = time(nullptr);

    book.reserve_B(reserveDate); // Книга зарезервированна

    ASSERT_TRUE(book.is_reserved());
}

TEST(BookTest, BookReturnedWithFine) {
    Book book("Title", "Author", "Publisher", 2023);
    time_t reserveDate = time(nullptr) - (15 * 86400); // 15 дней

    book.reserve_B(reserveDate);
    book.return_B();

    ASSERT_FALSE(book.is_reserved()); // Книга возвращена с просроком в 1 день
    ASSERT_EQ(book.return_B(), 5);  // Штраф 5 рублей
}

TEST(BookTest, BookReturnedInTime) {
    Book book("Title", "Author", "Publisher", 2023);
    time_t reserveDate = time(nullptr) - (10 * 86400); // 10 дней

    book.reserve_B(reserveDate);
    book.return_B();

    ASSERT_FALSE(book.is_reserved()); // Книга возвращена во время
    ASSERT_EQ(book.return_B(), 0);  // Штраф 0
}

TEST(BookTest, GettersTest) {
    Book book("Title", "Author", "Publisher", 2023);

    ASSERT_EQ(book.get_title(), "Title");
    ASSERT_EQ(book.get_author(), "Author");
    ASSERT_EQ(book.get_year(), 2023);
    ASSERT_EQ(book.is_reserved(), false);
}

TEST(BookTest, Print) {
    Book book("Title1", "Author1", "Publisher1", 1978);
    testing::internal::CaptureStdout();
    book.print_book();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Title: Title1\nAuthor: Author1\nPublisher: Publisher1\nYear: 1978\n");
}

TEST(LibraryTest, LibraryCanAddAndFindBooks) {
    Library library;
    Book book1("Title1", "Author1", "Publisher1", 2022);
    Book book2("Title2", "Author2", "Publisher2", 2023);

    library.add_book(&book1);
    library.add_book(&book2);

    ASSERT_EQ(library.find_books_by_author("Author2")[0]->get_author(), "Author2");
}

TEST(LibraryTest, LibraryCanReserveAndReturnBooks) {
    Library library;
    Book book("Title", "Author", "Publisher", 2023);
    time_t reserveDate = time(nullptr) - 1;

    library.add_book(&book);
    library.reserve_book("Title", reserveDate);

    ASSERT_TRUE(book.is_reserved());

    library.return_book("Title");

    ASSERT_FALSE(book.is_reserved());
}

TEST(LibraryTest, RemoveFromLibrary) {
    Library library;
    Book book("Title", "Author", "Publisher", 2023);
    library.add_book(&book);
    library.remove_book_by_title("Title");
    ASSERT_EQ(library.find_books_by_author("Author").size(), 0);
}

TEST(LibraryTest, ReservedBooksInLibrary) {
    Library library;
    Book book1("Title1", "Author1", "Publisher1", 2023);
    Book book2("Title2", "Author2", "Publisher2", 2023);
    library.add_book(&book1);
    time_t date = time(nullptr);
    library.reserve_book("Title1", date);
    ASSERT_EQ(library.reserved_books().size(), 1);
}



#endif // TESTS_H
