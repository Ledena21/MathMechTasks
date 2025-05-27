//main.cpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "queue.h"

const int MIN_PER_HR = 60;

bool newcustomer(double x);

int main() {
    using std::cin;
    using std::cout;
    using std::endl;

    std::srand(std::time(0));

    cout << "Case Study: Bank of Heather Automatic Teller\n";
    cout << "Enter maximum size of queue: ";
    int qs;
    cin >> qs;

    Queue line1(qs);
    Queue line2(qs);

    cout << "Enter the number of simulation hours: ";
    int hours;
    cin >> hours;

    long cyclelimit = MIN_PER_HR * hours;

    cout << "Enter the average number of customers per hour: ";
    double perhour;
    cin >> perhour;
    double min_per_cust = MIN_PER_HR / perhour;

    Item temp;
    long turnaways = 0;
    long customers = 0;
    long served = 0;
    long sum_line = 0;
    int wait_time1 = 0;
    int wait_time2 = 0;
    long line_wait = 0;

    for (long cycle = 0; cycle < cyclelimit; cycle++) {
        if (newcustomer(min_per_cust)) {
            if (line1.isfull() && line2.isfull())
                turnaways++;
            else {
                customers++;
                temp.set(cycle);
                if (line1.queuecount() <= line2.queuecount())
                    line1.enqueue(temp);
                else
                    line2.enqueue(temp);
            }
        }

        if (wait_time1 <= 0 && !line1.isempty()) {
            line1.dequeue(temp);
            wait_time1 = temp.ptime();
            line_wait += cycle - temp.when();
            served++;
        }

        if (wait_time2 <= 0 && !line2.isempty()) {
            line2.dequeue(temp);
            wait_time2 = temp.ptime();
            line_wait += cycle - temp.when();
            served++;
        }

        if (wait_time1 > 0) wait_time1--;
        if (wait_time2 > 0) wait_time2--;

        sum_line += line1.queuecount() + line2.queuecount();
    }

    if (customers > 0) {
        cout << "customers accepted: " << customers << endl;
        cout << "  customers served: " << served << endl;
        cout << "         turnaways: " << turnaways << endl;
        cout << "average queue size: ";
        cout.precision(2);
        cout << (double)sum_line / cyclelimit << endl;
        cout << " average wait time: "
            << (double)line_wait / served << " minutes\n";
    }
    else {
        cout << "No customers!\n";
    }

    cout << "Done!\n";
    return 0;
}

bool newcustomer(double x) {
    return (std::rand() * x / RAND_MAX < 1);
}


// queue.h

#ifndef QUEUE_H__
#define QUEUE_H__

#include <cstdlib> // для rand()

class Customer {
private:
    long arrive;     //момент появления клиента
    int processtime; //время обслуживания клиента
public:
    Customer() { arrive = processtime = 0; } //инициализирует arrive и processtime нулями
    void set(long when); //устанавливает время прибытия (arrive = when)
    long when() const { return arrive; } //возвращает время прибытия
    int ptime() const { return processtime; } //возвращает время обслуживания
};

typedef Customer Item;

class Queue {
private:
    struct Node { Item item; Node* next; };
    enum { Q_SIZE = 10 };
    Node* front;     // указатель на начало очереди
    Node* rear;      // указатель на конец очереди
    int items;       // текущее количество элементов
    const int qsize; // максимальный размер очереди
    Queue(const Queue& q) : qsize(0) {}
    Queue& operator=(const Queue& q) { return *this; }
public:
    Queue(int qs = Q_SIZE); // конструктор
    ~Queue();               // деструктор
    bool isempty() const;   // проверка на пустоту
    bool isfull() const;    // проверка на заполненность
    int queuecount() const; // текущее количество элементов
    bool enqueue(const Item& item); // добавить в конец очереди
    bool dequeue(Item& item);       // удалить из начала очереди
};

#endif


//queue.cpp

#include "queue.h"
#include <cstdlib>

Queue::Queue(int qs) : qsize(qs) {
    front = rear = nullptr; //изначально очередь пуста
    items = 0; //счетчик элементов в очереди
}

Queue::~Queue() { 
    Node* temp; 
    while (front != nullptr) {
        temp = front; //запоминаем текущий первый элемент
        front = front->next; //перемещаем указатель на следующий элемент
        delete temp; //удаляем запомненный элемент
    }
}

bool Queue::isempty() const {
    return items == 0;
}

bool Queue::isfull() const {
    return items == qsize;
}

int Queue::queuecount() const {
    return items;
}

bool Queue::enqueue(const Item& item) {
    if (isfull())
        return false;
    Node* add = new Node; //создаём новый узел
    add->item = item; //записываем данные
    add->next = nullptr; //это будет последний элемент
    items++; //увеличиваем счётчик элементов
    if (front == nullptr) //если очередь пуста
        front = add;  //новый элемент становится первым
    else
        rear->next = add; //иначе добавляем после последнего элемента
    rear = add; //обновляем указатель на конец очереди
    return true; //успешное добавление
}

bool Queue::dequeue(Item& item) {
    if (front == nullptr)
        return false; //очередь пуста
    item = front->item; //извлекаем данные первого элемента
    items--;  //уменьшаем счётчик
    Node* temp = front; //запоминаем первый элемент
    front = front->next; //сдвигаем указатель на следующий элемент
    delete temp; //удаляем старый первый элемент
    if (items == 0) //если очередь опустела
        rear = nullptr; //обнуляем указатель на конец
    return true;         //успешное извлечение
}

void Customer::set(long when) {
    processtime = std::rand() % 3 + 1;// случайное время обслуживания: 1, 2 или 3
    arrive = when; // фиксируем время прибытия
}
