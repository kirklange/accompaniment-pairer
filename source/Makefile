CC = g++
BUILD_DIR = ../build
RESRC_DIR = ../resrc
CFLAGS = -std=c++11 -I.


all : copa cp_resrc run

# "Collaborative Pairer"
copa : main.cpp CSVReader.cpp Student.cpp TimeSeg.cpp util.cpp
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@

cp_resrc :
	cp -R $(RESRC_DIR)/. $(BUILD_DIR)/

run :
	cd ../build && echo '' && ./copa && cd ../source

clean :
	rm -f $(BUILD_DIR)/*
