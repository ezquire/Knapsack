# Knapsack
[![Build Status](https://travis-ci.com/ezquire/Knapsack.svg?branch=master)](https://travis-ci.com/ezquire/Knapsack)

Comparison of the greedy approach versus dynamic programming to solve the Knapsack problem.

## Group Members
Tyler Gearing, Darin Brown


Usage
-----

To build the knapsack program, run
```
make
```

Then you can run the knapsack program from the current directory using the executable
```
./knapsack
```

Misc
-----

To generate the scatter plot based on input data run
```
gnuplot scatter.gnuplot
```

To clear the output files and executables use
```
make clean
```

Possible Output
-----
```
Enter file containing the capacity: c.txt
Enter file containing the weights: w.txt
Enter file containing the values: v.txt

Knapsack capacity = 100. Total number of items = 50

Dynamic Programming Optimal value: 833
Dynamic Programming Optimal subset: {9 19 20 21 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 47 48 49 50}
Dynamic Programming Time Taken: 0.000223539

Greedy Approach Optimal value: 824
Greedy Approach Optimal subset: {1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22}
Greedy Approach Time Taken: 3.591e-05

```

and output files
```
dptime.data | greedytime.data
```

after running gnuplot

![Scatterplot](/scatter.png)
