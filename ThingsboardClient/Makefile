GXX=/home/ubuntu/Desktop/buildroot2/buildroot-2022.11/output/host/bin/arm-buildroot-linux-gnueabihf-gcc
FLAGS= -Wall -pedantic -O2 -lm -lcjson
SRC=src
OUT=out
IPFILE=.lastip
MAIN=thingsboardclient
MODULES=accelerometer.o colorSensor.o json.o mosquittoClient.o
INCLUDEPATH=/home/ubuntu/Desktop/buildroot2/buildroot-2022.11/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/
LIBPATH=/home/ubuntu/Desktop/buildroot2/buildroot-2022.11/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib

.PHONY=all clean upload setIP
OUTMODULES=$(patsubst %,$(OUT)/%,$(MODULES))

all: $(MAIN) upload connect

test:
	echo $(OUTMODULES)

$(MAIN): $(SRC)/$(MAIN).c $(OUTMODULES)
	$(GXX) $(FLAGS) -I$(INCLUDEPATH) -L$(LIBPATH) -o $@ $^

$(OUT)/accelerometer.o: $(SRC)/accelerometer/accelerometer.c $(SRC)/accelerometer/accelerometer.h | $(OUT)
	$(GXX) -c $(FLAGS) -I$(INCLUDEPATH) -o $@ $<

$(OUT)/colorSensor.o: $(SRC)/colorSensor/colorSensor.c $(SRC)/colorSensor/colorSensor.h | $(OUT)
	$(GXX) -c $(FLAGS) -I$(INCLUDEPATH) -o $@ $<

$(OUT)/json.o: $(SRC)/json/json.c $(SRC)/json/json.h | $(OUT)
	$(GXX) -c $(FLAGS) -I$(INCLUDEPATH) -o $@ $<

$(OUT)/mosquittoClient.o: $(SRC)/mosquittoClient/mosquittoClient.c $(SRC)/mosquittoClient/mosquittoClient.h | $(OUT)
	$(GXX) -c $(FLAGS) -I$(INCLUDEPATH) -o $@ $<

clean:
	-@rm -rf $(OUT) $(MAIN) 2>/dev/null || true

$(OUT): 
	mkdir $(OUT)

cleanIP:
	-@rm $(IPFILE) 2>/dev/null || true

setIP:
	@read -p "Enter RaspberryPi's IP address: " raspiIP; \
    echo -n "$$raspiIP" > $(IPFILE); \
    unset raspiIP

upload: 
	scp $(MAIN) root@$$(cat $(IPFILE)):.

connect:
	ssh -t root@$$(cat $(IPFILE)) "./$(MAIN) $$(ifconfig ens33 | grep 'inet ' | awk '{print $$2}') 2000"

format:
	find . -name *.h -o -name *.c | xargs clang-format -i
