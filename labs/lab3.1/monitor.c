// REFERENCES FROM THE BOOK: The Linux Programming Interface
// https://bit.ly/2FprE5t (Google Books TheLPI)

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <ftw.h>
#include <sys/inotify.h>
#include "logger.h"

#define BUF_LEN(10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int inotifyFd;

static int get_files(const char *fpath, const struct stat *sb, int flag, struct FTW *ftwbuf) {
    /* Check for creation, deletion or rename of files */
    int wd = inotify_add_watch(inotifyFd, fpath,
		IN_CREATE | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO);
    if (wd == -1) {
        errorf("couldn't add to inotify_add_watch");
		exit(EXIT_FAILURE);
        }
        return 0;
}

static void displayInotifyEvent(struct inotify_event *i) {
	if (i->mask & IN_CREATE)
		infof("IN_CREATE ");
	if (i->mask & IN_DELETE)
		infof("IN_DELETE ");
	if (i->mask & IN_MOVED_FROM)
		infof("IN_MOVED_FROM ");
	if (i->mask & IN_MOVED_TO)
		infof("IN_MOVED_TO ");
	printf("\n");

	if (i->len > 0)
		printf("        name = %s\n", i->name);
}