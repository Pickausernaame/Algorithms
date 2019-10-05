#include "cmatrixgraph.h"

CMatrixGraph::CMatrixGraph(const std::size_t count) {
    Edges.resize(count);
    for(std::size_t i = 0; i < count; i++) {
        std::vector<int> buf(count, 0);
        Edges[i] = buf;
    }
    VCount = count;
}

CMatrixGraph::CMatrixGraph(const IGraph &graph) {
    VCount = graph.VerticesCount();
    std::vector<int> temp;
    Edges.resize(graph.VerticesCount());
    for (std::size_t i = 0; i < Edges.size(); i++) {
        std::vector<int> buf(graph.VerticesCount(), 0);
        Edges[i] = buf;
        temp = graph.GetNextVertices(i);

        for (int j : temp) {
            Edges[i][j] = 1;
        }
    }
}

void CMatrixGraph::AddEdge(int from, int to) {
    Edges[from][to] = 1;
}

int CMatrixGraph::VerticesCount() const {
    return VCount;
}

std::vector<int> CMatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    for (std::size_t i = 0; i < VerticesCount(); i++) {
        if (Edges[vertex][i] == 1) {
            res.push_back(i);
        }
    }
    return res;
}

std::vector<int> CMatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (std::size_t i = 0; i < VerticesCount(); i++) {
        if (Edges[i][vertex] == 1) {
            res.push_back(i);
        }
    }
    return res;
}
