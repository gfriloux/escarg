#include "escarg_private.h"

static int _escarg_init_count     = 0;
int        _escarg_log_dom_global = -1;

char *
escarg_cmd(
   Escarg_Mode mode,
   const char *app,
   const char *args,
   ...)
{
   va_list vargs;
   char   *s = NULL;
   Eina_Strbuf *buf;

   EINA_SAFETY_ON_NULL_RETURN_VAL(app, NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(args, NULL);

   va_start(vargs, args);

   buf = eina_strbuf_new();
   EINA_SAFETY_ON_NULL_RETURN_VAL(buf, NULL);

#define _CONSUME_STRING(_a, _b, _c)                                            \
   do {                                                                        \
      EINA_SAFETY_ON_NULL_GOTO(_a, _c);                                        \
      eina_strbuf_append(_b, _a);                                              \
      free(_a);                                                                \
   } while (0)

   switch (mode)
     {
      case ESCARG_MODE_BASH:
         s = escarg(ESCARG_MODE_BASH, "%s ", app);
         _CONSUME_STRING(s, buf, free_buf);

         s = escarg_bash(args, vargs);
         _CONSUME_STRING(s, buf, free_buf);
         break;
      case ESCARG_MODE_POSIX:
         s = escarg(ESCARG_MODE_POSIX, "%s ", app);
         _CONSUME_STRING(s, buf, free_buf);

         s = escarg_posix(args, vargs);
         _CONSUME_STRING(s, buf, free_buf);
         break;
      case ESCARG_MODE_WINDOWS:
         s = escarg_utils_strdupf("\"%s\" ", app);
         _CONSUME_STRING(s, buf, free_buf);

         s = escarg_windows(args, vargs);
         _CONSUME_STRING(s, buf, free_buf);
         break;
     }

#undef _CONSUME_STRING

   va_end(vargs);
   s = eina_strbuf_string_steal(buf);
   eina_strbuf_free(buf);
   return s;

free_buf:
   eina_strbuf_free(buf);
   return NULL;
}

char *
escarg(
   Escarg_Mode mode,
   const char *fmt,
   ...)
{
   va_list args;
   char   *s = NULL;

   EINA_SAFETY_ON_NULL_RETURN_VAL(fmt, NULL);

   va_start(args, fmt);

   switch (mode)
     {
      case ESCARG_MODE_BASH:
         s = escarg_bash(fmt, args);
         break;
      case ESCARG_MODE_WINDOWS:
         s = escarg_windows(fmt, args);
         break;
      case ESCARG_MODE_POSIX:
         s = escarg_posix(fmt, args);
         break;
      default:
         ERR("Unknown mode specified.");
     }

   va_end(args);
   return s;
}
int
escarg_init(
   void)
{
   if (++_escarg_init_count != 1)
      return _escarg_init_count;

   if ( !eina_init() )
     {
        fprintf(stderr, "Escarg can not initialize Eina\n");
        return --_escarg_init_count;
     }

   _escarg_log_dom_global = eina_log_domain_register("escarg", EINA_COLOR_RED);
   if (_escarg_log_dom_global < 0)
     {
        EINA_LOG_ERR("Escarg can not create a general log domain.");
        goto shutdown_eina;
     }

   DBG("Successfully started");
   return _escarg_init_count;

shutdown_eina:
   eina_shutdown();
   return --_escarg_init_count;
}
int
escarg_shutdown(
   void)
{
   if (_escarg_init_count <= 0)
     {
        fprintf(stderr, "Escarg init count not greater than 0 in shutdown.");
        return 0;
     }

   if (--_escarg_init_count != 0)
      return _escarg_init_count;

   eina_log_domain_unregister(_escarg_log_dom_global);
   _escarg_log_dom_global = -1;
   eina_shutdown();
   return _escarg_init_count;
}
