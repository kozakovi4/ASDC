// ASDC.Lab4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

/// <summary>
/// Выводит на экран таблицу, содержащую все элементы матрицы и их индексы.
/// </summary>
void ShowTable(matrix4<CITIZEN>& matrix);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	FILE* f = fopen("citizens.min.bin", "rb");

	// Считываем количество записей CITIZEN
	int count;
	fread(&count, sizeof(int), 1, f);

	// Считываем записи CITIZEN в массив
	CITIZEN* items = new CITIZEN[count];
	for (size_t i = 0; i < count; i++)
		items[i] = CITIZEN(f);
	fclose(f);

	// Так надо, чтобы обращаться к виртуальным член-функциям класса
	matrix4<CITIZEN>* m = new ilmatrix4<CITIZEN>(1, 3, 0, 2, -3, -1, 4, 7, items, count);
	ShowTable(*m);
	getchar();
    return 0;
}

void ShowTable(matrix4<CITIZEN>& matrix)
{
	printf("%-2s %-2s %-2s %-2s %-13s %-12s %-15s %-10s %-6s\n\n","i1","i2","i3","i4","PIN","FirstName","LastName","Birth","Gender");
	for (int i1 = matrix.getLowerBound(1); i1 <= matrix.getUpperBound(1); i1++)
		for (int i2 = matrix.getLowerBound(2); i2 <= matrix.getUpperBound(2); i2++)
			for (int i3 = matrix.getLowerBound(3); i3 <= matrix.getUpperBound(3); i3++)
				for (int i4 = matrix.getLowerBound(4); i4 <= matrix.getUpperBound(4); i4++)
				{
					CITIZEN& item = matrix.at(i1, i2, i3, i4);
					printf("%2d %2d %2d %2d %13lld %-12s %-15s %02d.%02d.%4d %-6s\n", i1, i2, i3, i4, item.pin, item.first_name, item.last_name, item.birth.tm_mday, item.birth.tm_mon, item.birth.tm_year, item.gender == GENDER::MALE ? "Male" : "Female");
				}
	printf("\nСложений: %d   Умножений: %d", matrix.getAddCount() * matrix.getLength(), matrix.getMulCount() * matrix.getLength());
}
