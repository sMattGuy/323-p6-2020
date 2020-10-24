#include <iostream>
#include <fstream>
using namespace std;

class dijktra{
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
	void loadCostMatrix(){
		
	}
	void setBestCostAry(int sourceNode){
		
	}
	void setFatherAry(){
		
	}
	void setMarkedAry(int sourceNode){
		
	}
	int findMinNode(){
		return 0;
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
	dijktra path();
	return 0;
}