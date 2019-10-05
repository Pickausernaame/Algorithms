#ifndef CLISTGRAPH_H
#define CLISTGRAPH_H
#include "igraph.h"
#include <list>

class CListGraph: public IGraph {
public:

    explicit CListGraph(const std::size_t count);
    explicit CListGraph(const IGraph& graph);

    ~CListGraph() = default;

    int VerticesCount() const override;

    void AddEdge(int from, int to) override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;


private:
    std::size_t VCount;
    std::vector<std::list<int>> Edges;

};

#endif // CLISTGRAPH_H
