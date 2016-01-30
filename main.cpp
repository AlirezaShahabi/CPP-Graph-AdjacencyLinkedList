

#include "Graph.h"
#include <string>
#include <iostream>

int main() {
    
    Graph<std::string> g1;
    
    g1.add_vertex("alex");
    g1.add_vertex("george");
    g1.add_vertex("sara");
    g1.add_vertex("sam");
    g1.add_vertex("tim");
    g1.add_vertex("mike");
    
    g1.add_edge("alex", "george", 1);
    g1.add_edge("alex", "sara", 1);
    g1.add_edge("george", "sam", 1);
    g1.add_edge("sara", "sam", 1);
    g1.add_edge("sara", "tim", 1);
    g1.add_edge("sam", "tim", 1);
    g1.add_edge("george", "mike", 1);
    g1.add_edge("sam", "mike", 1);
    
    g1.find_adj_vertices("alex", std::cout);
    g1.find_adj_vertices("sara", std::cout);
    g1.find_adj_vertices("sam", std::cout);
    g1.find_adj_vertices("tim", std::cout);
    
    std::cout << g1.check_connection("sara", "mike") << std::endl;
    std::cout << g1.check_connection("sara", "tim") << std::endl;
    
    g1.depth_first_search(0, std::cout);
    g1.breadth_first_search(0, std::cout);

    g1.rem_edge("tim", "sara");
    
    g1.find_adj_vertices("alex", std::cout);
    g1.find_adj_vertices("sara", std::cout);
    g1.find_adj_vertices("sam", std::cout);
    g1.find_adj_vertices("tim", std::cout);
    
    std::cout << g1.check_connection("sara", "mike") << std::endl;
    std::cout << g1.check_connection("sara", "tim") << std::endl;
    
    g1.depth_first_search(0, std::cout);
    g1.breadth_first_search(0, std::cout);
        
    return 0;
}


