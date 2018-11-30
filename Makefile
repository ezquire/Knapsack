CXXFLAGS = -g -Wall -Werror

srcs = $(wildcard *.cpp)

objs = $(srcs:.cpp=.o)

all : knapsack

knapsack : $(objs)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

clean :
	rm knapsack *~ *.o
