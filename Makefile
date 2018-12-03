CXXFLAGS = -g -Wall -Werror -pedantic -std=c++11

srcs = $(wildcard *.cpp)

objs = $(srcs:.cpp=.o)

all : knapsack ec1 ec2

knapsack : $(objs)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean :
	rm knapsack *~ *.o dp* greedy*
