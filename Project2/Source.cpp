#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
using namespace std;

//#define MIN_SIZE		50
//#define MAX_SIZE		800
//#define MIN_LINE_WIDTH	1
//#define MAX_LINE_WIDTH	25
//
//#define MAX_HORIZONTAL_RESOLUTION	800
//#define MAX_VERTICAL_RESOLUTION		600

namespace MyGeometry
{
	enum Color
	{
		RED = 0x000000FF,
		GREEN = 0x0000FF00,
		BLUE = 0x00FF0000,
		GREY = 0x00AAAAAA,
		YELLOW = 0x0000FFFF
	};
#define SHAPE_TAKE_PARAMETERS unsigned int x, unsigned int y, unsigned int line_width = 5, Color color = Color::GREY
#define SHAPE_GIVE_PARAMETERS x, y, line_width, color
	class Shape
	{
	protected:
		unsigned int x;
		unsigned int y;
		unsigned int line_width;
		Color color;
	public:
		static const int MIN_SIZE = 50;
		static const int MAX_SIZE = 800;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 25;
		static const int MAX_HORIZONTAL_RESOLUTION = 800;
		static const int MAX_VERTICAL_RESOLUTION = 600;
		unsigned int get_x()const
		{
			return x;
		}
		unsigned int get_y()const
		{
			return y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		unsigned int set_size(unsigned int size)
		{
			return
				size < MIN_SIZE ? MIN_SIZE :
				size > MAX_SIZE ? MAX_SIZE :
				size;
		}
		void set_x(unsigned int x)
		{
			this->x = x < MAX_HORIZONTAL_RESOLUTION ? x : MAX_HORIZONTAL_RESOLUTION;
		}
		void set_y(unsigned int y)
		{
			this->y = y < MAX_VERTICAL_RESOLUTION ? y : MAX_VERTICAL_RESOLUTION;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width < MIN_LINE_WIDTH)line_width = MIN_LINE_WIDTH;
			if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
			this->line_width = line_width;
		}

		//				Constructors:
		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_x(x);
			set_y(y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		//				Methods:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		virtual void info()const
		{
			cout << "������� ������: " << get_area() << endl;
			cout << "�������� ������: " << get_perimeter() << endl;
			draw();
		}
	};

	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		void set_width(double width)
		{
			this->width = set_size(width);
		}
		void set_height(double height)
		{
			this->height = set_size(height);
		}

		//				Constructors:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :
			Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}

		//				Methods:
		double get_area()const override
		{
			return width * height;
		}
		double get_perimeter()const override
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			/*for (int i = 0; i < heigth; i++)
			{
				for (int j = 0; j < width; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}*/

			//HWND - Handler to Window (���������� ����, ����� ��� ���� ����� ���������� � ���)
			HWND hwnd = GetConsoleWindow();	//�������� ���������� ���� �������.
			//HWND hwnd = GetDesktopWindow();	//�������� ���������� ���� �������.

			//��� ���� ����� ��������, ����� �������� ���������� (Device Context), �� ���� ������� ����
			HDC hdc = GetDC(hwnd);
			//hdc - ��� ��, �� ��� �� ����� ��������.

			//������ ����� ��, ��� �� ����� ��������:

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//�������� ������ ������ ������
			HBRUSH hBrush = CreateSolidBrush(color);	//����� �������� ������

			//������ ����� ������� ��� � �� ��� ����� ��������:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, x, y, x + width, y + height);

			//������� ��� ��������� ������� ��� ���� ����� ���������� �������:

			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������: " << width << endl;
			cout << "������: " << height << endl;
			Shape::info();
		}
	};
	class Square : public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :
			Rectangle(side, side, SHAPE_GIVE_PARAMETERS)
		{

		}
		~Square()
		{

		}
	};
	class Circle : public Shape
	{
		double radius;
	public:
		double getRadius() const
		{
			return radius;
		}
		void setRadius(double radius)
		{
			this->radius = set_size(radius);
		}
		Circle(double radius, SHAPE_TAKE_PARAMETERS) : Shape (SHAPE_GIVE_PARAMETERS)
		{
			setRadius(radius);
		}
		~Circle()
		{

		}
		double get_diameter() const
		{
			return 2 * radius;
		}
		double get_area() const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter() const override
		{
			return M_PI * get_diameter();
		}
		void draw() const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN pen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH brush = CreateSolidBrush(color);
			SelectObject(hdc, pen);
			SelectObject(hdc, brush);
			::Ellipse(hdc, x, y, x + get_diameter(), y + get_diameter());
			DeleteObject(pen);
			DeleteObject(brush);
			ReleaseDC(hwnd, hdc);
		}
		void info() const override
		{
			cout << typeid(*this).name() << endl
				<< "Radius: " << getRadius() << endl
				<< "Diameter: " << get_diameter() << endl;
			Shape::info();
		}
	};
	Shape* ShapeFactory(int shape_id)
	{
		Shape* shape = nullptr;
		int size = rand() % Shape::MAX_SIZE;
		switch (shape_id)
		{
		case 1: new Rectangle(rand() % Shape::MAX_SIZE, rand() % Shape::MAX_SIZE,
			rand() % Shape::MAX_HORIZONTAL_RESOLUTION, rand() % Shape::MAX_VERTICAL_RESOLUTION,
			rand() % Shape::MAX_LINE_WIDTH);
		case 2:

		}
		return shape
	}
}

void main()
{
	setlocale(LC_ALL, "");
	MyGeometry::Rectangle rect(100, 50, 300, 100, 8, MyGeometry::Color::RED);
	rect.info();
	MyGeometry::Square square(44, 550, 100, 8, MyGeometry::Color::GREY);
	square.info();
	MyGeometry::Circle circle(75, 750, 100, 5, MyGeometry::Color::YELLOW);
	circle.info();
}