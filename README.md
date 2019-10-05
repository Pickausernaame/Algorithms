# Algorithms
Решение задач с курса "Алгоритмы и структуры данных" технопарка

## Пересечение множеств

Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение. Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в массиве A.. В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1]. n, k ≤ 10000.

### Формат ввода и вывода

| Ввод  | Вывод |
| :---: | :-:   |
|  5  | 1 3 5   |
|  3  |       |
|  1 2 3 4 5  |      |
|  1 3 5  |       |
