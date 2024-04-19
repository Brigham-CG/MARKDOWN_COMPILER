all: run

run:
	g++ scanner.cpp -o scanner.exe

clean:
	rm -f *.exe