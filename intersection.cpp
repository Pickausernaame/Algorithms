// Студент: Мартынов А.П.   Группа: АПО-13
// Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n-1] и B[0..m-1]. n » m.
// Найдите их пересечение. Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в массиве A..
// В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1]. n, k ≤ 10000.

#include <iostream>


template<class T>
void GetLimit(T& array, const size_t& size , size_t& left, size_t& right, int& elem) {

	while (array[right] < elem) {
		left = right - 1;
		right = right * 2;
		if (right >= size - 1) {
			right = size - 1;
			//left = right - 1;
			break;
		}
	}

}


template<class T>
size_t BinarySearch (T& array, size_t b_left, size_t b_right, int elem) {

    int index = -1;
    size_t mid = b_left + (b_right - b_left) / 2;
    //std::cout << b_left << "  " << b_right << "\n";
    if (b_left == b_right) {
    	if (array[mid] == elem) {
            index = mid;
            return index;
        }
    }

    while (b_left < b_right) {

        if (array[mid] == elem) {
            index = mid;
            break;
        }

        if (array[mid] < elem) {
            b_left = mid + 1;
        }

        if (array[mid] > elem) {
            b_right = mid;
        }

        mid  = b_left + (b_right - b_left) / 2;

        if (array[mid] == elem) {
            index = mid;
            break;
        }

    }
    return index;
}


int main() {
	
	int n = 0, k = 0;
	size_t left = 0, right = 1;
	
	std::cin >> n >> k;
	//if(n == 0 || k == 0){
	//	return 0;
    //}

	int* A = new int[n];
    int* B = new int[k];
    int* output = new int[k];

	for (int i = 0; i < n; i++) {
		std::cin >> A[i];
	}

	for (int j = 0; j < k; j++) {
		std::cin >> B[j];
	}

    size_t e = 0;
    for (int j = 0; j < k; j++) {

    	if (A[0] > B[k - 1]) {
    		break;
    	}

    	if (A[n - 1] < B[0]) {
    		break;
    	}

    	GetLimit(A, n, left, right, B[j]);
        int index = BinarySearch(A, left, right, B[j]);

        if (index > -1) {
            output[e] = B[j];
            e++;
            left = index + 1;

        }
	}

	for (size_t i = 0; i < e; i++) {
		std::cout << output[i] << " ";
	}

	delete[] A;
	delete[] B;
	delete[] output;
	
	return 0;
}