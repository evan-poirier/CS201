/*
Name: Evan Poirier
Email: espoirier@crimson.ua.edu
Course Section: Fall 2024 CS 201
Homework #: 4
*/

#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <limits>
#include <queue>

class Vertex {
public:
	bool visited;
	int distance;
	int previous;
	int finish;
	std::list<int> adj;
};

class Graph {
public:
	Graph(int V, int E, std::pair<int, int> *edges) {
		_V = V;
		_E = E;
		vertices = new Vertex[_V];
		for (int i = 0; i < _V; i++) {
                    vertices[i].visited = false;
                    vertices[i].distance = 65535; // Instead using INFINITY, you can use a large int number to initialize your graph
                    vertices[i].previous = -1;
		}
		for (int i = 0; i < _E; i++) {
		    addEdge(edges[i].first, edges[i].second);
		}
	}

	virtual ~Graph() {
		for (int i=0; i<_V; ++i) {
		    auto adj = vertices[i].adj;
		    adj.clear(); // clear list
		}

		delete[] vertices; // delete array of vertices
	}

	int V() {
		return _V;
	}

	int E() {
		return _E;
	}

	void addEdge(int u, int v) {
		vertices[u].adj.push_back(v);
	}

	std::list<int> getEdges(int u) {
		return vertices[u].adj;
	}

	int degree(int u) {
		return vertices[u].adj.size();
	}

	void bfs(int s) {
		// create queue
		std::queue<int> vertexQueue;

		// initialize all vertices to unvisited, effectively infinite distance, no predecessor
		for (int i = 0; i < _V; i ++) {
			vertices[i].visited = false;
			vertices[i].distance = 65535;
			vertices[i].previous = -1;
		}

		// set starting vertex distance to 0, mark it as visited, and add it to the queue
		vertices[s].distance = 0;
		vertices[s].visited = true;
		vertexQueue.push(s);

		// while there are vertices in the queue...
		while (!vertexQueue.empty()) {
			// read the first vertex, then remove it
			int currVertex = vertexQueue.front();
			vertexQueue.pop();

			// for each vertex adjacent to the current vertex
			for (auto it = vertices[currVertex].adj.begin(); it != vertices[currVertex].adj.end(); it ++) {
				// if the neighbor vertex in question has not been visited:
				//	- mark it as visited
				// 	- set its distance to that of the current vertex + 1
				//  - set its predecessor to the current vertex
				// 	- add it to the queue

				int vertexNum = *it;
				if (!vertices[vertexNum].visited) {
					vertices[vertexNum].visited = true;
					vertices[vertexNum].distance = vertices[currVertex].distance + 1;
					vertices[vertexNum].previous = currVertex;
					vertexQueue.push(vertexNum);
				}
			}
		}
	}

	void dfs() {
		// initalize all vertices to unvisited, with no predecessor. set time to 0.
		for (int i = 0; i < _V; i ++) {
			vertices[i].visited = false;
			vertices[i].previous = -1;
		}
		time = 0;

		// perform dfs_visit on unvisited nodes
		for (int i = 0; i < _V; i ++) {
			if(!vertices[i].visited) {
				dfs_visit(i);
			}
		}

		// print discovery and finishing time for each node
		for (int i = 0; i < _V; i ++) {
			std::cout << i << ": " << vertices[i].distance << "/" << vertices[i].finish << std::endl;
		}
	}

	void dfs_visit(int u) {
		// increment time, set distance of node to time, mark node visited
		time ++;
		vertices[u].distance = time;
		vertices[u].visited = true;

		// for all unvisited neighbors of u, set their previous to u and perform dfs_visit recursively on them
		for (auto it = vertices[u].adj.begin(); it != vertices[u].adj.end(); it ++) {
			int vertexNum = *it;
			if (!vertices[vertexNum].visited) {
				vertices[vertexNum].previous = u;
				dfs_visit(vertexNum);
			}
		}

		// increment time, set finishing time of node to time
		time ++;
		vertices[u].finish = time;
	}

	void print_path(int s, int v) {
		if (v == s)
		   std::cout << s;
		else if (vertices[v].previous == -1)
		   std::cout << "not connected";
		else {
		   print_path(s,vertices[v].previous);
		   std::cout << "->" << v;
		}
	}

	std::string toString() {
		std::stringbuf buffer;
		std::ostream os(&buffer);
		os << "Vertices = " << _V << ", Edges = " << _E << std::endl;
		for (int i = 0; i < _V; ++i) {
		    os << i << "(" << degree(i) << "): ";
		    for (const auto& l : vertices[i].adj) 
			os << l << " ";
		    os << std::endl;
		}

		return buffer.str();
	}
private:
	int _V; // no. of vertices
	int _E; // no. of edges
	Vertex *vertices; // array of vertices
	int time; // measures time during dfs
};

#endif
