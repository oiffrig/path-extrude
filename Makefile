
CXX = g++
CXXFLAGS = -Wall -O3
LD = g++
LDFLAGS = -Wall -O3 -lm

SRCS = geometry.cxx matrix.cxx paths.cxx path_extrude.cxx tests.cxx
OBJS = $(addprefix obj/,main.o $(SRCS:.cxx=.o))
EXE = path_extrude

all: $(EXE)

obj/main.o: src/main.cxx
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/%.o: src/%.cxx src/%.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(EXE): $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $^

clean:
	rm obj/*.o

