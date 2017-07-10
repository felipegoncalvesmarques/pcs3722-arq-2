SYSTEMC_INC_DIR = $(SYSTEMC_HOME)/include
SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib

# LIBTOOL Setting
SHELL           = /bin/bash
LIBTOOL_DIR     = $(SYSTEMC_HOME)/build
LIBTOOL         = $(LIBTOOL_DIR)/libtool

GXX             = g++
GCC             = gcc
LD              = g++

FLAGS           = -g -Wall -pedantic -Wno-long-long \
                 -DSC_INCLUDE_DYNAMIC_PROCESSES -fpermissive \
                 -I$(SYSTEMC_INC_DIR)
LDFLAGS         = -L$(SYSTEMC_LIB_DIR) -lsystemc -lm

SRCS = sc_main.cpp jpec_enc_block_zz.cpp
OBJS=$(SRCS:.cpp=.o)

# main
main: $(OBJS)
	$(LIBTOOL) --mode=link --tag=CXX g++ -o $@ $(OBJS) $(LDFLAGS)

.cpp.o:
	$(LIBTOOL) --mode=compile --tag=CXX g++ -c $(FLAGS) $<

%.o: %.c
	$(LIBTOOL) --mode=compile --tag=CXX gcc -Wall -c $<

clean:
	rm -f main *.o *.lo
	rm -rf .libs
