#include "clistgraph.h"

CListGraph::CListGraph(const std::size_t count) {
    VCount = count;
    Edges.resize(count);
}

CListGraph::CListGraph(const IGraph& graph) {
    VCount = graph.VerticesCount();
    Edges.resize(graph.VerticesCount());
    for (std::size_t i = 0; i < graph.VerticesCount(); i++) {
        std::vector<int> buf = graph.GetNextVertices(i);
        for (int j : buf) {
            Edges[i].push_back(j);
        }
    }
}


int CListGraph::VerticesCount() const {
    return VCount;
}

void CListGraph::AddEdge(int from, int to) {

    Edges[from].push_back(to);
    VCount = Edges.size();
}


std::vector<int> CListGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    for (int i : Edges[vertex]) {
        res.push_back(i);
    }
    return res;
}

std::vector<int> CListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (std::size_t i = 0; i < VerticesCount(); i++) {
        for (int j : Edges[i]) {
            if (j == vertex) {
                res.push_back(i);
            }
        }
    }
    return res;
}
