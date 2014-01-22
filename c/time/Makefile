CLOCKS=REALTIME REALTIME_COARSE MONOTONIC MONOTONIC_RAW MONOTONIC_COARSE PROCESS_CPUTIME_ID THREAD_CPUTIME_ID
all: $(addprefix clock_gettime_,$(CLOCKS))
	gcc -O2 time.c -o time -lrt
	gcc -O2 ftime.c -o ftime -lrt
	gcc -O2 gettimeofday.c -o gettimeofday -lrt
	gcc -O2 clock_gettime.c -o clock_gettime -lrt
	gcc -O2 cached_time.c -o cached_time -lrt -lpthread

clock_gettime_%: clock_gettime.c
	gcc -O2 $< -o $@ -lrt -DMYCLOCK=CLOCK_$*

run:
	./time
	./ftime
	./gettimeofday
	@echo "./clock_gettime_*" ; $(foreach c,$(CLOCKS), \
	  echo CLOCK_$c ;  ./clock_gettime_$c ;)
	./cached_time

clean:
	rm -f time
	rm -f ftime
	rm -f gettimeofday
	rm -f clock_gettime $(addprefix clock_gettime_,$(CLOCKS))
	rm -f cached_time

