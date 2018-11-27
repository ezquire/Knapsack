#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int max (int a, int b) { return (a > b) ? a : b; }

int knapsack(int c, vector<int> v, vector<int> w, int n, vector<int>& opt) {
	if( n == 0 || c == 0 )
		return 0;

	if( w[n - 1] > c )
		return knapsack(c, v, w, n - 1, opt);

	else {
		int included = v[n - 1] + knapsack(c - w[n - 1], v, w, n - 1, opt);
		int excluded = knapsack(c, v, w, n - 1, opt);
		int subset = max(included, excluded);

		// logic for subsets
		if ( subset == included)
			opt.push_back((n - 1) + 1);
		
		return subset;
	}
}

int main() {
	int n = 0;
	int val = 0;
	int weight = 0;
	int c = 0;
	vector<int> v;
	vector<int> w;
	vector<int> opt;

	string filename;
	ifstream infile;

	// Get the capacity of the "knapsack"
	cout << "Enter file containing the capacity: ";
	cin >> filename;	
	infile.open(filename.c_str(), ios::in);
	if(infile.fail()) {
		cout << "Error opening file: " << filename << endl;
		exit(-1);
	}
	infile >> c;
	infile.close();

	// Get the weights of the items
	cout << "Enter file containing the weight: ";
	cin >> filename;
	infile.open(filename.c_str(), ios::in);
	if(infile.fail()) {
		cout << "Error opening file: " << filename << endl;
		exit(-1);
	}
	while(infile >> weight)
		w.push_back(weight);
	infile.close();

	// Get the values of the items
	cout << "Enter file containing the values: ";
	cin >> filename;
	infile.open(filename.c_str(), ios::in);
	if(infile.fail()) {
		cout << "Error opening file: " << filename << endl;
		exit(-1);
	}
	while(infile >> val)
		v.push_back(val);
	infile.close();

	// Check for equal number of values and weights
	if(v.size() != w.size()) {
		cout << "Error the number of values and weights must be equal" << endl;
		exit(-1);
	}
	
	cout << "\nKnapsack capacity = " << c;
	cout << ". Total number of items = ";
	cout << v.size() << endl;

	n = v.size();

	cout << "\nDynamic Programming Optimal value: " << knapsack(c, v, w, n, opt);
	cout << "\nDynamic Programming Optimal subset: {" << endl;
	for(unsigned i = 0; i < opt.size(); ++i)
		cout << opt[i] << ' ';
	cout << " }\n";
	return 0;
}
