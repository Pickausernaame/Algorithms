//      Студент: Мартынов А.П.      Группа: АПО-13
// Дан массив натуральных чисел A[0..n), n не превосходит 10^6. Так же задан размер некоторого окна
// (последовательно расположенных элементов массива) в этом массиве k, k<=n. Требуется для каждого
// положения окна (от 0 и до n-k) вывести значение максимума в окне.
// Скорость работы O(n log n), память O(n).
// Формат входных данных. Вначале вводится n - количество элементов массива. Затем вводится n строк
// со значением каждого элемента. Затем вводится k  - размер окна.
// Формат выходных данных. Разделенные пробелом значения максимумов для каждого положения окна.


#include <iostream>
#include <cstring>
#include <vector>


// Структура, хранящая значение элемента и его индекс
typedef struct {
    int val;
    size_t ind;
} Elements;

// Класс, сравнивающий элементы массива
class Comparator {
 public:
    Comparator() = default;
    bool operator() (Elements& left, Elements& right) {
        return left.val > right.val;
    }
};

// Класс собственного вектора
template <class T>
class MyVector {
public:
    //Правило Пяти

    // Конструктор
    MyVector() : array(nullptr), numb(0), capacity(0) {}

    // Конструктор копирования
    MyVector(const MyVector& copy) : numb(copy.numb), capacity(copy.capacity) {
        delete[] array;
        array = new T[sizeof(copy.array)];
        std::copy(copy.array, copy.array + copy.capacity, array);
    }

    // Конструктор перемещения
    MyVector(MyVector&& rvalue) noexcept {
        delete[] array;
        numb = rvalue.numb;
        capacity = rvalue.capacity;
        array = rvalue.array;
        rvalue.array = nullptr;
    }

    // Оператор присваивания копированием
    MyVector& operator= (const MyVector& rvalue) {
        delete[] array;
        numb = rvalue.numb;
        capacity = rvalue.capacity;
        array = new T(capacity);
        std::copy(rvalue.array, rvalue.array + rvalue.capacity, array);
        return *this;
    }

    // Оператор присваивания перемещением
    MyVector& operator= (MyVector&& rvalue) {
        delete[] array;
        numb = rvalue.numb;
        capacity = rvalue.capacity;
        array = rvalue.array;
        rvalue.array = nullptr;
        return *this;
    }

    // Деструктор
    ~MyVector() {
        if (array) {
            delete[] array;
        }
    }

    T& operator[] (size_t i) {
        return array[i];
    }

    void PushBack(T input);
    T& PopBack();
    size_t size();

private:

    // Метод, отвечающий за реаллокацию памяти
    void Reallocate(size_t size) {
        T* temp = new T[size];
        memcpy(temp, array, capacity*sizeof(T));
        delete[] array;
        array = temp;
        capacity = size;
    }

    // Метод, отвечающий за первичное выделение памяти под массив
    int ArrayInitialization() {
        array = new T[memrate];
        capacity = memrate;
        return 0;
    }

    // Коэф. увеличения памяти
    const size_t memrate = 2;
    T* array;
    size_t numb;
    size_t capacity;

};


template <class T>
void MyVector<T>::PushBack(T input) {
    if (capacity == 0) {
        ArrayInitialization();
    }
    if ((numb + 1 == capacity)) {
        Reallocate(capacity * memrate);
    }
    array[numb] = input;
    ++numb;
};

template <class T>
T& MyVector<T>::PopBack() {
    T output;
    if (numb != 0) {
        --numb;
        output = array[numb];
    }
    return output;
}

template <class T>
size_t MyVector<T>::size() {
    return numb;
}


// Класс Кучи
template <class T, typename Compare>
class MyHeap {

public:

    MyHeap(MyVector<T>& arr, int size, int start);
    void Add(T value);
    void ExtractMax();
    T& Max();

private:
    void SiftDown(int i);
    void SiftUp(int i);
    void HeapBuilding();
    MyVector<T> heap;
};



template <class T, typename Compare>
MyHeap<T, Compare>::MyHeap(MyVector<T>& arr, int size, int start) {
    for(int i = start; i < size; i++) {
        heap.PushBack(arr[i]);
    }
    HeapBuilding();
}


template <class T, class Compare>
void MyHeap<T, Compare>::SiftDown(int i) {
    Compare cmp;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int large = i;
    if (left < heap.size()) {
        if (cmp(heap[left], heap[i])) {
            large = left;
        }
    }

    if (right < heap.size()) {
        if (cmp(heap[right], heap[large])) {
            large = right;
        }
    }
    if(large != i) {
        std::swap(heap[i], heap[large]);
        SiftDown(large);
    }
}

template <class T, class Compare>
void MyHeap<T, Compare>::SiftUp(int i) {
    if (heap.size() != 0)
        while (i > 0) {
            int parent = (i - 1) / 2;
            if(heap[i].val <= heap[parent].val)
                return;
            std::swap(heap[i], heap[parent]);
            i = parent;
        }
}


template <class T, class Compare>
void MyHeap<T, Compare>::HeapBuilding() {
    for(int i = (heap.size() / 2) - 1; i >= 0; i--) {
        SiftDown(i);
    }
}

template <class T, class Compare>
void MyHeap<T, Compare>::Add(T value) {
    heap.PushBack(value);
    SiftUp(heap.size() - 1);
}

template <class T, class Compare>
void MyHeap<T, Compare>::ExtractMax() {
    if (heap.size() < 2) {
        return;
    }
    T max = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.PopBack();
    SiftDown(0);
}


template<class T, class Compare>
T& MyHeap<T, Compare>::Max() {
    if (heap.size() != 0)
        return heap[0];
}

// Функция, выполняющая поиск маскимума в окне
template <class Heap>
MyVector<int> SlidingMaximum(Heap& heap, MyVector<Elements>& array, size_t window) {
    MyVector<int> output;

    for(int i = window; i < array.size(); i++) {
        while(heap.Max().ind < i - window) {
            heap.ExtractMax();
        }
        output.PushBack(heap.Max().val);
        heap.Add(array[i]);
    }

    while(heap.Max().ind < array.size()- window) {
        heap.ExtractMax();
    }

    output.PushBack(heap.Max().val);
    return output;
}


int main() {

    int n = 0;

    std::cin >> n;
    if (n > 100000 || n <= 0) {
        return 0;
    }

    MyVector<Elements> inputElem;
    Elements input;

    for (int i = 0; i < n; i++) {
        std::cin >> input.val;
        input.ind = i;
        inputElem.PushBack(input);
    }

    int win = 0;
    std::cin >> win;
    if (win < 1 || win > n) {
        return 0;
    }

    MyHeap<Elements, Comparator> heap(inputElem, win, 0);

    MyVector<int> res(SlidingMaximum(heap, inputElem, win));
    for (int i = 0; i < res.size(); i++) {
        std::cout << res[i] << " ";
    }
    return 0;
}