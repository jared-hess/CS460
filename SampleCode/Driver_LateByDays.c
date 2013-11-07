/* C driver to test other functions
||
|| Author: Dr. Zaman; WSU-5261
|| Date:
*/
#include "MyHeader.h"
int main (void)
{
  char duedt[9];
  char subdt[9];
  int dtdue, dtsub, dtlate;

  printf("Note: this program does not check the correctness of entered values.\n");
  printf("Please enter valid values.\n");

  printf("Enter hw01 due date as YYYYMMDD> ");
  scanf("%s", duedt);
  printf("You entered %s\n", duedt);

  printf("Enter hw01 submission date as YYYYMMDD> ");
  scanf("%s", subdt);
  printf("You entered %s\n", subdt);

  dtdue = atoi(duedt);
  dtsub = atoi(subdt);
  if ( (dtsub == dtdue) || (dtsub < dtdue) ){
    printf("Not a late submission.\n");
    exit (0);
  }/* end if */

  dtlate = LateByDays(duedt, subdt);
  if ( dtlate < 0)
    printf("Error in LateByDays() function!\n");
  else
    printf("You are late by %d day(s).\n", dtlate);

  return (0);
}/* end main */

