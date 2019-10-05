#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <queue>

// Структура вершины
struct Vertex {
    unsigned short int minpath;
    unsigned short int entry;
    std::list<unsigned short int> connect;
};

// Класс графа
class Graph {
public:
    explicit Graph(const std::size_t count) {
        Edges.resize(count);
    }
    // Функция, возвращяющая число вершин графа
    int VerticesCount() {
        return VCount;
    }

    // Функция, добавляющая ребро 
    void AddEdge(int from, int to) {
        Edges[from].connect.push_back(to);
        Edges[to].connect.push_back(from);
    }
    
    // Функция, осуществляющая поиск числа минимальнх путей
    int GetMinPaths(int from, int to) {
        // Очередь в которой хранятся вершины, которые мы не посетили
        std::queue<unsigned short int> q;
        q.push(from);
        
        Edges[from].entry = 1;
        Edges[from].minpath = 0;
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            // Взвешиваем граф единицей
            int newpath = Edges[current].minpath + 1;
            for (int i : Edges[current].connect) {                    
                    if (Edges[i].entry == 0) {
                        Edges[i].entry += Edges[current].entry;
                        Edges[i].minpath = newpath;
                        q.push(i);
                        
                    } else {
                        
                        if (newpath < Edges[i].minpath) {
                            Edges[i].minpath = newpath;
                            Edges[i].entry = Edges[current].entry;
                        } else if (newpath == Edges[i].minpath) {
                            Edges[i].entry += Edges[current].entry;
                        }
                    }
            }
        }
        return Edges[to].entry;
    }

private:
    std::size_t VCount;
    std::vector<Vertex> Edges;
};




int main() {

    int n = 0;
    std::cin >> n;
    Graph graph(n);
    int e = 0;
    int from = 0;
    int to = 0;
    std::cin >> e;
    for(int i = 0; i < e; i++){
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }
    std::cin >> from >> to;
    std::cout << graph.GetMinPaths(from, to) << std::endl;
    return 0;
}
