#include <iostream>

// Структура, отвечающая за хранение ключа
template <class T>
struct HashTableUnit {
    T key;
    bool isDel;
};

// Хэширующий функтр
template <class T>
class HashFunctr {
public:

    int operator() (int numb, const T &key, const int size) {
        int res = -1;

        // Выбор хэш-функции
        if (numb == 1) {
            res = HashFunc1(key, size);
        } else if (numb == 2) {
            res = HashFunc2(key, size);
        }

        return res;
    }

private:

    int HashFunc1(const T &key, const int size) {
        int h = 0;

        for(int i = key.size() ; i >= 0; i--) {
            h += (key[i] + 57 * h) % size;
        }

        h = h % size;
        return h;
    }

    int HashFunc2(const T &key, int size) {
        int h = 0;

        for(int i = key.size(); i >= 0; i--) {
            h += (key[i] + 7 * h) % size;
        }

        // Условие нечетности
        h = (2 * h + 1) % size;
        return h;
    }

};

// Класс хэш-таблцы
template<class T>
class HashTable {
public:
    HashTable():size(0), capacity(8) {
        hTable = new HashTableUnit<T>* [capacity];
        for (int i = 0; i < capacity; i++) {
            hTable[i] = nullptr;
        }
    }

    // Павило пяти

    // Конструктор копирования
    HashTable(const HashTable& copy) : size(copy.size), capacity(copy.capacity) {
        if (hTable) {
            for (int i = 0; i < capacity; i++) {
                delete hTable[i];
            }
            delete[] hTable;
        }
        hTable = new T[sizeof(copy.hTable)];
        std::copy(copy.hTable, copy.hTable + copy.capacity, hTable);
    }

    // Конструктор перемещения
    HashTable(HashTable&& rvalue) noexcept {
        if (hTable) {
            for (int i = 0; i < capacity; i++) {
                delete hTable[i];
            }
            delete[] hTable;
        }
        size = rvalue.size;
        capacity = rvalue.capacity;
        hTable = rvalue.hTable;
        rvalue.hTable = nullptr;
    }

    // Оператор присваивания копированием
    HashTable& operator= (const HashTable& rvalue) {
        if (hTable) {
            for (int i = 0; i < capacity; i++) {
                delete hTable[i];
            }
            delete[] hTable;
        }
        size = rvalue.size;
        capacity = rvalue.capacity;
        hTable = new T(capacity);
        std::copy(rvalue.hTable, rvalue.hTable + rvalue.capacity, hTable);
        return *this;
    }

    // Оператор присваивания перемещением
    HashTable& operator= (HashTable&& rvalue) {
        if (hTable) {
            for (int i = 0; i < capacity; i++) {
                delete hTable[i];
            }
            delete[] hTable;
        }
        size = rvalue.size;
        capacity = rvalue.capacity;
        hTable = rvalue.hTable;
        rvalue.hTable = nullptr;
        return *this;
    }

    // Деструктор
    ~HashTable() {
        if (hTable) {
            for (int i = 0; i < capacity; i++) {
                delete hTable[i];
            }
            delete[] hTable;
        }
    }

    // Метод, добавляющий элемент в таблицу
    bool AddElement(const T &key) {
        // Если таблица заполнится на 3/4 - перехеширование
        if((double)(size / capacity) >= rehashVal) {
            ReHash();
        }

        // Индекс стертого элемента
        int delind = -1;

        // Первое хэширование
        int h1 = HashFunc(1, key, capacity);

        // Проверка на поворение, а так же поиск удаленных элементов
        for (int i = 0; hTable[h1] != nullptr && i < capacity; i++) {

            if(hTable[h1]->key == key && hTable[h1]->isDel == false) {
                return false;
            }

            if(hTable[h1]->isDel == true && delind == -1) {
                delind = h1;
            }
            // Второе хэширование
            int h2 = HashFunc(2, key, capacity);
            h1 = (h1 + h2) % capacity;
        }
        // Если нет удаленных элементов, создаем новый
        if(delind == -1) {
            hTable[h1] = new HashTableUnit<T>;
            hTable[h1]->key = key;
            hTable[h1]->isDel = false;
        }
        // Если есть удаленные элементы, заполняем их
        else {
            hTable[delind]->key = key;
            hTable[delind]->isDel = false;
        }
        size++;
        return true;
    }

    // Метод, удаляющий элемент из таблицы
    int RemoveElement(const T &key) {

        // Первое хэширование
        int h1 = HashFunc(1, key, capacity);
        for(int i = 0; hTable[h1] != nullptr && i < capacity; i++) {

            // Если ключ в таблице - удаляем
            if(hTable[h1]->key == key && !hTable[h1]->isDel) {
                hTable[h1]->isDel = true;
                size--;
                return true;
            }

            // Второе хэширование
            int h2 = HashFunc(2, key, capacity);
            h1 = (h1 + h2) % capacity;
        }
        return false;
    }

    // Метод, проверяющий наличие элемента в таблице
    int HasElement(const T &key) {

        // Первое хэширование
        int h1 = HashFunc(1, key, capacity);
        int i = 0;

        // Пока не упремся в конец таблицы
        while(hTable[h1] != nullptr && ++i < capacity) {
            // Элемент найден
            if(hTable[h1]->key == key && !hTable[h1]->isDel) {
                return true;
            }

            // Второе хэширование
            int h2 = HashFunc(2, key, capacity);
            h1 = (h1 + h2) % capacity;
        }
        return false;
    }

private:
    // Перехеширование таблицы
    void ReHash() {
        // Создаем новую таблицу
        int new_capacity = capacity * memrate;
        HashTableUnit<T>** new_hTable = new HashTableUnit<T>* [new_capacity];

        for (int i = 0; i < new_capacity; i++) {
            new_hTable[i] = nullptr;
        }

        for(int i = 0; i < capacity; i++) {
            // Если элемент существует, то генерируем для него индекс в новой таблице
            if(hTable[i] != nullptr && !hTable[i]->isDel) {
                // Первое хэширование
                int h1 = HashFunc(1, hTable[i]->key, new_capacity);

                for(int j = 0; new_hTable[h1] != nullptr && j < new_capacity; j++) {
                    // Второе хеширование
                    int h2 = HashFunc(2, hTable[i]->key, new_capacity);
                    h1 = (h1 + h2) % new_capacity;
                }

                // Переносим элемент
                new_hTable[h1] = hTable[i];
            }
        }
        delete[] hTable;
        hTable = new_hTable;
        capacity = new_capacity;
    }

    HashTableUnit<T>** hTable;
    HashFunctr <std::string> HashFunc;
    int size;
    int capacity;
    int memrate = 2;
    double rehashVal = 0.75;

};


int main() {
    HashTable<std::string> table;
    char cmd = '\0';
    std::string key;
    bool result = false;

    while(std::cin >> cmd >> key) {
        switch(cmd) {

        case '+':
            result = table.AddElement(key);
            break;

        case '-':
            result = table.RemoveElement(key);
            break;

        case '?':
            result = table.HasElement(key);
            break;

        default:
            continue;
        }
        if (result) {
            std::cout << "OK\n";
        } else {
            std::cout << "FAIL\n";
        }
    }
    return 0;
}
