// Студент: Мартынов А.П.   Группа: АПО-13

// Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием. Общее время работы алгоритма O(n log n).
// В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа).
// Каждому покупателю необходимо показать минимум 2 рекламы. Рекламу можно транслировать только в целочисленные моменты времени.
// Покупатель может видеть рекламу от момента прихода до момента ухода из магазина. В каждый момент времени может показываться только одна реклама.
// Считается, что реклама показывается мгновенно. Если реклама показывается в момент ухода или прихода, то считается,
// что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.


#include <iostream>
#include <cstring>
#include <algorithm>

// Структура, хранящая в себе время входа и выхода каждого покупателя
typedef struct {
    int entry;
    int exit;
} Buyer;

// Класс, сравнивающий время выхода\входа посетитетлей
template <class T>
class Compare {
public:
    Compare() = default;
    bool operator() (T a, T b) {
        if (a.exit < b.exit)
            return true;
        if (a.exit == b.exit)
            return a.entry > b.entry;
    }
};



// Функция, выполняющая подсчет рекламы
template <class T>
int AdvCounter(T* arr, int size) {

    if (size == 0) {
        return 0;
    } else if (size == 1) {
        return 2;
    }

    int adv = 0;
    int exit = -1;
    int entry = -1;

    for (int i = 0; i < size; i++) {

        //  cлучай, когда:  покупатель        ______
        //                  отрезок      __

        if (arr[i].entry > exit ) {
            //std::cout << "FIRST\n";
            adv = adv + 2;
            entry = arr[i].exit - 1;
            exit = arr[i].exit;
        }

            //  cлучай, когда:  покупатель     ______
            //                  отрезок      __

        else if (arr[i].entry == exit) {
            //std::cout << "SECOND\n";
            adv++;
            entry = exit;
            exit = arr[i].exit;
        }

            //  cлучай, когда:  покупатель      ______
            //                  отрезок      _____

        else if (arr[i].entry > entry) {
            //std::cout << "THIRD\n";
            adv++;
            if (arr[i].exit > exit) {
                entry = exit;
                exit = arr[i].exit;
            } else if (arr[i].entry < exit) {
                entry = arr[i].exit;
            }
        }

    }
    return adv;
}

// Функция, объединяющая разбитый массив
template <class T,class Compare>
void Merge(T* arr, int l, int m, int r, Compare cmp) {
    
    int i = 0;
    int j = 0;
    int k = l;
    int n1 = m - l + 1;
    int n2 =  r - m;

    T* lefttemp = new T[n1];
    T* righttemp = new T[n2];

    std::copy(arr + l, arr + l + n1, lefttemp);
    std::copy(arr + m + 1, arr + m + 1 + n2, righttemp);

    while (i < n1 && j < n2) {
        if (cmp(lefttemp[i], righttemp[j])) {
            arr[k] = lefttemp[i];
            i++;
        } else {
            arr[k] = righttemp[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k++] = lefttemp[i++];
    }

    while (j < n2) {
        arr[k++] = righttemp[j++];
    }

    delete[] lefttemp;
    delete[] righttemp;
}

// Сортировка слиянием
template <class T, class Compare>
void MergeSort(T* arr , int begin, int end, Compare cmp) {

    if (begin < end) {

        int mid = begin + (end - begin) / 2;

        MergeSort(arr, begin, mid, cmp);
        MergeSort(arr, mid + 1, end, cmp);

        Merge(arr, begin, mid, end, cmp);
    }
}


int main() {

    int n = 0;
    std::cin >> n;
    if (n <= 0) {
        return 0;
    }
    
    Buyer* buyers = new Buyer[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> buyers[i].entry >> buyers[i].exit;
    }

    MergeSort(buyers, 0, n - 1, Compare<Buyer>());

    std::cout << AdvCounter(buyers, n);

    delete[] buyers;
    return 0;
}
