// Задача 4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <iostream>
#include <string>

using namespace std;
const char MINUS = '-';

int main()
{
	setlocale(LC_ALL, "RUS");

	char a[255], b[255];
	cout << "Введите первое число:" << endl;
	cin.getline(a, 255);

	cout << "Введите второе число:" << endl;
	cin.getline(b, 255);



	static int lenA = sizeof(a);
	static int lenB = sizeof(b);
	bool is_first_more = false;					//Если в первом числе больше разрядов
	static int difference = 0;					//Разница в количестве разрядов
	static bool remainder = 0;					//Для переноса в следующий разряд
	static int _offset = 0;

	static bool is_first_negative = false;
	static bool is_second_negative = false;

	static char result;

	__asm {
		push eax;
		push ebx;
		push ecx;
		push edx;
		push edi;

		xor eax, eax;
		xor ebx, ebx;
		xor ecx, ecx;
		xor edx, edx;
		xor edi, edi;

	IS_FIRST_NEGATIVE:mov al, MINUS;				//Проверяем, являются ли числа отрициательными
		cmp al, a[0];
		jne IS_SECOND_NEGATIVE;
		mov is_first_negative, 1;
	IS_SECOND_NEGATIVE: cmp al, b[0];
		jne COMPARE_SIGNES;
		mov is_second_negative, 1;

	COMPARE_SIGNES: mov al, is_first_negative;
		cmp al, is_second_negative;
		je INIT_LEN_COUNT;
		cmp eax, 1;
		je SECOND_MORE;
	FIRST_MORE:mov result, 62;
		jmp _END;
	SECOND_MORE: mov result, 60;
		jmp _END;

	INIT_LEN_COUNT: dec edi;
		xor eax, eax;
		//В al всегда будет 0
		//Подсчет длины первой строки
	A_LEN_LOOP: inc edi;
		mov bl, a[edi];
		cmp bl, al;
		jne A_LEN_LOOP;
		mov lenA, edi;

		mov edi, -1;

		//Подсчет длины второй строки
	B_LEN_LOOP: inc edi;
		mov bl, b[edi];
		cmp bl, al;
		jne B_LEN_LOOP;
		mov lenB, edi;

		mov eax, lenA;				// Записали в регистр длину первого числа
		cmp is_first_negative, 1;	// Отрицательные ли числа
		je CMP_NEGATIVE;			// Если числа отрицательные - сравниваем соответственно
		cmp eax, lenB;				// Сравнение длин, если числа положительные
		je CMP_EQUAL_LEN;
		jg FIRST_MORE;
		jmp SECOND_MORE;
	CMP_NEGATIVE: cmp eax, lenB;	// Сравнение длин, если оба числа отрицательные
		je CMP_EQUAL_LEN;
		jg SECOND_MORE;
		jmp FIRST_MORE;

	CMP_EQUAL_LEN:xor edi, edi;
		mov di, word ptr[is_first_negative];
		dec edi;
		mov ecx, lenB;
		sub cl, is_first_negative;
	LOOP_LBL: push eax;
		push ebx;
		push edx;

		xor eax, eax;
		xor ebx, ebx;
		xor edx, edx;

		inc edi;
		cmp ecx, edi;
		je EQUAL;

		mov al, a[edi];				//Получаем первые цифры-буквы
		mov bl, b[edi];
		sub al, 48;					//Первые цифры-цифры
		sub bl, 48;
		cmp is_first_negative, 1;
		je CMP_NEGATIVE_NUMB;

	CMP_POSITIVE_NUMB: cmp al, bl;
		je LOOP_LBL;
		jg FIRST_MORE;
		jmp SECOND_MORE;
	CMP_NEGATIVE_NUMB: cmp al, bl;
		je LOOP_LBL;
		jg SECOND_MORE;
		jmp FIRST_MORE;

	EQUAL: mov result, 61;
	_END: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}

	cout << result;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
