// Задача 2 (нормальная версия).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <string>
#include <iostream>

using namespace std;

//Разность двоично-десятичных чисел
int main()
{
	static string A, B, result, reverse_result;
	static int lenA, lenB, difference, count = 4;
	static bool is_negative, is_CF;

	setlocale(LC_ALL, "RUS");			// Установить Русский язык в консоли
	printf("Введите первое число:\n");	// Ввод чисел 
	getline(cin, A);
	printf("Введите второе число: \n");
	getline(cin, B);

	if (A.size() < B.size())				// Длина числа А всегда больше длины числа В
		swap(A, B);

	lenA = A.size();					// Запоминаем длины чисел
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
	SUB_BOTH: add ecx, difference;
		dec ecx;						//Для удобства адресации
		mov al, [esi + ecx];			// Загрузили цифру первого числа
		sub al, 48;
		aaa;

		sub al, is_CF;
		jc _SUB;
		mov is_CF, 0;

	_SUB:sub ecx, difference;
		mov bl, [edi + ecx];			//Загрузили цифру второго числа
		sub bl, 48;
		aaa;

		sbb al, bl;
		aas;
		jnc OUTPUT;
		mov is_CF, 1;

	OUTPUT: add al, 48;
		mov ebx, count;
		mov[result + ebx], al;			//Запись результата
		inc count;
		inc ecx;
		loop SUB_BOTH;

		mov ecx, difference;
		cmp is_CF, 0;
		je LBL_WRITE;
	LOOP_SUB_IS_CF:	dec ecx;
		mov al, [esi + ecx];
		sub al, 48;
		sbb al, is_CF;
		aas;
		jnc NO_OVERFLOW;
		mov is_CF, 1;
		jmp _OUTPUT_2;
	NO_OVERFLOW: mov is_CF, 0;
	_OUTPUT_2:add al, 48;
		mov ebx, count;
		mov[result + ebx], al;			//Запись результата
		inc count;
		cmp is_CF, 1;
		je LOOP_SUB_IS_CF;

		cmp ecx, 0;
		je _REVERSE_INIT;
	LBL_WRITE: 
		cmp difference,0;
		je _REVERSE_INIT;
		dec ecx;
		mov al, [esi + ecx];
		mov ebx, count;
		mov[result + ebx], al;
		inc count;
		inc ecx;
		loop LBL_WRITE;



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
