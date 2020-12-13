//Демина Виктория - М8О-206Б-19 - 4 вариант
//Создать программу, которая позволяет :
//•       Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
//•       Сохранять созданные фигуры в динамический массив std::vector<Figure*>.
//•   	Вызывать для всего массива общие функции(1 - 3 см.выше).Т.е.распечатывать для каждой фигуры в массиве геометрический центр, координаты вершин и площадь.
//•       Необходимо уметь вычислять общую площадь фигур в массиве.
//•       Удалять из массива фигуру по индексу.
//Фигуры : Трапеция, Ромб, Пятиугольник.

#include <iostream>
#include <vector>
#include<cmath>

using namespace std;

struct Point {  // Описание точки
	double x;
	double y;

	Point operator+(const Point& val){
		return{ val.x + x, val.y + y };
	}

	Point operator-(const Point& val) {
		return{ x - val.x, y - val.y };
	}

	Point operator*(const int val) {
		return{ val * x, val * y };
	}

	Point operator+=(const Point& val) {
		x += val.x;
		y += val.y;
		return { x, y };
	}
};


istream& operator>>(istream& input, Point& point) { // Ввод точки
	input >> point.x >> point.y;
	return input;
}

ostream& operator<<(ostream& output, const Point& point) { // Вывод точки
	output << "[" << point.x << ", " << point.y << "]";
	return output;
}

double Sin(double deg) {                      
	double rad = deg * 3.14159265 / 180.0;   // Вычисление синуса в градусах
	return (round(sin(rad) * 1000) / 1000);
}

double Cos(double deg) {
	double rad = deg * 3.14159265 / 180.0;   // Вычисление косинуса в градусах
	return (round(cos(rad) * 1000) / 1000);
}

Point turn(const Point& A, const Point& O, const int& deg) {  // Поворот на n градусов относитенльно центра
	Point a;
	a.x = A.x - O.x;
	a.y = A.y - O.y;

	double resx = (a.x * Cos(deg)) - (a.y * Sin(deg));
	double resy = (a.y * Cos(deg)) + (a.x * Sin(deg));

	return{ resx + O.x , resy + O.y };
}

double S_Triengle(const Point& A, const Point& B, const Point& C) {    // Площадь треугольника
	double res = ((A.x * (B.y - C.y)) + (B.x * (C.y - A.y)) + (C.x * (A.y - B.y))) / 2;
	if (res > 0) {
		return(((A.x * (B.y - C.y)) + (B.x * (C.y - A.y)) + (C.x * (A.y - B.y))) / 2);
	}
	else return -res;
}

class Figure {    // Класс Фигур
public:
	virtual double area() const = 0;
	virtual Point A() { return { 0,0 }; }
	virtual Point B() { return { 0,0 }; }
	virtual Point C() { return { 0,0 }; }
	virtual Point D() { return { 0,0 }; }
	virtual Point E() { return { 0,0 }; }
	virtual Point Center() { return { 0,0 }; }

	virtual void set(Point a, Point o) {}
	virtual void set(Point a, Point c, Point o, double alpha) {}

protected:
	Point A_, B_, C_, D_, E_, Center_;
};

class Rhombus : public Figure {  // Ромб
public:

	void set(Point a, Point o) {
		Center_ = o;
		A_ = a;
		B_ = turn(A_, Center_, 90);
		C_ = turn(A_, Center_, 180);
		D_ = turn(A_, Center_, 270);
	}
	double area() const override {
		return(S_Triengle(A_, B_, C_) + S_Triengle(D_, A_, B_));
	}

	Point A() { return A_; }
	Point B() { return B_; }
	Point C() { return C_; }
	Point D() { return D_; }
	Point Center() { return Center_; }
};

class Trapezoid : public Figure {  // Трапеция
public:

	void set(Point a, Point c, Point o, double alpha) {
		Center_ = o;
		A_ = a;
		C_ = c;
		B_ = turn(A_, Center_, alpha);
		D_ = turn(C_, Center_, alpha);
	}

	double area() const override {
		return(S_Triengle(A_, B_, C_) + S_Triengle(D_, A_, B_));
	}

	Point A() { return A_; }
	Point B() { return B_; }
	Point C() { return C_; }
	Point D() { return D_; }
	Point Center() { return Center_; }

};

class Pentagon : public Figure {   // Пятиугольник
public:

	void set(Point a, Point o) {
		Center_ = o;
		A_ = a;
		B_ = turn(A_, Center_, 72);
		C_ = turn(A_, Center_, 144);
		D_ = turn(A_, Center_, 216);
		E_ = turn(A_, Center_, 288);
	}

	double area() const override {
		return(S_Triengle(A_, B_, C_) + S_Triengle(C_, A_, D_) + S_Triengle(A_, D_, E_));
	}

	Point A() { return A_; }
	Point B() { return B_; }
	Point C() { return C_; }
	Point D() { return D_; }
	Point E() { return E_; }
	Point Center() { return Center_; }
};



