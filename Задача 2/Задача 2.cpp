// Задача 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

/* Если будет время допиши дополнительный код для отрицательных чисел
*/
const char MINUS = '-';

int main()
{
	//Перевод в двоичную
	setlocale(LC_ALL, "RUS");	//Установить Русский язык в консоли
	char stroka[] = "-900";
	const int l = sizeof(stroka)-1;			//длина строки
	char symb[] = { '\0' };
	static int number = 0;
	static bool is_negative = false;
	static bool is_word;
	char resDW[16] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };
	char resW[8] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };
	char count = 0;

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

		mov ecx, l;				// Запоминаем длину строки
		mov edi, 1;				// Степень 10

		//Отрицательное число или нет
		mov al, MINUS;
		cmp al, stroka[0];
		jne TO_10SS;
		mov is_negative, 1;

		//Перевод в 10СС
	TO_10SS: mov al, stroka[ecx - 1];	// Получение последней цифры-символа строки
		sub al, 48;						// Получение последней цифры-цифры
		mul edi;						// Умножение на 10 в степени
		add number, eax;				// Добавление к числу в десятичной СС

		mov eax, 10;					// Увеличение степени 10
		mul edi;
		mov edi, eax;

		xor eax, eax;					// Обнуление цифры
		dec ecx;
		mov bl, is_negative;
		cmp ecx, ebx
		jne TO_10SS;

		mov eax, number;
		cmp eax, 127;
		jg IS_NEGATIVE;
		mov is_word, 1;

	IS_NEGATIVE:mov al, 1;
		cmp al, is_negative;				// Проверка отрицательное число или нет
		jne INIT;							// Если число не отрицательное, то сразу же переходим к переписыванию бит
		xor edi, edi;
		mov ecx, 16;
	LOOP_IS_NEGATIVE: btc number, edi;		// Цикл перевода в отрицательное число в памяти
		inc edi;
		loop LOOP_IS_NEGATIVE;
		inc number;

	INIT: xor edi, edi;
		mov edi, 16;				// По умолчанию считаем, что у нас двойное слово. Максимум - 15 цифр
		mov ebx, 2;
	TO_2SS:
		xor edx, edx;
		mov eax, number;
		div ebx;					// Разделили число на 2
		mov resDW[edi - 1], dl;		// Записали остаток
		dec edi;					// Сдвинули индекс
		mov number, eax;			// Запомнили частное от деления
		inc count;
		cmp eax, 0;					// Пока в eax что-то есть - продолжаем делить
		jne TO_2SS;

		mov al, is_word;
		cmp al,1;
		jl _end;

		mov ecx, 8;
		mov edi, 15
	LOOP_LBL_WORD: mov al, resDW[edi];
		mov resW[edi-8], al;
		dec edi;
		loop LOOP_LBL_WORD;

	_end: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}

	if (is_word)
		for (int i = 0; i < sizeof(resW); i++)
			cout<<(int)resW[i];
	else 
		for (int i = 0; i < sizeof(resDW); i++)
			cout<<(int)resDW[i];
		
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
