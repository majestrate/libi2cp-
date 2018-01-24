PACKAGES=openssl
CXX=g++
CXX_DEBUG_FLAGS=-g
CXXFLAGS=-Wall $(shell pkg-config --cflags $(PACKAGES)) -std=c++11  -I./include -fPIC $(CXX_DEBUG_FLAGS)
LDFLAGS=$(shell pkg-config --libs $(PACKAGES)) -pthread 

SRCS=$(wildcard src/*.cpp)
SRCS += $(wildcard src/libi2pd/*.cpp)
OBJS=$(SRCS:.cpp=.cpp.o)
TEST_SRCS=$(wildcard test/test_*.cpp)
TEST_OBJS=$(TEST_SRCS:%.cpp=%.bin)
LIB=libi2cp++.a
EXE=i2cplookup

all: $(EXE)

%.cpp.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $<.o

$(LIB): $(OBJS)
	$(AR) -r $(LIB) $(OBJS)

$(EXE): $(LIB)
	$(CXX) $(CXXFLAGS) tools/lookup.cpp -o $(EXE) $(LDFLAGS) $(LIB)

clean: 
	rm -f $(OBJS) $(TEST_OBJS) $(LIB) $(EXE)
