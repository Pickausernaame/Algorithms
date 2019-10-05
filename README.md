# Algorithms
Решение задач с курса "Алгоритмы и структуры данных" технопарка

## Количество различных путей

Дан базовый интерфейс для представленияориентированного графа:
```
struct IGraph {
virtual ~IGraph() {}
    
    // Добавление ребра от from к to.
virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

virtual std::vector<int> GetNextVertices(int vertex) const = 0;
virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};
```

Необходимо написать несколько реализаций интерфейса:
1. CListGraph, хранящий граф в виде массива списков смежности,
2. CMatrixGraph, хранящий граф в виде матрицы смежности,
3. CSetGraph, хранящий граф в виде массива хэш-таблиц,
4. CArcGraph, хранящий граф в виде одного массива пар {from, to}.
5. Также необходимо реализовать конструктор, принимающий const IGraph*. Такой конструктор должен скопировать переданный граф в создаваемый объект.

Для каждого класса создавайте отдельные h и cpp файлы.
Число вершин графа задается в конструкторе каждой реализации.
