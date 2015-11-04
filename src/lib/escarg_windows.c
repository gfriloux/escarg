#include "escarg_private.h"

int
_escarg_windows_string_has_space(const char *s,
                               size_t l)
{
   char *p = (char *)s,
        *m = (char *)s + l;
   while (p < m) if (*(p++) == ' ') return 1;
   return 0;
}

char *
_escarg_windows_escape_string(const char *dir)
{
   size_t l;
   int r;
   char *s,
        *p,
        *pb,
        *pe,
        delim = '/';

   l = strlen(dir);
   s = calloc(1, l * 2);
   EINA_SAFETY_ON_NULL_RETURN_VAL(s, NULL);

   p = s;
   pb = strchr(dir, '/');
   if (!pb)
     {
        delim = '\\';
        pb = strchr(dir, '\\');
     }
   EINA_SAFETY_ON_NULL_RETURN_VAL(pb, NULL);

   if (pb != dir)
     {
        strncpy(s, dir, pb-dir);
        p += pb-dir;
        goto first_run;
     }

   while (1)
     {
        size_t ld;
        pb = strchr(pb, delim);
        EINA_SAFETY_ON_NULL_RETURN_VAL(pb, NULL);

first_run:
        pe = strchr(pb+1, delim);
        ld = pe ? pe-pb : (dir+l) - (pb);
        *(p++) = delim;

        r = _escarg_windows_string_has_space(pb, ld);
        if (r) *(p++) = '"';

        strncpy(p, pb+1, ld-1);
        p += ld-1;

        if (r) *(p++) = '"';
        if (!pe) break;

        *(p) = delim;
        pb = pe;
        if (*(pb+1) == 0) break;
     }

   return s;
}

char *
_escarg_windows_escape(Escarg_Type type,
                       void *data)
{
   switch(type)
     {
      case ESCARG_TYPE_DOUBLE:
        {
           double *d = (double *)data;
           return gstring_strdupf("%f", *d);
        }
      case ESCARG_TYPE_UNSIGNED_LONG_LONG_INT:
        {
           unsigned long long int *i = (unsigned long long int *)data;
           return gstring_strdupf("%llu", *i);
        }
      case ESCARG_TYPE_UNSIGNED_LONG_INT:
        {
           unsigned long int *i = (unsigned long int *)data;
           return gstring_strdupf("%lu", *i);
        }
      case ESCARG_TYPE_UNSIGNED_INT:
        {
           unsigned int *i = (unsigned int *)data;
           return gstring_strdupf("%u", *i);
        }
      case ESCARG_TYPE_LONG_LONG_INT:
        {
           long long int *i = (long long int *)data;
           return gstring_strdupf("%lli", *i);
        }
      case ESCARG_TYPE_LONG_INT:
        {
           long int *i = (long int *)data;
           return gstring_strdupf("%li", *i);
        }
      case ESCARG_TYPE_INT:
        {
           int *i = (int *)data;
           return gstring_strdupf("%i", *i);
        }
      case ESCARG_TYPE_STRING:
        {
           char *s = (char *)data;

           return _escarg_windows_escape_string(s);
        }
      case ESCARG_TYPE_CHAR:
        {
           char *c = (char *)data;
           return gstring_strdupf("%c", *c);
        }
      default:
        {
           ERR("Unknown type passed");
           return NULL;
        }
     }

   return NULL;
}

char *
escarg_windows(const char *fmt,
               va_list args)
{
   return escarg_utils_escape(_escarg_windows_escape, fmt, args);
}
