#ifndef CARCGRAPH_H
#define CARCGRAPH_H
#include "igraph.h"

class CArcGraph: public IGraph {
public:

    explicit CArcGraph(const IGraph& graph);
    explicit CArcGraph(const std::size_t count);

    ~CArcGraph() = default;

    int VerticesCount() const override;

    void AddEdge(int from, int to) override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::size_t Capacity;
    std::size_t VCount;
    std::vector<std::pair<int, int> > Edges;
};

#endif // CARCGRAPH_H
