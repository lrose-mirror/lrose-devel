/*
 * Read tape, report status, number of blocks read and block sizees
 * Does extended status queries supported by Apunix sx driver.
 *						gdm 02/18/92
 */
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mtio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef APUNIX
#include <scsi/scsi_exabyte.h>
#endif

#include <sys/param.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#define BUFFLEN 500000
char *tapename;

static int tapestatus (int fd, int error,int write,int *retry,int nblk);
static int tapeproblemabort (void);

void mt_print_status(int fd) 

{
  struct mtget status;
  if (ioctl(fd,MTIOCGET,&status)==-1) {
    perror (tapename); exit(1);
  }

  printf("type  dsreg  erreg  resid  file#   blk# flags bf\n");
  printf("0x%.2x 0x%.4x 0x%.4x %6d %6d %6d\n",
	 status.mt_type,status.mt_dsreg,status.mt_erreg,
	 (int) status.mt_resid,
	 (int) status.mt_fileno, (int) status.mt_blkno);
}
#ifdef APUNIX
void mt_print_sense(int fd) 

{
  struct xb_extsense sense;
  long remtape,errcnt;

  if (ioctl(fd,XBIOCSENSE,&sense)==-1) {
    perror (tapename); return;
  };
  remtape = sense.xs_remtape[0]<<16 | sense.xs_remtape[1]<<8 |
	    sense.xs_remtape[2];
  errcnt = sense.xs_errcnt[0]<<16 | sense.xs_errcnt[1]<<8 |
	    sense.xs_errcnt[2];

  printf("val seg sens   info  len clas/cod as qual  res\
 errcnt status res remtape\n");
  printf(" %.2x  %.2x   %.2x %.2x%.2x%.2x%.2x %.2x %.2x%.2x%.2x%.2x\
 %.2x   %.2x %.2x%.2x%7d %.2x%.2x%.2x %.2x%8d\n",
	sense.xs_valid,sense.xs_segment,sense.xs_sense,
	sense.xs_info[0],sense.xs_info[1],sense.xs_info[2],sense.xs_info[3],
	sense.xs_len,
	sense.xs_res1[0],sense.xs_res1[1],sense.xs_res1[2],sense.xs_res1[3],
	sense.xs_asense,
	sense.xs_aqual,
	sense.xs_res2[0],sense.xs_res2[1],errcnt,
	sense.xs_status[0],sense.xs_status[1],sense.xs_status[2],
	sense.xs_res3,remtape);
}
void mt_print_inquiry(int fd) 
{
  struct xb_inquiry inq;
  if (ioctl(fd,XBIOCINQ,&inq)==-1) {
    perror (tapename); return;
  }

  printf("typ qual ansi resp len  res   vendor   product rev\n");
  printf(" %.2x   %.2x   %.2x   %.2x %.2x %.2x%.2x%.2x %.8s %.16s\
 %.4s\n",
	inq.xi_type,inq.xi_qual,inq.xi_ansi,inq.xi_response,
	inq.xi_len,
	inq.xi_res[0],inq.xi_res[1],inq.xi_res[2],
	inq.xi_vendor,inq.xi_product,inq.xi_rev);
}
#endif
int main(int argc, char **argv)

{
  char block[BUFFLEN];
  int fd,nblk,retry,ifile,nfiles = -1,lenread,error;
  int bad_usage=0,till_deof=0;
  char **argp,*getenv();

  if ((tapename = getenv("TAPE")) == NULL) 
    tapename = "/dev/nosuchdevice";
  
  for (argp = argv+1; --argc; argp++) {
    if (**argp == '-') {
      switch ((*argp)[1]) {
	case 'f':
	case 't':
	  tapename = *(++argp); argc--;
	  break;
	case 'n':
	  nfiles = atoi((argc--,*(++argp)));
	  break;
	default:
	  fprintf(stderr,"Unknown option: -%s\n",*argp);
          bad_usage = 1;
	  break;
      }
    }
  }
  if (bad_usage) {
    fprintf(stderr,
	"Usage: ctape [-n nfiles] [-f tape_device]\n");
    exit(1);
  }
  printf ("tape: %s, nfiles: %d\n",tapename,nfiles);

  if ((fd = open(tapename,O_RDONLY)) < 0) { 
    perror(tapename); exit(1); 
  }

#ifdef APUNIX
  mt_print_status(fd);
  mt_print_sense(fd);
  mt_print_inquiry(fd);
#endif

  if (nfiles < 0) {
    till_deof = 1;
    nfiles = 32767;
  }

  for (ifile = 0; ifile < nfiles; ifile++) {
    error = 0;
    for (nblk=0;;nblk++) {
readagain:
      lenread = read(fd,block,BUFFLEN);
      if (lenread <= 0) {  /* EOF returns lenread==0 */
	error = tapestatus(fd,lenread,0,&retry,nblk);
	if (retry) goto readagain;
	lenread = error;
      }
      if (error == -12) break;	/* eof */
      if (nblk % 10 == 0) printf("%.5d",nblk);
      printf("%6.5d",lenread);
      if (nblk % 10 == 9) printf("\n");
    }
    if (till_deof && ifile && ! nblk) break;
    printf("\nEnd of file %d\n",ifile+1);
    mt_print_status(fd);
#ifdef APUNIX
    mt_print_sense(fd);
    mt_print_inquiry(fd);
#endif
  }
  if (till_deof) {
    printf("\nEnd of volume (double EOF)\n");
    mt_print_status(fd);
#ifdef APUNIX
    mt_print_sense(fd);
    mt_print_inquiry(fd);
#endif
  }
  return (0);
}

