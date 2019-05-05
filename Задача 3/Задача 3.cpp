// Задача 3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

const char MINUS = '-';

using namespace std;
int main()
{
	//Перевод в десятичную 
	setlocale(LC_ALL, "RUS");	//Установить Русский язык в консоли
	char stroka[] = "111101000010010000000";
	int len = sizeof(stroka) - 1;
	unsigned int number = 0;;
	bool is_negative = 0;
	static char res[14];
	static int rankCount = 0;

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

		mov edi, 1;						//Запоминаем текущую степень 2-ки
		mov ecx, len;					//Запоминаем длину строки

		//Отрицательное число или нет
		mov al, MINUS;
		cmp al, stroka[0];
		jne TO_10SS;
		mov is_negative, 1;

	TO_10SS: mov al, stroka[ecx - 1];
		sub al, 48;					//Получение последней цифры-цифры
		mul edi;					//Умножение на 2 в степени
		add number, eax;

		mov eax, 2;					//увеличение 2-ки
		mul edi;
		mov edi, eax;

		xor eax, eax;				//Обнуление цифры
		dec ecx;
		mov bl, is_negative;
		cmp ecx, ebx;
		jne TO_10SS;

		mov ecx, 14;
		mov edi, 10;


	TO_CHAR_ARRAY: xor edx, edx;
		mov eax, number;
		div edi;
		mov number, eax;

		cmp ecx, 14;
		je WRITE_LBL;

	WRITE_SPACES: push edx;				//Запись пробелов в итоговое число
		push eax;
		push ebx;

		xor edx, edx;
		xor eax, eax;
		xor ebx, ebx;

		cmp rankCount, 3;
		jne CONT_LBL;
		mov res[ecx - 1], ' ';
		dec ecx;
		mov rankCount,0;

	CONT_LBL: pop ebx;
		pop eax;
		pop edx;

		push eax;

	WRITE_LBL:add dl, 48;
		mov res[ecx - 1], dl;		//запись цифры в массив

		pop eax;

		inc rankCount;
		dec ecx;
		cmp eax, 0;
		jne TO_CHAR_ARRAY;

		mov al, is_negative;
		cmp al, 1;
		jne _END;
		mov res[ecx - 1], '-';

	_END: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}

	for (int i = 0; i < sizeof(res); i++)
		cout << res[i];
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
