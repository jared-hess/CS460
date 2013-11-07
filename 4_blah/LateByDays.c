/* C function to calculate the difference between two dates in fall 2013
||
|| Inputs: duedate = "YYYYMMDD"
||         subdate = "YYYYMMDD"
|| Outputs: (subdate - duedate)
||
|| Author: Dr. Zaman; WSU-5261
|| Date: 2013/08/22
|| Modified by: Jared Hess, for use with 
*/
#include "LateByDays.h"

int LateByDays(char *duedt, char *subdt){
  int d1, m1, y1;
  int d2, m2, y2;
  char tmp[5];
  int days1, days2;

/* printf("subdt = %s and duedt = %s \n", subdt, duedt); */

  /* identify year, month, and day of due date */
  strncpy(tmp, &duedt[0], 4);
  tmp[4] = '\0';
  y1 = atoi(tmp);
  strncpy(tmp, &duedt[4], 2);
  tmp[2] = '\0';
  m1 = atoi(tmp);
  strncpy(tmp, &duedt[6], 2);
  tmp[2] = '\0';
  d1 = atoi(tmp);

  /* identify year, month, and day of submission date */
  strncpy(tmp, &subdt[0], 4);
  tmp[4] = '\0';
  y2 = atoi(tmp);
  strncpy(tmp, &subdt[4], 2);
  tmp[2] = '\0';
  m2 = atoi(tmp);
  strncpy(tmp, &subdt[6], 3);
  tmp[2] = '\0';
  d2 = atoi(tmp);

  printf("%i %i %i , %i %i %i\n", y1, m1, d1, y2, m2, d2);
  /* check if it is fall 2013 
  if((y1 != 2013) || (y2 != 2013))
    return (-1);
  if((m1 < 8) || (m1 > 12) || (m2 < 8) || (m2 > 12))
    return (-1);
*/
  /* translate due year-month-day into day of the year */
  /* J=31, F=29, M=31, A=30, M=31, J=30, J=31, A=31, S=30, O=31, N=30, D=31 */
  if (m1 == 8){
    if ((d1 < 1) || (d1 > 31)) return (-2);
    days1 = 31+29+31+30+31+30+31+d1;
  }
  else if (m1 == 9){
    if ((d1 < 1) || (d1 > 30)) return (-1);
    days1 = 31+29+31+30+31+30+31+31+d1;
  }
  else if (m1 == 10){
    if ((d1 < 1) || (d1 > 31)) return (-1);
    days1 = 31+29+31+30+31+30+31+31+30+d1;
  }
  else if (m1 == 11){
    if ((d1 < 1) || (d1 > 30)) return (-1);
    days1 = 31+29+31+30+31+30+31+31+30+31+d1;
  }
  else if (m1 == 12){
    if ((d1 < 1) || (d1 > 31)) return (-1);
    days1 = 31+29+31+30+31+30+31+31+30+31+30+d1;
  }

  /* translate submission year-month-day into day of the year */
  /* J=31, F=29, M=31, A=30, M=31, J=30, J=31, A=31, S=30, O=31, N=30, D=31 */
  if (m2 == 8){
    if ((d2 < 1) || (d2 > 31)) return (-1);
    days2 = 31+29+31+30+31+30+31+d2;
  }
  else if (m2 == 9){
    if ((d2 < 1) || (d2 > 30)) return (-1);
    days2 = 31+29+31+30+31+30+31+31+d2;
  }
  else if (m2 == 10){
    if ((d2 < 1) || (d2 > 31)) return (-1);
    days2 = 31+29+31+30+31+30+31+31+30+d2;
  }
  else if (m2 == 11){
    if ((d2 < 1) || (d2 > 30)) return (-1);
    days2 = 31+29+31+30+31+30+31+31+30+31+d2;
  }
  else if (m2 == 12){
    if ((d2 < 1) || (d2 > 31)) return (-1);
    days2 = 31+29+31+30+31+30+31+31+30+31+30+d2;
  }

/* printf("days1 = %d and days2 = %d \n", days1, days2); */

  /* calculate and return the number of late days */
  if (days1>days2) return 0;
  return (days2 - days1);
}/* end LateByDays */

