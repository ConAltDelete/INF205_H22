/* undirected incidence-list graph implementation */

#ifndef UNDIR_INCLIST_GRAPH_H
#define UNDIR_INCLIST_GRAPH_H

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

/*
 * Memory management rule for the classes below: 
 * It is the graph (UndirInclistGraph) object that has ownership over all its nodes and edges.
 * Nodes and edges just access non-owning pointers to each other; they never need to delete each other directly.
 */
namespace graph
{
   class UndirInclistGraphEdge;  // needs to be declared before we can use it in class UndirInclistGraphNode
   
   class UndirInclistGraphNode
   {
   public:
      UndirInclistGraphNode() {}  // default constructor
      UndirInclistGraphNode(std::string in_label) { this->set_label(in_label); }
      
      std::string get_label() const { return this->label; }
      void set_label(std::string in_label) { this->label = in_label; }
      
      std::vector<UndirInclistGraphEdge*> get_incident_edges() const { return this->incidence; }
      void append_edge(UndirInclistGraphEdge* e) { this->incidence.push_back(e); }
      
   private:
      std::string label = "";  // in this implementation, nodes have a string label, taken to be their unique name
      std::vector<UndirInclistGraphEdge*> incidence = std::vector<UndirInclistGraphEdge*>();
   };
   
   class UndirInclistGraphEdge
   {
   public:
      UndirInclistGraphEdge() {}  // default constructor
      UndirInclistGraphEdge(UndirInclistGraphNode* na, int in_label, UndirInclistGraphNode* nb) {
         this->set_nodes(na, nb);
         this->set_label(in_label);
      }

      int get_label() const { return this->label; }
      void set_label(int in_label) { this->label = in_label; }
      
      std::string get_node_a_label() const { return this->node_a->get_label(); }
      std::string get_node_b_label() const { return this->node_b->get_label(); }
      void set_nodes(UndirInclistGraphNode* na, UndirInclistGraphNode* nb) {
         this->node_a = na;
         this->node_b = nb;
      }
      
      // write to *target
      void out(std::ostream* target) const {
         *target << "<" << this->get_node_a_label() << ">\t"
                 << this->label << "\t<" << this->get_node_b_label() << ">\n";
      }

   private:
      int label = 0;  // in this implementation, edges have an int label (could be a weight or a distance); _not_ a unique identifier!
      UndirInclistGraphNode* node_a = nullptr;  // edge connects *node_a to *node_b and vice versa
      UndirInclistGraphNode* node_b = nullptr;  // if it was a directed graph, we might call them "source" and "target"
   };

   class UndirInclistGraph
   {
   public:
      // default constructor
      UndirInclistGraph() {
         // debug output
         std::clog << "\tlog output: calling UndirInclistGraph default constructor\n\t\t(this == " << this << ")\n"; 
      }
      
      // return pointer to the node with given label if it exists, nullptr otherwise
      UndirInclistGraphNode* find_node(std::string node_label) {
         auto iter = this->nodes.find(node_label);
         if(iter == this->nodes.end()) return nullptr;
         else return &(iter->second);
      }

      UndirInclistGraphEdge* create_edge(std::string node_a_label, int edge_label, std::string node_b_label);
      UndirInclistGraphNode* create_node(std::string node_label);  // create new node with given label, if non-existing
      
      // read from *source
      void in(std::istream* source) {
         while(this->generate_edge_from(source)) {}  // read edge by edge, until generate_edge_from returns nullptr
      }
      // write to *target
      void out(std::ostream* target) const {
         for(auto iter = this->edges.begin(); iter != this->edges.end(); iter++)
            (*iter)->out(target);  // output edge by edge
         *target << "<>\n";  // format: empty label for end of content
      }
      
      // destructor:
      // deallocate objects subject to manual memory management that are owned by this object
      ~UndirInclistGraph();
      
      // copy constructor:
      // needed for "deep copy" of owned properties subject to manual memory management
      UndirInclistGraph(const UndirInclistGraph& original);
      
      // overloaded copy assignment operator:
      // similar to the copy constructor, but used in case where this object is already constructed
      UndirInclistGraph& operator=(const UndirInclistGraph& right_hand_side);
      
      // move constructor:
      // "this" is getting constructed while at the same time "old" is deallocated
      UndirInclistGraph(UndirInclistGraph&& old);
      
      // overloaded move assignment operator:
      // used for an assignment where "this" already exists and "old" is a rhs term to be deallocated
      UndirInclistGraph& operator=(UndirInclistGraph&& old);
      
   private:
      // for this implementation, node labels are unique, and we identify nodes through their labels
      // hence it makes sense to use an STL map with the label as the key and the node as the value
      std::map<std::string, UndirInclistGraphNode> nodes = std::map<std::string, UndirInclistGraphNode>();
      
      // one possible solution: edges on the heap, owned by the graph object, accessed through a set of pointers
      std::set<UndirInclistGraphEdge*> edges = std::set<UndirInclistGraphEdge*>();
      
      UndirInclistGraphEdge* generate_edge_from(std::istream* source);  // create a single edge based on information from the stream
   };
}

/*
 * I/O stream operator overloading for UndirInclistGraph
 */
std::istream& operator>>(std::istream& is, graph::UndirInclistGraph& g);
std::ostream& operator<<(std::ostream& os, const graph::UndirInclistGraph& g);

/*
 * I/O stream operator overloading for UndirInclistGraphEdge
 */
std::ostream& operator<<(std::ostream& os, const graph::UndirInclistGraphEdge& e);

#endif
