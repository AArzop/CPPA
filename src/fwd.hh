#pragma once

typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;


typedef boost::adjacency_list<
   boost::vecS, boost::vecS, boost::directedS,
   boost::property<boost::vertex_bundle_t, VertexProperties>,
   boost::property<boost::edge_bundle_t, EdgeProperties>,
   boost::property<boost::graph_bundle_t, GraphProperties>
> lGraph;

