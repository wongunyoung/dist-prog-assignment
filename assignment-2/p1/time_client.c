/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "time.h"
#include <stdlib.h>

void
time_prog_1(char *host, int delay_time)
{
	CLIENT *clnt;
	int  *result_1;
	char *get_time_1_arg;
	int  *result_2;
	int  delay_1_arg = delay_time;

#ifndef	DEBUG
	clnt = clnt_create (host, TIME_PROG, TIME_VERS, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = get_time_1((void*)&get_time_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("Result of get_time : %d\n", *result_1);

	printf("Delay %d seconds...\n", delay_1_arg);
	result_2 = delay_1(&delay_1_arg, clnt);
	if (result_2 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	result_1 = get_time_1((void*)&get_time_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("Result of get_time : %d\n", *result_1);

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	int delay_time;

	if (argc < 3) {
		printf ("usage: %s <server_host> <delay time>\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	delay_time = atoi(argv[2]);
	time_prog_1 (host, delay_time);
exit (0);
}
