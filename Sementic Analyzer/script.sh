bison -d -y 1505066.y
echo '1'
g++ -std=c++11 -w -c -o y.o y.tab.c
echo '2'
flex 1505066.l
echo '3'
g++ -std=c++11 -fpermissive -w -c -o l.o lex.yy.c
echo '4'
g++ -std=c++11 -o a.out y.o l.o -lfl -ly
echo '5'
./a.out intro.c sementic_log.txt sementic_error.txt
