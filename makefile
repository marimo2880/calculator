# -*- Makefile -*-
# Makefile for calculator problem 2013.
# Just type `make', and you'll get executable file `calc'.

CC = gcc
#CFLAGS = -O2 -g -Wall
CFLAGS = -g -Wall

TARGET = calc
OBJS = calculator.o lexical_analysis.o syntactic_analysis.o semantic_analysis.o hash.o

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(TARGET)

#$(TARGET) : $(OBJS)
#	$(CC) -o $@ $?
$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS) *~

calculator.o: calculator.c
lexical_analysis.o : lexical_analysis.c
syntactic_analysis.o : syntactic_analysis.c
semantic_analysis.o : semantic_analysis.c
hash.o : hash.c