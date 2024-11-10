//
//  main.cpp
//  CppGraphTest
//
//  Created by Dave Duprey on 25/11/2019.
//  Copyright © 2019 Dave Duprey. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <set>
#include <chrono>

using namespace std;


struct Edge {
  const int source;
  const int destination;
};


class GraphCycleDetector
{
public:
  GraphCycleDetector(const std::vector<Edge>& edges)
  {
    build_graph(edges);
    m_visited = std::vector<bool>(m_graph.size(), false);
  }

  bool solve()
  {
    for (const auto& [vertex, _] : m_graph)
    {
      if (!m_visited[vertex] && is_cycle(vertex, -1))
      {
        return true;
      }
    }

    return false;
  }

private:
  void build_graph(const std::vector<Edge>& edges)
  {
    for (const Edge& e : edges)
    {
      m_graph[e.source].emplace(e.destination);
      m_graph[e.destination].emplace(e.source);
    }
  }

  bool is_cycle(int vertex, int parent_vertex)
  {
    m_visited[vertex] = true;

    for (int adj_vertex : m_graph.at(vertex))
    {
      if (!m_visited[adj_vertex])
      {
        if (is_cycle(adj_vertex, vertex))
        {
          return true;
        }
      }
      else if (adj_vertex != parent_vertex)
      {
        return true;
      }
    }

    return false;
  }

  std::vector<bool> m_visited;
  std::unordered_map<int, std::unordered_set<int>> m_graph;  // Map vertex -> its adjacent vertexs
};


bool has_cycle(const vector<Edge> &edges) {
  // Implement your solution here to detect whether this undirected graph contains a cycle or not.

  GraphCycleDetector detector(edges);
  return detector.solve();
  }


void report_results(bool cycle_found) {
  if (cycle_found)
    cout << "Graph contains a cycle\n";
  else
    cout << "Graph does NOT contain any cycles\n";
}


void check_for_cycles(const vector<Edge> &edges) {
  bool cycle_found = has_cycle(edges);
  report_results(cycle_found);
}


int main(int argc, const char *argv[]) {

  const vector<Edge> edges_with_cycle    = { {0, 1}, {0, 2}, {0, 3}, {1, 4}, {1, 5}, {4, 8}, {4, 9}, {3, 6}, {3, 7}, {6, 10}, {6, 11}, {5, 9} };
  const vector<Edge> edges_without_cycle = { {0, 1}, {0, 2}, {0, 3}, {1, 4}, {1, 5}, {4, 8}, {4, 9}, {3, 6}, {3, 7}, {6, 10}, {6, 11} };

  check_for_cycles(edges_with_cycle);
  check_for_cycles(edges_without_cycle);

  return 0;
}
