/* undirected incidence-list graph implementation */

#include <fstream>
#include <iostream>
#include <string>

#include "dijkstra.h"
#include "undir-inclist-graph.h"

int main(int argc, char** argv)
{
   /*
    * read graph data from file argv[1]
    */
   if(argc < 2)
   {
      std::cerr << "Error! Input file name required as command line argument, but missing.\n";
      return EXIT_FAILURE;
   }
   std::clog << "\tlog output: Reading from " << argv[1] << ".\n";
   
   std::ifstream infile(argv[1]);
   if(!infile)
   {
      std::cerr << "Error! File " << argv[1] << " cannot be read.\n";
      return EXIT_FAILURE;
   }
   
   // normally we would not create the graph on the heap
   // this is done here just to test that "deep copying" works correctly
   graph::UndirInclistGraph* g = new graph::UndirInclistGraph;
   infile >> *g;
   infile.close();
   
   graph::UndirInclistGraph h = *g;  // test copy constructor
   delete g;  // g is gone, does h still work as it should?
   std::cout << "\nContent of h after copying and deallocating g:\n" << h << "\n";
   
   std::string root_label = "";
   std::cout << "\n*** SHORTEST PATH COMPUTATION ***\n\nWhat node do you select as the root? ";
   std::cin >> root_label;
   
   h = std::move(graph::shortest_paths(&h, root_label));  // construct tree of shortest paths
   std::cout << "\nThe following spanning tree was computed, containing the shortest paths from "
             << root_label << ":\n" << h << "\n";
}
