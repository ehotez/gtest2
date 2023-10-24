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

### BookReturnedWithFine

- **Описание:** Проверяет, что книга, возвращенная с просрочкой, влечет штраф.

### BookReturnedInTime

- **Описание:** Проверяет, что книга, возвращенная вовремя, не влечет штраф.

### GettersTest

- **Описание:** Проверяет правильность работы методов получения информации о книге.

### Print

- **Описание:** Проверяет правильность вывода информации о книге.

## Тесты для класса `Library`

### LibraryCanAddAndFindBooks

- **Описание:** Проверяет возможность добавления книг в библиотеку и их поиска.

### LibraryCanReserveBooks

- **Описание:** Проверяет возможность резервации книг в библиотеке.

### LibraryCanReturnBooks

- **Описание:** Проверяет возможность возврата книг в библиотеку.

### LibraryCannotReturnUnknownBook

- **Описание:** Проверяет, что нельзя вернуть книгу, которой нет в библиотеке.

### LibraryCannotTakeReservedBook

- **Описание:** Проверяет, что нельзя зарезервировать уже зарезервированную книгу.

### RemoveFromLibrary

- **Описание:** Проверяет, что книгу можно удалить из библиотеки.

### ReservedBooksInLibrary

- **Описание:** Проверяет, что можно получить список зарезервированных книг в библиотеке.

## Дополнительные тесты для поиска книг

### SimilarBooksByOneWord

- **Описание:** Проверяет поиск книг по одному слову в названии.

### SimilarBooksByWords

- **Описание:** Проверяет поиск книг по нескольким словам в названии.

### SimilarBooksUpperCase

- **Описание:** Проверяет поиск книг в независимости от регистра букв.






