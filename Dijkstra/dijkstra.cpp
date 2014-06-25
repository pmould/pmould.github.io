#include "graph.h"
#include "SeparateChaining.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <iomanip>
using namespace std;

struct tableRow
{
	string Vertices;
	bool markVertex;
	int totDist;
	string prevVertex;
};

int findMin( tableRow array[100], int size);
void PrintRow(string vertices, int distance, string previous);
void initializeArray(tableRow array[100], vector<string>&  vertices, bool mark, int distance, string previous);
int findIndex(string a, vector<string> v);
int maxElemLength(const vector<string>& a);
void Padding(vector<string>& v);
int getLetterPos(string v, int k);
int GetLetterNum( string number, int k);
vector<queue<string> > ItemsToQueues(const vector<string>& L, int k);
vector<string> QueuesToArray(vector<queue<string> >& QA, int numVals);
void RadixSort(vector<string>& L, int numDigits);
void PrintVector(const vector<string>& L);

void PrintFlightQ(const Queue<string>& FlightQ);
vector<string> BuildGraph (Graph<string>& Flights, char *fileName);
//void Cycle(Graph<string> Flights,string startVertex);

int main( int argc, char *argv[])
{
	if(argc==1)
	{
		exit(1);
		return 0;
	}

//  cout.setf ( ios::right, ios::basefield );       // set hex as the basefield
 // cout.setf ( ios::showbase );                  // activate showbase
 // cout << 100 << endl;
 // cout.setf ( 0, ios::showbase );               // deactivate showbase
 // cout << 100 << endl;
//	cout << "START" << endl;i

//cout << setw(50 ) << "Left"<< endl;
	Graph<string> Flights;
	Queue<string> FlightQ;

	vector<string> v;

	char *fileName = argv[1];	
	//cout <<" FileNAme: "<< file<< endl;
	v = BuildGraph (Flights, fileName);
	vector<string> printV = v;
	Padding(printV);
	RadixSort(printV, maxElemLength(printV));
        PrintVector(printV);
	int currIndex;
	int vNum = v.size();
	tableRow myArray[100];
	initializeArray( myArray, v, false, INT_MAX, "");

	
	/*for (int i  = 0; i< vNum;i++)
	{
		cout << "v: "<< v[i]<<" "<< i <<endl;
	}
*/

	

//Cycle(Flights,"Atlanta");

	string currVertex;
	cout << endl;
	cout << "Please input your starting vertex: ";
	cin >> currVertex;
	cout <<endl;
//	cout << "startingVertex: "<<currVertex <<endl;
	//cout <<"Index Value of starting vertice within array of strings: "<< findIndex(currVertex, v)<< endl;


	int markCount =0;
	 currIndex = findIndex(currVertex, v);
	myArray[currIndex].markVertex = true;
	markCount++;
	myArray[currIndex].totDist = 0;
	myArray[currIndex].prevVertex = "N/A"; 

	cout << setfill('-') << setw(85) <<"-"<<endl;
	cout << setfill(' ') << setw(30) << "Vertex"<< setw(25) <<"Distance"<< setw(30)<< "Previous" <<endl;
	cout << "\n";
	PrintRow(myArray[currIndex].Vertices,0, "N/A");

	string adjVertex;
	int adjIndex;
	int weight;
	int minIndex;

	while(markCount != vNum)	
	{
//cout << " Start of looking at Graph: " << endl;
		Flights.GetToVertices(myArray[currIndex].Vertices, FlightQ);
		
//cout << " After GetToVertices " << endl;
		while(!FlightQ.isEmpty())
		{
//cout << " Second While loop " << endl;
		adjVertex = FlightQ.getFront();
//cout << " FLightsQ.getFront(): " << FlightQ.getFront()<< endl;
	 	adjIndex = findIndex(adjVertex, v);
//cout << " adjIndex:  "<< adjIndex << endl;
		weight = Flights.WeightIs(myArray[currIndex].Vertices,myArray[adjIndex].Vertices);
//cout << " Weight:  " << weight<< endl;
			if(myArray[adjIndex].markVertex == false    &&   myArray[adjIndex].totDist > (weight+myArray[currIndex].totDist)  )
			{
//cout << " First If Statement " << endl;
				myArray[adjIndex].totDist = (weight+myArray[currIndex].totDist);
//cout << " myArray[adjIndex].totDist:  " << myArray[adjIndex].totDist << endl;
			
			

			myArray[adjIndex].prevVertex = myArray[currIndex].Vertices;
//cout << "prevVertex:  "<< myArray[adjIndex].prevVertex << endl;
		
//cout << " DEQUEUE!!!!!!" << endl;
			}
			FlightQ.dequeue();
		}	

		minIndex = findMin(myArray,vNum);
//cout << " FindMin() minIndex:  "<< findMin(myArray, vNum) << endl;
		currIndex = minIndex;
//cout << " After setting currIdex to minIndex " << endl;
		myArray[currIndex].markVertex = true;	
//cout <<" After reinitializing Curr " << endl;
		PrintRow( myArray[currIndex].Vertices, myArray[currIndex].totDist, myArray[currIndex].prevVertex);
//cout << " After printRow" << endl;
		
		markCount++;

	}
		
		

	
	
	





	cout << endl;
	cout << endl;
	cout << setfill('-') << setw(85) <<"-"<<endl;
	cout << setfill(' ');
	cout << endl;
/* MY ATTEMT AT THE EXTRA CREDIT WHICH DIDNT COMPILE
 
	int count=0;
//	v = printV;
	string root;
	Queue<string> Q;
	stack<string> aStack;
	string TopVertex;
	string startVertex;
	int found = false;
	cout << "BEFORE FOR LOOP"<< endl;
	for (int i = 0; i < v.size() && !found; i++)
	{
		count = 0;
cout << "start of forLoop and city in array: "<< i<< endl;	
		startVertex = v[i];
cout << "startVertex: "<< startVertex<<endl;
		aStack.push(startVertex);
//cout << "aStack.: "<< startVertex<<endl;
		while(!aStack.empty() && !found)
		{
cout << "Inside First While Loop: "<<endl;

			TopVertex = aStack.top();
			aStack.pop();
			if ( TopVertex == startVertex && count ==1 )
			{	
//cout << "TopVertex City in Cycle: "<< TopVertex <<endl;
cout << "FOUND!!!!!!! A CYCLE"<<endl;
				{
			//	STORE ROOT VERTICE OF A  CYCLE
				string root = TopVertex;	
				found = true;	
				cout << "Root:" << TopVertex<< endl;
				}
			}
			else
			{
//cout << "ELSE STATEMENT: "<<endl;
				if( TopVertex == startVertex)
				{	
//cout << "IF THEY ARE THE SAME TopV and StartV: "<<endl;
				count++;
				}
				if (!Flights.IsMarked(TopVertex))
				{

cout << "TopVertex City in Cycle: "<< TopVertex <<endl;


//cout << "LAST IF STATEMENT "<<endl;
				//	STORE VERTEX OF A CYCLE
					Flights.MarkVertex(TopVertex);
//cout << "AFTER MARK VERTEX v[i]: "<< TopVertex <<endl;
//cout << "What is going on !!!!!!!!!!!!!!"<<endl;
			string S = TopVertex;
//cout << "What is going on AGAINNN!!!!!!!!!!!!!!"<<endl;
					Flights.GetToVertices(S,Q);

//cout << "AFTER GET ADJACENT VETICES INTO Q Q.getFront():  "<<endl;
					while (!Q.isEmpty() && !Flights.IsMarked(Q.getFront()))
					{
//cout << "SECOND WHILE LOOP "<<endl;
						aStack.push(Q.getFront());
						Q.dequeue();
//cout << "After DEQUE "<<endl; 
					} 

								

				}
			}
//cout << "END OF WHILE LOOP "<<endl

		}

	}
	
	if (found == true)
		cout << "The graph contains a cycle at " << root << endl;
	else
		cout << "The graph does not contain a cycle!!!!"<< endl;

*/
	

	return 0;	
}


