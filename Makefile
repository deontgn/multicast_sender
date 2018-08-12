PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = multicast_sender.o

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -O2
else
	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

all:	multicast_sender

multicast_sender:	$(OBJS)
	$(CXX) -o $@ $^



%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr multicast_sender $(OBJS)
