#ifndef CSETGRAPH_H
#define CSETGRAPH_H
#include <unordered_set>
#include "igraph.h"



class CSetGraph: public IGraph {
public:

    explicit CSetGraph(const std::size_t count);
    explicit CSetGraph(const IGraph& graph);

    int VerticesCount() const override;

    void AddEdge(int from, int to) override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;


private:
    std::size_t VCount;
    std::vector<std::unordered_set<int>> Edges;
};

#endif // CSETGRAPH_H
