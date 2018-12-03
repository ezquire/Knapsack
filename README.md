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
Enter file containing the capacity: p00_c.txt
Enter file containing the weights: p00_w.txt
Enter file containing the values: p00_v.txt

Knapsack capacity = 5. Total number of items = 4

Dynamic Programming Two-Row Optimal value: 37
Dynamic Two-Row Programming Time Taken: 1.0236e-05

Dynamic Programming Optimal value: 37
Dynamic Programming Optimal subset: {1 2 4}
Dynamic Programming Time Taken: 1.1429e-05

Greedy Approach Optimal value: 25
Greedy Approach Optimal subset: {1 2}
Greedy Approach Time Taken: 4.585e-06
```

and output files
```
dptime.txt | greedytime.txt | greedytime1.txt | greedyheap.txt
```

after running dp.gnuplot

![Scatterplot](/scatter.png)
