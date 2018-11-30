#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

int knapsack(int c, vector<int> v, vector<int> w, int n, vector<int>& opt) {
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
	j = c;
	int res = k[n][c]; //optimal value
	for(i = n; i > 0 && res > 0; --i) {
		if(res == k[i - 1][j]) // if the value above in the table is the same
			continue;          // this value is not included in optimal soln
		else {
			opt.push_back(i); // add item's index to the optimal soln
			res -= v[i - 1]; // subtract the value from total 
			j -= w[i - 1];   // subtract the weight from total
		}
	}
	return k[n][c];
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

	/*for(unsigned i = 0; i < w.size(); ++i) {
		cout << "w[" << i <<"]: " << w[i] << endl;
	}

	for(unsigned i = 0; i < v.size(); ++i) {
		cout << "v[" << i << "]: " << v[i] << endl;
		}*/

	auto start = high_resolution_clock::now();
	int res = knapsack(c, v, w, n, opt);
	auto end = high_resolution_clock::now();
	duration<double> time_dp = end - start;

	cout << "\nDynamic Programming Optimal value: " << res;
	cout << "\nDynamic Programming Optimal subset: {";
	for(unsigned i = opt.size() - 1; i > 0; --i)
		cout << opt[i] << ' ';
	cout << opt[0];
	cout << "}\n";
	cout << "Dynamic Programming Time Taken: " << time_dp.count() << endl;
	
	return 0;
}
