
all: clean client server

client: client/client
	@mv client/client build

server: server/server
	@mv server/server build

clean:
	@rm -rvf build
	@mkdir build

.PHONY:
