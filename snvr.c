#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

static void video(const char *video, const char *audio)
{
	pid_t pid = fork();

	if (pid < 0) {
		warn("fork for %s", video);
		return;
	}

	if (pid > 0)
		return;

	printf("handling %s+%s\n", video, audio);
	exit(0);
}

int main(int argc, char **argv)
{
	int opt;
	char *audio = NULL;

	while ((opt = getopt(argc, argv, "a:v:")) >= 0) {
		switch (opt) {
		case '?':
			fprintf(stderr, "bad options\n");
			exit(1);
		case 'a':
			audio = optarg;
			break;
		case 'v':
			video(optarg, audio);
			audio = NULL;
			break;
		}
	}
	wait(NULL);

	return 0;
}
