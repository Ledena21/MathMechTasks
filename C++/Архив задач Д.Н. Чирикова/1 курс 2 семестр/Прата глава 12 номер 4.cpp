//stack.h

#pragma once
#ifndef STACK_H
#define STACK_H
#include <iostream>

typedef unsigned long Item;

class Stack {
	enum { MAX = 10 }; // макс размер стека
	Item* pitems; // указатель на массив элемнтов
	int size; // вместимость стека
	int top; // индекс вершины стека
public:
	Stack(int n = 10);
	Stack(const Stack& st); // констуктор копирования
	~Stack();
	bool isempty() const; // проверка на пустоту
	bool isfull() const; // проверка на переполнение
	bool push(const Item& item);
	bool pop(Item& item);
	Stack& operator=(const Stack& st); // оператор присваивания
};

#endif //STACK_H


//stack.cpp

#include <iostream>
#include "stack.h" // <--

Stack::Stack(int n) {
    top = 0; // вершина стека
    size = n > MAX ? MAX : n; // рзмер стека
    pitems = new Item[size]; // выделяекм память под массив эл-ов
}

Stack::Stack(const Stack& st) { // констр копирования
    size = st.size; // копируем размер
    top = st.top; // копируем индекс вершины
    pitems = new Item[size]; // выделяем новый массим
    for (int i = 0; i < size; i++) {
        pitems[i] = st.pitems[i]; // копируем э
    }
}

Stack::~Stack() {
    delete[] pitems;
}

bool Stack::isempty() const {
    return top == 0;
} // если стек пуст
bool Stack::isfull() const {
    return top == size;
}
bool Stack::push(const Item& item) {
    if (top < size) { // если есть место добавим 
        pitems[top++] = item;
        return true;
    }
    else
        return false;
}
bool Stack::pop(Item& item) {
    if (top > 0) {
        item = pitems[--top];
        return true;
    }
    else
        return false;
}

Stack& Stack::operator=(const Stack& st) { // оператор присваивания
    if (this != &st) { // защита от самоприсваивания 
        delete[] pitems; // удаляем старый массив
        top = st.top; // копируем индекс вершины
        size = st.size; // комируем размер
        pitems = new Item[size]; // выделяем новый массив
        for (int i = 0; i < size; i++) {
            pitems[i] = st.pitems[i]; // комируемп
        }
    }
    return *this; // вернем ссылку на текущий объекст
}


//main.cpp

#include <iostream>
#include "stack.h" // <--

using namespace std;

int main() {
	Stack st(5); // создаем стек размером 5
	Item item; // переменная для извлечения эл-ов
	st.push(10);
	st.push(20);
	st.push(30);
	st.push(40);
	st.push(50);
	st.push(60);
	cout << st.pop(item) << ", " << item << endl;
	cout << st.pop(item) << ", " << item << endl;
	cout << st.pop(item) << ", " << item << endl;
	cout << st.pop(item) << ", " << item << endl;
	cout << st.pop(item) << ", " << item << endl;
	cout << st.pop(item) << ", " << item << endl;
	Stack st2(5);
	st2.push(100);
	st2.push(200);
	st2.push(300);
	st2.push(400);
	st2.push(500);
	st2.push(600);
	Stack st3(st2);
	st = st3;
	cout << st.pop(item) << ", " << item << endl;
	cout << st.pop(item) << ", " << item << endl;
	cout << st.pop(item) << ", " << item << endl;
	cout << st.pop(item) << ", " << item << endl;
	cout << st.pop(item) << ", " << item << endl;
	cout << st.pop(item) << ", " << item << endl;
}
