#include "Header.h"

int main() {
    try {
        setlocale(LC_ALL, "Russian");  
        GameManager game;              
        game.StartGame();              
    }
    catch (const InvalidInputException& e) {
        cerr << "Ошибка ввода: " << e.what() << endl;
        return 1;
    }
    catch (const OutOfRangeException& e) {
        cerr << "Ошибка диапазона: " << e.what() << endl;
        return 2;
    }
    catch (const EmptyListException& e) {
        cerr << "Ошибка списка: " << e.what() << endl;
        return 3;
    }
    catch (const exception& e) {
        cerr << "Неизвестная ошибка: " << e.what() << endl;
        return 4;
    }
    return 0;
}
