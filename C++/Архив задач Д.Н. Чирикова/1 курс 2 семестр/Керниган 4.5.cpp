//calc.h

#define NUMBER '0'
/*когда функция getop() встречает число, она возвращает NUMBER*/

void push(double); //добавляет число в стек
double pop(void); //извлекает число из стека
int getop(char[]); //принимает массив char[]
int getch(void); //получает следующий символ, сначала проверяет буфер, потом getchar()
void ungetch(int); //возвращает символ в буфер ввода, позволяет "заглянуть" на символ вперёд


//getch.cpp

#include <stdio.h>
#define BUFSIZE 100 //максимальный размер буфера

char buf[BUFSIZE]; /* буфер для ungetch, массив символов, куда складываем символы, которые нужно вернуть в поток ввода */
int bufp = 0; /* след, свободная позиция в буфере, когда буфер пуст, равна 0 */

int getch(void){ /* взять (возможно возвращенный) символ */
	return (bufp > 0) ? buf[--bufp] : getchar();
	/* если в буфере есть символы (bufp>0), возвращаем символ с позиции bufp и уменьшаем bufp на 1*/
}

void ungetch(int c){ /* вернуть символ на ввод */
	if (bufp >= BUFSIZE) { //если буфер переполнен, выводим сообщение об ошибке.
		printf("ungetch: too many chars\n");
	}
	else {
		buf[bufp++] = c; //есть место, после последнего символа кладем символ c в буфер
	}
}


//stack.cpp

#include <stdio.h>
#include "calc.h"
#define MAXVAL 100 /* максимальная глубина стека */

int sp = 0; /* следующая свободная позиция в стеке */
double val[MAXVAL]; /* стек */

/* push: положить значение f в стек */
void push(double f) {
	if (sp < MAXVAL) { //если есть место в стеке
		val[sp++] = f; //кладём f в стек и увеличиваем sp
	}
	else {
		printf("ошибка: стек полон, %g не помещается", f);
	}
}

/* pop: взять с вершины стека и выдать в качестве результата */
double pop(void) {
	if (sp > 0) //если стек не пуст
		return val[--sp]; //возвращаем последнее значение и уменьшаем указатель на верхушку стека
	else {
		printf("Error: stack is empty");
		return 0.0;
	}
}


//getop.cpp

#include <ctype.h> // для isdigit, isalpha
#include <stdio.h>
#include <string.h>
#include "calc.h"

int getch(void);
void ungetch(int);

int getop(char s[]) {
	int i, c; //i индекс в строке s, c текущий символ
	while (true) {
		c = getch(); //получаем символ
		s[0] = c; //записываем в s[0]
		if (c != ' ' && c != '\t') {  //если не пробел и не таб
			break; //выходим из цикла
		}
	}
	s[1] = '\0'; //завершаем строку

	if (!isdigit(c) && c != '.' && c != '-') { //если не цифра, не точка и не минус
		i = 0; //начинаем запись в строку s с индекса 0.
		if (isalpha(c)){ //если это буква
			while (isalpha(s[++i] = c = getch()));  //пока символы буквенные
			s[i] = '\0'; //завершаем строку
			ungetch(c); //возвращаем последний прочитанный символ (не буквенный) в буфер.
			if (strcmp(s, "sin") == 0){ //пришел синус, вызываем команду для синуса
				return 's';
			}
			if (strcmp(s, "e") == 0){
				return 'e';
			}
			if (strcmp(s, "^") == 0){
				return '^';
			} 
			if (strcmp(s, "q") == 0) {
				return 'q';
			} 
		}
		return c; /* не число и не команда возвращается назад */
	}
	i = 0; //начинаем записывать число с начала строки s
	if (c == '-') { //если это минус
		if (isdigit(c = getch()) || c == '.') { //если это цифра или точка
			s[++i] = c; //это часть отрицательного числа, сохраняем символ
		}
		else { //иначе это оператор вычитания
			ungetch(c); //убираем c
			return '-'; //возвращаем символ -
		}
	}
	if (isdigit(c)) /* если текущий символ цифра, в цикле читаем и сохраняем все последующие цифры
		записываем их в массив s, увеличивая индекс i */
		while (isdigit(s[++i] = c = getch()));
	if (c == '.') /* накапливаем дробную часть */
		while (isdigit(s[++i] = c = getch()));
	s[i] = '\0'; //присоединяем нуль-терминатор в конец строки

	if (c != EOF){ //если прочитанный символ не конец файла
		ungetch(c); //возвращаем его обратно в буфер ввода, так как он принадлежит уже следующей операции
	}
	return NUMBER;
}


//main.cpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "calc.h"
#define MAXOP 100

int main() {
    
    int type; //тип текущей операции
    double op1, op2; //операнды для операций
    char s[MAXOP]; //буфер для хранения чисел

    printf("Calculator (supports +, -, *, /, ^, e, sin)\n");
    printf("Enter the expression in reverse polish notation (type q to exit)\n");

    while ((type = getop(s)) != EOF) { //читаем операции до конца ввода
        switch (type) {
        case NUMBER:
            push(atof(s)); //преобразуем строку в double и кладём в стек
            break;
        case '+':
            push(pop() + pop()); //извлекаем 2 числа, складываем, результат в стек
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop(); //извлекаем второй операнд (делитель)
            if (op2 != 0.0) { //если он не ноль, делим
                push(pop() / op2);
            }
            else {
                printf("Error: division by zero\n");
            }
            break;
        case 's':
            push(sin(pop())); //извлекаем число, вычисляем синус, кладём результат
            break;
        case 'e':
            push(exp(pop())); //извлекаем число, вычисляем e^x, кладём результат
            break;
        case '^':
            op2 = pop();
            op1 = pop();
            if (op1 == 0.0 && op2 <= 0.0) {
                printf("Error: base 0 when degree <= 0\n"); //0^0 и 0^(-n) - математически неопределены
            }
            else {
                push(pow(op1, op2));
            } 
            break;
        case 'q':
            return 0;
        case '\n':
            printf("%.8g\n", pop()); //извлекаем и печатаем результат с точностью до 8 значащих цифр
            break;
        default:
            printf("Error: undefined operation % s \n", s);
            break;
        }
    }
    return 0;
}
