CXXFLAGS = -g -Wall -Werror -pedantic -std=c++11

srcs = $(wildcard *.cpp)

objs = $(srcs:.cpp=.o)

all : knapsack

knapsack : $(objs)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean :
	rm knapsack *~ *.o dp* greedy*