/*
void Cycle(Graph<string>& Flights,string startVertex)
{
	cout << startVertex<<endl;
	Queue <string> Q;
	Flights.MarkVertex(startVertex);
	Flights.GetToVertices(startVertex, Q);
	 while (!Q.isEmpty())
	{
		Cycle(Flights,Q.getFront());
	}
	
}
*/

int findMin( tableRow array[100], int size)
{
//cout << "Start of findMin()" << endl;
	int index;
	int minimum=INT_MAX;
	for ( int i =0; i < size;i++)
	{
//cout << " For loop findmin " << endl;
		if (minimum > array[i].totDist && array[i].markVertex == false)
		{
			minimum = array[i].totDist;
			index =  i;
//cout << " if statment find Min after index:  "<< index  << endl;
		}
	}
//cout << " EndOf FindMin " << endl;
	return index;
}

void PrintRow(string vertices, int distance, string previous)
{
//int indention = 30-vertices.length();
//cout << "Length: "<< indention<<endl;

cout << setw(30) << vertices;
cout << setw(25) << distance;
cout << setw(30) << previous;
cout<< endl;
//cout << vertices<<endl;
}



int findIndex(string a, vector<string> v)
{
//cout << "start findIndex()"<< endl;
	for (int i=0;i<v.size();i++)
	{
//		cout <<"v: "<<v[i]<<" "<< i<<endl;
//		cout << "start forLoop "<<endl;
		if ( a == v[i])
			return i;
	
	}
	return -1;
}

void initializeArray(tableRow array[100], vector<string>&  vertices, bool mark, int distance, string previous)
{
	for(int i = 0; i < vertices.size();i++)
	{
        	array[i].Vertices= vertices[i];
        	array[i].markVertex = mark;
        	array[i].totDist = distance;
       		array[i].prevVertex= previous;
	}
}

