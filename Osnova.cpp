#include "Header.h"

// Получение целого числа из ввода
int InputChecker::GetValidNumber() {
    int number;
    while (true) {
        cin >> number;
        if (cin.fail()) {  
            cin.clear();
            ClearBuffer();
            throw InvalidInputException("Некорректный ввод! Ожидается целое число.");
        }
        else {
            return number;
        }
    }
}

// Очистка буфера ввода
void InputChecker::ClearBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Деструктор - освобождение памяти
BallList::~BallList() {
    while (Head != nullptr) {
        Node* temp = Head;
        Head = Head->Next;
        delete temp;
    }
}

// Добавление шара в конец списка
void BallList::AddBall(int color) {
    
    if (color < 0 || color > 9) {
        throw OutOfRangeException("Цвет шара должен быть в диапазоне 0-9");
    }

    Node* newNode = new Node(color);
    if (Head == nullptr) {  
        Head = newNode;
    }
    else {  
        Node* current = Head;
        while (current->Next != nullptr) {
            current = current->Next;
        }
        current->Next = newNode;
    }
    Count++; 
}

// Удаление последовательности узлов от start до end
void BallList::DeleteNodes(Node* start, Node* end) {
    if (start == nullptr) {
        throw EmptyListException("Попытка удаления из пустого списка");
    }

    Node* current = start;
    Node* stop = (end != nullptr) ? end->Next : nullptr;

    while (current != stop) {  
        Node* next = current->Next;
        delete current;
        current = next;
        Count--;  
    }
}

// Поиск и удаление одной последовательности (возвращает количество удаленных)
int BallList::FindAndRemoveSequence() {
    if (Head == nullptr) return 0;  

    Node* current = Head;
    Node* prev = nullptr;
    Node* seqStart = nullptr;
    Node* seqEnd = nullptr;
    int seqLength = 1;  

    while (current != nullptr && current->Next != nullptr) {
        if (current->Color == current->Next->Color) {  
            if (seqStart == nullptr) {  
                seqStart = current;
                seqLength = 2;
            }
            else {  
                seqLength++;
            }
            seqEnd = current->Next;
            current = current->Next;
        }
        else {  
            if (seqLength >= 3 && seqStart != nullptr) {  
                Node* afterSeq = seqEnd->Next;
                int deletedCount = seqLength;
                DeleteNodes(seqStart, seqEnd);  

                
                if (prev == nullptr) {  
                    Head = afterSeq;
                }
                else {  
                    prev->Next = afterSeq;
                }
                return deletedCount;  
            }
            
            seqStart = nullptr;
            seqLength = 1;
            prev = current;
            current = current->Next;
        }
    }

    
    if (seqLength >= 3 && seqStart != nullptr) {
        int deletedCount = seqLength;
        DeleteNodes(seqStart, nullptr);
        if (prev == nullptr) {
            Head = nullptr;
        }
        else {
            prev->Next = nullptr;
        }
        return deletedCount;
    }

    return 0;  
}

// Удаление всех последовательностей в списке
int BallList::RemoveAllSequences() {
    int totalRemoved = 0;
    int removed;
    while ((removed = FindAndRemoveSequence()) > 0) {
        totalRemoved += removed;  
    }
    return totalRemoved;
}

// Вывод списка в консоль
void BallList::PrintList() const {
    Node* current = Head;
    while (current != nullptr) {
        cout << current->Color << " ";
        current = current->Next;
    }
    cout << endl;
}

// Вывод приветственного сообщения
void GameManager::ShowWelcome() {
    cout << "================================\n"
        << "        ИГРА: ШАРИКИ      \n"
        << "================================\n"
        << "Правила:\n"
        << " Введите кол-во шаров в линии (1-100000)\n"
        << " Введите последовательность шаров (0-9)\n"
        << " Цепочки из 3+ одинаковых шаров удаляются\n"
        << " Оставшиеся шары сдвигаются. Процесс повторяется автоматически\n"
        << " В конце программа выдаст: кол-во удаленных шаров,комбинацию из чисел (оставшихся), кол-во оставшихся шаров\n"
        << "================================\n\n";
}

// Получение ввода от пользователя
void GameManager::GetUserInput() {
    cout << "Введите количество шаров (1-100000): ";
    this->TotalBalls = InputChecker::GetValidNumber();
    if (this->TotalBalls < 1 || this->TotalBalls > 100000) {
        throw OutOfRangeException("Количество шаров должно быть от 1 до 100000");
    }

    cout << "Введите " << this->TotalBalls << " цветов (0-9 через пробел): ";
    for (int i = 0; i < this->TotalBalls; ) {
        int color = InputChecker::GetValidNumber();
        if (color >= 0 && color <= 9) {
            Balls.AddBall(color);
            i++;
        }
        else {
            throw OutOfRangeException("Цвет шара должен быть в диапазоне 0-9");
        }
    }
    InputChecker::ClearBuffer();
}

// Вывод результатов игры
void GameManager::ShowResults(int removed) {
    cout << "\n================================\n"
        << "Результат:\n"
        << "Удалено шаров: " << removed << "\n"
        << "Осталось шаров: " << Balls.GetCount() << "\n"
        << "Оставшиеся: ";
    Balls.PrintList();
    cout << "================================\n";
}

// Запуск игрового процесса
void GameManager::StartGame() {
    ShowWelcome();          
    GetUserInput();         

    cout << "\nИсходная последовательность: ";
    Balls.PrintList();     

    int removed = Balls.RemoveAllSequences();  
    ShowResults(removed);   

    cout << "\nИгра завершена.\n";
}
