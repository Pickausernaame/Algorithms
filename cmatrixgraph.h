#ifndef CMATRIXGRAPH_H
#define CMATRIXGRAPH_H
#include "igraph.h"

class CMatrixGraph: public IGraph {
public:

    explicit CMatrixGraph(const std::size_t count);
    explicit CMatrixGraph(const IGraph& graph);

    ~CMatrixGraph() = default;

    int VerticesCount() const override;


    void AddEdge(int from, int to) override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;


private:
    std::size_t VCount;
    std::vector<std::vector<int>> Edges;

};

#endif // CMATRIXGRAPH_H