vector<string> BuildGraph (Graph<string>& Flights, char *fileName)
{
//cout << "Start of Build Graph" << endl;


	vector<string> vertices;

	const string NotFound = "ZZZ";
	ifstream infile;
	infile.open(fileName);
	string aline; 
	string city1, city2; int weight;
	HashTable<string> Cities(NotFound, 34);

//cout << "After initializing Hash" << endl;
	
	getline(infile,aline);	
	city1 = aline.substr(0,aline.find(";"));
//	cout << "city1:"<<city1<< endl;
	city2 = aline.substr( aline.find(";")+1   ,   aline.find_last_of(";") - aline.find(";") -1   );
//	cout <<"city2:"<< city2<<endl;
	string w = aline.substr(aline.find_last_of(";")+1);	
	weight = atoi(w.c_str());
//	cout << "Weight:" <<weight<< endl;

//cout << "After inputting from infile" << endl;
	while (infile)
	{

//cout << "Inside While loop" << endl;
		if ((Cities.find(city1) != city1))
		{	Flights.AddVertex(city1);Cities.insert(city1);
			vertices.push_back(city1);
		 }
	
		if ((Cities.find(city2) != city2))
		{	Flights.AddVertex(city2); Cities.insert(city2);
			vertices.push_back(city2);
		 }
		
		Flights.AddEdge(city1,city2, weight);

		getline(infile,aline);
        	city1 = aline.substr(0,aline.find(";"));
//        	cout << "city1:"<<city1<< endl;
        	city2 = aline.substr( aline.find(";")+1   ,   aline.find_last_of(";") - aline.find(";") -1   );
//        	cout <<"city2:"<< city2<<endl;
        	string w = aline.substr(aline.find_last_of(";")+1);
        	weight = atoi(w.c_str());
//        	cout << "Weight:" <<weight<< endl;

//cout << "Endof of a while loop" << endl;


	}

	return vertices;
}




void PrintFlightQ(const Queue<string>& FlightQ)
{
//cout << "Print Flight" << endl;
	Queue<string> TempQ = FlightQ;
	while (! TempQ.isEmpty())
	{

//cout << "while loop Print" << endl;
		cout << TempQ.getFront() << endl;
		TempQ.dequeue();
//cout << "endwhile loop Print" << endl;
	}
}





//Returns the length of the longest string in an array of strings
int maxElemLength(const vector <string>& v)
{
	int max= v[0].length();
	for ( int i= 0; i<v.size()-1;i++)
	{
		if ( max < v[i+1].length())
		{
			max = v[i+1].length();
		}
	}
	return max;
}

// This method  pads the ends of all strings(whose smaller than the largest string) with the space character so that all strings are of the same size
void Padding( vector<string>& v)
{	
	for(int i = 0; i<v.size();i++)
	{
		while(v[i].length()< maxElemLength(v) )	
		{
			v[i] = v[i] +  " ";	
		}
		
	}
}	

//Gets the index position  of a character in the string. This index number is used to find rhw integer value of this character in the GetLetterNum function
int getLetterPos(string v, int k)
{
	return( v.length()-1-k);
}




	
//Returns the integer value of the character that is used to put it at that characters bucket index in the array of queues
int GetLetterNum( string  number, int k)
{	 
	int m = getLetterPos(number,k);
	 int letterNum = (int) number[m];
	 return letterNum;	
}



// Puts the strings in the array to the appropriate queue in the array of queues or buckets

vector<queue<string> > ItemsToQueues(const vector<string>& L, int k)
{
	vector<queue<string> > v(500);

	for (int i= 0; i < L.size(); i++)
	{
		v[GetLetterNum(L[i],k)].push(L[i]);
	}

	return v;
}

// Copies over the strings in the queues in the array of queues to an array of strings. THis array of strings is then returned
vector<string> QueuesToArray(vector<queue<string> >& QA, int numVals)
{
	vector<string>  L(numVals);
	int index = 0;
	for (int i =0; i < QA.size();i++)
	{
		while(!QA[i].empty())
		{
			L[index] = QA[i].front();		
			QA[i].pop();
			index++;
		}
	
	}	
	return L;
}
//Performs a Radix Sort on a array of strings
void RadixSort(vector<string>& L, int numDigits)
{
 	vector<queue<string> > QA(500);
	for(int i=0; i<numDigits; i++)
	{
		QA = ItemsToQueues(L, i);
		L = QueuesToArray(QA,L.size());
	}
}
// Prints out an array of strings
void PrintVector( const vector<string>& L)
{	
	
	int count = 0;
	cout<< "\n\t ^^^^^^^^^^^^^^^^   DIJKSTRA'S ALGORITHM   ^^^^^^^^^^^^^^^^\n"<<endl;
	cout << "\tA Weighted Graph Has Been Built For These 7 cities :\n" <<endl;
	for (int i=0; i<L.size();i++)
	{
		cout << "\t"<< L[i];
		count++;
		if (count == 3)
		{
			cout <<"\n";
			count = 0;
		}
	}
	cout <<endl;
}
	





