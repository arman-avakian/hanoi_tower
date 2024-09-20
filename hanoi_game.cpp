#include <iostream>
#include <vector>
#include <stack>
#include <cmath>

// Определение функции hanoiRecursive
// Эта функция решает задачу Ханойской башни рекурсивно
// n - количество колец
// from_rod - стержень, с которого нужно переместить кольца
// to_rod - стержень, на который нужно переместить кольца
// aux_rod - вспомогательный стержень
// moves - вектор для хранения оптимальной последовательности ходов
void hanoiRecursive(int n, int from_rod, int to_rod, int aux_rod, std::vector<std::pair<int, int>>& moves) {
    // Базовый случай рекурсии
    if (n == 1) {
        moves.push_back({from_rod, to_rod});
        return;
    }
    // Рекурсивный вызов для перемещения n-1 колец на вспомогательный стержень
    hanoiRecursive(n - 1, from_rod, aux_rod, to_rod, moves);
    // Перемещение оставшегося кольца на целевой стержень
    moves.push_back({from_rod, to_rod});
    // Рекурсивный вызов для перемещения n-1 колец со вспомогательного стержня на целевой стержень
    hanoiRecursive(n - 1, aux_rod, to_rod, from_rod, moves);
}

// Определение функции displayTowers
// Функция отображает текущее состояние стержней
void displayTowers(const std::vector<std::stack<int>>& towers, int num_disks) {
    std::cout << "\nТекущее состояние стержней:\n";
    // Создаем копии стержней для безопасного извлечения элементов
    std::vector<std::stack<int>> temp_towers = towers;

    // Вывод стержней построчно
    for (int level = num_disks; level >= 1; --level) {
        for (int i = 0; i < 3; ++i) {
            if (temp_towers[i].size() >= level) {
                std::cout << " " << temp_towers[i].top() << " ";
                temp_towers[i].pop();
            } else {
                std::cout << " | ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "----\n";
    std::cout << " 1  2  3 \n\n";
}

// Определение функции makeMove
// Функция выполняет ход игрока
bool makeMove(std::vector<std::stack<int>>& towers, int from, int to) {
    // Проверка на наличие кольца на исходном стержне
    if (towers[from].empty()) {
        return false;
    }
    int disk = towers[from].top();
    // Проверка возможности перемещения на целевой стержень
    if (!towers[to].empty() && towers[to].top() < disk) {
        return false;
    }
    // Перемещение кольца
    towers[from].pop();
    towers[to].push(disk);
    return true;
}

// Определение функции isGameWon
// Функция проверяет, завершена ли игра
bool isGameWon(const std::vector<std::stack<int>>& towers, int num_disks) {
    return towers[2].size() == num_disks;
}

int main() {
    // Выбор размера игры
    std::cout << "Выбор размера игры:\n\n";
    std::cout << "3 4 5\n6 7 8\n\n";

    // Получение ввода от пользователя
    int n;
    std::cout << "Введите количество колец (3-8): ";
    std::cin >> n;

    // Проверка корректности ввода
    if (n < 3 || n > 8) {
        std::cout << "Неправильный выбор. Пожалуйста, перезапустите программу и выберите число от 3 до 8.\n";
        return 1;
    }

    std::cout << "\nНачинается новая игра\n\n";

    // Правила игры
    std::cout << "Правила игры\n";
    std::cout << "Цель этой игры заключается в перемещении колец с левой стороны на стержень с правой стороны.\n";
    std::cout << "Ход состоит в том, чтобы перенести одно кольцо на другой стержень, с условием что в пункте назначения оно самое маленькое (по размеру).\n";
    std::cout << "Удачи!\n\n";

    // Инициализация стержней
    std::vector<std::stack<int>> towers(3);
    for (int i = n; i >= 1; --i) {
        towers[0].push(i);
    }

    // Вычисление оптимального решения с помощью рекурсивной функции
    std::vector<std::pair<int, int>> optimalMoves;
    hanoiRecursive(n, 1, 3, 2, optimalMoves); // Стержни обозначены числами 1,2,3

    int minMoves = optimalMoves.size();
    int userMoves = 0;

    // Игровой цикл
    while (true) {
        // Отображение текущего состояния игры
        displayTowers(towers, n);

        // Ввод хода игрока
        int from, to;
        std::cout << "Введите номер стержня, с которого хотите переместить кольцо (1-3): ";
        std::cin >> from;
        std::cout << "Введите номер стержня, на который хотите переместить кольцо (1-3): ";
        std::cin >> to;

        // Проверка корректности ввода
        if (from < 1 || from > 3 || to < 1 || to > 3) {
            std::cout << "Неправильный ввод. Пожалуйста, введите числа от 1 до 3.\n";
            continue;
        }

        // Выполнение хода
        if (!makeMove(towers, from - 1, to - 1)) {
            std::cout << "Неправильный ход. Нельзя перемещать большее кольцо на меньшее.\n";
            continue;
        }

        userMoves++;

        // Проверка на победу
        if (isGameWon(towers, n)) {
            displayTowers(towers, n);
            std::cout << "Поздравляем! Вы успешно переместили все кольца!\n";
            std::cout << "Минимальное количество ходов: " << minMoves << "\n";
            std::cout << "Вы сделали ходов: " << userMoves << "\n";
            if (userMoves == minMoves) {
                std::cout << "Вы достигли оптимального решения!\n";
            } else {
                std::cout << "Вы можете попробовать улучшить результат.\n";
            }
            break;
        }
    }

    return 0;
}

