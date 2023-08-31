// ДЗ 3 01,07.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//3) Создать шаблонный класс динамического массива (см. урок №2, с. 56). 
// Добавить в этот класс методы для добавления элемента к массиву и удаления элемента из массива.
//Добавить метод для расчета суммы элементов этого массива Sum()
//Создать объекты этого класса, инкапсулирующие массивы типа int, double, char и Point.
//Для каждого из этих объектов вызвать метод Sum().
//

#include <iostream>
#include <cstdlib>
#include <ctime>

class Point {
	
public:
	int X;
	int Y;

	Point() :X(0), Y(0) {};
	

	Point(int x, int y) {
		X = x;
		Y = y;
	}
	
	void show() {
		std::cout << "X: " << X << " Y: " << Y << std::endl;
	}
	
	Point sum(const Point& other) {
		int newX = X + other.X;
		int newY = Y + other.Y;
		return Point(newX, newY);
	}
	
	friend std::ostream& operator<<(std::ostream& os, const Point& point);
}; 

Point operator+(const Point& left, const Point& right)
{
	return Point(left.X + right.X, left.Y + right.Y);
}
Point& operator+=(Point& left, const Point& right)
{
	left.X += right.X;
	left.Y += right.Y;
	return left;
}

template <typename T>
class DynArray
{
	T* arr;
	int size;
	int capacity; // Добавляем переменную capacity
public:

	DynArray(const DynArray& other) : size(other.size), capacity(other.capacity)//конструктор копирования
	{
		arr = new T[capacity];
		for (int i = 0; i < size; ++i) {
			arr[i] = other.arr[i];
		}
	}

	DynArray(int sizeP) : arr{ new T[sizeP] {} }, size{ sizeP }, capacity{ sizeP }{}//конструктор копирования с одним аргументом 

	DynArray() : DynArray(5) {}//конструктор по умолчанию  с начальным размером 5 элементов.

	DynArray(int sizeP, const T& initialValue) : arr{ new T[sizeP] {} }, size{ sizeP }, capacity{ sizeP }//конструктор с заданным размером и начальным значением.
	{
		for (int i = 0; i < size; ++i) {
			arr[i] = initialValue;
		}
	}

	T getElem(int idx) { return arr[idx]; }
	void setElem(int idx, T val) { arr[idx] = val; }
	void print();
	void randomize();
	void appendString(const T* str);
	void pushBack(T value);
	void popBack();
	T sum();

	~DynArray();

	DynArray<T>& operator=(const DynArray<T>& other) {
		if (this != &other) {
			delete[] arr;
			size = other.size;
			capacity = other.capacity;
			arr = new T[capacity];
			for (int i = 0; i < size; ++i) {
				arr[i] = other.arr[i];
			}
		}
		return *this;
	}


};


template <typename T>
void DynArray<T>::print()
{
	for (int i = 0; i < size; ++i) {
		std::cout << arr[i] << ' ';
	}

	std::cout << '\n';
}
template<typename T>
void DynArray<T>::randomize()
{
	for (int i{ 0 }; i < size; ++i)
	{
		arr[i] = (rand() % 11) - 5;
	}
}
;



template<typename T>
void DynArray<T>::appendString(const T* str)
{
	int strLength = strlen(str);
	if (size + strLength > capacity) {
		int newCapacity = capacity * 2; // Увеличиваем емкость в два раза
		T* newData = new T[newCapacity];
		for (int i = 0; i < size; ++i) {
			newData[i] = arr[i];
		}
		delete[] arr;
		arr = newData;
		capacity = newCapacity;
	}

	for (int i = 0; i < strLength; ++i) {
		arr[size++] = str[i];
	}
}

template<typename T>
void DynArray<T>::pushBack(T value)
{
	if (size >= capacity) {
		int newCapacity = size+1;
		T* newData = new T[newCapacity];
		for (int i = 0; i < size; ++i) {
			newData[i] = arr[i];
		}
		delete[] arr;
		arr = newData;
		capacity = newCapacity;
	}
	arr[size++] =  value;
}

template<typename T>
void DynArray<T>::popBack()
{
	if (size > 0) {
		--size;
	}
}

template<typename T>
T DynArray<T>::sum()
{
	T total = T(); // Инициализируем начальное значение суммы в зависимости от типа T
	for (int i = 0; i < size; ++i) {
		total += arr[i];
	}
	return total;
}
// Перегрузка оператора += для пользовательского типа T
template<typename T>
T& operator+=(T& left, const T& right)
{
	left.sum(right);
	return left;
}

template<typename T>
T operator+(const T& left, const T& right)
{
	T result = left;
	result += right;
	return result;
}

template<typename T>
DynArray<T>::~DynArray()
{
	std::cout << "~DynArray\n";
	//std::cout << "Try to free memory from DynArray for" << arr << " pointer\n";
	delete[] arr;
	//std::cout << "DynArr destructed for " << size << " elements, for " << this << '\n';
}



int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));// позволяет получать разные последовательности случайных чисел при каждом запуске программы.
	DynArray<int> intArray(5);
	intArray.randomize();
	std::cout << "intArray elements: ";
	intArray.print();
	intArray.pushBack(7);
	intArray.print();
	intArray.popBack();
	intArray.print();
	int intsum = intArray.sum();
	std::cout << "Sum of elements: " << intsum << std::endl;


	DynArray<double> doubleArray(5);
	doubleArray.randomize();
	std::cout << "doubleArray elements: ";
	doubleArray.print();
	doubleArray.pushBack(7.5);
	doubleArray.print();
	doubleArray.popBack();
	doubleArray.print();
	double doublesum = doubleArray.sum();
		std::cout << "Sum of elements: " << doublesum << std::endl;
		
	 
	std::cout << "charArray elements: ";
	DynArray<char> charArray(5);
	charArray.appendString("Hello");
	charArray.print();
	charArray.pushBack('o');
	charArray.print();
	charArray.popBack();
	charArray.print();

//в данном случае сумма символов будет иметь смысл только
//если символы имеют числовые значения и суммируются как числа.
	int charsum = charArray.sum();
	std::cout << "Sum of ASCII codes " << charsum << std::endl;
	
	
	DynArray<Point> pointArray(3);
	pointArray.setElem(0, Point(1, 2));
	pointArray.setElem(1, Point(3, 4));
	pointArray.setElem(2, Point(7, 8));

	std::cout << "pointArray elements: \n";
	pointArray.print();

	Point sumResult = pointArray.sum();
	std::cout << "Sum of pointArray elements: ";
	sumResult.show();

	return 0;


}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
	os << "X: " << point.X << " Y: " << point.Y<<std::endl;
	return os;
}
