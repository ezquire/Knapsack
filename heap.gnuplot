set term png
set key font ",10"
set title font ",10"
set style data points
set key left top
set output "heap.png"
set title "Scatter Plot of n items versus time"
set xlabel "Number of Items"
set ylabel "Time"
set grid
set pointsize
plot "greedytime1.txt" title "Greedy Standard", "greedyheap.txt" title "Greedy Heap"  with points lt 2 pt 3
quit