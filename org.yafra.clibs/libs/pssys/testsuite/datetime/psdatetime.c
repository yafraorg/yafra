#include <stdio.h>
#include <time.h>
#include <pssys.h>

#define _UNDEF -1
#define _BEZLEN 30

void main(int, char **);

void main(int argc, char *argv[])
{
	char	tmp_date[_BEZLEN+1];
	char	tmp_time[_BEZLEN+1];
	char	new_tmp[_BEZLEN+1];
	char	new_tmp_bez1[_BEZLEN+1];
	char	new_tmp_bez2[_BEZLEN+1];
	char	new_tmp_bez3[_BEZLEN+1];
	char	new_tmp_bez4[_BEZLEN+1];
	time_t	intdate;
	time_t	inttime;
	int	cret;
	size_t len;
	struct tm DateTime;

	*new_tmp_bez1 = (char)NULL;
	*new_tmp_bez2 = (char)NULL;
	*new_tmp_bez3 = (char)NULL;
	*new_tmp_bez4 = (char)NULL;
	*new_tmp      = (char)NULL;
	*tmp_date     = (char)NULL;
	*tmp_time     = (char)NULL;

	if (argc == 5)
		{
		if ((strcmp(argv[1], "-d")) == 0 && strlen(argv[2]) > 0 &&
		    (strcmp(argv[3], "-t")) == 0 && strlen(argv[4]) > 0)
			{
			strcpy(tmp_date, argv[2]);
			strcpy(tmp_time, argv[4]);
			}
		else
			{
			printf("\nusage: mptimes -d Date [dd.mm.yyyy] -t Time [hh.mm]\n\n");
			exit(0);
			}
		}
	else
		{
		printf("\nusage: mptimes -d Date [dd.mm.yyyy] -t Time [hh.mm]\n\n");
		exit(0);
		}
	tzset();

	printf("\n");
	printf("Actual Date and Time:\n");
	printf("============================================\n");
	PSSYSwriteDate(0, new_tmp_bez1, new_tmp_bez2, (size_t)_BEZLEN+1, PSSYS_DAT_GERMAN);
	printf(" Date: ==> %s\n", new_tmp_bez1);
	printf(" Time: ==> %s\n", new_tmp_bez2);

	printf("\n");
	printf("Convert Date and Time in Integer and revers:\n");
	printf("============================================\n");

	/* ------ NEW DATE TO INT ------ */
	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	len = strlen(tmp_date);
	if (len > 8)
		{
		DateTime.tm_hour=(int)_UNDEF;
		DateTime.tm_min=(int)_UNDEF;
		}
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	strcpy(new_tmp_bez1, tmp_date);
	strcpy(new_tmp, new_tmp_bez1);
	intdate = -1;
	cret = PSSYSdatetime2int(&DateTime,(time_t *)&intdate, new_tmp_bez1, PSSYS_DAT_GERMAN);
	if (cret == PSOK)
		printf(" Date-Integer: %s ==> %d\n", new_tmp, intdate);
	else
		printf(" Error by converting\n");

	/* ------ NEW TIME TO INT ------ */
	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	DateTime.tm_hour=(int)_UNDEF;
	DateTime.tm_min =(int)_UNDEF;
	strcpy(new_tmp_bez2, tmp_time);
	strcpy(new_tmp, new_tmp_bez2);
	inttime = -1;
	cret = PSSYSdatetime2int(&DateTime,(time_t *)&inttime, new_tmp_bez2, PSSYS_TIME_GERMAN);
	if (cret == PSOK)
		printf(" Time-Integer: %s ==> %d\n", new_tmp, inttime);
	else
		printf(" Error by converting\n");

	/* ------ NEW INT TO DATE ------ */
	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	*new_tmp_bez3 = NULL;
	cret = PSSYSint2datetime(&DateTime, (time_t *)&intdate, new_tmp_bez3, (size_t)_BEZLEN+1, "%c %Z", PSSYS_DAT_GERMAN);
	if (cret == PSOK)
		printf(" Integer-Date: %d ==> %s\n", intdate, new_tmp_bez3);
	else
		printf(" Error by converting\n");

	/* ------ NEW INT TO TIME ------ */
	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	DateTime.tm_min  = (int)_UNDEF;
	DateTime.tm_hour = (int)_UNDEF;
	*new_tmp_bez4 = NULL;
	cret = PSSYSint2datetime(&DateTime, (time_t *)&inttime, new_tmp_bez4, (size_t)_BEZLEN+1, NULL, PSSYS_TIME_GERMAN);
	if (cret == PSOK)
		printf(" Integer-Time: %d ==> %s\n", inttime, new_tmp_bez4);
	else
		printf(" Error by converting\n");

}
