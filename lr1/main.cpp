// Демина Виктория - М8О-206Б-19 - 8 вариант
 // Создать класс Money для работы с денежными суммами. Сумма денег должна быть представлено двумя полями: 
 // типа unsigned long long для рублей и типа unsigned char – для копеек. Дробная часть (копейки) при выводе 
 // на экран должна быть отделена от целой части запятой. Реализовать сложение сумм, вычитание, деление сумм, 
 // деление суммы на дробное число, умножение на дробное число и операции сравнения.

#include <iostream>

using namespace std;

class Money { //  класс Money
public:
	Money(const unsigned long long& rub = 0, const unsigned char& cop = 0) {
		Rub = rub;
		Cop = cop;
	}

	unsigned long long rub() const {
		return Rub;
	}

	unsigned long long& rub() {
		return Rub;
	}

	unsigned char cop() const {
		return Cop;
	}

	unsigned char& cop() {
		return Cop;
	}

private:
	unsigned long long Rub;
	unsigned char Cop;
};

bool operator>(const Money& a, const Money& b) {// сравнение (больше)
	int acop = a.cop();
	int bcop = b.cop();

	return ((a.rub() > b.rub()) || ((acop > bcop) && (a.rub() == b.rub())));
}

bool operator<(const Money& a, const Money& b) { // сравнение (меньше)
	int acop = a.cop();
	int bcop = b.cop();

	return ((a.rub() < b.rub()) || ((acop < bcop) && (a.rub() == b.rub())));
}

Money operator+(const Money& a, const Money& b) { // сложение
	int acop = a.cop();
	int bcop = b.cop();

	if (acop + bcop < 99) {
		unsigned char cop = acop + bcop;
		return { a.rub() + b.rub(), cop };
	}
	else {
		unsigned char cop = acop + bcop - 100;
		return { a.rub() + b.rub() + 1, cop };
	}
}

Money operator-(const Money& a, const Money& b) { // вычитание
	int acop = a.cop();
	int bcop = b.cop();
	if (a > b) {
		if (acop - bcop > 0) {
			unsigned char cop = acop - bcop;
			return { a.rub() - b.rub(), cop };
		}
		else {
			unsigned char cop = 100 - (acop - bcop);
			return { a.rub() - b.rub() - 1, cop };
		}
	}
	else {
		if (bcop + acop > 0) {
			unsigned char cop = bcop - acop;
			return { b.rub() - a.rub(), cop };
		}
		else {
			unsigned char cop = 100 - (bcop - acop);
			return { b.rub() - a.rub() - 1, cop };
		}
	}
}

Money operator/(const Money& a, const Money& b) { // деление сумм
	int acop = a.cop();
	int bcop = b.cop();
	double aa = a.rub() + (acop * 0.01);
	double bb = b.rub() + (bcop * 0.01);
	if (bb != 0) {
		double res = aa / bb;
		unsigned long long  r = res * 100;
		if (res * 100 == r) {
			unsigned char m = r % 100;
			return{ r / 100, m };
		}
		else {
			cout << "(Так как число копеек не может быть дробным, результат будет округлен)";
			cout << "   ";
			unsigned char m = r % 100;
			return{ r / 100, m };
		}
	}

}

Money operator/(const Money& a, const double n) { // деление сумм на дробное число
	int acop = a.cop();
	unsigned long long b = (a.rub() * 100) + acop;
	if (n > 0) {
		double res = b / n * 100;
		unsigned long long  r = res;
		if (res == r) {
			unsigned char m = (r % 10000) / 100;
			return{ r / 10000, m };
		}
		else {
			cout << "(Так как число копеек не может быть дробным, результат будет округлен)";
			cout << "   ";
			unsigned char m = (r % 10000) / 100;
			return{ r / 10000, m };
		}

	}
}

Money operator*(const Money& a, const double n) { // умножение сумм на дробное число
	int acop = a.cop();
	double b = a.rub() + (acop * 0.01);
	if (n >= 0) {
		double res = b * n;
		unsigned long long  r = res * 100;
		if (res * 100 == r) {
			unsigned char m = r % 100;
			return{ r / 100, m };
		}
		else {
			cout << "(Так как число копеек не может быть дробным, результат будет округлен)";
			cout << "   ";
			unsigned char m = r % 100;
			return{ r / 100, m };
		}
	}
}

ostream& operator<<(ostream& output, const Money& p) {  // вывод 
	int cop = p.cop();
	if (cop < 10) {
		output << p.rub() << ",0" << cop;
	}
	else {
		output << p.rub() << "," << cop;
	}
	return output;
}

istream& operator>>(istream& input, Money& p) {  // ввод 
	long long int rub;
	input >> rub;
	while (rub < 0) {
		cout << "ERROR!! (Рубли - положительное число)" << endl;
		input >> rub;
	}

	int cop;
	input >> cop;
	while (cop >= 100) {
		cout << "ERROR!! (Копеек должно быть меньше 100)" << endl;
		input >> cop;
	}
	while (cop < 0) {
		cout << "ERROR!! (Копейки - положительное число)" << endl;
		input >> cop;
	}

	if (cop < 100) {
		p.rub() = rub;
		p.cop() = cop;
	}

	return input;
}

int main() {

	setlocale(LC_ALL, "rus");
	Money a, b;
	double n;

	try {
		cout << " Введите 2 объекта класса Money в формате <<Рубли Копейки>>:" << endl;

		if (cin >> a >> b) {

			cout << " Введите положительное дробное число:" << endl;

			cin >> n;
			while (n <= 0) {
				cout << " Введите ПОЛОЖИТЕЛЬНОЕ дробное число:" << endl;
				cin >> n;
			}

			cout << " Сумма:  ";
			cout << a + b << endl;

			cout << " Разность:  ";
			cout << a - b << endl;

			cout << " Частное от деления:  ";
			cout << a / b << endl;

			cout << " Частное от деления на дробное число(1):  ";
			cout << a / n << endl;

			cout << " Частное от деления на дробное число(2):  ";
			cout << b / n << endl;

			cout << " Умножение на дробное число(1):  ";
			cout << a * n << endl;

			cout << " Умножение на дробное число(2):  ";
			cout << b * n << endl;

			cout << " Сравнение:  ";
			if (a > b) {
				cout << " Первая сумма больше второй";
			}
			else if (a < b) {
				cout << " Вторая сумма больше первой";
			}
			else {
				cout << " Суммы равны";
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
