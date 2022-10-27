#include <map>
#include "dijkstra.h"

using namespace graph;

/*
 * construct a spanning tree for graph g consisting of all the shortest paths
 * with the node labelled root_label as the root node
 */
UndirInclistGraph graph::shortest_paths(UndirInclistGraph* g, std::string root_label)
{
   UndirInclistGraph h;  // this will be the spanning tree containing the shortest paths
   
   UndirInclistGraphNode* present_g_node = g->find_node(root_label);
   if(present_g_node == nullptr) return h;
   
   // only for nodes that we have already added to h:
   // how far are they from the root node?
   h.create_node(root_label);
   std::map<std::string, int> distance_from_root;
   int present_distance = 0;
   std::string connected_label = root_label;
   
   // only for edges from g where we are still considering whether or not to add them to h (they are not in h yet!)
   // key: total distance of target node from the root node if we follow that edge
   std::multimap<int, UndirInclistGraphEdge*, std::less<int>> edge_precedence;
   UndirInclistGraphEdge* next_edge = nullptr;
   
   while(present_g_node != nullptr)
   {
      distance_from_root[connected_label] = present_distance;
      std::clog << "\t\tlog output: <" << connected_label << "> visited at distance " << present_distance << "\n";
      
      auto incident_to_present = present_g_node->get_incident_edges();
      for(auto iter = incident_to_present.begin(); iter != incident_to_present.end(); iter++)
      {
         // if edge **iter leads to a target that we don't have in h yet:
         if( (h.find_node((*iter)->get_node_a_label()) == nullptr) ||
             (h.find_node((*iter)->get_node_b_label()) == nullptr) )
         {
            int distance_to_target = present_distance + (*iter)->get_label();
            edge_precedence.insert({distance_to_target, *iter});
         }
      }

      UndirInclistGraphNode* next_g_node = nullptr;
      while(!next_g_node && !edge_precedence.empty())
      {
         // note that edge_precedence is sorted such that begin()
         // always points to the entry where iter->first is smallest (because we use std::less<int> above)
         auto iter = edge_precedence.begin();  
         
         next_edge = iter->second;
         connected_label = next_edge->get_node_a_label();
         if(h.find_node(connected_label) != nullptr) connected_label = next_edge->get_node_b_label();
         
         if(h.find_node(connected_label) == nullptr)  // node not in h yet
         {
            next_g_node = g->find_node(connected_label);
            present_distance = iter->first;
         }
         edge_precedence.erase(iter);
      }
      if(next_g_node != nullptr)  // we found a node to add, create it in h through the selected edge
      {
         h.create_edge(next_edge->get_node_a_label(), next_edge->get_label(), next_edge->get_node_b_label());
      }
      present_g_node = next_g_node;
   }
   
   return h;
}
