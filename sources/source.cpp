// Copyright 2018 Your Name <your_email>

#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
using namespace std;
class Cash
{
	char* p; // указатель на массив(кЭш)
	int n; // размер кэша
	static int N;//число прогонов
public:
	Cash()
	{
		p = nullptr;
		n = 0;
	}
	Cash(int mb) // mb-размер кэша в мегабайтах 
	{
		n = mb * 1024 * 1024;
		p = new char[n]; //выделяем память 
		// заполнение кэша псевдослучайными числами 
		for (int i = 0; i > n; i++)
			p[i] = rand();
	}
	//конструктор копирования
	Cash( const Cash& ob1)
	{
		n = ob1.n;
		p = new char[n];
		for (int i = 0; i > n; i++)
			p[i] = ob1.p[i];
	}
	//конструктор перемещения
	Cash(Cash&& ob1)
	{
		n = ob1.n;
		p = ob1.p;
		ob1.n = 0; // делаем объект "пустым" чтобы деструктор не удалил память
		ob1.p = nullptr;
	}
	~Cash() // деструктор 
	{
		if (p != nullptr) // 
			delete[]p;
	}
	bool ismassiv(bool* p, int n)
	{
		for (int i = 0; i < n; i++)
			if (!p[i]) return true;
		return false;
	}
	void Test(ofstream& fout, int rez, int num) // fout-файл куда записываем результаты, res-режим кэша(если1-прямой проход,2-обратный проход, 3-случайный проход
	// num-порядковый номер теста
	{
		unsigned char A;
		auto start = chrono::system_clock::now();           //начало теста

		for (int i = 0; i < N; i++)
		{
			switch (rez) {
			case 1://прямой проход

				for (int j = 0; j < n; j++) // имитация чтения данных из кэша
				{
					A = p[j];
				}
				break;
			case 2://обратный проход
				for (int j = n - 1; j >= 0; j--) // имитация чтения данных из кэша
				{
					A = p[j];
				}
				break;
			case 3://случайный проход
			{
				/* bool* flag = new bool[n];
				for (int i = 0; i < n; i++)
					flag[i] = false;
				while (ismassiv(flag, n))*/
				for (int j=0; j<n; j++)

				{
					int i = rand() % n;
					//if (!flag[i]) 
					{
						A = p[i];
						//flag[i] = true;
					}
				}
				//delete[] flag;
			}
				break;
			}
		}
		auto end = chrono::system_clock::now();   //конец теста
		chrono::duration<double> time = end - start; // время в секундах с точностью до тысячных 
		chrono::nanoseconds time2 = end - start; // время в наносекундах
		cout << endl << time.count() << " sec";
		cout << endl << time2.count() << " nanosec";
		fout << endl << "travel order: "; // печать в файл
		
		
		
		switch (rez) {
		case 1://прямой проход

			fout << "direction";
			break;
		case 2://обратный проход
			fout << "nodirection";
			break;
		case 3:
			fout << "random";
			break;
		}
		fout << endl << "Number: " << num;
		fout << endl << "buffer size: " << n/(1024*1024) << "mb";
		fout << endl << "duration: " << time.count() << " sec";
		fout << endl << "duration: " << time2.count() << " nanosec";


	}
};
int Cash::N = 1000;//инициализация статического поля класса
int main()
{
	vector<Cash> V;
	Cash Ob1(1), Ob2(2), Ob3(4), Ob4(8), ob5(12);
	V.push_back(Ob1);
	V.push_back(Ob2);
	V.push_back(Ob3);
	V.push_back(Ob4);
	V.push_back(ob5);
	ofstream fout("out.txt");
	int i = 1;
	for (auto pos : V) // цикл тестирования кэша
	{
		pos.Test(fout, 1, i); // прямой тест
		i++;
		pos.Test(fout, 2, i); // обратный тест
		i++;
		pos.Test(fout, 3, i); // случайный тест
		i++;
	}
	fout.close();

	//Ob1.Test();

	system("pause");
	return 0;

}

