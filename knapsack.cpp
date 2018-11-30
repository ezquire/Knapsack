#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

struct item {
	int val, weight;
};

int dp(int c, vector<int> v, vector<int> w, int n, vector<int>& opt) {
	int i, j;
	int k[n + 1][c + 1];

	// initialize knapsack for DP algorithm
	for(i = 0; i <= n; ++i)
		k[i][0] = 0;
	for(j = 0; j <= c; ++j)
		k[0][j] = 0;

	// fill knapsack array with values
	for(i = 1; i <= n; ++i) {
		for(j = 1; j <= c; ++j) {
			if( w[i - 1] <= j )
				k[i][j] = max( k[i-1][j], (v[i-1] + k[i-1][j - w[i-1]]) );
			else
                 k[i][j] = k[i - 1][j];
		}
	}

	// Backtracking portion to find optimal soln
	j = c; // start at last column
	int res = k[n][c]; //optimal value 
	for(i = n; i > 0 && res > 0; --i) { // start at last row 
		// if the value in the table above is the same don't add it to soln
		if(res == k[i - 1][j]) 
			continue;
		else {
			// add item's index to the optimal soln
			opt.push_back(i);
			// subtract the val of the item from optimal val
			res -= v[i - 1];
			// subtract the weight of the item from capacity
			j -= w[i - 1];
		}
	}
	return k[n][c]; // return the optimal value
}

int greedy(int c, vector<int> v, vector<int> w, int n, vector<int>& opt) {
	return 0;	
}

void getinput(vector<int>& v, vector<int>& w, int& c, vector<item>& items) {

	int val = 0;
	int weight = 0;
	item it;
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
	if(c < 1) {
		cout << "Error: capacity must be > 0\n";
		infile.close();
		exit(-1);
	}
	infile.close();

	// Get the weights of the items
	cout << "Enter file containing the weights: ";
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
		cout << "Error: the number of values and weights must be equal\n";
		exit(-1);
	}

	// add items if # vals and weights are equal
	for(unsigned i = 0; i < v.size(); ++i) {
		it.val = v[i];
		it.weight = w[i];
		items.push_back(it);
	}
}

int main() {
	int n = 0;
	int c = 0;
	vector<int> v;
	vector<int> w;
	vector<int> opt;
	vector<item> i;

	getinput(v, w, c, i);
	
	cout << "\nKnapsack capacity = " << c;
	cout << ". Total number of items = ";
	cout << v.size() << endl;
	n = v.size();

 	auto start = high_resolution_clock::now();
	int res = dp(c, v, w, n, opt);
	auto end = high_resolution_clock::now();
	duration<double> time = end - start;

	cout << "\nDynamic Programming Optimal value: " << res;
	cout << "\nDynamic Programming Optimal subset: {";
	for(unsigned i = opt.size() - 1; i > 0; --i)
		cout << opt[i] << ' ';
	cout << opt[0];
	cout << "}";
	cout << "\nDynamic Programming Time Taken: " << time.count() << endl;

	opt.resize(0);
 	start = high_resolution_clock::now();
	cout << "finish this" << endl;
	end = high_resolution_clock::now();
	time = end - start;
	
	cout << "\nGreedy Approach Optimal value: " << res;
	/*cout << "\nGreedy Approach Optimal subset: {";
	for(unsigned i = opt.size() - 1; i > 0; --i)
		cout << opt[i] << ' ';
	cout << opt[0];
	cout << "}";*/
	cout << "\nGreedy Approach Time Taken: " << time.count() << endl;
	
	return 0;
}
