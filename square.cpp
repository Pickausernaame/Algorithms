// Студент: Мартынов А.П. Группа: АПО-13
// Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин.
// Вначале вводится количество вершин, затем последовательно целочисленные координаты всех
// вершин в порядке обхода по часовой стрелке.
// n < 1000, координаты < 10000.

// Указание. Для вычисления площади n-угольника можно посчитать сумму ориентированных площадей
// трапеций под каждой стороной многоугольника.


// Исправления:
// 1) Структура точек
// 2) Вынести расчет площади в функцию, принимающую массив точек


#include <iostream>

typedef struct {
	double x;
	double y;
} point;


int Square (point* points, size_t size) {
	double result = 0;
	for (size_t i = 0; i < size - 1; i++) {
		result += ((points[i + 1].x - points[i].x) * (points[i + 1].y + points[i].y)) * 0.5;
	}
	result += ((points[1].x - points[size - 1].x) * (points[1].y + points[size -1].y)) * 0.5;
	std::cout << result << std::endl;
	return result;
}




int main() {
	size_t n = 0;
	std::cin >> n;
	point* points = new point[n];
	for (size_t i = 0; i < n; i++) {
		std::cin >> points[i].x >> points[i].y; 
	}
	double result = abs(Square(points, n));
	std::cout << result;
	return 0;
}