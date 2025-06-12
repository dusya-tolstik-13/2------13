#pragma once
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

// Класс исключения для неверного ввода
class InvalidInputException : public runtime_error {
public:
    InvalidInputException(const string& message) : runtime_error(message) {}
};

// Класс исключения для значений вне допустимого диапазона
class OutOfRangeException : public runtime_error {
public:
    OutOfRangeException(const string& message) : runtime_error(message) {}
};

// Класс исключения для пустого списка
class EmptyListException : public runtime_error {
public:
    EmptyListException(const string& message) : runtime_error(message) {}
};

// Класс для проверки корректности ввода
class InputChecker {
public:
    // Получение валидного числа из ввода
    static int GetValidNumber();
    // Очистка буфера ввода
    static void ClearBuffer();
};

// Класс для работы со списком шаров
class BallList {
private:
    // Структура узла списка
    struct Node {
        int Color;      // Цвет шара (0-9)
        Node* Next;     // Указатель на следующий узел
        Node(int color) : Color(color), Next(nullptr) {}
    };

    Node* Head;         // Указатель на начало списка
    int Count;          // Количество элементов в списке

    // Удаление последовательности узлов от start до end
    void DeleteNodes(Node* start, Node* end);
    // Поиск и удаление одной последовательности (возвращает количество удаленных)
    int FindAndRemoveSequence();

public:
    BallList() : Head(nullptr), Count(0) {}
    ~BallList();        // Деструктор

    // Добавление шара в конец списка
    void AddBall(int color);
    // Удаление всех последовательностей (возвращает общее количество удаленных)
    int RemoveAllSequences();
    // Вывод списка в консоль
    void PrintList() const;
    // Получение количества элементов
    int GetCount() const { return Count; }
};

// Класс для управления игровым процессом
class GameManager {
private:
    BallList Balls;         // Список шаров
    int TotalBalls;         // Общее количество шаров

    // Вывод приветственного сообщения
    void ShowWelcome();
    // Вывод результатов игры
    void ShowResults(int removed);
    // Получение ввода от пользователя
    void GetUserInput();

public:
    // Запуск игрового процесса
    void StartGame();
};
