#include "logger.c"

int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);

int main()
{
	infof("Testing information\n");
	warnf("Testing a %s \n", "warn");
	errorf("Testing an %s %s\n", "error", "test");
	panicf("Testing panic\n");
	return 0;
}

