/* undirected incidence-list graph implementation */

#include "undir-inclist-graph.h"

using namespace graph;

// return pointer to node with given label; create a new node only if previously nonexistent
UndirInclistGraphNode* UndirInclistGraph::create_node(std::string node_label)
{
   // if node with the label exists, return pointer to that node
   UndirInclistGraphNode* found = this->find_node(node_label);
   if(found != nullptr) return found;
         
   // otherwise, create a new node, stored in this->nodes
   this->nodes[node_label] =  UndirInclistGraphNode(node_label);
   return &this->nodes[node_label];  // return pointer to the new node
}

// return pointer to a newly created edge
UndirInclistGraphEdge* UndirInclistGraph::create_edge(
   std::string node_a_label, int edge_label, std::string node_b_label
) {
   // "create_node" only creates a new node if needed,
   // otherwise returns pointer to the pre-existing node
   UndirInclistGraphNode* na = this->create_node(node_a_label);
   UndirInclistGraphNode* nb = this->create_node(node_b_label);
   
   // edge object created, owned by this graph object, handled by manual memory management
   UndirInclistGraphEdge* new_edge = new UndirInclistGraphEdge(na, edge_label, nb);
   
   // now connect the nodes to the new edge
   na->append_edge(new_edge);
   nb->append_edge(new_edge);
   
   // update graph object property and return
   this->edges.insert(new_edge);
   return new_edge;
}

// create a single edge based on information from the stream
// if it fails, return nullptr
UndirInclistGraphEdge* UndirInclistGraph::generate_edge_from(std::istream* source)
{
   char single_symbol = '\0';
   
   // read label of the first node
   while(single_symbol != '<')
   {
      *source >> single_symbol;
      if(single_symbol == '\0') return nullptr;  // format: \0 means that we are done
   }
   std::string node_a_label = "";
   for(*source >> single_symbol; single_symbol != '>'; *source >> single_symbol)
      node_a_label += single_symbol;
   if(node_a_label == "") return nullptr;  // format: empty label means that we are done
   
   // read edge label
   int edge_label = 0;
   *source >> edge_label;
   
   // read label of the second node
   while(single_symbol != '<')
   {
      *source >> single_symbol;
      if(single_symbol == '\0') return nullptr;  // format: \0 means that we are done
   }
   std::string node_b_label = "";
   for(*source >> single_symbol; single_symbol != '>'; *source >> single_symbol)
      node_b_label += single_symbol;
   if(node_b_label == "") return nullptr;  // format: empty label means that we are done
   
   return this->create_edge(node_a_label, edge_label, node_b_label);
}

// destructor:
// deallocate objects subject to manual memory management that are owned by this object
// in this case, these are all the edges of the graph; pointers to these edges are stored in this->edges
UndirInclistGraph::~UndirInclistGraph()
{
   // debug output
   std::clog << "\tlog output: calling UndirInclistGraph destructor\n\t\t(this == " << this << ")\n"; 
   
   // deallocate all the edges
   for(auto iter = this->edges.begin(); iter != this->edges.end(); iter++) delete *iter;
}
      
// copy constructor:
// needed for "deep copy" of owned properties subject to manual memory management
UndirInclistGraph::UndirInclistGraph(const UndirInclistGraph& original)
{
   std::clog << "\tlog output: calling UndirInclistGraph copy constructor\n\t\t(this == "
             << this << ", &original = " << &original << ")\n";  // debug output
         
   for(auto iter = original.nodes.begin(); iter != original.nodes.end(); iter++)
      this->create_node(iter->first);
   for(auto iter = original.edges.begin(); iter != original.edges.end(); iter++)
   {
      this->create_edge((*iter)->get_node_a_label(), (*iter)->get_label(), (*iter)->get_node_b_label());
   }
}
      
// overloaded copy assignment operator:
// similar to the copy constructor, but used in case where this object is already constructed
// in our case this means that we need to dispose of the pre-existing edges, then deep-copy the new ones
UndirInclistGraph& UndirInclistGraph::operator=(const UndirInclistGraph& right_hand_side)
{
   std::clog << "\tlog output: calling UndirInclistGraph copy assignment operator\n\t\t(this == "
             << this << ", &right_hand_side = " << &right_hand_side << ")\n";  // debug output

   // deallocate all the edges and clear the sets of edges and nodes
   for(auto iter = this->edges.begin(); iter != this->edges.end(); iter++) delete *iter;
   this->edges.clear();
   this->nodes.clear();
   
   // deep copy of right_hand_side content into this
   for(auto iter = right_hand_side.nodes.begin(); iter != right_hand_side.nodes.end(); iter++)
      this->create_node(iter->first);
   for(auto iter = right_hand_side.edges.begin(); iter != right_hand_side.edges.end(); iter++)
   {
      this->create_edge((*iter)->get_node_a_label(), (*iter)->get_label(), (*iter)->get_node_b_label());
   }
   return *this;
}

// move constructor:
// "this" is getting constructed while at the same time "old" is deallocated
// we don't need to delete all the old edges, just let "this" take them over
UndirInclistGraph::UndirInclistGraph(UndirInclistGraph&& old)
{
   std::clog << "\tlog output: calling UndirInclistGraph move constructor\n\t\t(this == "
             << this << ", &old = " << &old << ")\n";  // debug output
             
   for(auto iter = old.nodes.begin(); iter != old.nodes.end(); iter++)
      this->create_node(iter->first);
   this->edges = old.edges;
   for(auto iter = this->edges.begin(); iter != this->edges.end(); iter++)
   {
      (*iter)->set_nodes(
         this->find_node((*iter)->get_node_a_label()),
         this->find_node((*iter)->get_node_b_label())
      );
   }
   old.edges.clear();
}

// overloaded move assignment operator:
// used for an assignment where "this" already exists and "old" is a rhs term to be deallocated
// compared to the move constructor, we first need to deallocate the pre-existing edges
UndirInclistGraph& UndirInclistGraph::operator=(UndirInclistGraph&& old)
{
   std::clog << "\tlog output: calling UndirInclistGraph move assignment operator\n\t\t(this == "
             << this << ", &old = " << &old << ")\n";  // debug output

   // deallocate all the edges and clear the sets of edges and nodes
   for(auto iter = this->edges.begin(); iter != this->edges.end(); iter++) delete *iter;
   this->edges.clear();
   this->nodes.clear();
   
   for(auto iter = old.nodes.begin(); iter != old.nodes.end(); iter++)
      this->create_node(iter->first);
   this->edges = old.edges;
   for(auto iter = this->edges.begin(); iter != this->edges.end(); iter++)
   {
      (*iter)->set_nodes(
         this->find_node((*iter)->get_node_a_label()),
         this->find_node((*iter)->get_node_b_label())
      );
   }
   old.edges.clear();
   return *this;
}

/*
 * I/O stream operator overloading for UndirInclistGraph
 */
std::istream& operator>>(std::istream& is, graph::UndirInclistGraph& g) {
   g.in(&is);
   return is;
}
std::ostream& operator<<(std::ostream& os, const graph::UndirInclistGraph& g) {
   g.out(&os);
   return os;
}

/*
 * I/O stream operator overloading for UndirInclistGraphEdge
 */
std::ostream& operator<<(std::ostream& os, const graph::UndirInclistGraphEdge& e) {
   e.out(&os);
   return os;
}
