bison -d -y 1505066.y
echo '1'
g++ -std=c++11 -w -c -o y.o y.tab.c -g
echo '2'
flex 1505066.l
echo '3'
g++ -std=c++11 -fpermissive -w -c -o l.o lex.yy.c -g
echo '4'
g++ -std=c++11 -o a.out y.o l.o -lfl -ly -g
echo '5'
gdb ./a.out 
