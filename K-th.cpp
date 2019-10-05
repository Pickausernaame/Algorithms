// Cтудент: Мартынов А.П. Группа: АПО-13
// Дан массив неотрицательных целых 64-разрядных чисел. 
// Количество чисел не больше 106. Отсортировать массив методом MSD по битам (бинарный QuickSort).

#include <iostream>


// Функтр 
class Compare {
public:
	Compare() = default;
	bool operator() (const long long int first, const long long int second){
		return first >= second ? false : true;
	}
};


// Функция, позврляющая найти медиану в массиве
template<class T, class TComp>
size_t GetMedian (T input, size_t left, size_t right, TComp compare) {
	if (left - right <= 1) {
		return left;
	}
	size_t mid = (left + right - 1) / 2;
	bool leftpivot = compare(input[left], input[mid]) && compare(input[right], input[left]);
	leftpivot |= compare(input[left], input[right]) && compare(input[mid], input[left]);

	bool midpivot = compare(input[mid], input[left]) && compare(input[right], input[mid]);
	midpivot |= compare(input[mid], input[right]) && compare(input[left], input[mid]);

	if (leftpivot) {
		return left;
	} else if (midpivot) {
		return mid;
	} else
		return right;
}


// Функция, выполняющая перебор массива и возвращает пивот
template<class T, class TComp>
size_t Partition(T input, size_t left, size_t right, TComp compare) {
	int pivot = GetMedian(input, left, right, compare);
	if (input[pivot] != input[right]) {
		std::swap(input[pivot], input[right]);
	}
	size_t i = left;
	size_t j = left;
	while (j < right) {

		if (compare(input[j], input[right])) {
			if (input[j] != input[i]) {
				std::swap(input[j], input[i]);
			}
			++i;
		}

		++j;
	}
	if (input[i] != input[right]) {
		std::swap(input[i], input[right]);
	}
	return i;
}

// Функция, отвечающая за поиск К-ой статистики
template<class T, class TComp>
size_t GetKth (T input, size_t n, size_t k, TComp compare) {
	size_t pivot = 0;
	size_t left = 0;
	size_t right = n - 1;
	pivot = Partition(input, left, right, compare);
	if (pivot == k) {
		return pivot;
	} else {
		while(pivot != k) {
			if (pivot < k) {
				left = pivot + 1;
				pivot = Partition(input, left, right, compare);
			} else if (pivot > k) {
				right = pivot - 1;
				pivot = Partition(input, left, right, compare);
			}
		}
	}
	return pivot;
}

int main() {
	size_t n = 0;
	size_t k = 0;

	std::cin >> n >> k;

	long long int* input = (long long int*)malloc(n * sizeof(long long int));
	for (size_t i = 0; i < n; i++) {
		scanf("%lld", &*(input + i));
	}

	k = GetKth(input, n, k, Compare());
	
	std::cout << input[k];
	free(input);
	return 0;
}