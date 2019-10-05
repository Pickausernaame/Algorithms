#include "carcgraph.h"


CArcGraph::CArcGraph(const std::size_t count): VCount(count) {}

CArcGraph::CArcGraph(const IGraph& graph) {
    VCount = graph.VerticesCount();
    std::vector<int> temp;
    for (std::size_t i = 0; i < VerticesCount(); i++) {
        temp = graph.GetNextVertices(i);
        for (std::size_t j = 0; j < temp.size(); j++) {
            Edges.push_back(std::make_pair(i,temp[j]));
        }
    }
}

int CArcGraph::VerticesCount() const {
    return VCount;
}

void CArcGraph::AddEdge(int from, int to) {
    VCount++;
    Edges.push_back(std::make_pair(from,to));

}

std::vector<int> CArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    for (std::pair<int, int> v : Edges) {
        if (v.first == vertex) {
            res.push_back(v.second);
        }
    }
    return res;
}

std::vector<int> CArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (std::pair<int, int> v : Edges) {
        if (v.second == vertex) {
            res.push_back(v.first);
        }
    }
    return res;
}
