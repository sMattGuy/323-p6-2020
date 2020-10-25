#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

class dijktra{
	public:
	//instance variables
	int numNodes;
	int sourceNode;
	int minNode;
	int currentNode;
	int newCost;
	//pointers
	int** costMatrix;
	int* fatherAry;
	int* markedAry;
	int* bestCostAry;
	//constructor
	dijktra(){
		this->numNodes = 0;
		this->sourceNode = 0;
		this->minNode = 0;
		this->currentNode = 0;
		this->newCost = 0;
	}
	//methods
	void loadCostMatrix(ifstream& input){
		int val1;
		int val2;
		int cost;
		input >> val1;
		while(input >> val1){
			input >> val2;
			input >> cost;
			this->costMatrix[val1][val2] = cost;
		}
	}
	void setBestCostAry(int sourceNode){
		
	}
	void setFatherAry(){
		
	}
	void setMarkedAry(int sourceNode){
		
	}
	int findMinNode(){
		int minCost = 99999;
		this->minNode = 0;
		int index = 1;
		while(index <= this->numNodes){
			if(this->markedAry[index] == 0){
				if(this->bestCostAry[index] < minCost){
					minCost = this->bestCostAry[index];
					this->minNode = index;
				}
			}
			index++;
		}
		return minNode;
	}
	int computeCost(int minNode,int currentNode){
		return 0;
	}
	void debugPrint(){
		
	}
	void printShortestPath(){
		
	}
};

int main(int argc, char* argv[]){
	//checks that correct args were supplied
	if(argc != 4){
		cout<<"Must have 3 arguments in this command to run correctly.\nDatafile, Results, Debug\n";
		return -1;
	}
	//creates input stream and checks that its readable
	ifstream input(argv[1]);
	if(!input.good()){
		cout<<"Failed to read input file, was name typed correctly?\n";
		return -1;
	}
	//creates dijktra class
	dijktra path;
	//discovers node amount
	int nodeCount = 0;
	input >> nodeCount;
	if(nodeCount > path.numNodes)
		path.numNodes = nodeCount;
	while(input >> nodeCount){
		if(nodeCount > path.numNodes)
			path.numNodes = nodeCount;
		input >> nodeCount;
		if(nodeCount > path.numNodes)
			path.numNodes = nodeCount;
		input >> nodeCount;
	}
	input.close();
	
	//initializing arrays based on number
	cout<<path.numNodes<<endl;
	//2d array
	path.costMatrix = new int*[path.numNodes + 1];
	for(int i=0;i<path.numNodes+1;i++){
		path.costMatrix[i] = new int[path.numNodes + 1];
	}
	for(int i=0;i<path.numNodes+1;i++){
		for(int j=0;j<path.numNodes+1;j++){
			if(i == j)
				path.costMatrix[i][j] = 0;
			else
				path.costMatrix[i][j] = 99999;
		}
	}
	//1d arrys
	path.fatherAry = new int[path.numNodes + 1];
	for(int i=0;i<path.numNodes+1;i++){
		path.fatherAry[i] = i;
	}
	path.markedAry = new int[path.numNodes + 1];
	for(int i=0;i<path.numNodes+1;i++){
		path.markedAry[i] = 0;
	}
	path.bestCostAry = new int[path.numNodes + 1];
	for(int i=0;i<path.numNodes+1;i++){
		path.bestCostAry[i] = 99999;
	}
	
	input.open(argv[1]);
	path.loadCostMatrix(input);
	input.close();
	
	return 0;
}