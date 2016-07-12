ROOT_PATH=$(shell pwd)
CC=g++
BIN=udp_data
MYJSONSRC=my_json.cpp
UDP_SRC=udp_data.cpp
MYJSONOBJ=my_json.o
UDP_OBJ=udp_data.o
MYJSON=$(ROOT_PATH)/json_lib/include

INCLUDE=-I$(MYJSON)
LDFLAGS=$(MYJSONCPPLIB)/libjsoncpp.a

$(BIN):$(UDP_OBJ) $(MYJSONOBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(UDP_OBJ):$(UDP_SRC)
	$(CC) -c $< $(INCLUDE)

$(MYJSONOBJ):$(MYJSONSRC)
	$(CC) -c $< $(INCLUDE) -D_DEBUG_

.PHONY:clean
clean:
	rm -rf *.o $(BIN)
