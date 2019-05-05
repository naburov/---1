// Задача 7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include <iostream>
#include <string>
#include "Задача 7.h"

// Работает!
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	cout << "Выберите задачу для проверки" << endl;
	cout << "1) Заполнение массива значением, введенным с клавиатуры" << endl;
	cout << "2) Заполнение массива значениями из второго массива" << endl;
	cout << "3) Поиск первого заданного элемента" << endl;
	cout << "4) Поиск последнего элемента" << endl;
	cout << "5) Сравнение массивов на совпадение" << endl;
	cout << "6) Первое несовпадающее слева значение" << endl;
	cout << "7) Первое несовадающее справа значение" << endl;
	cout << "8) Поиск подстроки" << endl;

	int choice;
	scanf("%d", &choice);

	switch (choice) {
	case 1:
		write_one_number();
		break;
	case 2:
		write_array();
		break;
	case 3:
		search_first_number();
		break;
	case 4:
		search_last_number();
		break;
	case 5:
		compare_strings();
		break;
	case 6:
		find_symbol_left();
		break;
	case 7:
		find_symbol_right();
		break;
	case 8:
		find_substring();
		break;
	}

}

void NewFunction()
{
	cout << "Hello world!";
}

void write_one_number() {
	int N, number;
	static int arr[50];


	cout << "Введите число, которым нужно заполнить массив" << endl;
	scanf("%d", &number);

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

		lea edi, [arr];
		mov ecx, 50;
		mov eax, number;

		rep stosd;

	__END: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;

	}

	for (int i = 0; i < 50; i++) {
		cout << arr[i];
		cout << ' ';
	}

}

void write_array() {
	static const int N = 5, M = 25;
	static int first_array[N] = { 13,55,23,32,12 };
	static int result_array[M];
	int how_much = M / N;


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

		mov ecx, how_much;
		lea edi, [result_array];
	REPEAT_FIRST_ARRAY: push ecx;
		mov ecx, N;
		lea esi, [first_array];
		rep movsd;
		pop ecx;
		loop REPEAT_FIRST_ARRAY;


	__END: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}

	for (size_t i = 0; i < M; i++)
	{
		cout << result_array[i];
		cout << ' ';
	}
}

void search_last_number() {
	static const int N = 16;
	static int number, result;
	static int arr[N] = { 13,55,23,32,12,1,2,3,4,5,6,7,8,9,10,10 };

	cout << "Введите число, которое нужно найти в массиве" << endl;
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


		mov eax, number;
		mov ecx, N;
		add ecx, 2;				//На 1 больше, чем кол-во элементов массива
		std;
		lea edi, [arr + 4 * 16];
		repne scasd;
		mov result, ecx;
		cld;

	__END: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}
	cout << "Индекс в массиве (начиная с 1). Если 0 - значение не найдено" << endl;
	cout << result;
}

void search_first_number() {
	static const int N = 16;
	static int number, result;
	static int arr[N] = { 13,55,23,32,12,1,2,3,4,5,6,7,8,9,10,10 };

	cout << "Введите число, которое нужно найти в массиве" << endl;
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


		mov eax, number;
		mov ecx, N;
		add ecx, 2;				//На 1 больше, чем кол-во элементов массива
		cld;
		lea edi, [arr];
		repne scasd;

		mov eax, N;
		sub eax, ecx;
		add eax, 2;
		mov result, eax;



	__END: pop edi;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}
	cout << "Индекс в массиве (начиная с 1). Если N+2 - значение не найдено" << endl;
	cout << result;
}

void compare_strings() {
	static string first_string, second_string;
	static bool are_equal = true;
	static int len_first, len_second;

	setlocale(LC_ALL, "RUS");			// Установить Русский язык в консоли
	printf("Введите первую строку:\n");	// Ввод чисел 
	cin.ignore(256, '\n');
	getline(cin, first_string);


	printf("Введите вторую строку: \n");
	getline(cin, second_string);

	if (first_string.size() != second_string.size())
		are_equal = false;

	len_first = first_string.size();
	len_second = second_string.size();

	if (are_equal)
	{
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

			lea edi, [first_string];
			lea esi, [second_string];

			add edi, 4;
			add esi, 4;

			mov ecx, len_first;
			inc ecx;
			repe cmpsb;

			cmp ecx, 0;
			je _END;
			mov are_equal, 0;

		_END:pop edi;
			pop edx;
			pop ecx;
			pop ebx;
			pop eax;
		}
	}

	if (!are_equal)
		cout << "Не равны";
	else
		cout << "Равны";

}

