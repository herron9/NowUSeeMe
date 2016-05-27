all:
	g++ -std=c++11 main.cpp parser.cpp scanner.cpp scanPre.cpp treeNode.cpp standardizer.cpp flatten.cpp cse.cpp -o p2
cl:
	rm -f *.o p2
test:
	perl ./difftest.pl -1 "./rpal FILE" -2 "./p2  FILE" -t ./tests/
