// Задача 8 (шифрование).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include <iostream>
#include <string>
#include "Задача 8.h"

using namespace std;

int main()
{
	int choice;

	setlocale(LC_ALL, "RUS");
	cout << "Выберите операцию" << endl;
	cout << "1) Шифрование" << endl;
	cout << "2) Дешифрование" << endl;
	scanf("%d", &choice);

	switch (choice) {
	case  1:
		Encrypt();
		break;
	case 2:
		Decrypt();
		break;
	}
}

void Encrypt() {
	// Шифрование осуществляется шифром цезаря, смещенным на четыре.

	string base_string, result_string;
	int len;

	cout << "Введите строку для шифрования" << endl;
	cin.ignore(256, '\n');
	getline(cin, base_string);

	len = base_string.size();

	_asm {
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

		mov ecx, len;
		lea esi, [base_string];
		lea edi, [result_string];

		add esi, 4;
		add edi, 4;

		mov ecx, len;
	MOVE_NEXT: lodsb;
		add al, 4;
		stosb;
		loop MOVE_NEXT;

	__END: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}

	const char* res = result_string.c_str();
	for (int i = 0; i < len; i++)
		cout << res[i];

}

void Decrypt() {

	string base_string, result_string;
	int len;

	cout << "Введите строку для дешифрования" << endl;
	cin.ignore(256, '\n');
	getline(cin, base_string);


	len = base_string.size();
	_asm {
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

		mov ecx, len;
		lea esi, [base_string];
		lea edi, [result_string];

		add esi, 4;
		add edi, 4;

		mov ecx, len;
	MOVE_NEXT: lodsb;
		sub al, 4;
		stosb;
		loop MOVE_NEXT;

	__END: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}

	const char* res = result_string.c_str();
	for (int i = 0; i < len; i++)
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
