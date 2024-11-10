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
#include <unordered_map>
#include <chrono>
#include <deque>

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
      if (!is_visited_vertex(vertex) && is_cycle_iterative(vertex, -1))
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

  bool is_visited_vertex(int vertex) const
  {
    if (vertex < 0 && vertex >= m_visited.size())
    {
      std::cerr << "get vertex is out of range: " << vertex << std::endl;
      return false;
    }
    return m_visited[vertex];
  }

  void set_visited_vertex(int vertex, bool flag)
  {
    if (vertex < 0 && vertex >= m_visited.size())
    {
      std::cerr << "set vertex is out of range: " << vertex << std::endl;
      return;
    }

    m_visited[vertex] = flag;
  }

  bool is_cycle(int vertex, int parent_vertex)
  {
    set_visited_vertex(vertex, true);

    for (int adj_vertex : m_graph.at(vertex))
    {
      if (!is_visited_vertex(adj_vertex))
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

  bool is_cycle_iterative(int vertex, int parent_vertex)
  {
    std::deque<int> vertexs;
    vertexs.push_front(vertex);
    while (!vertexs.empty())
    {
      int current_vertex = vertexs.front();
      vertexs.pop_front();

      if (is_visited_vertex(current_vertex))
      {
        return true;
      }

      set_visited_vertex(current_vertex, true);
      for (int adj_vertex : m_graph.at(current_vertex))
      {
        // Add adj vertexs of current vertex to front
        if (!is_visited_vertex(adj_vertex))
        {
          vertexs.push_front(adj_vertex);
        }
      }
    }

    return false;
  }

  std::vector<bool> m_visited;  // Mark visited vertex, assume that vertex is indexed start at 0 and end at size() - 1
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
  //const vector<Edge> edges = { {0, 1}, {1, 2}, {2, 3}, {2, 5}, {1, 4}, {5, 3} };

  check_for_cycles(edges_with_cycle);
  check_for_cycles(edges_without_cycle);
  //check_for_cycles(edges);

  return 0;
}
