#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "undir-inclist-graph.h"

namespace graph
{
   UndirInclistGraph shortest_paths(UndirInclistGraph* g, std::string root_label);
}

#endif
