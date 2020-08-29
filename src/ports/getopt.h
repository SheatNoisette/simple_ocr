#ifndef _GETOPT_H
#define _GETOPT_H 1

/* Minimal getopt */

struct option
{
#if defined (__STDC__) && __STDC__
  const char *name;
#else
  char *name;
#endif
  int has_arg;
  int *flag;
  int val;
};

extern int getopt (int argc, char *const *argv, const char *shortopts);
extern int getopt_long (int argc, char *const *argv, const char *shortopts,
                const struct option *longopts, int *longind);
extern int getopt_long_only (int argc, char *const *argv,
                 const char *shortopts,
                     const struct option *longopts, int *longind);
extern int _getopt_internal (int argc, char *const *argv,
                 const char *shortopts,
                     const struct option *longopts, int *longind,
                 int long_only);
#endif