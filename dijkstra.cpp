//// Submitter: justinic(Choi, Justin)
//// 40532889
//
//#include <string>
//#include <iostream>
//#include <fstream>
//#include "ics46goody.hpp"
//#include "array_queue.hpp"
//#include "hash_graph.hpp"
//#include "dijkstra.hpp"
//
//
//
//std::string get_node_in_graph(const ics::DistGraph& g, std::string prompt, bool allow_QUIT) {
//  std::string node;
//  for(;;) {
//    node = ics::prompt_string(prompt + " (must be in graph" + (allow_QUIT ? " or QUIT" : "") + ")");
//    if ((allow_QUIT && node == "QUIT") || g.has_node(node))
//      break;
//  }
//  return node;
//}
//
//
//int main() {
//  try {
//      ics::DistGraph graph;
//      std::string start_node;
//      std::string stop_node;
//      std::ifstream file;
//      ics::safe_open(file, "Enter graph file name", "flightcost.txt");
//      graph.load(file);
//      std::cout << graph << std::endl;
//
//      start_node = get_node_in_graph(graph, "Enter start node", false);
//      ics::CostMap answer_map = extended_dijkstra(graph, start_node);
//      std::cout << answer_map << std::endl << std::endl;
//      while (stop_node != "QUIT"){
//          stop_node = get_node_in_graph(graph, "Enter stop node", true);
//          if (stop_node != "QUIT") {
//
//              int stop_cost = answer_map[stop_node].cost;
//              std::cout << "Cost is " << stop_cost << "; path is " << recover_path(answer_map, stop_node) << std::endl << std::endl;
//          }
//      }
//
//
//
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//
//  return 0;
//}
