#include <stdio.h>
#include <stdarg.h>

int 
infof (const char *format, ...)
{
    va_list arg;
    int done;

    printf("INFO: ");

    va_start(arg, format);
    done = vprintf(format, arg);
    va_end(arg);
    return done;    
}

int 
warnf (const char *format, ...)
{
    va_list arg;
    int done;

    printf("WARN: ");

    va_start(arg, format);
    done = vprintf(format, arg);
    va_end(arg);
    return done;
}

int
errorf (const char *format, ...)
{
  va_list arg;
  int done;

  printf ("ERROR: ");
  
  va_start (arg, format);
  done = vprintf (format, arg);
  va_end (arg);
  return done;
}

int
panicf (const char *format, ...)
{
  va_list arg;
  int done;

  printf ("PANIC:");
  printf (" ");

  va_start (arg, format);
  done = vprintf (format, arg);
  va_end (arg);
  return done;
}
