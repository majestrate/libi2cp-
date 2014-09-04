PACKAGES=libcrypto++
CXX=g++
CXX_DEBUG_FLAGS=-g -DDEBUG_I2CP
CXXFLAGS=-Wall $(shell pkg-config --cflags $(PACKAGES)) -std=c++11  -I./include -fPIC $(CXX_DEBUG_FLAGS)
LDFLAGS=-L. -li2cp++ $(shell pkg-config --libs $(PACKAGES)) -pthread 

SRCS:=$(wildcard src/*.cpp)
OBJS=$(SRCS:%.cpp=%.o)
TEST_SRCS=$(wildcard test/test_*.cpp)
TEST_OBJS=$(TEST_SRCS:%.cpp=%.bin)


all: libi2cp++.so i2cplookup 

libi2cp++.so: $(OBJS)
	$(CXX) -shared $(OBJS) -o libi2cp++.so

i2cplookup: libi2cp++.so
	$(CXX) $(CXXFLAGS) tools/lookup.cpp -o i2cplookup $(LDFLAGS)

clean: 
	rm -f $(OBJS) $(TEST_OBJS)