static int tapestatus (int fd, int error,int write,int *retry,int nblk)

{
  extern char* sys_errlist[];
  extern int sys_nerr;
  int syserror;
  extern int errno;

  syserror = errno;
  *retry = 0;

#ifdef hpux
/* 
   When writing a tape, this ioctl status check causes the streaming
   tape drive to write its buffer, and return the status.  Thus,
   if it is called after every write, the streaming advantages
   are lost and the drive becomes a VERY slow start/stop drive.
   Therefore this routine should not be called after every write,
   unless write returns a -1.  If one wants this asynchronous write 
   streaming then one loses the capability of knowing exactly
   where an error occured, which is a problem near the EOT.
   As of 04/89 I will call it after EOF writes.
*/

  if (ioctl(fd,MTIOCGET,&status)==-1) {
    perror ("Tape drive status request");
    return error;
  }

  if (! GMT_ONLINE(status.mt_gstat)) {
    error = -6; *retry = 1; goto report; }

  if (write && GMT_WR_PROT(status.mt_gstat)) {
    error = -7; *retry = 1; goto report; }

  if (GMT_EOT(status.mt_gstat)) {
    error = -13; goto report; }

  if (GMT_EOF(status.mt_gstat)) {
    error = -12; goto report; } 

  if (GMT_BOT(status.mt_gstat)) { 
    error = 2; goto report; }

  report:

#else
  if (error)
    switch (syserror) {
    case EIO:
      error = -6; *retry = 1; break;  /* offline */
    case EACCES:
      error = -7; *retry = 1; break;  /* write protect */
    case EINVAL:
      error = -5; break;  /* not a multiple of physical record length */
    					/* (cartridge tapes ) */
    default:                          
      error = -1; break;  /* other unknown error, parity error??*/
    }
  else if (error==0) {
    error = -12;  /* double eof is caught later */
    if (write) error = -13;
  }
#endif
  
  perror("Here is the error: ");
  switch (error) {
    case   0: return error;
    case  -1: 
        fprintf (stderr,"Tape error -1 at block %d",nblk);
	if (syserror>=0 && syserror <= sys_nerr) 
	 fprintf (stderr,": syserr: %s\n",sys_errlist[syserror]);
	 else fprintf (stderr,"\n");
      break;
    case  -5: fprintf (stderr,"Tape error %d: Unsupported block size.\n",error);
      break;
    case  -6: fprintf (stderr,"Tape error %d: Device offline.\n",error);
      break;
    case  -7: fprintf (stderr,"Tape error %d: Tape write protected.\n",error);
      break;
    case -13: fprintf (stderr,"Tape error %d: End of tape.\n",error);
      break;
  }
  if (*retry) if (tapeproblemabort()) exit(1);
  return error;
}
static int tapeproblemabort (void)
{
  char ans[3];
  int i;
  quest:
    fprintf (stderr,
	"Fix problem and enter GO to continue, or AB to abort.  ");
    scanf ("%2s",ans);
    for (i=0; i<2; i++) if (islower(ans[i])) ans[i] = toupper(ans[i]);
    if (strcmp(ans,"AB") == 0) return 1;
    if (strcmp(ans,"GO") != 0) goto quest;
  return 0;
}