void find_symbol_left() {
	static string first_string, second_string;
	static bool are_equal = true;
	static int len_first, len_second, index = -1, size_max;

	setlocale(LC_ALL, "RUS");			// Установить Русский язык в консоли
	printf("Введите первую строку:\n");	// Ввод чисел 
	cin.ignore(256, '\n');
	getline(cin, first_string);


	printf("Введите вторую строку: \n");
	getline(cin, second_string);

	len_first = first_string.size();
	len_second = second_string.size();

	if (len_first > len_second)
		size_max = len_first;
	else size_max = len_second;

	if (are_equal)
	{
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

			lea edi, [first_string];
			lea esi, [second_string];

			add edi, 4;
			add esi, 4;

			cld;
			mov ecx, size_max;
			inc ecx;
			repe cmpsb;

			je _END;
			mov eax, size_max;
			sub eax, ecx;
			mov index, eax;

		_END:pop edi;
			pop edx;
			pop ecx;
			pop ebx;
			pop eax;
		}
	}
	cout << "Индекс несовпадающего элемента (индексация с 0)";
	cout << index;
}

void find_symbol_right() {
	static string first_string, second_string;
	static bool are_equal = true;
	static int len_first, len_second, index = -1, size_max;

	setlocale(LC_ALL, "RUS");			// Установить Русский язык в консоли
	printf("Введите первую строку:\n");	// Ввод чисел 
	cin.ignore(256, '\n');
	getline(cin, first_string);


	printf("Введите вторую строку: \n");
	getline(cin, second_string);

	len_first = first_string.size();
	len_second = second_string.size();

	if (len_first > len_second)
		size_max = len_first;
	else size_max = len_second;



	if (are_equal)
	{
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

			mov eax, len_first;
			mov ebx, len_second;

			lea edi, [first_string + eax];
			lea esi, [second_string + ebx];

			xor eax, eax;
			xor ebx, ebx;

			add edi, 4;
			add esi, 4;

			std;
			mov ecx, size_max;
			inc ecx;
			repe cmpsb;

			je _END;
			mov eax, size_max;
			sub eax, ecx;
			mov index, ecx;


		_END:cld;
			pop edi;
			pop edx;
			pop ecx;
			pop ebx;
			pop eax;
		}
	}
	cout << "Индекс несовпадающего элемента (индексация с 1) c начала наиболее длинного массива \n";
	cout << index;
}

void find_substring() {
	static string base_string, substring;
	static bool is_found = true;
	static int len_base, len_sub, beg_index = -1;

	setlocale(LC_ALL, "RUS");			// Установить Русский язык в консоли
	printf("Введите строку, в котоой нужно произвести поиск:\n");	// Ввод чисел 
	cin.ignore(256, '\n');
	getline(cin, base_string);


	printf("Введите строку, которую нужно найти: \n");
	getline(cin, substring);

	len_base = base_string.size();
	len_sub = substring.size();

	if (len_base < len_sub)
		is_found = false;

	if (is_found) {
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


			mov ecx, len_base;
			inc ecx;
			//mov ecx, len_base;			// Если оставшаяся часть строки меньше подстроки, то смысла проверять не будеты 
			//sub ecx, len_sub;			// Количество символов исходной строки, которые нужно проверить

			lea edi, [base_string];		// Помещаем строки в регистры
			lea esi, [substring];

			add edi, 4;
			add esi, 4;

			mov al, [esi];

		OUTER_CYCLE:
			repne scasb;				// Ищем первый символ подстроки
			mov beg_index, ecx;			// Нашли первый символ - запомнили
			mov ebx, ecx;
			inc ecx;
			dec edi;
			repe cmpsb;					// Сравниваем строки;
			//je FOUND;

			sub ebx, ecx;				// Получаем пройденную разницу
			cmp ebx, len_sub;			// Если она равна длине подстроки, то все отлично
			je FOUND;
			mov beg_index, -1;
			mov is_found, 0;
			loop OUTER_CYCLE;

		FOUND:
			mov eax, len_base;
			sub eax, beg_index;
			mov beg_index, eax;
			jmp _END;
			loop OUTER_CYCLE;

		_END:cld;
			pop edi;
			pop edx;
			pop ecx;
			pop ebx;
			pop eax;

		}
	}

	if (is_found) {
		cout << "Строка найдена" << endl;
		cout << "Начальный индекс найденной подстроки:";
		cout << beg_index;
	}
	else
		cout << "Строка не найдена" << endl;
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
