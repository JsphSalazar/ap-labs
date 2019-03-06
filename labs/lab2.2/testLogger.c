#include "logger.c"

int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);

int main()
{
	infof("General information.\n");
	warnf("Warnings.\n");
	errorf("Errors.\n");
	panicf("Panics. Non recoverable issues with core dump.\n");
	return 0;
}

