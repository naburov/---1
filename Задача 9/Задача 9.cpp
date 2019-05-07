// Задача 9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include <iostream>
#include <string>
#include "Задача 9.h"

using namespace std;
int main()
{
	static int choice, count;

	setlocale(LC_ALL, "RUS");
	cout << "Выберите операцию над множеством" << endl;
	cout << "1) Объединение" << endl;
	cout << "2) Пересечение" << endl;
	cout << "3) Разность" << endl;
	cout << "4) Определение принадлежности множеству" << endl;
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		_union();
		break;
	case 2:
		_intersect();
		break;
	case 3:
		_substract();
		break;
	case 4:
		_find();
		break;
	default:
		break;
	}

}

void _union() {
	static const int N = 15, M = 6, RES = N + M;
	/*static int first[N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
		second[M] = {1,72,3,4,16,35}, result[N + M], count, added_count=0;
*/
	static int first[N], second[M], result[RES], count, added_count = 0;
	for (size_t i = 0; i < N; i++)
	{
		cout << "Введите член множества" << endl;
		scanf("%d", &first[i]);
	}
	cout << "Ввод первого множества завершен" << endl;

	for (size_t i = 0; i < M; i++)
	{
		cout << "Введите член множества" << endl;
		scanf("%d", &second[i]);
	}
	cout << "Ввод втрого множества завершен" << endl;

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

		mov ecx, N;
		lea esi, [first];
		lea edi, [result];

		rep movsd;						// Переписали элементы первого множества

		mov ecx, M;
	SECOND_ARR_LOOP:
		push ecx;
		push ebx;
		mov ebx, count;
		mov eax, [second + 4 * ebx];	// Запомнили символ, который ищем
		pop ebx;
		lea edi, [result];				// Загрузили цепочку, где ищем символ
		mov ecx, RES;					// Установили счетчик (кол-во элементов во результирующем массиве)
		repne scasd;					// Сканирование уже переписанных во множество элементов 
		je NEXT;						// Если такой элемент все же нашли, то переходим к следующему
		mov ebx, N;
		add ebx, added_count;
		sub ebx, ecx;
		mov[result + 4 * ebx], eax;
		inc added_count;
	NEXT: inc count;
		pop ecx;
		loop SECOND_ARR_LOOP;


	__END: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}

	for (size_t i = 0; i < N + added_count; i++)
	{
		cout << result[i];
		cout << ' ';
	}
}

void _intersect() {
	static const int N = 15, M = 6, RES = N + M;
	//static int first[N] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 },
	//	second[M] = { 100,72,500,900,16,35 }, result[N + M], count, added_count = 0;

	static int first[N], second[M], result[RES], count, added_count = 0;
	for (size_t i = 0; i < N; i++)
	{
		cout << "Введите член множества" << endl;
		scanf("%d", &first[i]);
	}
	cout << "Ввод первого множества завершен" << endl;

	for (size_t i = 0; i < M; i++)
	{
		cout << "Введите член множества" << endl;
		scanf("%d", &second[i]);
	}
	cout << "Ввод втрого множества завершен" << endl;

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

		mov ecx, N;
	LOOP_LBL:
		push ecx;
		push ebx;
		mov ebx, count;
		mov eax, [first + 4 * ebx];		// Запомнили символ, который ищем
		pop ebx;
		lea edi, [second];				// Загрузили цепочку, где ищем символ
		mov ecx, M;						// Установили счетчик (кол-во элементов во второй цепочке массиве)
		repne scasd;
		jne NEXT;
		mov ebx, added_count;
		mov[result + 4 * ebx], eax;
		inc added_count;
	NEXT: inc count;
		pop ecx;
		loop LOOP_LBL;



	__END: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}

	for (size_t i = 0; i < added_count; i++)
	{
		cout << result[i];
		cout << ' ';
	}
	if (added_count == 0)
		cout << "В множествах нет одинаковых элементов";
}

void _find() {
	static const int N = 15;
	static int arr[N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}, number;
	static bool is_belong = false;

	//static int first[N],second[M], result[RES], count, added_count=0;
	//for (size_t i = 0; i < N; i++)
	//{
	//	cout << "Введите член множества" << endl;
	//	scanf("%d", &arr[i]);
	//}
	//cout << "Ввод первого множества завершен"<<endl;

	cout << "Введите число для проверки на принадлежность множеству" << endl;
	scanf("%d", &number);

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

		mov ecx, N;
		mov eax, number;
		lea edi, [arr];
		repne scasd;
		jne _END;
		mov is_belong, 1;

	_END: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}

	if (is_belong)
		cout << "Элемент принадлежит множеству";
	else cout << "Элемент не принадлежит множеству";

}

void _substract() {
	static const int N = 15, M = 6, RES = N + M;
	static int first[N] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 },
		second[M] = { 1,2,3,4,5,6 }, count, added_count = 0, result[RES];

	//static int first[N],second[M], result[RES], count, added_count=0;
	//for (size_t i = 0; i < N; i++)
	//{
	//	cout << "Введите член множества" << endl;
	//	scanf("%d", &first[i]);
	//}
	//cout << "Ввод первого множества завершен"<<endl;

	//for (size_t i = 0; i < M; i++)
	//{
	//	cout << "Введите член множества" << endl;
	//	scanf("%d", &second[i]);
	//}
	//cout << "Ввод втрого множества завершен"<<endl;

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

		mov ecx, N;
	LOOP_LBL:
		push ecx;
		push ebx;
		mov ebx, count;
		mov eax, [first + 4 * ebx];	// Запомнили символ, который ищем
		pop ebx;
		lea edi, [second];				// Загрузили цепочку, где ищем символ
		mov ecx, M;					// Установили счетчик (кол-во элементов во второй цепочке массиве)
		repne scasd;
		je NEXT;
		mov ebx, added_count;
		mov[result + 4 * ebx], eax;
		inc added_count;
	NEXT: inc count;
		pop ecx;
		loop LOOP_LBL;



	__END: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}

	for (size_t i = 0; i < added_count; i++)
	{
		cout << result[i];
		cout << ' ';
	}

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
