CC = g++
BUILD_DIR = ../build
RESRC_DIR = ../resrc
CFLAGS = -std=c++11 -I.


all : copa cp_resrc

# "Collaborative Pairer"
copa : main.cpp csv/CSVR.cpp
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@

cp_resrc :
	cp -R $(RESRC_DIR)/. $(BUILD_DIR)/

clean :
	rm -f $(BUILD_DIR)/*
