// Студент: Мартынов А.П.   Группа: АПО-13
// Реализовать дек с динамическим зацикленным буфером.
// Обрабатывать команды push * и pop *.

// В первой строке количество команд n. n ≤ 1000000.

// Каждая команда задаётся как 2 целых числа: a b.

// a = 1 - push front
// a = 2 - pop front
// a = 3 - push back
// a = 4 - pop back

// Если дана команда pop *, то число b - ожидаемое значение. Если команда pop * вызвана для пустой структуры данных, то ожидается “-1”.

#include <iostream>
#include <cstring>



// Класс деки
class Deque {

public:
	Deque() : array(nullptr), head(0), tail(0), numb(0),capacity(0) {}

	Deque(const Deque& copy) : head(copy.head), tail(copy.tail), numb(copy.numb), capacity(copy.capacity) {
		std::copy(array, array + capasity, copy.array);
	}
	
	void operator= (const Deque& copy) : array(copy.array), head(copy.head), tail(copy.tail), numb(copy.numb), capacity(copy.capacity) {}


	~Deque() {
    	if (array) {
    		delete[] array;
        }
    }

	int PushBack(int input) {
		if (capasity == 0) {
			ArrayInitialization();
		}
		if ((numb + 1 == capasity)) {
				Reallocate(capasity * memrate);
		}
		array[tail] = input;
		++tail;
		tail = tail % capasity;
		++numb;
		return 0;
	}

	int PushFront(int input) {
		if (capasity == 0) {
			ArrayInitialization();	
		}
		if (numb != 0) {
			if ((numb + 1 == capasity)) {
				Reallocate(capasity * memrate);
			}
			if (head == 0) {
				head = capasity;
			}
		--head;
		array[head] = input;
		tail = tail % capasity;
		}
		else {
			array[head] = input;
			++tail;
            tail = tail % capasity;
		}
		++numb;
		return 0;
	}

	int PopFront() {
		int output = 0;
		if (numb != 0) {
			output = array[head];
			head = (head + 1) % capasity;
			--numb;
		}
		return output;
	}

	int PopBack() {
		int output = 0;
		if (numb != 0) {
			if (tail == 0) {
				tail = capasity;
			}
			--tail;
			tail = tail % capasity;
			--numb;
			output = array[tail];
		}
		return output;
	}

	// Метод, предназначенный для печати деки(для дебага)
	void PrintDeque() {
		std::cout << "Head =" << head << "\n";
		std::cout << "Tail =" << tail << "\n";
		std::cout << "Capasity =" << capasity << "\n";
		std::cout << "Numb =" <<  numb << "\n";
		for (size_t i = 0; i < capasity; i++) {
			std::cout << "a[" << i << "] =" << array[i] << "  ";
		}
	}

	// Метод, возвращающий число элементов в деке
	size_t NumberOfElements() {
		return numb;
	}

private:

	// Метод, перевыделения памяти в деке
	int Reallocate(int size) {
		int* temp = new int[size];
		if (!temp) {
			throw std::bad_alloc{};
		}
		if (head > tail) {
			std::copy(array + head, array + capasity, temp + head);
			std::copy(array, array + tail, temp + capasity);
			tail += capasity;
		}
		else {
			std::copy(array, array + capasity, temp);
		}
		delete[] array;
		array = temp;
		capasity = size;
		return 0;
	}

	int ArrayInitialization() {
		array = new int[memrate];
		capasity = memrate;
		return 0;		
	}

	const size_t memrate = 2;
	int* array;
	size_t head;
	size_t tail;
	size_t numb;
	size_t capasity;
};


int main() {
	Deque d;
	int comand = 0;
	int expect = 0;
	std::string answer = "YES";
	size_t n = 0;
	std::cin >> n;
	for (size_t i = 0; i < n; i++) {
		std::cin >> comand >> expect;
		switch(comand) {
			case 1:
				d.PushFront(expect);
				break;
			case 2:
				if ((d.NumberOfElements() == 0)) {
					if (expect != -1) {
						answer = "NO";
					}
				} else if ((d.PopFront() != expect)) {
					answer = "NO";
				}
				break;
			case 3:
				d.PushBack(expect);
				break;
			case 4:
				if ((d.NumberOfElements() == 0)) {
					if (expect != -1) {
						answer = "NO";
					}
				} else if ((d.PopBack() != expect)) {
					answer = "NO";
				}
				break;
			default:
				break;
		}
	}
	std::cout << answer;
	return 0;
}