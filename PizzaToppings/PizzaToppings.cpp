// problem_c.cpp : Defines the entry point for the console application.
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;



/*
This function reads a line of int values into a vector function and returns that vector.
*/
vector<int> readlineofints(int start, int count) {
	// Input money line
	vector<int> linevalues;
	for (int j = start; j < count; j++) {
		int val;
		cin >> val;
		linevalues.push_back(val);
	}
	return linevalues; //Return line values as a vector
}


//Graph code, at least in large part, from http://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-1-dfs-of-unweighted-and-undirected/
//
// A simple representation of graph using STL,
// for the purpose of competitive programming

// A utility function to add an edge in an
// undirected graph.
void addEdge(vector<int> adj[], int u, int v) {
	adj[u].push_back(v);
	adj[v].push_back(u);
}

// A utility function to do DFS of graph recursively from a given vertex u.
//It's been converted to check for bipartite-ness
bool DFSUtil(int u, vector<int> adj[],vector<bool> &visited, vector<int> &color, int last_color) {
	visited[u] = true;
	if (color[u] == -1) { //If this node has no color
		color[u] = 1 - last_color; //Set this note to alternate color of previous node
	}		
	for (int i = 0; i < adj[u].size(); i++) {
		if (visited[adj[u][i]] == false) { //If the next node hasn't been visited, visit it
			if (DFSUtil(adj[u][i], adj, visited, color, color[u]) == false) {
				return false;
			}
		}
		else if (color[adj[u][i]] == color[u]) { //If it has been visited, check to see if it has the same color
			return false; //If it does return false
		}
	}
	return true;
}

// This function does DFSUtil() for all unvisited vertices, tracking color as you go.
bool DFS(vector<int> adj[], int V) {
	vector<bool> visited(V, false);
	vector<int> color(V,-1);
	bool graph_bipartite = true;
	for (int u = 0; u < V; u++) {
		if (visited[u] == false) {
			if (DFSUtil(u, adj, visited, color, 0) == false) { //Start by passing in 0 for color, setting top level to color 1 always
				return false;
			}
		}
	}
	return true;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	
	//get test case count
	int t;
	std::cin >> t;

	//loop over all the test cases
	for (int i = 1; i <= t; i++) {

		// Read in number of toppings and conflicts
		vector<int> params = readlineofints(0, 2);

		//Initialize adjacency list graph
		vector<int>* adj = new vector<int>[params[0]];


		//Iterate over conflicts
		for (int j = 0; j < params[1]; j++) {
			// Input current conflict line
			vector<int> this_conflict = readlineofints(0, 2);
			addEdge(adj, this_conflict[0]-1, this_conflict[1]-1); //Add conflict pair to adjacency list
		}

		bool toppings_work = DFS(adj, params[0]);
		if (toppings_work == true) {
			std::cout << "Case #" << i << ": " << "yes" << std::endl;
		}
		else {
			std::cout << "Case #" << i << ": " << "no" << std::endl;
		}
		delete[] adj;
	}		
	return 0;
}

