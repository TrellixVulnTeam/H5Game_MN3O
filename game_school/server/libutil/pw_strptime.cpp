#ifndef __linux

#include <ctype.h>
#include <string.h>
#include <time.h>
 

int
strptime_getnum (const char *buf,
				 int *num,
				 int *bi,
				 int *fi,
				 int min,
				 int max);

 char *
strptime(const char *buf, const char *format, struct tm *tm)
{
  int bi = 0;
  int fi = 0;
  bool percent = false;

  if (!buf || !format)
    return 0;

  while (format[fi] != '\0')
    {
      if (percent)
        {
          percent = false;
          switch (format[fi])
            {
            case '%':                        // an escaped %
              if (buf[bi] == '%')
                {
                  ++fi;
                  ++bi;
                }
              else
                return const_cast<char*> (buf + bi);
              break;

              /* not supported yet: weekday via locale long/short names
                 case 'a':                        / * weekday via locale * /
                 / * FALL THROUGH * /
                 case 'A':                        / * long/short names * /
                 break;
                 */

              /* not supported yet:
                 case 'b':                        / * month via locale * /
                 / * FALL THROUGH * /
                 case 'B':                        / * long/short names * /
                 / * FALL THROUGH * /
                 case 'h':
                 break;
                 */

              /* not supported yet:
                 case 'c':                        / * %x %X * /
                 break;
                 */

              /* not supported yet:
                 case 'C':                        / * date & time -  * /
                 / * locale long format * /
                 break;
                 */

            case 'd':                        /* day of month (1-31) */
              /* FALL THROUGH */
            case 'e':
              if (!strptime_getnum
                     (buf + bi, &tm->tm_mday, &bi, &fi, 1, 31))
                return const_cast<char*> (buf + bi);

              break;

            case 'D':                        /* %m/%d/%y */
              if (!strptime_getnum
                     (buf + bi, &tm->tm_mon, &bi, &fi, 1, 12))
                return const_cast<char*> (buf + bi);

              --fi;
              tm->tm_mon--;

              if (buf[bi] != '/')
                return const_cast<char*> (buf + bi);

              ++bi;

              if (!strptime_getnum
                     (buf + bi, &tm->tm_mday, &bi, &fi, 1, 31))
                return const_cast<char*> (buf + bi);

              --fi;
              if (buf[bi] != '/')
                return const_cast<char*> (buf + bi);
              ++bi;
              if (!strptime_getnum
                     (buf + bi, &tm->tm_year, &bi, &fi, 0, 99))
                return const_cast<char*> (buf + bi);
              if (tm->tm_year < 69)
                tm->tm_year += 100;
              break;

            case 'H':                        /* hour (0-23) */
              /* FALL THROUGH */
            case 'k':
              if (!strptime_getnum
                     (buf + bi, &tm->tm_hour, &bi, &fi, 0, 23))
                return const_cast<char*> (buf + bi);
              break;

              /* not supported yet:
                 case 'I':                        / * hour (0-12) * /
                 / * FALL THROUGH * /
                 case 'l':
                 break;
                 */

            case 'j':                        /* day of year (0-366) */
              if (!strptime_getnum
                     (buf + bi, &tm->tm_yday, &bi, &fi, 1, 366))
                return const_cast<char*> (buf + bi);

              tm->tm_yday--;
              break;

            case 'm':                        /* an escaped % */
              if (!strptime_getnum
                     (buf + bi, &tm->tm_mon, &bi, &fi, 1, 12))
                return const_cast<char*> (buf + bi);

              tm->tm_mon--;
              break;

            case 'M':                        /* minute (0-59) */
              if (!strptime_getnum
                     (buf + bi, &tm->tm_min, &bi, &fi, 0, 59))
                return const_cast<char*> (buf + bi);

              break;

              /* not supported yet:
                 case 'p':                        / * am or pm for locale * /
                 break;
                 */

              /* not supported yet:
                 case 'r':                        / * %I:%M:%S %p * /
                 break;
                 */

            case 'R':                        /* %H:%M */
              if (!strptime_getnum
                     (buf + bi, &tm->tm_hour, &bi, &fi, 0, 23))
                return const_cast<char*> (buf + bi);

              --fi;
              if (buf[bi] != ':')
                return const_cast<char*> (buf + bi);
              ++bi;
              if (!strptime_getnum
                     (buf + bi, &tm->tm_min, &bi, &fi, 0, 59))
                return const_cast<char*> (buf + bi);

              break;

            case 'S':                        /* seconds (0-61) */
              if (!strptime_getnum
                     (buf + bi, &tm->tm_sec, &bi, &fi, 0, 61))
                return const_cast<char*> (buf + bi);
              break;

            case 'T':                        /* %H:%M:%S */
              if (!strptime_getnum
                     (buf + bi, &tm->tm_hour, &bi, &fi, 0, 23))
                return const_cast<char*> (buf + bi);

              --fi;
              if (buf[bi] != ':')
                return const_cast<char*> (buf + bi);
              ++bi;
              if (!strptime_getnum
                     (buf + bi, &tm->tm_min, &bi, &fi, 0, 59))
                return const_cast<char*> (buf + bi);

              --fi;
              if (buf[bi] != ':')
                return const_cast<char*> (buf + bi);
              ++bi;
              if (!strptime_getnum
                     (buf + bi, &tm->tm_sec, &bi, &fi, 0, 61))
                return const_cast<char*> (buf + bi);

              break;

            case 'w':                        /* day of week (0=Sun-6) */
              if (!strptime_getnum
                     (buf + bi, &tm->tm_wday, &bi, &fi, 0, 6))
                return const_cast<char*> (buf + bi);

              break;

              /* not supported yet: date, based on locale
                 case 'x':                        / * date, based on locale * /
                 break;
                 */

              /* not supported yet:
                 case 'X':                        / * time, based on locale * /
                 break;
                 */

            case 'y':                        /* the year - 1900 (0-99) */
              if (!strptime_getnum
                     (buf + bi, &tm->tm_year, &bi, &fi, 0, 99))
                return const_cast<char*> (buf + bi);

              if (tm->tm_year < 69)
                tm->tm_year += 100;
              break;

            case 'Y':                        /* the full year (1999) */
              if (!strptime_getnum
                     (buf + bi, &tm->tm_year, &bi, &fi, 0, 0))
                return const_cast<char*> (buf + bi);

              tm->tm_year -= 1900;
              break;

            default:                        /* unrecognised */
              return const_cast<char*> (buf + bi);
            } /* switch (format[fi]) */

        }
      else
        { /* if (percent) */
          if (format[fi] == '%')
            {
              percent = true;
              ++fi;
            }
          else
            {
              if (format[fi] == buf[bi])
                {
                  ++fi;
                  ++bi;
                }
              else
                return const_cast<char*> (buf + bi);
            }
        } /* if (percent) */
    } /* while (format[fi] */

  return const_cast<char*> (buf + bi);
}

int
strptime_getnum (const char *buf,
                         int *num,
                         int *bi,
                         int *fi,
                         int min,
                         int max)
{
  int i = 0, tmp = 0;

  while (isdigit (buf[i]))
    {
      tmp = (tmp * 10) + (buf[i] - '0');
      if (max && (tmp > max))
        return 0;
      ++i;
    }

  if (tmp < min)
    return 0;
  else if (i)
    {
      *num = tmp;
      (*fi)++;
      *bi += i;
      return 1;
    }
  else
    return 0;
}
#endif