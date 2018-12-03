#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

// Struct for storing value/weight pairs
struct item {
	int val, weight;
};

// Function Prototypes
int dp(int, vector<int>, vector<int>, int, vector<int>&);
int dp_two_row(int, vector<int>, vector<int>, int, vector<int>&);
int greedy(int, vector<item>, vector<int>&);
int greedyHeap(int, vector<item>, vector<int>&);
bool greater_than(const struct item&, const struct item&);
bool less_than(const struct item&, const struct item&);
void graph_dp_greedy(int, vector<int>, vector<int>, int, vector<int>&,
		   vector<item>);
void graph_greedy_heap(int, vector<int>, vector<int>, int, vector<int>&, vector<item>);
void getinput(vector<int>&, vector<int>&, int&, vector<item>&, vector<item>&);

int main() {
	int n = 0;
	int c = 0;
	vector<int> v;
	vector<int> w;
	vector<int> opt;
	vector<item> it;
	vector<item> heap;

	getinput(v, w, c, it, heap);
	
	cout << "\nKnapsack capacity = " << c;
	cout << ". Total number of items = ";
	cout << v.size() << endl;
	n = v.size();

	auto two_start = high_resolution_clock::now();
	int two_res = dp_two_row(c, v, w, n, opt);
	auto two_end = high_resolution_clock::now();
	duration<double> two_time = two_end - two_start;
	cout << "\nDynamic Programming Two-Row Optimal value: " << two_res;
	cout << "\nDynamic Two-Row Programming Time Taken: " << two_time.count();
	cout << endl;
	
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
	opt.resize(0); // reset optimal subset vector
	
	start = high_resolution_clock::now();
	res = greedy(c, it, opt);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "\nGreedy Approach Optimal value: " << res;
	cout << "\nGreedy Approach Optimal subset: {";
	for(unsigned i = 0; i < opt.size() - 1; ++i)
		cout << opt[i] << ' ';
	cout << opt[opt.size() - 1];
	cout << "}";
	cout << "\nGreedy Approach Time Taken: " << time.count() << endl;
	opt.resize(0); // reset optimal subset vector
	
	graph_dp_greedy(c, v, w, n, opt, it);
	graph_greedy_heap(c, v, w, n, opt, it);
	return 0;
}

void getinput(vector<int>& v, vector<int>& w, int& c, vector<item>& items,
			  vector<item>& heap) {

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

	// add item pairs if # vals and weights are equal
	for(unsigned i = 0; i < v.size(); ++i) {
		it.val = v[i];
		it.weight = w[i];
		items.push_back(it);
		heap.push_back(it);
	}
}

int dp(int c, vector<int> v, vector<int> w, int n, vector<int>& opt) {
	int i, j;
	vector< vector<int> > k(n + 1, vector<int>(c + 1));

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
	int res = k[n][c]; //optimal value
	j = c; // start at last column
	for(i = n; i > 0 && res > 0; --i) { // start at last row 
		// if the value in the table above is the same don't add it to soln
		if(res == k[i - 1][j]) 
			continue;
		else {
			opt.push_back(i); // add to optimal subset
			res -= v[i - 1];  // subtract from total values
			j -= w[i - 1];    // subtract from 
		}
	}
	return k[n][c]; // return the optimal value
}

int dp_two_row(int c, vector<int> v, vector<int> w, int n, vector<int>& opt) {
	int i, j;
	vector< vector<int> > k(2, vector<int>(c + 1));

	// fill knapsack array with values
	for(i = 0; i < n; ++i) {		
		for(j = 1; j <= c; ++j) {
			if( w[i] <= j )
				k[1][j] = max( k[0][j], (v[i] + k[0][j - w[i]]) );
			else
				k[1][j] = k[0][j];
		}
		k[0] = k[1];
		k[1].assign(c + 1, 0);
	}
	return k[0][c]; // return the optimal value
}

int greedy(int c, vector<item> items, vector<int>& opt) {
	int total_w = 0;
	int total_v = 0;
	sort(items.begin(), items.end(), greater_than);

	for(unsigned i = 0; i < items.size(); ++i) {
		if(total_w + items[i].weight <= c) {
			total_w += items[i].weight;
			total_v += items[i].val;
			opt.push_back(i + 1);
		}
		else
			break;
	}
	return total_v;
}

int greedyHeap(int c, vector<item> items, vector<int>& opt) {
	int total_w = 0;
	int total_v = 0;
	int index = 0;
	make_heap(items.begin(),items.end(), less_than);
	while (total_w + items.front().weight <= c) {
		total_w += items.front().weight;
		total_v += items.front().val;
		opt.push_back(index + 1);
		pop_heap(items.begin(), items.end(), less_than);
		items.pop_back();
		make_heap(items.begin(),items.end(), less_than);
		++index;
	}
	return total_v;
}

// Ratio comparison utility function for greedy standard
bool greater_than(const struct item& a, const struct item& b) {
	double r1 = (double)a.val / (double)a.weight;
	double r2 = (double)b.val / (double)b.weight;
	return r1 > r2;
}

// Ratio comparison utility function for greedy with heap
bool less_than(const struct item& a, const struct item& b){
	double r1 = (double)a.val / (double)a.weight;
	double r2 = (double)b.val / (double)b.weight;
	return r1 < r2;
}

// Graphing utility function
void graph_dp_greedy(int c, vector<int> v, vector<int> w, int n,
					 vector<int>& opt, vector<item> it) {
	ofstream dptime;
	ofstream greedytime;
	dptime.open("dptime.txt", ios::out);
	greedytime.open("greedytime.txt", ios::out);
	vector<item> temp;
	
	for(int i = 1; i <= n; ++i) {
		temp.push_back(it[i - 1]); // Build a larger list as we go
		auto start = high_resolution_clock::now();
		dp(c, v, w, i, opt);
		auto end = high_resolution_clock::now();
		duration<double> time = end - start;
		dptime << i << " " << time.count() << endl;
		opt.resize(0); // Not really necessary but might be best

		start = high_resolution_clock::now();
		greedy(c, temp, opt);
		end = high_resolution_clock::now();
		time = end - start;
		greedytime << i << " " << time.count() << endl;
	}
}

void graph_greedy_heap(int c, vector<int> v, vector<int> w, int n,
					   vector<int>& opt, vector<item> it) {
	ofstream greedytime;
	ofstream greedyheaptime;
	greedytime.open("greedytime1.txt", ios::out);
	greedyheaptime.open("greedyheap.txt", ios::out);
	vector<item> temp;
	
	for(int i = 1; i <= n; ++i) {
		temp.push_back(it[i - 1]); // Build a larger list as we go
		auto start = high_resolution_clock::now();
		greedy(c, temp, opt);
		auto end = high_resolution_clock::now();
		duration<double> time = end - start;
		greedytime << i << " " << time.count() << endl;
		opt.resize(0); // Not really necessary but might be best

		start = high_resolution_clock::now();
		greedyHeap(c, temp, opt);
		end = high_resolution_clock::now();
		time = end - start;
		greedyheaptime << i << " " << time.count() << endl;
	}
}
