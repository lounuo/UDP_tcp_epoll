ROOT_PATH=$(shell pwd)
SERVER=$(ROOT_PATH)/server
CLIENT=$(ROOT_PATH)/client
COMM=$(ROOT_PATH)/comm
DATA_POOL=$(ROOT_PATH)/data_pool
PLUGIN=$(ROOT_PATH)/plugin
CONF=$(ROOT_PATH)/conf
MYJSON=$(ROOT_PATH)/comm/json_lib/include
WINDOW=$(ROOT_PATH)/windows

SERVER_BIN=udp_server
CLIENT_BIN=udp_client

INCLUDE=-I$(COMM) -I$(DATA_POOL) -I$(MYJSON) -I$(WINDOW)
#MYJSON_LINK=-l$(ROOT_PATH)/lib/lib
CC=g++
FLAGS=
#LDFLAGS=-lpthread $(MYJSONCPPLIB)/libjsoncpp.a #-static
LDFLAGS=-lpthread /home/lounuo/UDP/lib/lib/libjsoncpp.a -lncurses#-static

SERVER_SRC=$(shell ls -R $(SERVER) | grep -E '*\.cpp')
SERVER_SRC+=$(shell ls -R $(COMM) | grep -E '*\.cpp')
SERVER_SRC+=$(shell ls -R $(DATA_POOL) | grep -E '*\.cpp')
SERVER_OBJ=$(SERVER_SRC:.cpp=.o)

CLIENT_SRC=$(shell ls -R $(CLIENT) | grep -E '*\.cpp')
CLIENT_SRC+=$(shell ls -R $(COMM) | grep -E '*\.cpp')
CLIENT_SRC+=$(shell ls -R $(WINDOW) | grep -E '*\.cpp')
CLIENT_OBJ=$(CLIENT_SRC:.cpp=.o)

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)
	
$(SERVER_BIN):$(SERVER_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Linking [ $^ ] to [ $@ ]...done."

$(CLIENT_BIN):$(CLIENT_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Linking [ $^ ] to [ $@ ]...done."

%.o:$(SERVER)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "Compling [ $(shell basename $<) ] to [ $@ ]...done."

%.o:$(CLIENT)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "Compling [ $(shell basename $<) ] to [ $@ ]...done."

%.o:$(COMM)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "Compling [ $(shell basename $<) ] to [ $@ ]...done."

%.o:$(DATA_POOL)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "Compling [ $(shell basename $<) ] to [ $@ ]...done."

%.o:$(WINDOW)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "Compling [ $(shell basename $<) ] to [ $@ ]...done."


.PHONY:clean
clean:
	@rm -rf *.o $(SERVER_BIN) $(CLIENT_BIN) output
	@echo "Clean...done."

.PHONY:debug
debug:
	@echo $(SERVER_SRC)
	@echo $(SERVER_OBJ)
	@echo $(CLIENT_SRC)
	@echo $(CLIENT_OBJ)

.PHONY:output
output:all
	@mkdir -p output/server
	@mkdir -p output/server/lib
	@mkdir -p output/server/log
	@mkdir -p output/server/conf
	@mkdir -p output/client
	@cp -f $(SERVER_BIN) output/server/
	@cp -f $(CLIENT_BIN) output/client/
	@cp -f $(PLUGIN)/server_ctl.sh output/server/
	@cp -f $(PLUGIN)/client_ctl.sh output/client/
	@cp -f $(CONF)/server.conf output/server/conf
	@echo "output done..."






