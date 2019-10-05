#include "csetgraph.h"

CSetGraph::CSetGraph(const std::size_t count) {
    VCount = count;
    Edges.resize(VCount);
}

CSetGraph::CSetGraph(const IGraph &graph) {
    VCount = graph.VerticesCount();
    Edges.resize(VCount);
    std::vector<int> temp;
    for (std::size_t i = 0; i < graph.VerticesCount(); i++) {
        temp = graph.GetNextVertices(i);
        for (int j : temp) {
            Edges[i].insert(j);
        }
    }

}

void CSetGraph::AddEdge(int from, int to) {
    Edges[from].insert(to);
}

int CSetGraph::VerticesCount() const {
    return VCount;
}

std::vector<int> CSetGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    for (int i : Edges[vertex]) {
        res.push_back(i);
    }
    return res;
}

std::vector<int> CSetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (std::size_t i = 0; i < VerticesCount(); i++) {
        if (Edges[i].find(vertex)!= Edges[i].end()) {
            res.push_back(i);
        }
    }
    return res;
}
