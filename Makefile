all:
	g++ first.cpp functionDefined.cpp -o f



#functiondefined: 
	g++ -c functionDefined.cpp -o fd
	chmod 777 fd
#first: 
	g++ -c first.cpp -o first
#hello: first functiondefined 
	#gcc -c first functiondefined -o hello

clean:
	rm -rf *o hello	

run:
	./first




