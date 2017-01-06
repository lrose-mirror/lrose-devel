#include "DsrWebPost.hh"
#include <toolsa/str.h>
#include <signal.h>
#include <toolsa/pmu.h>
using namespace std;

// file scope

static void tidy_and_exit (int sig);
static DsrWebPost *Prog;

// main

int main(int argc, char **argv)

{

  // set signal handling

  PORTsignal(SIGINT, tidy_and_exit);
  PORTsignal(SIGHUP, tidy_and_exit);
  PORTsignal(SIGTERM, tidy_and_exit);
  PORTsignal(SIGQUIT, tidy_and_exit);
  PORTsignal(SIGKILL, tidy_and_exit);
  PORTsignal(SIGPIPE, (PORTsigfunc)SIG_IGN);

  // create program object

  DsrWebPost *Prog;
  Prog = new DsrWebPost(argc, argv);
  if (!Prog->isOK) {
    return(-1);
  }

  // run it

  int iret = Prog->Run();

  // clean up

  tidy_and_exit(iret);
  return (iret);
  
}

// tidy up on exit

static void tidy_and_exit (int sig)

{
  delete Prog;
  PMU_auto_unregister();
  exit(sig);
}
