#define _CRT_SECURE_NO_WARNINGS 
#include "Main.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		int countThreads = atoi(argv[1]); // преобразовать строковый аргумент в int 
		if (countThreads > 0 && countThreads <= MAX_COUNT_THREADS)
		{
			// создать массив 
			// генерируем числа в каждом массиве
			int** arrOfArraysForNewThread;
			arrOfArraysForNewThread = (int**)malloc(sizeof(int**) * countThreads);

			for (int i = 0; i < countThreads; i++)
			{
				arrOfArraysForNewThread[i] = (int*)malloc(sizeof(int) * ARRAY_SIZE);
				GenereteArrayNums(arrOfArraysForNewThread[i]);
			}

			InitializeCriticalSection(&gCriticalSection);
			gdwTlsIndex = TlsAlloc();
			threadHandles = (HANDLE*)malloc(sizeof(HANDLE) * countThreads);
			DWORD* dwThreadsID = (DWORD*)malloc(sizeof(DWORD) * countThreads);

			for (int i = 0; i < countThreads; i++) // создаем новые потоки
			{
				threadHandles[i] = CreateThread(NULL,
					NULL,
					StartNewThread,
					arrOfArraysForNewThread[i],
					NULL,
					&dwThreadsID[i]);
			}
			WaitForMultipleObjects(countThreads, threadHandles, TRUE, INFINITE);

		}
	}
	else
	{
		cout << "Wrong count of arguments\n";
	}
}

DWORD WINAPI StartNewThread(LPVOID param)
{
	EnterCriticalSection(&gCriticalSection);
	int maxDivisors[ARRAY_SIZE] = { 1 };
	TlsSetValue(gdwTlsIndex, maxDivisors);

	cout << "---------------------------------------------\n";
	cout << "Thread ID:" << GetCurrentThreadId() << endl;
	cout << "Generated array:";
	PrintArrayToStdout((int*)param, ARRAY_SIZE);
	cout << endl;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		maxDivisors[i] = CalcLargestDivisor(((int*)param)[i]);
	}
	cout << "Max divisors:   ";
	PrintArrayToStdout((int*)TlsGetValue(gdwTlsIndex), ARRAY_SIZE);
	cout << endl;
	cout << "Numbers sum:" << ArrNumsSum((int*)param) << endl;
	cout << "---------------------------------------------\n";
	LeaveCriticalSection(&gCriticalSection);
	return 0;
}

void PrintArrayToStdout(int* array, int lenght)
{
	for (int i = 0; i < lenght; i++)
		cout << " " << array[i] << " ";
}

void GenereteArrayNums(int* arr)
{
	int randRange = ARRAY_NUM_MAX_BOUNDARY - ARRAY_NUM_MIN_BOUNDARY;
	// генерация массива
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		arr[i] = (rand() % randRange) + ARRAY_NUM_MIN_BOUNDARY;
	}
}

int CalcLargestDivisor(int num)
{
	int halfNum = ceil(num / 2), res = 1;
	for (int i = 2; i <= halfNum; i++)
	{
		if (num % i == 0)
		{
			res = i;
		}
	}
	return res;
}

// сумма массивов
int ArrNumsSum(int* arr)
{
	int sum = arr[0];
	for (int i = 1; i < ARRAY_SIZE; i++)
	{
		sum += arr[i];
	}
	return sum;
}