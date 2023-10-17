#include "main.h"
#include <stdarg.h>
#include <unistd.h>

int _printf(const char *format, ...)
{
    int printed_chars = 0;
    va_list args;

    va_start(args, format);

    if (format == NULL)
        return (0);

    while (*format)
    {
        char c;

        if (*format == '%' && (*(format + 1) == 'c' || *(format + 1) == 's' || *(format + 1) == '%'))
        {
            format++;
            switch (*format)
            {
                case 'c':
                    c = va_arg(args, int);
                    printed_chars += write(1, &c, 1);
                    break;
                case 's':
                {
                    char *str = va_arg(args, char *);
                    str = (str == NULL) ? "(null)" : str;
                    while (*str)
                    {
                        printed_chars += write(1, str++, 1);
                    }
                    break;
                }
                case '%':
                    printed_chars += write(1, "%", 1);
                    break;
            }
        }
        else
        {
            printed_chars += write(1, format, 1);
        }
        format++;
    }

    va_end(args);
    return (printed_chars);
}

