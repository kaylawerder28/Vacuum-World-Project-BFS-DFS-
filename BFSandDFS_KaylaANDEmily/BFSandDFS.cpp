#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;
// Vacuum World Scenario for BFS and DFS 

class Vacuum {
public:
	string data;
	Vacuum * left;
	Vacuum * right;
	Vacuum() {}; // empty constructor
	Vacuum(string x) { data = x; left = nullptr; right = nullptr; }
};

class Matrix {
public:
	Vacuum * V;
	int size = -1;
	int last = -1;
	
	int ** Matrix2;

	Matrix() {}
	Matrix(int  s) {
		size = s;
		V = new Vacuum[size];
		Matrix2 = new int *[size];
		for (int i = 0; i < size; i++) {
			Matrix2[i] = new int[size];
			for (int j = 0; j < size; j++) {
				Matrix2[i][j]=0;
			}
		}
	}

	void InsertRoom(string room) {	// here we created a function to insert the nodes/rooms we want
		Vacuum vacuum(room);
		last++;
		V[last] = vacuum;
	}

	void InsertHallway(string first, string final, int total) {	// here we created a function to insert a connection between the nodes/rooms
		int start = Search(first);
		int end = Search(final);
		Matrix2[start][end] = total;
		Matrix2[end][start] = total; //creates the connection between rooms both ways
	}

	int Search(string node) {	// function created to search through the tree
		for (int i = 0; i <= last; i++) {
			if (V[i].data == node) return i; // if the node we are searching exists then it returns the node
		}
		return -1;
	}

	void Print() {
		cout << "These are the room numbers: ";
		for (int i = 0; i <= last; i++) {
			cout << V[i].data << " " ; // this prints all of the nodes/room numbers
		}
		cout << endl;
		cout << endl;
	}

	void PrintMatrix() {
		cout << "The path is: " << endl;
		for (int i = 0; i < size; i++) {
			cout << V[i].data << ":  ";
			for (int j = 0; j < size; j++) {
				cout << Matrix2[i][j] << "  "; // this prints the matrix
			}
			cout << endl;
		}
			cout << endl;
	}

	void BreadthFirstSearch(string node) {
		int beginSearch = Search(node);
		bool* enteredRoom = new bool[size]; // did we enter the room, check here
		for (int i = 0; i < size; i++) { enteredRoom[i] = 0; }

		queue <int> q; // create the queue for traversal outputs
		enteredRoom[beginSearch] = true;
		q.push(beginSearch);

		cout << "Completing Breadth First Traversal of the Tree" << endl;
		while (!q.empty()) {
			beginSearch = q.front(); // defined in the queue class
			q.pop(); // removes node from the front of the array in the queue

			cout << V[beginSearch].data << endl;
			for (int i = 0; i < size; i++) {
				if (Matrix2[beginSearch][i] > 0 && !enteredRoom[i]) { // if the room/node exists and is not already an entered room 
					enteredRoom[i] = true; // make it an entered room
					q.push(i);
				}
			}
		}
		cout << endl;
	}

	
	
	void DepthFirstSearchRecursion(int search, bool * enteredRoom) {
		cout << search << endl;

		for (int i = 0; i < size; i++) {
			if (Matrix2[search][i] > 0 && !enteredRoom[i]) {   // if the room/node exists and is not already an entered room 
				enteredRoom[i] = true; // make it an entered room
				DepthFirstSearchRecursion(i, enteredRoom); // continue to recurse after entering room

			}
		}
	}
	void DepthFirstSearch(string node) {
		int beginSearch = Search(node);
		bool* enteredRoom = new bool[size];  // did we enter the room, check here
		for (int i = 0; i < size; i++) { enteredRoom[i] = 0; }
		
		cout << "Completing Depth First Traversal of the Tree" << endl;

		enteredRoom[beginSearch] = true;
		DepthFirstSearchRecursion(beginSearch, enteredRoom); // recurse
		
	
	}
	
	

};

int main()
{
	Matrix* matrix = new Matrix(6);
	matrix->InsertRoom("0");
	matrix->InsertRoom("1");
	matrix->InsertRoom("2");
	matrix->InsertRoom("3");
	matrix->InsertRoom("4");
	matrix->InsertRoom("5");

	matrix->InsertHallway("0", "1", 1);
	matrix->InsertHallway("0", "2", 1);
	matrix->InsertHallway("1", "3", 1);
	matrix->InsertHallway("1", "4", 1);
	matrix->InsertHallway("2", "5", 1);

	matrix->Print();
	cout << endl;
	matrix->PrintMatrix();

	matrix->BreadthFirstSearch("0");
	
	matrix->DepthFirstSearch("0");

	system("pause");
	return 0;
}