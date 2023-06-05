g++ -std=c++11 -DNDEBUG -Wall *.cpp
./a.out <example_test.in >new.txt
diff new.txt example_test.out 
valgrind --track-origins=yes --leak-check=full -s ./a.out <example_test.in >newnew.txt
diff new.txt example_test.out