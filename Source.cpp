#include <iostream>
#include <algorithm>
#include <thread>

using std::cout;
using std::endl;


class Figure 
{
public:
	virtual double calc_square() const= 0;
	virtual void printf() const = 0;
	
};

class Circle : public Figure {
	double radius;

public:
	Circle (double r) : radius(r)
	{}
	double calc_square() const {
		
		return 3.14 * radius * radius;
	}
	void printf() const  {
		cout<< calc_square();
	}
};

class Triangle : public Figure {
	double base{}, hight{};
public:
	Triangle(double b, double h) : base(b), hight(h)
	{}
	double calc_square() const {
		return base * hight / 2;
	}
	void printf() const {
		cout << calc_square();
	}
};

class Rectangle : public Figure {
	double width{}, length{};
public:
	Rectangle(double w, double l) : width(w), length (l)
	{}
	double calc_square() const {
		return width * length;
	}
	void printf() const {
		cout<< calc_square();
	}
};

class
	Square : public Figure {
	double length{};
public:
	Square(double l) : length (l)
	{}
	double calc_square() const {
		return length * length;
	}
	void printf() const {
		cout << calc_square();
	}
};


void Figure_print(Figure* fig[], int size, const char* sortType) {
	cout << "Sort: " << sortType << endl;
	for (int i = 0; i < size; ++i) {
		fig[i]->printf(); cout << " ";
	}
	cout << endl;
}

	void bubble_sort(Figure* fig[], int size)
	{
	for (int i = 0; i < size - 1; ++i) {
		for (int j = 0; j < size - i - 1; ++j) {
			if (fig[j]->calc_square() > fig[j + 1]->calc_square()) {
				std::swap(fig[j], fig[j + 1]);
			}
		}
	}
	
}
	




	void quickSort(Figure* fig[], int left, int right) {
		if (left >= right) return;
		
		Figure* supp = fig[(left + right) / 2];
		int i = left;
		int j = right;
		while (i <= j) {
			while (fig[i]->calc_square() < supp->calc_square()) i++;
			while (fig[j]->calc_square() > supp->calc_square()) j--;
			if (i <= j) {
				std::swap(fig[i], fig[j]);
				i++;
				j--;
			}
		}
		quickSort(fig, left, j);
		quickSort(fig, i, right);
		
	}





int main() {
	Figure* fig[] = {
	new Circle(3),
	new Triangle(3,5),
	new Rectangle(4,2),
	new Square(3)
	};
	const int size = sizeof(fig) / sizeof(fig[0]);



	Figure* fig1[size];
	std::copy(fig, fig + size, fig1);
	

	// Создание потоков
	std::thread t1(bubble_sort, fig, size);
	std::thread t2(quickSort, fig1, 0, size-1);

	t1.join();
	t2.join();

	Figure_print(fig, size, "Bubble");
	Figure_print(fig1, size, "QuickSort");


	for (int i = 0; i < size; ++i) {
		delete fig[i];
	}

	
	
	return 0;
}