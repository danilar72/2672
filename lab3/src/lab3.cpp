#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Dish {
    string fullName;
    string type;
    double cost;
};

void addDishToFile(const Dish& dish) {
    ofstream outFile("menu.txt");
    if (outFile.is_open()) {
        outFile << dish.fullName << "," << dish.type << "," << dish.cost << endl;
        outFile.close();
        cout << "<Блюдо успешно добавлено." << endl;
    } else {
        cerr << "Не удалось открыть файл для записи." << endl;
    }
}

void searchDishByName(const string& name) {
    ifstream inFile("menu.txt");
    if (inFile.is_open()) {
        string line;
        bool found = false;
        while (getline(inFile, line)) {
            size_t pos = line.find(',');
            string fullName = line.substr(0, pos);
            if (fullName == name) {
                cout << "Найдено блюдо: " << line << endl;
                found = true;
                break;
            }
        }
        inFile.close();
        if (!found) {
            cout << "Блюдо с таким названием не найдено." << endl;
        }
    } else {
        std::cerr << "Не удалось открыть файл для чтения." << endl;
    }
}

void sortDishesByType() {
    ifstream inFile("menu.txt");
    if (inFile.is_open()) {
        string lines[100];
        int count = 0;
        string line;
        while (std::getline(inFile, line)) {
            lines[count] = line;
            count++;
        }
        inFile.close();
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                size_t pos1 = lines[j].find_last_of(',');
                size_t pos2 = lines[j + 1].find_last_of(',');
                double grade1 = std::stod(lines[j].substr(pos1 + 1));
                double grade2 = std::stod(lines[j + 1].substr(pos2 + 1));
                if (grade1 < grade2) {
                    std::swap(lines[j], lines[j + 1]);
                }
            }
        }
        std::ofstream outFile("students.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << lines[i] << std::endl;
            }
            outFile.close();
            std::cout << "Блюда отсортированы по типу." << std::endl;
        } else {
            std::cerr << "Не удалось открыть файл для записи." << std::endl;
        }
    } else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

void sortDishesByCost() {
    ifstream inFile("menu.txt");
    if (inFile.is_open()) {
        string lines[100];
        int count = 0;
        string line;
        while (std::getline(inFile, line)) {
            lines[count] = line;
            count++;
        }
        inFile.close();
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                size_t pos1 = lines[j].find_last_of(',');
                size_t pos2 = lines[j + 1].find_last_of(',');
                double grade1 = std::stod(lines[j].substr(pos1 + 1));
                double grade2 = std::stod(lines[j + 1].substr(pos2 + 1));
                if (grade1 < grade2) {
                    std::swap(lines[j], lines[j + 1]);
                }
            }
        }
        std::ofstream outFile("students.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << lines[i] << std::endl;
            }
            outFile.close();
            std::cout << "Блюда отсортированы по типу." << std::endl;
        } else {
            std::cerr << "Не удалось открыть файл для записи." << std::endl;
        }
    } else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

int main() {
    int choice;
    string name;
    string fullName, type;
    double cost;
    cout << "Введите название блюда: ";
    getline(cin, fullName);
    while (!fullName.empty()) {
    	cout << "Введите тип блюда: ";
    	getline(cin, type);
    	cout << "Введите цену: ";
    	cin >> cost;
    	Dish newDish = {fullName, type, cost};
    	addDishToFile(newDish);
    	cin.ignore();
        cout << "Введите название блюда: ";
        getline(cin, fullName);
    }
    if (fullName.empty()){
    	cout << "Ввод прерван." <<endl;
    }
    do {
        cout << "Меню:" <<endl;
        cout << "1. Добавить блюдо" <<endl;
        cout << "2. Поиск блюда по названию" <<endl;
        cout << "3. Сортировать блюда по типу или цене" <<endl;
        cout << "0. Выйти" << std::endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cin.ignore();
                cout << "Введите название блюда: ";
                getline(cin, fullName);
                cout << "Введите тип блюда: ";
                getline(cin, type);
                cout << "Введите цену: ";
                cin >> cost;
                Dish newDish = {fullName, type, cost};
                addDishToFile(newDish);
                break;
            }
            case 2: {
                cin.ignore();
                cout << "Введите название блюда для поиска: ";
                getline(cin, name);
                searchDishByName(name);
                break;
            }
            case 3: {
                sortDishesByType();
                break;
            }
            case 0: {
                cout << "Программа завершена." << endl;
                break;
            }
            default: {
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
