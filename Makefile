src := $(wildcard *.cpp)
obj := $(src:%.cpp=%.o)
hdr := $(wildcard *.h)
bin := filesend

CXX := $(shell which g++ || which clang++)
CXXFLAGS := -Wall -W -std=c++11 -g -O0 -Wno-unused-result
LDFLAGS := -lcurl

UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
  LDFLAGS := $(LDFLAGS) -lpthread
endif

all: $(bin)

$(bin): $(obj) $(hdr)
	$(CXX) -o $(bin) $(obj) $(LDFLAGS)

%.o: %.cpp $(hdr)
	$(CXX) $(CXXFLAGS) -c $(<) -o $(@)

.PHONY: clean
clean:
	rm -f $(bin) $(obj)
