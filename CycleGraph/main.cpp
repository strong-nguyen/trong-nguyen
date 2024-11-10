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
    for (const auto& [node, _] : m_graph)
    {
      if (!is_visited_node(node) && is_cycle_iterative(node))
      {
        return true;
      }

      // Or use recursive way
      //if (!is_visited_node(node) && is_cycle(node, -1))
      //{
      //  return true;
      //}
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

  bool is_visited_node(int node) const
  {
    if (node < 0 && node >= m_visited.size())
    {
      std::cerr << "is_visited_node is out of range: " << node << std::endl;
      return false;
    }

    return m_visited[node];
  }

  void set_visited_node(int node, bool flag)
  {
    if (node < 0 && node >= m_visited.size())
    {
      std::cerr << "set_visited_node is out of range: " << node << std::endl;
      return;
    }

    m_visited[node] = flag;
  }

  bool is_cycle(int node, int parent_node)
  {
    set_visited_node(node, true);

    for (int adj_node : m_graph.at(node))
    {
      if (!is_visited_node(adj_node))
      {
        if (is_cycle(adj_node, node))
        {
          return true;
        }
      }
      else if (adj_node != parent_node)
      {
        return true;
      }
    }

    return false;
  }

  bool is_cycle_iterative(int node)
  {
    std::deque<int> nodes;
    nodes.push_front(node);
    while (!nodes.empty())
    {
      int current_node = nodes.front();
      nodes.pop_front();

      if (is_visited_node(current_node))
      {
        return true;
      }

      set_visited_node(current_node, true);
      for (int adj_node : m_graph.at(current_node))
      {
        // Add adj nodes of current node to front
        if (!is_visited_node(adj_node))
        {
          nodes.push_front(adj_node);
        }
      }
    }

    return false;
  }

  std::vector<bool> m_visited;  // Mark visited node, assume that node is indexed start at 0 and end at size() - 1
  std::unordered_map<int, std::unordered_set<int>> m_graph;  // Map node -> its adjacent nodes
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
