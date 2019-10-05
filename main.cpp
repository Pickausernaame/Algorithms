#include <gtest/gtest.h>

#include <algorithm>

#include "clistgraph.h"
#include "cmatrixgraph.h"
#include "carcgraph.h"
#include "csetgraph.h"


class TestGraph : public ::testing::Test {
protected:
    void SetUp() {
        CListGraph graph(7);
        graph.AddEdge(0, 1);
        graph.AddEdge(0, 5);
        graph.AddEdge(1, 2);
        graph.AddEdge(1, 3);
        graph.AddEdge(1, 5);
        graph.AddEdge(1, 6);
        graph.AddEdge(3, 2);
        graph.AddEdge(3, 6);
        graph.AddEdge(4, 3);
        graph.AddEdge(5, 4);
        graph.AddEdge(5, 6);
        graph.AddEdge(6, 4);
        _graph = new CListGraph(graph);
    }
    CListGraph* _graph;
};

TEST_F(TestGraph, CListGraphTest) {
    CListGraph c(*_graph);
    std::vector<int> ans = {2, 3, 5 ,6};
    std::vector<int> buf = c.GetNextVertices(1);
    std::sort(buf.begin(), buf.end());

    ASSERT_EQ(buf, ans);
    ASSERT_EQ(c.VerticesCount(), 7);
}

TEST_F(TestGraph, CArcGraphTest) {
    CArcGraph c(*_graph);
    std::vector<int> ans = {2, 3, 5 ,6};
    std::vector<int> buf = c.GetNextVertices(1);
    std::sort(buf.begin(), buf.end());

    ASSERT_EQ(buf, ans);
    ASSERT_EQ(c.VerticesCount(), 7);
}

TEST_F(TestGraph, CMatrixGraphTest) {
    CMatrixGraph c(*_graph);
    std::vector<int> ans = {2, 3, 5 ,6};
    std::vector<int> buf = c.GetNextVertices(1);
    std::sort(buf.begin(), buf.end());

    ASSERT_EQ(buf, ans);
    ASSERT_EQ(c.VerticesCount(), 7);
}

TEST_F(TestGraph, CSetGraphTest) {
    CSetGraph c(*_graph);
    std::vector<int> ans = {2, 3, 5 ,6};
    std::vector<int> buf = c.GetNextVertices(1);
    std::sort(buf.begin(), buf.end());

    ASSERT_EQ(buf, ans);
    ASSERT_EQ(c.VerticesCount(), 7);
}

void PrintVect(const std::vector<int>& v){
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

