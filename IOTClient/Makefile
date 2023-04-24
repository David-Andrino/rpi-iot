GXX=/home/ubuntu/Desktop/buildroot2/buildroot-2022.11/output/host/bin/arm-buildroot-linux-gnueabihf-gcc
FLAGS= -Wall -pedantic -O2
SRC=src
IPFILE=.lastip

.PHONY=all clean upload setIP

all: udpclient upload connect

udpclient: src/udpclient.c
	$(GXX) $(FLAGS) -o udpclient $<

clean:
	-@rm -f udpclient 2>/dev/null || true

cleanIP:
	-@rm $(IPFILE) 2>/dev/null || true

setIP:
	@read -p "Enter RaspberryPi's IP address: " raspiIP; \
    echo -n "$$raspiIP" > $(IPFILE); \
    unset raspiIP

upload: 
	scp udpclient root@$$(cat $(IPFILE)):.

connect:
	ssh -t root@$$(cat $(IPFILE)) "./udpclient"

format:
	clang-format -i src/udpclient.c
