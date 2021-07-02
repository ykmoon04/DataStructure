//--------------------------------------------------------------------
//
//  Laboratory 14                                          wtgraph.cpp
//
//  Implementation of the Weighted Graph ADT
//
//--------------------------------------------------------------------
#include "wtgraph.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------------

WtGraph::WtGraph(int maxNumber)
{
	maxSize = maxNumber;
	size = 0;
	vertexList = new Vertex[maxSize];
	adjMatrix = new int[maxSize*maxSize];
	pathMatrix = new int[maxSize * maxSize];

	for (int i = 0; i < maxSize * maxSize; i++) {
		adjMatrix[i] = infiniteEdgeWt;
		pathMatrix[i] = infiniteEdgeWt;
	}
}

WtGraph::~WtGraph()
{
	delete[] vertexList;
	delete[] adjMatrix;
}

//--------------------------------------------------------------------

int WtGraph::getIndex(char* v)
{
	for (int i = 0; i < size; i++) {
		if (strcmp(vertexList[i].label,v)==0)
			return i;
	}

	return -1; 
}

int WtGraph::getEdge(int row, int col)
{
	return adjMatrix[row * maxSize + col];
}

void WtGraph::setEdge(int row, int col, int wt) 
{
	adjMatrix[row * maxSize + col] = wt;
	adjMatrix[col * maxSize + row] = wt;
}

//--------------------------------------------------------------------

void WtGraph::insertVertex(Vertex newVertex)
{
	// pre: not full
	if (isFull()) {
		cout << "Graph is full" << endl;
		return;
	}
	// if the vertex already exists in the graph, then updates it
	int  idx = getIndex(newVertex.label);
	if (idx != -1) {
		vertexList[idx] = newVertex;
	}
	else {
		vertexList[size++] = newVertex;
	}

}

void WtGraph::insertEdge(char* v1, char* v2, int wt)
{
	// pre: Graph includes vertices v1 and v2
	int row = getIndex(v1);
	int col = getIndex(v2);

	if (row == -1 || col == -1) {
		cout << "Failed -- Either v1 and v2 doesn't exist" << endl;
		return;
	}

	// if there is already an edge, then updates the weight of the edge
	setEdge(row, col, wt);
}

//--------------------------------------------------------------------

bool WtGraph::retrieveVertex(char* v, Vertex& vData)
{
	// search a graph for vertex v
	int idx = getIndex(v);
	if (idx == -1) {
		return false;
	}
	else {
		vData = vertexList[idx];
		return true;
	}
}

bool WtGraph::getEdgeWeight(char* v1, char* v2, int& wt)
{
	// pre: Graph includes vertices v1 and v2
	int row = getIndex(v1);
	int col = getIndex(v2);

	if (row == -1 || col == -1) {
		return false;
	}

	if (getEdge(row, col) != infiniteEdgeWt) {
		wt = adjMatrix[row * maxSize + col];
		return true;
	}
	else {
		return false;
	}
}

//--------------------------------------------------------------------

void WtGraph::removeVertex(char* v)
{
	int idx = getIndex(v);
	// pre: graph includes vertex v
	if (idx == -1) {
		cout << "Vertex NOT found" << endl;
		return;
	}

	for (int i = idx; i < size-1; i++) {
		vertexList[i] = vertexList[i + 1];
	}	

	for (int i = 0; i < size; i++) {
		for (int j = idx; j < size - 1; j++) {
			adjMatrix[i * maxSize + j] = adjMatrix[i * maxSize + j + 1];
		}
		adjMatrix[i * maxSize + size - 1] = infiniteEdgeWt;
	}

	for (int i = idx; i < size - 1; i++) {
		for (int j = 0; j < maxSize; j++) {
			adjMatrix[i * maxSize + j] = adjMatrix[(i + 1) * maxSize + j];
		}
	}

	for (int i = 0; i < maxSize; i++) {
		adjMatrix[(size - 1) * maxSize + i] = infiniteEdgeWt;
	}
	size--;
}

void WtGraph::removeEdge(char* v1, char* v2)
{
	// pre: Graph includes vertices v1 and v2
	int row = getIndex(v1);
	int col = getIndex(v2);

	if (row == -1 || col == -1) {
		cout << "Failed -- Either v1 and v2 doesn't exist" << endl;
		return;
	}

	setEdge(row, col, infiniteEdgeWt);
}

//--------------------------------------------------------------------

void WtGraph::clear()
{
	size = 0;
	for (int i = 0; i < maxSize * maxSize; i++) {
		adjMatrix[i] = infiniteEdgeWt;
	}
}

bool WtGraph::isEmpty() const
{
	return (size == 0);
}

bool WtGraph::isFull() const
{
	return (size == maxSize);
}

//--------------------------------------------------------------------

void WtGraph::showStructure()

// Outputs a graph's vertex list (w/ color) and adjacency matrix.
// This operation is intended for testing/debugging purposes only.

{
	int wt,         // Edge weight
		row, col;   // Loop counters

	if (size == 0)
		cout << "Empty graph" << endl;
	else
	{
		cout << endl << "Vertex list : " << endl;
		for (row = 0; row < size; row++)
			cout << row << '\t' << vertexList[row].label << endl;

		cout << endl << "Edge matrix : " << endl << '\t';
		for (col = 0; col < size; col++)
			cout << col << '\t';
		cout << endl;
		for (row = 0; row < size; row++)
		{
			cout << row << '\t';
			for (col = 0; col < size; col++)
			{
				wt = getEdge(row, col);
				if (wt == infiniteEdgeWt)
					cout << "- \t";
				else
					cout << wt << '\t';
			}
			cout << endl;
		}

		cout << endl << "Path matrix : " << endl << '\t';
		for (col = 0; col < size; col++)
			cout << col << '\t';
		cout << endl;
		for (row = 0; row < size; row++)
		{
			cout << row << '\t';
			for (col = 0; col < size; col++)
			{
				wt = getPath(row, col);
				if (wt == infiniteEdgeWt)
					cout << "- \t";
				else
					cout << wt << '\t';
			}
			cout << endl;
		}
	}
}

//--------------------------------------------------------------------


 int WtGraph::getPath(int row, int col)
 {
	 return pathMatrix[row * maxSize + col];
 }

void WtGraph::setPath(int row, int col, int wt) {
	pathMatrix[row * maxSize + col] = wt;
	pathMatrix[col * maxSize + row] = wt;
 }

 void WtGraph::computePaths() 
 {
	 // init
	 for (int i = 0; i <size; i++) {
		 for (int j = 0; j < size; j++) {
			 if (i == j) pathMatrix[i * maxSize + j] = 0;
			 else pathMatrix[i * maxSize + j] = adjMatrix[i * maxSize + j];
		 }
	 }

	 for (int m = 0; m < size; m++) {
		 for (int j = 0; j < size; j++) {
			 for (int k = 0; k < size; k++) {
				 int path1 = getPath(j, m);
				 int path2 = getPath(m, k);
				 int path = getPath(j, k);
				 if (path1 != infiniteEdgeWt && path2 != infiniteEdgeWt && path1 + path2 < path) {
					 setPath(j, k, path1+path2);
				 }
			 }
		 }
	 }

 }