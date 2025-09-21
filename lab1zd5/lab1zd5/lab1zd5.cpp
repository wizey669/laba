#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct Student {
    string surname;
    string name;
    int age;
    string group;
};

struct Node {
    Student data;
    Node* next;
};


// Функция для вывода данных студента
void printStudent(const Student& s) {
    cout << "Фамилия: " << s.surname << endl;
    cout << "Имя: " << s.name << endl;
    cout << "Возраст: " << s.age << endl;
    cout << "Группа: " << s.group << endl;
    cout << "------------------------" << endl;
}

void append(Node*& head, const Student& s) {
    Node* newNode = new Node{ s, nullptr };
    if (!head) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next)
            current = current->next;
        current->next = newNode;
    }
}


void printAll(const Node* head) {
    const Node* current = head;
    int count = 0;
    while (current) {
        printStudent(current->data);
        current = current->next;
        count++;
    }
    if (count == 0)
        cout << "Список пуст.\n";
}

void findBySurname(const Node* head, const string& surname) {
    const Node* current = head;
    int found = 0;
    while (current) {
        if (current->data.surname == surname) {
            printStudent(current->data);
            found++;
        }
        current = current->next;
    }
    if (found == 0)
        cout << "Студенты с фамилией '" << surname << "' не найдены.\n";
}


void findByName(const Node* head, const string& name) {
    const Node* current = head;
    int found = 0;
    while (current) {
        if (current->data.name == name) {
            printStudent(current->data);
            found++;
        }
        current = current->next;
    }
    if (found == 0)
        cout << "Студенты с именем '" << name << "' не найдены.\n";
}


void findByAge(const Node* head, int age) {
    const Node* current = head;
    int found = 0;
    while (current) {
        if (current->data.age == age) {
            printStudent(current->data);
            found++;
        }
        current = current->next;
    }
    if (found == 0)
        cout << "Студенты возраста " << age << " не найдены.\n";
}

void findByGroup(const Node* head, const string& group) {
    const Node* current = head;
    int found = 0;
    while (current) {
        if (current->data.group == group) {
            printStudent(current->data);
            found++;
        }
        current = current->next;
    }
    if (found == 0)
        cout << "Студенты группы '" << group << "' не найдены.\n";
}

void deleteList(Node*& head) {
    while (head) {
        Node* temp = head ;
        head = head->next;
        delete temp;
    }
}

void deleteLastStudent(Node*& head) {
    Node* temp = head, *prev = NULL;
    int i = 0;
    int n;
    cin >> n;
    while (temp && i < n) {
        i++;
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        return;
    }
    if (head == temp) {
        head = temp->next;
    }
    else {
        if (prev) {
            prev->next = temp->next;
        }
    }
    free(temp);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Node* students = nullptr;

    
    append(students, { "Иванов", "Иван", 20, "ИТ-101" });
    append(students, { "Петров", "Петр", 21, "ИТ-101" });
    append(students, { "Сидорова", "Мария", 19, "ИТ-102" });
    append(students, { "Иванов", "Алексей", 20, "ИТ-102" });
    append(students, { "Кузнецова", "Елена", 22, "ИТ-101" });

    int choice;
    do {
        cout << "\n=== ПОИСК СТУДЕНТОВ ===" << endl;
        cout << "1. По фамилии" << endl;
        cout << "2. По имени" << endl;
        cout << "3. По возрасту" << endl;
        cout << "4. По группе" << endl;
        cout << "5. Показать всех студентов" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите вариант: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string surname;
            cout << "Введите фамилию: ";
            cin >> surname;
            findBySurname(students, surname);
            break;
        }
        case 2: {
            string name;
            cout << "Введите имя: ";
            cin >> name;
            findByName(students, name);
            break;
        }
        case 3: {
            int age;
            cout << "Введите возраст: ";
            cin >> age;
            findByAge(students, age);
            break;
        }
        case 4: {
            string group;
            cout << "Введите группу: ";
            cin >> group;
            findByGroup(students, group);
            break;
        }
        case 5: {
            printAll(students);
            break;
        }
        case 6:
        {
            string surname;
            string name;
            int age;
            string group;
            cout << "Enter surname" << endl;
            cin >> surname;
            cout << "Enter name" << endl;
            cin >> name;
            cout << "Enter age" << endl;
            cin >> age;
            cout << "Enter group" << endl;
            cin >> group;
            append(students, { surname,name,age,group });
            break;
        }
        case 7: {
            deleteLastStudent(students);
        }
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);

    deleteList(students); 
    return 0;
}
