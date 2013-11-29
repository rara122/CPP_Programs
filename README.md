Shortestpaths
=============

Algorithms Project for Calculating Shortest Path! 

In this project we will implement Dijkstra's algorithm on a graph using Priority
Queue. The implementation should accept the source node and the description
of the graph in a file. The format of the file would be the same as the Stanford
graph in the last programming assignment. Given this information the code
should be able to compute the lengths of the shortest paths from the source to
all other vertices in the graph. The output should be written to a file out.txt
and should contain the following:


	Dijkstra
	Source : S
	NODE S : 0
	NODE 1 : 7
	NODE 2 : 1
	NODE 3 : 9
	NODE 4 : 5
	NODE 5 : 4
	NODE 6 : 2
	End Dijkstra


Once the Dijkstra's Algorithm has been done we will use another algorithm The
Shortest Reliable Paths Algorithm that was discussed in the review. Here we
are given a number k and a source node S and would like to find the shortest
paths of length at most k, that is one that uses at most k edges, from the source
to every other node in the graph. Let d(v; k) be the shortest path from S to
v that uses at most k edges from the graph. Note that the total weight of the
path is the sum of weights of the edges but there can be at most k edges on the
path. A dynamic programming solution is given by:

	d(v, i) = min(u, v) inTheSet E[d(u, i-1) + w(u, v)]

Use the above recurrence to solve the reliable shortest paths problem. Your
code should use memoization. The input to the code would be the source node
S, the file containing the graph and the integer k. Note that the integer cannot
be more than |V| - 1. The output should be as written in the same file out.txt
below the output for Dijkstra's Algorithm. The output should have the follow-
ing format:


	Shortest Reliable Paths Algorithm
	Integer k : 5 Source : S
	NODE S : 0
	NODE 1 : 7
	NODE 2 : 1
	NODE 3 : 9
	NODE 4 : 5
	NODE 5 : 4
	NODE 6 : 2
	End Shortest Reliable Paths Algorithm


The examples above a cooked up and the numbers don't reflect actual compu-
tation results. In general the shortest paths for Dijkstra will be smaller than
the ones for the Shortest Reliable Paths Algorithm.
