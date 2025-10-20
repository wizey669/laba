#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
using namespace std;

struct Task {
    string name;
    int priority;
    Task* next;
};

class PriorityQueue {
private:
    Task* head;
    Task* tail;
    int size;

    Task* createTask(const string& name, int priority) {
        Task* newTask = new Task;
        newTask->name = name;
        newTask->priority = priority;
        newTask->next = nullptr;
        return newTask;
    }

public:
    PriorityQueue() : head(nullptr), tail(nullptr), size(0) {}

    ~PriorityQueue() {
        while (head != nullptr) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(const string& name, int priority) {
        Task* newTask = createTask(name, priority);

        if (head == nullptr || newTask->priority < head->priority) {
            newTask->next = head;
            head = newTask;
            if (tail == nullptr) {
                tail = newTask;
            }
        }
        else {
            Task* current = head;
            while (current->next != nullptr && current->next->priority <= newTask->priority) {
                current = current->next;
            }

            newTask->next = current->next;
            current->next = newTask;

            if (newTask->next == nullptr) {
                tail = newTask;
            }
        }
        size++;
    }

    void pop() {
        if (head == nullptr) {
            throw runtime_error("Очередь пуста");
        }

        Task* temp = head;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;
        size--;
    }

    Task top() const {
        if (head == nullptr) {
            throw runtime_error("Очередь пуста");
        }
        return *head;
    }

    bool empty() const { return head == nullptr; }

    int getSize() const { return size; }

    bool removeByPriority(int priority) {
        if (head == nullptr) {
            cout << "Очередь пуста.\n";
            return false;
        }

        bool found = false;
        Task* current = head;
        Task* prev = nullptr;

        while (current != nullptr) {
            if (current->priority == priority) {
                found = true;

                if (prev == nullptr) {
                    head = current->next;
                    delete current;
                    current = head;

                    if (head == nullptr) {
                        tail = nullptr;
                    }
                }
                else {
                    prev->next = current->next;

                    if (current == tail) {
                        tail = prev;
                    }

                    delete current;
                    current = prev->next;
                }
                size--;
            }
            else {
                prev = current;
                current = current->next;
            }
        }

        if (!found) {
            cout << "Задача с приоритетом " << priority << " не найдена.\n";
        }
        return found;
    }

    void printAll() const {
        if (head == nullptr) {
            cout << "Очередь пуста.\n";
            return;
        }

        cout << left << setw(25) << "Название задачи" << "Приоритет\n";
        cout << string(40, '-') << "\n";

        Task* current = head;
        while (current != nullptr) {
            cout << left << setw(25) << current->name << current->priority << "\n";
            current = current->next;
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    system("chcp 1251 > nul");
    PriorityQueue pq;
    int choice;



    do {
        cout << "\n=== Меню приоритетной очереди ===\n";
        cout << "1. Добавить задачу\n";
        cout << "2. Показать самую важную задачу\n";
        cout << "3. Удалить выполненную задачу (с наивысшим приоритетом)\n";
        cout << "4. Показать все задачи\n";
        cout << "5. Удалить задачу по определенному приоритету\n";
        cout << "6. Показать количество задач в очереди\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string name;
            int priority;

            cout << "Введите название задачи: ";
            getline(cin, name);
            cout << "Введите приоритет (чем меньше число, тем выше приоритет): ";
            cin >> priority;

            pq.push(name, priority);
            cout << "Задача добавлена!\n";
            break;
        }
        case 2:
            if (!pq.empty()) {
                Task top = pq.top();
                cout << "\nСамая важная задача:\n";
                cout << "Название: " << top.name << "\nПриоритет: " << top.priority << "\n";
            }
            else {
                cout << "Очередь пуста.\n";
            }
            break;
        case 3:
            if (!pq.empty()) {
                Task t = pq.top();
                pq.pop();
                cout << "Задача \"" << t.name << "\" с приоритетом " << t.priority << " выполнена и удалена.\n";
            }
            else {
                cout << "Очередь пуста.\n";
            }
            break;
        case 4:
            pq.printAll();
            break;
        case 5: {
            if (pq.empty()) {
                cout << "Очередь пуста.\n";
                break;
            }
            int priority;
            cout << "Введите приоритет для удаления: ";
            cin >> priority;

            if (pq.removeByPriority(priority)) {
                cout << "Все задачи с приоритетом " << priority << " удалены.\n";
            }
            break;
        }
        case 6:
            cout << "Количество задач в очереди: " << pq.getSize() << "\n";
            break;
        case 0:
            cout << "Выход из программы...\n";
            break;
        default:
            cout << "Неверный выбор. Повторите ввод.\n";
        }

    } while (choice != 0);

    return 0;
}
