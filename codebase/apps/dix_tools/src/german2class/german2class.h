/* header file for german2class
 */

#include <toolsa/umisc.h>

#define LABLEN 128

extern int copy_cal_to_class(char *cal_name, FILE *class);

extern int process_file(char *apa_name,
			char *cal_name,
			char *class_name);

extern int read_apa(char *apa_name,
		    double *lat, double *lon, double *ht,
		    char *NS, char *EW,
		    long *rs_number, long *computing_freq,
		    date_time_t *start_time,
		    double *ptu_identified,
		    char *gc_corr,
		    char *wind_mode,
		    char *excluded_sta);


extern int process_file(char *apa_name, char *cal_name, char *class_name);

extern int write_class(char *cal_name,
		       char *class_name,
		       double lat, double lon, double ht,
		       char *NS, char *EW,
		       long rs_number, long computing_freq,
		       date_time_t *start_time,
		       double ptu_identified,
		       char *gc_corr,
		       char *wind_mode,
		       char *excluded_sta);

     
