#include <iostream>
#include <fstream>
#include <stdlib.h>
/**
* Matthew Flammia, 23661371
* 323.35 Project 6 SSS
* To compile: g++ -o FlammiaM_Project6_CPP main.cpp
* To run: ./FlammiaM_Project6_CPP.exe SSS_Data.txt Output.txt Debug.txt
* Program will not run if arguments arent supplied or input file cannot be read
**/
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
		this->sourceNode = 1;
		this->minNode = 0;
		this->currentNode = 1;
		this->newCost = 0;
	}
	//methods
	void loadCostMatrix(ifstream& input, ofstream& debug){
		int val1;
		int val2;
		int cost;
		input >> val1;
		while(input >> val1){
			input >> val2;
			input >> cost;
			this->costMatrix[val1][val2] = cost;
		}
		debug<<"Printing Cost Matrix\n";
		for(int i=0;i<=this->numNodes;i++)
			debug<<i<<"\t";
		debug<<endl;
		for(int i=1;i<=this->numNodes;i++){
			debug<<i<<"\t";
			for(int j=1;j<this->numNodes + 1;j++){
				debug<<this->costMatrix[i][j]<<"\t";
			}
			debug<<endl;
		}
	}
	void setBestCostAry(int sourceNode){
		for(int i=1;i<this->numNodes+1;i++){
			this->bestCostAry[i] = this->costMatrix[sourceNode][i]; //if doesnt work flip sourcenode and i
		}
	}
	void setFatherAry(){
		for(int i=1;i<this->numNodes+1;i++){
			this->fatherAry[i] = i;
		}
	}
	void setMarkedAry(int sourceNode){
		for(int i=1;i<=this->numNodes;i++)
			this->markedAry[i] = 0;
		this->markedAry[sourceNode] = 1;
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
		int bestCost;
		bestCost = this->bestCostAry[minNode] + this->costMatrix[minNode][currentNode];
		return bestCost;
	}
	void debugPrint(ofstream& debug, string location){
		debug<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		debug<<location<<endl;
		debug<<"=============================\nPrinting Father Array\n";
		for(int i=1;i<this->numNodes + 1;i++){
			debug<<this->fatherAry[i]<<" ";
		}
		debug<<"\n=============================\nPrinting Best Cost Array\n";
		for(int i=1;i<this->numNodes + 1;i++){
			debug<<this->bestCostAry[i]<<" ";
		}
		debug<<"\n=============================\nPrinting Marked Array\n";
		for(int i=1;i<this->numNodes + 1;i++){
			debug<<this->markedAry[i]<<" ";
		}
		debug<<"\n=============================\nPrinting Values\n";
		debug<<"numNodes = "<<this->numNodes<<endl;
		debug<<"sourceNode = "<<this->sourceNode<<endl;
		debug<<"minNode = "<<this->minNode<<endl;
		debug<<"currentNode = "<<this->currentNode<<endl;
		debug<<"newCost = "<<this->newCost<<endl;
	}
	//todo
	void printShortestPath(int currentNode, int sourceNode, ofstream& output){
		int cost = this->bestCostAry[currentNode];
		output<<"The path from "<<sourceNode<<" to "<<currentNode<<" : ";
		while(currentNode != this->fatherAry[currentNode]){
			output<<currentNode<<"<-";
			currentNode = fatherAry[currentNode];
		}
		output<<currentNode<<"<-"<<sourceNode<<" : cost = "<<cost<<endl;
	}
	bool completelyMarked(){
		for(int i=1;i<this->numNodes + 1;i++){
			if(this->markedAry[i] != 1){
				return false;
			}
		}
		return true;
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
	ofstream output(argv[2]);
	ofstream debug(argv[3]);
	//creates dijktra class
	dijktra path;
	//discovers node amount
	input >> path.numNodes;
	input.close();
	output<<"==============================\n";
	output<<"There are "<<path.numNodes<<" in the input graph. Below are all the pairs of shortest paths:\n";
	output<<"==============================\n";
	output.close();
	//initializing arrays based on number
	//2d array
	path.costMatrix = new int*[path.numNodes + 1];
	for(int i=1;i<path.numNodes+1;i++){
		path.costMatrix[i] = new int[path.numNodes + 1];
	}
	for(int i=1;i<path.numNodes+1;i++){
		for(int j=1;j<path.numNodes+1;j++){
			if(i == j)
				path.costMatrix[i][j] = 0;
			else
				path.costMatrix[i][j] = 99999;
		}
	}
	
	//1d arrys
	path.fatherAry = new int[path.numNodes + 1];
	path.markedAry = new int[path.numNodes + 1];
	for(int i=1;i<path.numNodes+1;i++){
		path.markedAry[i] = 0;
	}
	path.bestCostAry = new int[path.numNodes + 1];
	for(int i=1;i<path.numNodes+1;i++){
		path.bestCostAry[i] = 9999;
	}
	//loads cost matrix
	input.open(argv[1]);
	path.loadCostMatrix(input, debug);
	input.close();
	debug.close();
	//sets best cost array
	path.sourceNode = 1;
	while(path.sourceNode <= path.numNodes){
		path.setBestCostAry(path.sourceNode);
		//sets father array
		path.setFatherAry();
		//sets marked array
		path.setMarkedAry(path.sourceNode);
		//step 3
		while(!path.completelyMarked()){
			path.currentNode = 1;
			path.minNode = path.findMinNode();
			path.markedAry[path.minNode] = 1;
			//debug print
			debug.open(argv[3],ios::app);
			path.debugPrint(debug,"printing from outside");
			debug.close();
			//sets current node
			//loop of steps 5 to 6
			while(path.currentNode <= path.numNodes){
				if(path.markedAry[path.currentNode] == 0){
					path.newCost = path.computeCost(path.minNode, path.currentNode);
					if(path.newCost < path.bestCostAry[path.currentNode]){
						path.bestCostAry[path.currentNode] = path.newCost;
						path.fatherAry[path.currentNode] = path.minNode;
						debug.open(argv[3], ios::app);
						path.debugPrint(debug, "printing from inside");
						debug.close();
					}
				}
				path.currentNode++;
			}
		}
		//path printing begins
		path.currentNode = 1;
		output.open(argv[2],ios::app);
		output<<"Source node = "<<path.sourceNode<<endl<<endl;
		while(path.currentNode <= path.numNodes){
			path.printShortestPath(path.currentNode, path.sourceNode, output);
			path.currentNode++;
		}
		output<<"==============================\n";
		output.close();
		path.sourceNode++;
	}
	return 0;
}