#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

static char const *const fdname[] = {
	"input",
	"output"
};

int main(int argc, char *argv[]) {
	size_t psize = 1048576u;

	if (argc == 2) {
		psize = strtoul(argv[1], NULL, 10);
	}

	if (argc > 2 || psize == 0) {
		fprintf(stderr, "Usage: %s [pipe size]\n", argv[0]);
		return EXIT_FAILURE;
	}

	bool ispipe = false;

	for (int fd = 0; fd <= 1; ++fd) {
		struct stat st;

		if (fstat(fd, &st)) {
			fprintf(stderr, "Failed to stat %s: %m\n", fdname[fd]);
			return EXIT_FAILURE;
		}

		if (!S_ISFIFO(st.st_mode)) {
			continue;
		}

		if (fcntl(fd, F_SETPIPE_SZ, psize) < 0) {
			fprintf(stderr, "Failed to set %s pipe size to %lu: %m\n", fdname[fd], psize);
			return EXIT_FAILURE;
		}

		ispipe = true;
	}

	if (!ispipe) {
		fputs("Neither input nor output is a pipe\n", stderr);
		return EXIT_FAILURE;
	}

	ssize_t len;

	do {
		len = splice(0, NULL, 1, NULL, psize, SPLICE_F_MOVE | SPLICE_F_MORE);
		if (len < 0) {
			perror("splice");
			return EXIT_FAILURE;
		}
	} while (len > 0);

	return EXIT_SUCCESS;
}
