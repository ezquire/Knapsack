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

Knapsack capacity = 165. Total number of items = 10

Dynamic Programming Optimal value: 309
Dynamic Programming Optimal subset: {1 2 3 4 6}
Dynamic Programming Time Taken: 6.5063e-05

Greedy Approach Optimal value: 266
Greedy Approach Optimal subset: {1 2 3 4}
Greedy Approach Time Taken: 5.714e-06
```

and output files
```
dptime.data greedytime.data
```

after running gnuplot
![Scatterplot](/scatter.png)
