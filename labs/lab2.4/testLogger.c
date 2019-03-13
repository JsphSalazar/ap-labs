#include "logger.c"

int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);
int initLogger(char *logType);

int main()
{
	infof("General information.\n");
	warnf("Warnings.\n");
	errorf("Errors.\n");
	panicf("Panics. Non recoverable issues with core dump.\n");

    	infof("Check your syslog file at /var/log/syslog to see the rest of calls\n");

	initLogger("Syslog");

    	infof("<info> General information\n");
	warnf("<warn> Warnings %s from syslog\n", "warn");
	errorf("<error> Errors %s %s from syslog\n", "error", "test");
   	panicf("<panic> Panics from syslog\n");

    return 0;
}
