#ifdef HAVE_CONFIG
#include "libizy/config.h"
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "libizy/izy.h"
#include "izymakecheck.h"


int main()
{
#include "vd_acos_c.inc"
  int i;
  double * results_data = NULL;
  results_data = (double * ) malloc(n_expected*sizeof(double));
  if(!results_data)
    {
      return _MALLOCERROR;
    }

  const int offsetin0 = 0;
  const int offsetout0 = 0;
  const int count = n_in;

  /* make izy call */
  vd_acos(&count,in_data,&offsetin0,results_data,&offsetout0);

  /* check */
  for(i=0; i<n_expected; i++)
    {
      if(fabs(results_data[i]-expected_data[i])>=IZY_DBL_EPSILON)
        {
          return _INCORRECTRESULT;
        }

    }

  /* stage offset call */
  const int offsetin_used0 = (int)0.2*offsetin0;
  const int offsetout_used0 = (int)0.4*offsetin0;;
  const int count_used = count - offsetout_used0;
  memset(results_data,0x0,count*sizeof(double));

  /* make izy call */
  vd_acos(&count_used,in_data,&offsetin_used0,results_data,&offsetout_used0);

  /* check */
  for(i=offsetout_used0; i < offsetout_used0+count_used; i++)
    {
      if(fabs(results_data[i]-expected_data[i])>=IZY_DBL_EPSILON)
        {
          return _INCORRECTRESULT;
        }

    }

  /* stage calls to saturation */
  double IVAL =  0.e0;
  double RVAL =  0.e0;
  const int one = 1;

  /* test NaN */
  IVAL = NAN;
  vd_acos(&one, &IVAL, &offsetin0,&RVAL,&offsetout0);
  if(!isnan(RVAL))
    {
      return _INCORRECTRESULT;
    }

  /* test +INF */
  IVAL = INFINITY;
  vd_acos(&one, &IVAL, &offsetin0,&RVAL,&offsetout0);
  if(!isnan(RVAL))
    {
      return _INCORRECTRESULT;
    }

  /* test -INF */
  IVAL = -INFINITY;
  vd_acos(&one, &IVAL, &offsetin0,&RVAL,&offsetout0);
  if(!isnan(RVAL))
    {
      return _INCORRECTRESULT;
    }

  /* stage calls to out of bounds */
  IVAL = 2;
  vd_acos(&one, &IVAL, &offsetin0,&RVAL,&offsetout0);
  if(!isnan(RVAL))
    {
      return _INCORRECTRESULT;
    }

  IVAL = -2;
  vd_acos(&one, &IVAL, &offsetin0,&RVAL,&offsetout0);
  if(!isnan(RVAL))
    {
      return _INCORRECTRESULT;
    }

  /* stage calls at poles, should ret 0 */
  IVAL = 1;
  vd_acos(&one, &IVAL, &offsetin0,&RVAL,&offsetout0);
  if(fabs(RVAL)>=IZY_DBL_EPSILON)
    {
      return _INCORRECTRESULT;
    }

  IVAL = -1;
  vd_acos(&one, &IVAL, &offsetin0,&RVAL,&offsetout0);
  if(fabs(RVAL-M_PI)>=IZY_DBL_EPSILON)
    {
      return _INCORRECTRESULT;
    }



  free(results_data);
  return 0;
}