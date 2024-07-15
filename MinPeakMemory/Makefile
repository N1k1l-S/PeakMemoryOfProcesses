CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20

SRCS = try.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = my_program
INPUT_FILES = $(wildcard input*)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

output_files/input%_out.txt: input%
	@mkdir -p output_files
	@echo "Running $< with input file $@"
	@./$(EXEC) < $^ > $@
	@{ time ./$(EXEC) < $^ ;} 2>> $@


run: $(patsubst input%,output_files/input%_out.txt,$(INPUT_FILES))

clean:
	rm -rf $(OBJS) $(EXEC) 

output_files_clean:
	rm -rf output_files