#include <iostream>
#include <stack>
#include <set>
#include <map>
using namespace std;

//This code is takn from techiedelight.com
//Given in the homework questions sheet
// Data structure to store an element and its index in the array
struct Node
{
	int elem;
	int index;
};

// overload compare operator for inserting into set
inline bool operator<(const Node& lhs, const Node& rhs)
{
	return lhs.elem < rhs.elem;
}

// Function to print LIS using parent array
void print(int input[], auto parent, set<Node> S)
{
	// container to store LIS in reverse order
	stack<int> lis;
	
	// start from the last element of S
	int index = S.rbegin()->index;

	// get length of LIS
	int n = S.size();

	// retrieve LIS from parent array
	while (n--)
	{
		lis.push(input[index]);
		index = parent[index];
	}

	// print LIS
	cout << "LIS is ";
	while(!lis.empty())
	{
		cout << lis.top() << " ";
		lis.pop();
	}
}

// Function to find Longest Increasing Subsequence in given array
void printLIS(int arr[], int n)
{
	// create an empty ordered set S (ith element in S is defined as the
	// smallest integer that ends an increasing sequence of length i)
	set<Node> S;

	// parent[i] will store the predecessor of element with index i in the
	// LIS ending at element with index i
	map<int, int> parent;

	// process every element one by one
	for (int i = 0; i < n; i++)
	{
		// construct node from current element and its index
		Node curr = {arr[i], i};

		// ignore the current element if already present in the set
		if (S.find(curr) != S.end()) {
			continue;
		}

		// insert current node into the set and get iterator to the
		// inserted node
		auto it = S.insert(curr).first;

		// if the node is not inserted at the end, then delete the next node
		if (++it != S.end())
			S.erase(it);

		// get iterator to the current node and update parent
		it = S.find(curr);
		parent[i] = (--it)->index;
	}

	// print LIS using parent map
	print(arr, parent, S);
}

// main function
int main()
{
	int arr[] = { 2, 6, 3, 4, 1, 2, 9, 5, 8 };
	int n = sizeof(arr) / sizeof(arr[0]);

	printLIS(arr, n);

	return 0;
}