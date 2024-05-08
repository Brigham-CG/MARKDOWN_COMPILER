all: run

run:
	g++ main.cpp -o main.exe
clean:
	rm -f *.exe