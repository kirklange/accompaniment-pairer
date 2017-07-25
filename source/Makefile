CC = g++
BUILD_DIR = ../build
RESRC_DIR = ../resrc
CFLAGS = -std=c++11 -I$(RESRC_DIR)

all : copa

# "Collaborative Pairer"
copa : main.cpp
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@

clean :
	rm -f $(BUILD_DIR)/*
