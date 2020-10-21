// Демина Виктория - М8О-206Б-19 - 17 вариант
//Создать класс Budget для работы с бюджетом.Класс состоит из двух вещественных чисел(a, b).
//Где a – собственная часть средств бюджета в рублях, b – заемная часть средств бюджета рублях.
//Оба числа должны округляться до второго знака после запятой.Реализовать арифметические операции сложения, 
//вычитания, умножения и деления, а также операции сравнения в виде перегрузки операторов.
//Необходимо реализовать пользовательский литерал для работы с константами типа Budget.

#include <iostream>
#include <math.h> 

using namespace std;


class Budget { //  класс Budget
public:
	Budget(const double& a = 0, const double& b = 0) {
		A = a;
		B = b;
	}

	double a() const {
		return A;
	}

	double& a() {
		return A;
	}

	double b() const {
		return B;
	}

	double& b() {
		return B;
	}

private:
	double A;
	double B;
};

long double operator "" _yen(long double const a) { // пользовательский литерал для перевода из рублей в йены
	return (1.33 * a);
}

  double ok (long double const a) { // округление
	double res = round(a * 100) / 100;
	return res;
}


bool operator>(const Budget& one, const Budget& two) {// сравнение (больше)
	return (ok(one.a()+one.b()) > ok(two.a() + two.b()));
}

bool operator<(const Budget& one, const Budget& two) { // сравнение (меньше)
	return (ok(one.a() + one.b()) < ok(two.a() + two.b()));
}

Budget operator+(const Budget& one, const Budget& two) { // сложение
	double sum = ok((one.a() + one.b() + two.a() + two.b()));
	cout << "\n	 Общая сумма: " << sum << ' ';
	return { ok(one.a() + two.a()), ok(one.b() + two.b()) };
}

Budget operator-(const Budget& one, const Budget& two) { // вычитание
	double sum = ok((one.a() - two.a()) + (one.b() - two.b()));
	cout << "\n	 Общая разность: " << sum << ' ';
	return { ok(one.a() - two.a()), ok(one.b() - two.b()) };
}

Budget operator*(const Budget& one, const Budget& two) { // умножение
	double sum = ok((one.a() * two.a()) + (one.b() * two.b()));
	cout << "\n	 Общее произведение: " << sum << ' ';
	return { ok(one.a() * two.a()), ok(one.b() * two.b()) };
}

Budget operator/(const Budget& one, const Budget& two) { // деление
	double sum = ok((one.a() / two.a()) + (one.b() / two.b()));
	cout << "\n	 Общее частное: " << sum << ' ';
	return { ok(one.a() / two.a()), ok(one.b() / two.b()) };
}



ostream& operator<<(ostream& output, const Budget& p) {  // вывод 
		output << "\n	 Собственная часть: "  << p.a() << "\n	 Заемная часть: " << p.b();
		return output;
}

istream& operator>>(istream& input, Budget& p) {  // ввод 
	input >> p.a();
	input >> p.b();

	if (p.b() <= 0 || p.a() <= 0) {
		cout << " Бюджет - число положительное, пожалуйста введите оба значения заново:  ";
		input >> p.a();
		input >> p.b();
	}
	return input;
}

int main() {

	setlocale(LC_ALL, "rus");
	Budget a, b;

	try {
		cout << " Введите бюджеты 2-х фирм в формате: Собственная часть Заемная часть\n" << endl;
		cout << " Бюджет японской фирмы:  ";
		if (cin >> a ) {
			cout << " Бюджет российской фирмы:  ";
			if (cin >> b) {

				long double yena = 1000.00_yen;

				cout << "\n 1000 российских рублей равна " << yena << " йен\n";

				cout << "\n Сумма:  ";
				cout << a + b << endl;

				cout << "\n Разность:  ";
				cout << a - b << endl;

				cout << "\n Частное:  ";
				cout << a / b << endl;

				cout << "\n Произведение:  ";
				cout << a * b << endl;

				cout << "\n Сравнение:  ";
				if (a > b) {
					cout << " Бюджет японской фирмы больше\n";
				}
				else if (a < b) {
					cout << " Бюджет российской фирмы больше\n";
				}
				else {
					cout << " Бюджеты обеих фирм равны\n";
				}
			}
			else {
				cout << "ERROR!!: (Ошибка ввода)" << endl;
			}
		}
		else {
			cout << "ERROR!!: (Ошибка ввода)" << endl;
		}
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}
	return 0;
}

