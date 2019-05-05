// Задача 4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

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

	static char result[255];

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

		dec edi;

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

		mov eax, lenA;
		cmp eax, lenB;				//Сравниваем длины строк, чтобы понять, в каком числе цифр больше
		jl FIRST_LESS;				//Если во втором числе цифр меньше
		mov is_first_more, 1;		//Если во втором числе цифр больше, то
		mov ecx, lenB;				//Записываем счетчик цикла
		mov eax, lenA;				//Для вычисления разницы двух чисел
		jmp _START;

	FIRST_LESS:
		mov ecx, lenA;
		mov eax, lenB;


	_START: sub eax, ecx;
		mov difference, eax;


	LOOP_LBL: push eax;
		push ebx;
		push edx;

		xor eax, eax;
		xor ebx, ebx;
		xor edx, edx;

		mov esi, difference;
		dec esi;
		add esi, ecx;

		cmp is_first_more, 1;
		jne SECOND_MORE_1;
		mov al, a[esi];						//Берем первую цифру;
		mov bl, b[ecx - 1];					//Берем вторую цифру
		jmp CONT;
	SECOND_MORE_1: mov al, a[ecx - 1];
		mov bl, b[esi];

	CONT:sub al, 48;							//Переход к целым числам от кодов аски
		sub bl, 48;
		add al, bl;							//Сложение
		add al, remainder;

		mov remainder, 0;					//Обнуление разряда, котороый не переносим

		cmp al, 10;							//Проверка на переход через десяток
		jl WRITE;
		mov remainder, 1;					//Если перешли

	WRITE: mov ebx, 10;
		div ebx;
		mov esi, _offset;					//Запись результата
		mov[result + esi], dl;
		add[result + esi], 48;
		inc _offset;
		loop LOOP_LBL;

		cmp difference, 0;
		je ADD_REMAINDER;
		cmp is_first_more, 1;				//После окончания цикла, если в первом числе больше цифр
		mov ecx, difference;				//Чтобы дозаписать цифры из большего числа
		jne SECOND_MORE;
	LOOP_LBL_WRITE: mov al, a[ecx - 1];
		sub al, 48;
		add al, remainder;
		mov remainder, 0;
		cmp al, 10;
		jne NOT_MORE_THAN_10;
		mov remainder, 1;
	NOT_MORE_THAN_10: xor edx, edx;
		mov ebx, 10;			//Получение последней цифры
		div ebx;
		mov esi, _offset;
		mov[result + esi], dl;
		add[result + esi], 48;
		inc _offset;
		loop LOOP_LBL_WRITE;

		jmp ADD_REMAINDER;

	SECOND_MORE:mov al, b[ecx - 1];
		sub al, 48;
		add al, remainder;
		mov remainder, 0;
		cmp al, 10;
		je NOT_MORE_THAN_10_2;
		mov remainder, 1;
	NOT_MORE_THAN_10_2: xor edx, edx;
		mov ebx, 10;			//Получение последней цифры
		div ebx;
		mov esi, _offset;
		mov[result + esi], dl;
		add[result + esi], 48;
		inc _offset;
		loop SECOND_MORE;

	ADD_REMAINDER:cmp remainder, 1;
		jne INIT_REVERSE;
		mov esi, _offset;
		mov[result + esi], 49;

		mov ecx, 100;
	INIT_REVERSE:mov al, 0;
		mov edi, -1;
	REVERSE: inc edi;
		cmp al, result[edi];
		jne REVERSE;


		mov eax, -1;
	START:
		dec edi;
		inc eax;
		cmp edi, eax;
		jl _END;
		mov cl, result[eax];
		mov ch, result[edi];
		mov result[eax], ch;
		mov result[edi], cl;
		mov ebx, eax;
		cmp eax, edi;
		jl START;


	_END: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}

	for (int i = 0; i < sizeof(result); i++)
		cout << result[i];


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
