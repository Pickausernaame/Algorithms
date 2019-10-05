// Студент: Мартынов А.П.
// Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 1000000.
// Отсортировать массив методом поразрядной сортировки LSD по байтам. 
#include <iostream>


// Функция, проверяющая бит на 0 или 1
template<class T>
bool LeftBit (T elem, const size_t rate) {

	int bit = (elem >> (rate - 1)) & 1;
	if (bit == 0) {
		return false;
	}
	return true;

};

// Сортировка 
template<class T>
void MyBMSD(T array, size_t left, size_t right, size_t rate) {

	if ((rate == 0) || left >= right) {
		return;
	}

	size_t i = left;
	size_t j = right;

	while (i != j) {

		while (!(LeftBit(array[i], rate)) && i < j) { 	
			i++;
		}

		while ((LeftBit(array[j], rate)) && i < j) {
			j--;
		}

		if (i != j) {
			std::swap(array[i], array[j]);
		}

	}

	if (!(LeftBit(array[i], rate))) {
		j++;
	}

	if (j != 0) {
		MyBMSD(array, left, j - 1, rate - 1);
	} 

	MyBMSD(array, j, right, rate - 1);
};

// Класс массива long long int 
class LongLong {
 
 public:

 	LongLong() {

 		this->size = 0;
 		this->array = nullptr;

 	}

 	LongLong(size_t n) {

 		this->size = n;
 		this->array = new long long int[size];

 	}

 	~LongLong() {

 		if (!array) {
 			delete[] array;
 			array = nullptr;
 		}

 	}

 	long long int& operator[] (size_t i) {
 		return array[i];
 	}

 	// Метод, отвечающий за заполнение массива
 	int InputArray();
 	// Метод, отвечающий за вывод мссива
 	int OutputArray();
 	// Метод, отвечающий за возврат значения размера массива
 	size_t SizeOfArray();
 	// Метод, возвращающий указатель на массив
 	long long int* GetArray() {
 		return this->array;
 	}

 private:

 	size_t size;
 	long long int* array;

};

int LongLong::InputArray() {

 		for (size_t i = 0; i < this->size; i++) {
 			std::cin >> array[i]; 
 		}
 		return 0;

 	}

int LongLong::OutputArray() {
 
 		for (size_t i = 0; i < this->size; i++) {
 			std::cout << array[i] << " ";
 		}
 		return 0;

 	}

size_t LongLong::SizeOfArray() {

 		return this->size;

 	}




int main() {

	size_t n = 0;
	std::cin >> n;

	if (n < 1) {
		return -1;
	}

	LongLong array(n);
	array.InputArray();
	MyBMSD(array, 0, array.SizeOfArray() - 1, 64);
	array.OutputArray();
	return 0;
}