//Лабораторная работа №3 Вариант №3 Данилов Артём ИУ1-12Б
//Я не записываю результаты в output.txt, а вывожу в терминал
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
    ofstream outFile("menu.txt",ios::app);
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
        cerr << "Не удалось открыть файл для чтения." << endl;
    }
}

void sortDishesByType() {
    ifstream inFile("menu.txt");
    if (inFile.is_open()) {
        string lines[100];
        int count = 0;
        string line;
        while (getline(inFile, line)) {
            lines[count] = line;
            count++;
        }
        inFile.close();
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                size_t pos1 = lines[j].find(',');
                size_t pos2 = lines[j].find_last_of(',');
                size_t pos3 = lines[j+1].find(',');
                size_t pos4 = lines[j+1].find_last_of(',');
                string type_1 =lines[j].substr(pos1 + 1,pos2);
                string type_2 =lines[j+1].substr(pos3 + 1,pos4);
                if (type_1>type_2) {
                    swap(lines[j], lines[j + 1]);
                }
            }
        }
        ofstream outFile("menu.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << lines[i] << endl;
            }
            outFile.close();
            cout << "Блюда отсортированы по типу." << endl;
        } else {
            cerr << "Не удалось открыть файл для записи." << endl;
        }
    } else {
        cerr << "Не удалось открыть файл для чтения." << endl;
    }
}

void sortDishesByCost() {
    ifstream inFile("menu.txt");
    if (inFile.is_open()) {
        string lines[100];
        int count = 0;
        string line;
        while (getline(inFile, line)) {
            lines[count] = line;
            count++;
        }
        inFile.close();
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                size_t pos1 = lines[j].find_last_of(',');
                size_t pos2 = lines[j + 1].find_last_of(',');
                double grade1 = stod(lines[j].substr(pos1 + 1));
                double grade2 = stod(lines[j + 1].substr(pos2 + 1));
                if (grade1 > grade2) {
                    swap(lines[j], lines[j + 1]);
                }
            }
        }
        ofstream outFile("menu.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << lines[i] << endl;
            }
            outFile.close();
            cout << "Блюда отсортированы по цене." << endl;
        } else {
            cerr << "Не удалось открыть файл для записи." << endl;
        }
    } else {
        cerr << "Не удалось открыть файл для чтения." << endl;
    }
}

void dishesUnderTheCost(const double& underCost) {
    ifstream inFile("menu.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
        	size_t pos = line.find_last_of(',');
        	double cost = stod(line.substr(pos + 1));
            if (cost < underCost) {
                cout << line << endl;
            }
        }
        inFile.close();
    } else {
        cerr << "Не удалось открыть файл для чтения." << endl;
    }
}

int main() {
    int choice;
    string name;
    string fullName, type;
    double cost, underCost;
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
        cout << "3. Сортировать блюда по цене" <<endl;
        cout << "4. Сортировать блюда по типу" <<endl;
        cout << "5. Вывести блюда, цена которых не превышает определенного значения" <<endl;
        cout << "0. Выйти" << endl;
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
                sortDishesByCost();
                break;
            }
            case 4: {
            	sortDishesByType();
            	break;
            }
            case 5: {
                cout << "Введите цену: ";
                cin>>underCost;
                dishesUnderTheCost(underCost);
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
