all:
	g++ -std=c++11 main.cpp parser.cpp scanner.cpp scanPre.cpp treeNode.cpp standardizer.cpp flatten.cpp cse.cpp csePre.cpp -o p3
cl:
	rm -f *.o p3
test:
	perl ./difftest.pl -1 "./p2 FILE" -2 "./p3  FILE" -t ./tests/
