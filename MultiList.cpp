// MultiList.cpp : Defines the entry point for the console application.
//Veerpartap Singh
//Project 2 CSCI 36200

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;



typedef struct _NODE //definition of node
{
	int StudentNum;
	int ClassNum;
	int Grade;
	struct _NODE *NextStudent;
	struct _NODE *NextClass;
	_NODE()
	{
		NextStudent = NULL;
		NextClass = NULL;
	}
	_NODE(int sn, int cn)
	{
		StudentNum = sn;
		ClassNum = cn;
		NextStudent = NULL;
		NextClass = NULL;
	}
} Node;

vector<Node *> indexStudent; //student index nodes
vector<Node *> indexClass; //class index nodes

//in the case there exists the node with same student number return true
//in the case there doesn't exist the node with same student number return false
bool findMatchNodeWithStudent(Node* start, Node *node, Node*& match) //find node with the same StudentNum with the specific one
{
	Node *currentNode = start;
	while(currentNode->NextStudent)
	{
		if(currentNode->StudentNum == node->StudentNum)
		{
			match = currentNode;
			return true;
		}
		currentNode = currentNode->NextStudent;

	}
	if(currentNode->StudentNum == node->StudentNum)
	{
		match = currentNode;
		return true;
	}
	match = currentNode;
	return false;
}

bool findMatchNodeWithClass(Node* start, Node *node, Node*& match) //find node with the same ClassNum with the specific one
{
	Node *currentNode = start;
	while(currentNode->NextClass)
	{
		if(currentNode->ClassNum == node->ClassNum)
		{
			match = currentNode;
			return true;
		}
		currentNode = currentNode->NextClass;

	}
	if(currentNode->ClassNum == node->ClassNum)
	{
		match = currentNode;
		return true;
	}
	match = currentNode;
	return false;
}

void linkWithStudentIndex(Node *node) //create or link with the student index node
{
	Node *match;
	bool rv;
	unsigned int i;
	for(i = 0; i < indexStudent.size(); i++)
	{
		if(indexStudent[i]->StudentNum == node->StudentNum)
			break;
	}
	
	if(i == indexStudent.size())
	{
		indexStudent.push_back(node);
	}
	else
	{
		rv = findMatchNodeWithClass(indexStudent[i], node, match);
		if(rv == true)
			return;
		match->NextClass = node;
	}
}

void linkWithClassIndex(Node *node) //create or link with the class index node
{
	Node *match;
	bool rv;
	int i;
	for(i = 0; i < indexClass.size(); i++)
	{
		if(indexClass[i]->ClassNum == node->ClassNum)
			break;
	}
	
	if(i == indexClass.size())
	{
		indexClass.push_back(node);
	}
	else
	{
		rv = findMatchNodeWithStudent(indexClass[i], node, match);
		if(rv == true)
			return;
		match->NextStudent = node;
	}
}


void insertNode(Node *node) //insert node to multilist
{
	linkWithClassIndex(node);
	linkWithStudentIndex(node);

}
void outputWithStudent(Node *node) //output by student
{
	int student = node->StudentNum;
	int clas = node->ClassNum;
	cout<<"student "<<student<<" : classes "<<clas;
	Node *currentNode = node->NextClass;
	while(currentNode)
	{
		cout<<","<<currentNode->ClassNum;
		currentNode = currentNode->NextClass;
	}
	cout<<endl;
}
void outputWithClass(Node *node) //output by class
{
	int student = node->StudentNum;
	int clas = node->ClassNum;
	cout<<"class "<<clas<<" : students "<<student;
	Node *currentNode = node->NextStudent;
	while(currentNode)
	{
		cout<<","<<currentNode->StudentNum;
		currentNode = currentNode->NextStudent;
	}
	cout<<endl;
}
void output() //output
{
	for(int i = 0; i < indexClass.size(); i++)
		outputWithClass(indexClass[i]);
	cout<<endl<<endl;
	for(int i = 0; i < indexStudent.size(); i++)
		outputWithStudent(indexStudent[i]);
}
void finalize() //release memory
{
	for(int i = 0 ; i < indexClass.size(); i++)
	{
		Node *currentNode = indexClass[i];
		while(currentNode)
		{
			Node *temp = currentNode;
			currentNode = currentNode->NextStudent;
			delete temp;
		}

	}
	
	
}

string getFirstPart(string& total, char delim) //get first string seperated by delimiter
{
	int k = total.find_first_of(delim);
	string temp = total;
	if (k == total.npos)
	{
		total = "";
		return temp;
	}
	total = total.substr(k + 1, total.length() - k - 1);
	return temp.substr(0, k);
}
void stripParenth(string &str) //remove the parenthesis
{
	if (str[0] == '[' && str[str.length() - 1] == ']')
	{
		str = str.substr(1, str.length() - 2);
		return;
	}
	if (str[0] == '(' && str[str.length() - 1] == ')')
		str = str.substr(1, str.length() - 2);
}

int main()
{
	int st, cl;
	string line;

	cout<<"Input data in this format"<<endl<<"(x1,y1)"<<endl<<"(x2,y2)"<<endl<<"..."<<endl<<"After you are done type for result (-1,-1)"<<endl;
	/*	input format
		3,4  or  (3,4)
		4,6  or  (4,6)
		4,5  or  (4,5)
		end: -1,-1  or  (-1,-1)
				*/
	while(getline(std::cin, line))
	{
		stripParenth(line);
		st = atoi(getFirstPart(line, ',').c_str());
		cl = atoi(line.c_str());

		if(st == -1 && cl == -1)
			break;
		Node *node = new Node(st, cl);
	    insertNode(node);

	}

/*	while(cin>>st>>cl)
	{
		if(st == -1 && cl == -1)
			break;
		Node *node = new Node(st, cl);
	    insertNode(node);
	} */
	output();
	finalize();
	return 0;
}