int main() {
	setlocale(LC_ALL, "rus");
	vector<Figure*> figur;
	vector<unsigned int> pentagon;
	int i = 0; 
	unsigned int input = 0;
	unsigned int n = 0;

	cout << "Список команд:" << endl
		<< "1 - Добавить новую фигуру" << endl
		<< "2 - Удалить фигуру" << endl
		<< "3 - Вывести координаты вершин" << endl
		<< "4 - Вывести координаты центра" << endl
		<< "5 - Узнать площадь фигуры" << endl
		<< "6 - Вычислить общую площадь введенных фигур" << endl
		<< "7 - Завершить работу программы"
		<< endl;


	while (input != 7) {

		cout << "Введите команду: ";
		if (!(cin >> input)) {
			cout << "Команда введена некорректно." << endl;
			break;
		}

		double AllS = 0;
		Point O, A, C;
		double Alph;

		switch (input) {
		case 1:
			cout << "Какую фигуру хотите создать?" << endl;
			cout << "1 - Ромб" << endl;
			cout << "2 - Трапеция" << endl;
			cout << "3 - Пятиугольник" << endl;
			cin >> n;

			switch (n) {
			case 1:
				figur.push_back(new Rhombus);
				cout << "Введите координаты центра ромба:\nO: ";
				cin >> O;
				cout << "Введите координаты одной из вершин ромба:\nA: ";
				cin >> A;
				figur[i]->set(A, O);
				++i;
				break;
			case 2:
				figur.push_back(new Trapezoid);
				cout << "Введите координаты центра трапеции:\nO: ";
				cin >> O;
				cout << "Введите координаты одной из вершин трапеции:\nA: ";
				cin >> A;
				cout << "Введите координаты вершины трапеции принадлежащую другому основанию и не лежащую на той же диагонали\nC: ";
				cin >> C;
				cout << "Введите угол между диагоналями трапеции:\nAlpha: ";
				cin >> Alph;
				figur[i]->set(A, C, O, Alph);
				++i;
				break;
				break;
			case 3:
				figur.push_back(new Pentagon);
				cout << "Введите координаты центра пятиугольника:\nO: ";
				cin >> O;
				cout << "Введите координаты одной из вершин пятиугольника:\nA: ";
				cin >> A;
				figur[i]->set(A, O);
				++i;
				pentagon.push_back(i);
				break;
				break;
			default:
				cout << "ERROR!! - Фигуры с таким номером не существует" << endl;
				break;
			}
			break;
		case 2:int n;
			if (i == 0) {
				cout << "ERROR!! - Создайте хотя бы одну фигуру" << endl;
				break;
			}
			cout << "Введите номер фигуры, которую вы хотите удалить: ";
			cin >> n;
			--n;
			if (n >= i) {
				cout << " ERROR!! - Невозможно удалить фигуру " << n + 1 << ", тк количество фигур в массиве " << i << endl;
				break;
			}
			else {
				for (n; n < i - 1; ++n) {
					figur[n] = figur[n + 1];
				}
				figur.pop_back();
				--i;
			}
			break;
		case 3:
			if (i == 0) {
				cout << "ERROR!! - Создайте хотя бы одну фигуру" << endl;;
				break;
			}
			cout << "Введите номер фигуры, координаты вершин которой хотите узнать: ";
			cin >> n;
			--n;
			if (n >= i) {
				cout << " ERROR!! - Количество фигур в массиве " << i << endl;
				break;
			}
			else {
				int val = 0;
				for (int x : pentagon) {
					if (x == i) ++val;
				}
				if (val != 0) {
					cout << "A = " << figur[n]->A() << endl
						<< "B = " << figur[n]->B() << endl
						<< "C = " << figur[n]->C() << endl
						<< "D = " << figur[n]->D() << endl
						<< "E = " << figur[n]->E() << endl;
						
				}
				else {
					cout << "A = " << figur[n]->A() << endl
						<< "B = " << figur[n]->B() << endl
						<< "C = " << figur[n]->C() << endl
						<< "D = " << figur[n]->D() << endl;
			
					
				}
			}
			break;
		case 4:
			if (i == 0) {
				cout << "ERROR!! - Создайте хотя бы одну фигуру" << endl;
				break;
			}
			cout << "Введите номер фигуры, геометрический центр которой хотите узнать: ";
			cin >> n;
			--n;
			if (n >= i) {
				cout << " ERROR!! - Количество фигур в массиве " << i << endl;
				break;
			}
			else {
				cout << "O = " << figur[n]->Center() << endl;
					
				
			}
			break;

		case 5:
			if (i == 0) {
				cout << "ERROR!! - Создайте хотя бы одну фигуру" << endl;
				break;
			}
			cout << "Введите номер фигуры, площадь которой хотите узнать: ";
			cin >> n;
			--n;
			if (n >= i) {
				cout << " ERROR!! - Количество фигур в массиве " << i << endl;
				break;
			}
			else {
				cout << "Площадь = " << figur[n]->area() << endl;
				
			}
			break;

		case 6:
			for (int n = 0; n < i; ++n) {
				AllS += figur[n]->area();
			}
			cout << "Общая площадь  = " << AllS  << endl;
			break;

		case 7: break;
		default: 
			cout << " ERROR!! - Подобной команды не существует" << endl;
			break;
		}
		cout << endl;
	}
}
