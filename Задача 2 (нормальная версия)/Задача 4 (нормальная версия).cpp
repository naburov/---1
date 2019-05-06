// Задача 2 (нормальная версия).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <string>
#include <iostream>

using namespace std;

//Сумма двоично-десятичных чисел
int main()
{
	static string A, B, result, reverse_result;
	static int lenA, lenB, difference, count = 4;
	static bool is_negative, is_CF;

	setlocale(LC_ALL, "RUS");				// Установить Русский язык в консоли
	printf("Введите первое число:\n");		// Ввод чисел 
	getline(cin, A);
	printf("Введите второе число: \n");
	getline(cin, B);

	if (A.size() < B.size())				// Длина числа А всегда больше длины числа В
		swap(A, B);

	lenA = A.size();						// Запоминаем длины чисел
	lenB = B.size();

	__asm {
	__START:push eax;
		push ebx;
		push ecx;
		push edx;
		push edi;

		xor eax, eax;
		xor ebx, ebx;
		xor ecx, ecx;
		xor edx, edx;
		xor edi, edi;

	DIFFERENCE:mov eax, lenA;
		mov ebx, lenB;
		sub eax, ebx;
		mov difference, eax;

		xor eax, eax;
		xor ebx, ebx;

		lea esi, [A];
		lea edi, [B];

		add esi, 4;
		add edi, 4;

		clc;
		mov ecx, lenB;
	SUM_BOTH: add ecx, difference;
		dec ecx;						// Для удобства адресации
		mov al, [esi + ecx];			// Загрузили цифру первого числа
		sub al, 48;
		aaa;

		add al, is_CF;
		mov is_CF, 0;

		sub ecx, difference;
		mov bl, [edi + ecx];			// Загрузили цифру второго числа
		sub bl, 48;
		aaa;

		adc al, bl;
		aaa;
		jnc OUTPUT;
		mov is_CF, 1;

	OUTPUT: add al, 48;
		mov ebx, count;
		mov[result + ebx], al;			// Запись результата
		inc count;
		inc ecx;
		loop SUM_BOTH;

		xor eax, eax;
		xor ebx, ebx;
		mov ecx, difference;
		add al, is_CF;
		cmp al, 0;
		jne IS_CF;						// Осталась ли единица
		cmp difference, 0;				// Есть ли разница между числами в длине
		je _REVERSE_INIT;
		mov ecx, difference;
	LOOP_LBL:dec ecx;
		mov al, [esi + ecx];
		mov ebx, count;
		mov[result + ebx], al;			// Запись результата
		inc count;
		inc ecx;
		loop LOOP_LBL;
		jmp _REVERSE_INIT;

	IS_CF: cmp difference, 0;
		jne LOOP_LBL_DIFF;
		mov ebx, count;
		mov[result + ebx], 49;
		inc count;
		jmp _REVERSE_INIT;

		mov ecx, difference;
	LOOP_LBL_DIFF: mov al, 0;
		dec ecx;
		mov bl, [esi + ecx];
		add al, bl;
		add al, is_CF;
		aaa;
		jnc NO_OVERFLOW;
		mov is_CF, 1;
		jmp _OUTPUT_2;
	NO_OVERFLOW: mov is_CF, 0;
	_OUTPUT_2:mov ebx, count;
		add al, 48;
		mov[result + ebx], al;			//Запись результата
		inc count;
		inc ecx;
		xor eax, eax;
		loop LOOP_LBL_DIFF;
		cmp is_CF, 1;
		jne _REVERSE_INIT;
		mov ebx, count;
		add al, 48;
		mov[result + ebx], 49;
		inc count;

	_REVERSE_INIT:
		xor eax, eax;
		add eax, 4;
		mov ecx, count;
	LOOP_LBL_REVERSE: dec ecx;
		mov bl, [result + ecx];
		mov[reverse_result + eax], bl;
		inc eax;
		inc ecx;
		dec ecx;
		cmp ecx, 4;
		jne LOOP_LBL_REVERSE;

		pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}
	printf(reverse_result.c_str());
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
