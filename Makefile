
CXX = g++
CXXFLAGS = -Wall -O3
LD = g++
LDFLAGS = -Wall -O3 -lm

SRCS = geometry.cxx matrix.cxx paths.cxx path_extrude.cxx
OBJS = $(addprefix obj/,$(SRCS:.cxx=.o))

EX_SRCS = examples.cxx
EX_OBJS = $(addprefix obj/ex_,main.o $(EX_SRCS:.cxx=.o))
EX_TRGT = path_extrude_examples

all: $(EX_TRGT)

obj/ex_main.o: examples/main.cxx
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/ex_%.o: examples/%.cxx examples/%.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/%.o: src/%.cxx src/%.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(EX_TRGT): $(EX_OBJS) $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $^

clean:
	rm obj/*.o

