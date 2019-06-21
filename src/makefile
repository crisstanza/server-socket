TARGETS = server-socket-test

default: clean server-socket-test

server-socket-test: server-socket-test.o 
	$(CXX) -o $@ $< $(LDFLAGS)
	rm -f *.o

clean:
	rm -f *.o $(TARGETS)
