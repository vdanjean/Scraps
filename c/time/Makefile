CLOCKS=REALTIME REALTIME_COARSE MONOTONIC MONOTONIC_RAW MONOTONIC_COARSE PROCESS_CPUTIME_ID THREAD_CPUTIME_ID
CC=gcc
C_OPTS=-O2
LIBS=-lrt -lpthread

all: $(addprefix clock_gettime_,$(CLOCKS))
	$(CC) $(C_OPTS) $(LIBS) time.c -o time
	$(CC) $(C_OPTS) $(LIBS) ftime.c -o ftime
	$(CC) $(C_OPTS) $(LIBS) gettimeofday.c -o gettimeofday
	$(CC) $(C_OPTS) $(LIBS) clock_gettime.c -o clock_gettime
	$(CC) $(C_OPTS) $(LIBS) cached_time.c -o cached_time

clock_gettime_%: clock_gettime.c
	$(CC) $(C_OPTS) $(LIBS)  $< -o $@ -DMYCLOCK=CLOCK_$*

run:
	./time
	./ftime
	./gettimeofday
	@echo "./clock_gettime_*" ; $(foreach c,$(CLOCKS), \
	  echo CLOCK_$c ;  ./clock_gettime_$c ;)
	./cached_time

clean:
	rm -f *.o
	rm -f time
	rm -f ftime 
	rm -f gettimeofday
	rm -f clock_gettime $(addprefix clock_gettime_,$(CLOCKS))
	rm -f cached_time

