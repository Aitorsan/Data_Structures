

LD_FLAGS:= -L./lib/googletest -lgtest_main -lgtest -lgmock_main -lgmock
EXENAME = test
CXX:=clang++
CFLAGS:= -std=c++11 -Wall -W 
INCLUDE:= -I./_Tests/googletest
OutDir:= ./build/$(EXENAME)
SRC:=_Tests/main.cpp

test: 
	$(CXX) $^ $(LD_FLAGS) -o $(OutDir)

main.o:  $(SRC)
	$(CXX) $(CFLAGS) $(INCLUDE) -c $(SRC)

.PHONY: clean run
clean:
	rm build/$(EXENAME)
run:
	./build/$(EXENAME)

