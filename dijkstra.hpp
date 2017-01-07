// Submitter: justinic(Choi, Justin)
// 40532889

#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>                    //Biggest int: std::numeric_limits<int>::max()
#include "array_queue.hpp"
#include "array_stack.hpp"
#include "heap_priority_queue.hpp"
#include "hash_graph.hpp"


namespace ics {


class Info {
  public:
    Info() { }

    Info(std::string a_node) : node(a_node) { }

    bool operator==(const Info &rhs) const { return cost == rhs.cost && from == rhs.from; }

    bool operator!=(const Info &rhs) const { return !(*this == rhs); }

    friend std::ostream &operator<<(std::ostream &outs, const Info &i) {
      outs << "Info[" << i.node << "," << i.cost << "," << i.from << "]";
      return outs;
    }

    //Public instance variable definitions
    std::string node = "?";
    int cost = std::numeric_limits<int>::max();
    std::string from = "?";
  };


  bool gt_info(const Info &a, const Info &b) { return a.cost < b.cost; }

  typedef ics::HashGraph<int> DistGraph;
  typedef ics::HeapPriorityQueue<Info, gt_info> CostPQ;
  typedef ics::HashMap<std::string, Info, DistGraph::hash_str> CostMap;
  typedef ics::pair<std::string, Info> CostMapEntry;


//Return the final_map as specified in the lecture-node description of
//  extended Dijkstra algorithm
CostMap extended_dijkstra(const DistGraph &g, std::string start_node) {
        CostMap info_map;
        CostMap answer_map;
        CostPQ info_pq;

        // 3a Update info_map and info_pq;
        for (auto x : g.all_nodes()){
            Info temp = Info(x.first);
            if (x.first == start_node)
                temp.cost = 0;
                info_map[x.first] = temp;
                info_pq.enqueue(temp);

        }

        while (info_map.empty() ==false){
            Info min_info = info_pq.dequeue(); // remove info with smallest cost (initially the start node)
            std::string min_node = min_info.node;
            int min_cost = min_info.cost;

            if (min_cost == std::numeric_limits<int>::max()){ // if min_cost == infinity
                break;
            }

            if (answer_map.has_key(min_node) == false){ //if node isn't in answer_map
                answer_map[min_node] = info_map[min_node]; //3c2
                info_map.erase(min_node);                  //3c3

                for (auto d : g.out_nodes(min_node)){      //3c4
                    if (answer_map.has_key(d) == false){
                        if (info_map[d].cost == std::numeric_limits<int>::max() or
                            info_map[d].cost > min_cost +
                            g.edge_value(min_node, d)){    // if infinite or sum is smaller
                            info_map[d].cost = min_cost + g.edge_value(min_node, d);    //3c4 (1)
                            info_map[d].from = min_node;   // 3c4 (2)
                            info_pq.enqueue(info_map[d]);
                        }
                    }
                }

            }

        }
        return answer_map; // 3d - Info values in answer_map are
                           // filled with min cost to reach each node
                           // and the node preceding it.
}


//Return a queue whose front is the start node (implicit in answer_map) and whose
//  rear is the end node
ArrayQueue <std::string> recover_path(const CostMap &answer_map, std::string end_node) {
        ics::ArrayStack<std::string> stackerino;   // 4
        while (end_node != "?"){                   // while end_node != from (?)
            stackerino.push(end_node);
            std::string prev = answer_map[stackerino.peek()].from;
            end_node = prev;
        }

        return ArrayQueue<std::string> (stackerino);

}


}

#endif /* DIJKSTRA_HPP_ */
