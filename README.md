[![CI/CD GitHub Actions](https://github.com/ehotez/gtest2/actions/workflows/test-action.yml/badge.svg)](https://github.com/ehotez/gtest2/actions/workflows/test-action.yml)
[![Coverage Status](https://coveralls.io/repos/ehotez/gtest2/badge.svg?branch=main)](https://coveralls.io/github/ehotez/gtest2?branch=main)
[![Quality Gate](https://sonarcloud.io/api/project_badges/measure?project=ehotez_gtest2&metric=alert_status)](https://sonarcloud.io/dashboard?id=ehotez_gtest2)
[![Code smells](https://sonarcloud.io/api/project_badges/measure?project=ehotez_gtest2&metric=code_smells)](https://sonarcloud.io/dashboard?id=ehotez_gtest2)

# Класс Book

Класс `Book` представляет собой объект книги в библиотеке.

### Свойства

- `title` (string): Заголовок книги.
- `author` (string): Автор книги.
- `publisher` (string): Издательство книги.
- `year` (int): Год издания книги.
- `reserved` (bool): Флаг, указывающий, забронирована ли книга.
- `reserveDay` (time_t): Дата бронирования книги.
- `returnDay` (time_t): Дата возврата книги.

### Методы

- `Book(string title, string author, string publisher, int year)`: Конструктор класса `Book`. Создает новый экземпляр книги с указанными свойствами.
- `void reserve_B(time_t date)`: Метод для бронирования книги на указанную дату.
- `int return_B()`: Метод для возврата книги.
- `int calculate_fine()`: Метод для подсчета штрафа просроченности.
- `string get_title()`: Метод для получения заголовка книги.
- `string get_author()`: Метод для получения имени автора книги.
- `int get_year()`: Метод для получения года издания книги.
- `bool is_reserved()`: Метод для проверки, забронирована ли книга.
- `void print()`: Метод для вывода информации о книге.

# Класс Library

Класс `Library` представляет собой библиотеку с коллекцией книг.

### Свойства

- `books` (vector<Book*>): Вектор, содержащий экземпляры книг.

### Методы

- `void add_book(Book* book)`: Метод для добавления книги в библиотеку.
- `int books_amount`: Метод для получения количества книг в библиотеке.
- `vector<Book*> find_books_by_author(string author)`: Метод для поиска книг по имени автора.
- `void reserve_book(string title, time_t date)`: Метод для бронирования книги по заголовку.
- `void return_book(string title)`: Метод для возврата книги и расчета штрафа, если он есть.
- `Book* find_book_by_title(string title)`: Метод для поиска книги по заголовку.
- `void remove_book_by_title(string title)`: Метод для удаления книги по заголовку.
- `void print_books()`: Метод для вывода списка книг в библиотеке.
- `vector<Book*> similar_books(string key_words)`: Метод для поиска похожих по названию книг в библиотеке

# План тестирования библиотеки управления книгами

Библиотека `Library` предоставляет функциональность для управления книгами и их резервацией. Этот план тестирования охватывает тесты для классов `Book` и `Library`, а также функциональности поиска и управления книгами.

## Тесты для класса `Book`

### BookCanBeReserved

- **Описание:** Проверяет, что книгу можно успешно зарезервировать.  
**Входные данные:**  
book("Title", "Author", "Publisher", 2023) - экземпляр книги   
reserveDate = time(nullptr) - сегодняшняя дата  
**Выходные данные:**  
book.is_reserved() = True - книга забронирована

### BookReturnedWithFine

- **Описание:** Проверяет, что книга, возвращенная с просрочкой, влечет штраф.  
**Входные данные:**  
book("Title", "Author", "Publisher", 2023) - экземпляр книги   
reserveDate = time(nullptr) - (15 * 86400) - дата 15 дней назад  
**Выходные данные:**  
book.is_reserved() = False - книга не забронирована  
book.return_B() = 5 - пени равны 5  

### BookReturnedInTime

- **Описание:** Проверяет, что книга, возвращенная вовремя, не влечет штраф.  
**Входные данные:**  
book("Title", "Author", "Publisher", 2023) - экземляр книги  
reserveDate = time(nullptr) - (10 * 86400) - дата 10 дней назад  
**Выходные данные:**  
book.is_reserved() = False - книга не забронирована  
book.return_B() = 0 - пени 0 рублей  

### GettersTest

- **Описание:** Проверяет правильность работы методов получения информации о книге.  
**Входные данные:**  
book("Title", "Author", "Publisher", 2023) - экземляр книги  
**Выходные данные:**  
book.get_title() = "Title" - название книги  
book.get_author() = "Author" - автор книги  
book.get_year() = 2023 - год  
book.is_reserved() = false - книга не забронирована  

### Print

- **Описание:** Проверяет правильность вывода информации о книге.  
**Входные данные:**  
book("Title", "Author", "Publisher", 2023) - экземляр книги   
**Выходные данные:**  
Выводит данные в формате  
"Title: Title1  
Author: Author1  
Publisher: Publisher1  
Year: 1978"    

## Тесты для класса `Library`

Для каждого теста создается экземпляр класса `Library`:  
`Library library;` 

### LibraryCanAddBooks

- **Описание:** Проверяет возможность добавления книг в библиотеку.  
**Входные данные:**  
book1("Title1", "Author1", "Publisher1", 2022) - экземпляр книги  
book2("Title2", "Author2", "Publisher2", 2023) - экземпляр книги  
**Выходные данные:**  
library.books_amount() = 2 - количество книг в библиотеке

### LibraryCanFindBooksByAuthor
- **Описание:** Проверяет возможность поиска книг по автору в библиотеке.  
**Входные данные:**  
library - 
book1("Title1", "Author1", "Publisher1", 2022) - экземпляр книги  
book2("Title2", "Author2", "Publisher2", 2023) - экземпляр книги  
**Выходные данные:**  
title = "Title2" -  при поиске по Author2 получаем данное значение

### LibraryCanReserveBooks

- **Описание:** Проверяет возможность резервации книг в библиотеке.  
**Входные данные:**  
library - 
book("Title", "Author", "Publisher", 2023) - экземпляр книги  
reserveDate = time(nullptr) - 1 - дата бронирования книги  
**Выходные данные:**  
book.is_reserved() = True - книга забронирована

### LibraryCannotReserveUnknownBook

- **Описание:** Проверяет, что нельзя зарезервировать книгу, которой нет в библиотеке.  
**Входные данные:**  
library - 
book("Title", "Author", "Publisher", 2023) - экземпляр книги  
reserveDate = time(nullptr) - 1 - дата бронирования  
book_to_reserve = "Title1" - название книги для брони  
**Выходные данные:**  
Выводит сообщение "Unknown book"  

### LibraryCanReturnBooks

- **Описание:** Проверяет возможность возврата книг в библиотеку.  
**Входные данные:**  
library - 
book("Title", "Author", "Publisher", 2023) - экземпляр книги  
reserveDate = time(nullptr) - 1 - дата брони  
**Выходные данные:**  
book.is_reserved() = False - книга не забронирована  

### LibraryCannotReturnUnknownBook

- **Описание:** Проверяет, что нельзя вернуть книгу, которой нет в библиотеке.  
**Входные данные:**  
library - 
book("Title", "Author", "Publisher", 2023) - экземпляр книги  
book_to_return = "Title1" - название книги, которую пытаются вернуть    
**Выходные данные:**  
Выводит сообщение "Unknown book"

### LibraryCannotReturnNotReservedBook

- **Описание:** Проверяет, что нельзя вернуть книгу, которую не забронировали.  
**Входные данные:**  
book("Title", "Author", "Publisher", 2023) - экземпляр книги  
book_to_return = "Title1" - название книги которую пытаются вернуть  
**Выходные данные:**  
Выводит сообщение "Book is not reserved"

### LibraryCannotTakeReservedBook

- **Описание:** Проверяет, что нельзя зарезервировать уже зарезервированную книгу.  
**Входные данные:**  
library - 
book("Title", "Author", "Publisher", 2023) - экземпляр книги  
reserveDate = time(nullptr) - 1 - дата бронирования  
**Выходные данные:**  
Выводит сообщение "Book already reserved"  

### RemoveFromLibrary

- **Описание:** Проверяет, что книгу можно удалить из библиотеки.  
**Входные данные:**  
book("Title", "Author", "Publisher", 2023) - экземпляр книги  
book_to_remove = "Title" -  название книги для удаления  
**Выходные данные:**  
library.books_amount() = 0 - количество книг в библиотеке становится равно 0  

### ReservedBooksInLibrary

- **Описание:** Проверяет, что можно получить список зарезервированных книг в библиотеке.  
**Входные данные:**  
book1("Title1", "Author1", "Publisher1", 2023) - экземпляр книги  
book2("Title2", "Author2", "Publisher2", 2023) - экземпляр книги  
date = time(nullptr) - дата бронирования
reserve_title = "Title1" - название книги для бронирования
**Выходные данные:**  
Выводит сообщение в формате  
"Title: Title1  
Author: Author1  
Publisher: Publisher1  
Year: 2023"   

### SimilarBooksByOneWord

- **Описание:** Проверяет поиск книг по одному слову в названии.  
**Входные данные:**  
book("The Catcher in the Rye", "J.D. Salinger","Publisher", 1984) - 1 книга  
book("To Kill a Mockingbird", "Harper Lee","Publisher", 1984) - 2 книга  
book("The Great Gatsby", "F. Scott Fitzgerald","Publisher", 1984) - 3 книга  
book("1984", "George Orwell","Publisher", 1984) - 4 книга  
search_title = "Mockingbird" - фраза для поиска  
**Выходные данные:** 
Выводит название найденной книги "To Kill a Mockingbird\n"  

### SimilarBooksByWords

- **Описание:** Проверяет поиск книг по нескольким словам в названии.  
**Входные данные:**  
book("The Catcher in the Rye", "J.D. Salinger","Publisher", 1984) - 1 книга  
book("To Kill a Mockingbird", "Harper Lee","Publisher", 1984) - 2 книга  
book("The Great Gatsby", "F. Scott Fitzgerald","Publisher", 1984) - 3 книга  
book("1984", "George Orwell","Publisher", 1984) - 4 книга  
search_title = "Mockingbird Great rye" - фраза для поиска  
**Выходные данные:**  
Выводит названия найденных книг  
"The Catcher in the Rye  
To Kill a Mockingbird  
The Great Gatsby"   

### SimilarBooksUpperCase

- **Описание:** Проверяет поиск книг в независимости от регистра букв.  
**Входные данные:**  
book("The Catcher in the Rye", "J.D. Salinger","Publisher", 1984) - 1 книга  
book("To Kill a Mockingbird", "Harper Lee","Publisher", 1984) - 2 книга  
book("The Great Gatsby", "F. Scott Fitzgerald","Publisher", 1984) - 3 книга  
book("1984", "George Orwell","Publisher", 1984) - 4 книга  
search_title = "GaTsBy" - фраза для поиска  
**Выходные данные:**  
Выводит название найденной книги "The Great Gatsby"   

### NoSimilarBooks

- **Описание:** Проверяет поиск книг в независимости от регистра букв.  
**Входные данные:**  
book("The Catcher in the Rye", "J.D. Salinger","Publisher", 1984) - 1 книга  
book("To Kill a Mockingbird", "Harper Lee","Publisher", 1984) - 2 книга  
book("The Great Gatsby", "F. Scott Fitzgerald","Publisher", 1984) - 3 книга  
book("1984", "George Orwell","Publisher", 1984) - 4 книга  
search_title = "Harry Potter" - фраза для поиска  
**Выходные данные:** 
books.size() = 0 - количество найденых книг равно 0  



