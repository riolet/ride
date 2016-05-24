all: clean rixc

rix.tab.c rix.tab.h:	rix.y
	bison -d rix.y

lex.yy.c: rix.l rix.tab.h
	flex rix.l

rixc: lex.yy.c rix.tab.c rix.tab.h
	gcc -g -ggdb preproc.c ObjectTree.c rix.tab.c lex.yy.c rixc.c errors.c crsl.c -lfl -o rixc 	

parser: lex.yy.c rix.tab.c rix.tab.h
	gcc -ggdb preproc.c ObjectTree.c rix.tab.c lex.yy.c rixc.c errors.c crsl.c parser.c -lfl -o parser -pthread -lrt

clean:
	-rm rixc parser rix.tab.c lex.yy.c rix.tab.h out.c out.h out.log temp_parse_file.rit
