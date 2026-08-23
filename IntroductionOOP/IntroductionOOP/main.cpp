#include<iostream>
#include <cmath>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define delimeter "\n-----------------------------------\n"
class Point
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}
	//Constructors
	/*Point()
	{
	x = y = 0;
	cout << "DefaultConstructor:\t" << this << endl;
	}*/
	/*Point(double x)
	{
	this->x = x;
	this->y = 0;
	cout << "SingleArgumentConstructor:" << this << endl;
	//Конструктор с одним параметром
	}*/
	Point(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t\t" << this << endl;
	}
	Point(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t\t" << this << endl;;
	}
	//Operators
	Point& operator = (const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	//Methods
	double Distance(const Point& other) const
	{
		//this - эта точка (находим расстояние от этой точки);
		//other - та точка (до указанной точки);
		//this->x *= 100;		//E0137
		//other.x *= 100;	//E0137
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		return sqrt(x_distance * x_distance + y_distance * y_distance);
	}
	void Print() const
	{
		cout << this << ":\tX = " << x << ",\tY = " << y << endl;
	}
};

//#define STRACT_POINT
//#define DISTANCE_CHECK
//#define CONSTRUCTOR_CHECK
//#define ASSIGNMENT_CHECK

double distance(const Point& A, const Point& B)
{
	return sqrt(pow((A.get_x() - B.get_x()), 2) + pow((A.get_y() - B.get_y()), 2));
}

Point operator+(const Point& left, const Point& right)
{
	Point result;
	result.set_x(left.get_x() + right.get_x());
	result.set_y(left.get_y() + right.get_y());
	return result;
}

void main()
{
	setlocale(LC_ALL, "");
#ifdef STRACT_POINT
	setlocale(LC_ALL, "");
	int a;		//Объявление переменной 'a' типа 'int';
	Point A;	//Объявление переменной 'A' типа 'Point';
	//Создание объекта 'A' структуры 'Point';
	//Создание экземпляра 'A' структуры 'Point';
	//'A' is instance of struct 'Point'
	//Instantiate - создать объект.
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;
	cout << pA->x << "\t" << pA->y << endl;
#endif // STRACT_POINT

#ifdef DISTANCE_CHECK
	Point A;
	A.set_x(2);
	A.set_y(3);
	Point B;
	B.set_x(7);
	B.set_y(8);
	cout << "Координаты точки A(" << A.get_x() << "," << A.get_y() << ")" << endl;
	cout << "Координаты точки B(" << B.get_x() << "," << B.get_y() << ")" << endl;
	cout << delimeter << endl;
	cout << "Расстояние от точки 'А' до точки 'В': " << A.Distance(B) << endl;
	cout << delimeter << endl;
	cout << "Расстояние от точки 'B' до точки 'A': " << B.Distance(A) << endl;
	cout << delimeter << endl;

	cout << "Расстояние между точками 'A' и 'B': " << distance(A, B) << endl;
	cout << delimeter << endl;
	cout << "Расстояние между точками 'B' и 'A': " << distance(B, A) << endl;
#endif // DISTANCE_CHECK

#ifdef CONSTRUCTOR_CHECK
	Point A; //Здесь мы просто создаем объект, и для этого неявно вызывается конструктор по умолчанию
	A.Print();
	/*{
		Point B;
		cout << "Point B существует" << endl;
	}
	cout << "Здесь Point B уже не существует" << endl;*/

	Point B = 5;  //Single-argument constructor - Конструктор с одним параметром
	B.Print();

	Point C(7, 8);
	C.Print();

	Point D = C; // Copy constructor
	D.Print();

	Point E; // Default constructor
	E = D;   //Assignment operator
	E.Print();

#endif // CONSTRUCTOR_CHECK

#ifdef ASSIGNMENT_CHECK
	int a, b, c;
	a = b = c = 0;
	cout << a << "\t" << b << "\t" << c << endl;

	Point A, B, C;
	cout << delimeter << endl;
	A = B = C = Point(2, 3);
	//Point(2,3) - здесь мы явно вызываем конструктор, и создаем временный безымянный объект
	cout << delimeter << endl;
	A.Print();
	B.Print();
	C.Print();
#endif // ASSIGNMENT_CHECK

	Point A(2, 3);
	Point B(7, 8);
	Point C = A + B;
	C.Print();
}