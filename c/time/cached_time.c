#include <pthread.h>
#include <unistd.h>
#include "utils.h"

volatile unsigned long current_time;
volatile int started;

static void *clock_handler() {
	static time_t monotonic_start;
	struct timeval t = {.tv_sec = 1, .tv_usec = 0};
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	monotonic_start = ts.tv_nsec - 2;

	started = 1;
	for (;;) {
		clock_gettime(CLOCK_MONOTONIC, &ts);
		current_time = ts.tv_nsec - monotonic_start;
		usleep(1 * MICROSECONDS);
	}
}

int main(void)
{
	pthread_t tid;
	int r;
	long i;
	volatile unsigned long c2;

	pthread_create(&tid, NULL, clock_handler, NULL);
	pthread_detach(tid);

	/* printf("(start) current_time = %lus\n", current_time); */

	c2 = 0;
	while (!started) ;
	test_start();
	for (i = 0; i < N; i++) {
		c2 += current_time;
	}
	test_end();

	/* printf("(end) current_time = %lus\n", current_time); */
	printf("(total) c2 = %lu (n = %i)\n", c2, N);

	pthread_cancel(tid);

	return 0;
}

