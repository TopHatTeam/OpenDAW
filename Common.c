// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      Common things we need to make the world go around
//
// ---------------------------------------------------------

#include "headers/Common.h"

char* cstrdup(const char* x)
{
    char* copy = malloc(strlen(x) + 1);
    if (copy)
    {
        strcpy(copy, x);
    }
    return copy;
}

double csin(double x)
{
    // Let's opmtimize the sin function 
    double x2 = x * x; 
    double x3 = x2 * x;
    double x4 = x3 * x;
    double x5 = x4 * x;
    double x6 = x5 * x;
    double x7 = x6 * x;
    double x8 = x7 * x;
    double x9 = x8 * x;
    // Taylor series expansion for sin(x) around 0
    // sin(x) = x - x^3/3! + x^5/5! - x^7/7! + x^9/9!
    return x - (x3 / 6.0) + (x5 / 120.0) - (x7 / 5040.0) + (x9 / 362880.0);
} 

float csinf(float x)
{
    // Oooooo, let's optimize this bad boy!
    float x2 = x * x;
    float x3 = x2 * x;
    float x4 = x3 * x;
    float x5 = x4 * x;
    float x6 = x5 * x;  
    float x7 = x6 * x;
    float x8 = x7 * x;
    float x9 = x8 * x;
    // Taylor series expansion for sin(x) around 0
    // sin(x) = x - x^3/3! + x^5/5! - x^7/7! + x^9/9!
    return x - (x3 / 6.0f) + (x5 / 120.0f) - (x7 / 5040.0f) + (x9 / 362880.0f);
}

#if !defined(HAS_LIBC)

static int skip_atoi(const char** s)
{
    int i = 0; 
    while (isdigit(**s))
    {
        i = i * 10 + *((*s)++) - '0';
    }

    return i;
}

size_t strnlen(const char* s, size_t count)
{
    const char* sc;

    for (sc = s; count-- && *sc != '\0'; ++sc)
    
    return sc - s;
}

static char* number(char* string, long number, int base, int size, int precision, int type)
{
    static const char digits[16] = "0123456789ABCDEF";

    char temp[66];
    char c, sign, locase;
    int i;

    locase = (type & SMALL);
    if (type & LEFT)
    {
        /* '&=' is a fancy way of doing this
            type = type & ~ZEROPAD;

            also ~ZEROPAD just flips every single bit
            example:
                ZEROPAD     = 0b0001
                ~ZEROPAD    = 0b1110
        */
        type &= ~ZEROPAD;
    }

    /* This just checks to see if base is invalid
        if base is less than 2 or base is greater than 16
    */
    if (base < 2 || base > 16)
    {
        /* We can't handle i, so just return an NULL value aka error*/
        return NULL;
    }

    c = (type & ZEROPAD) ? '0' : ' ';
    sign = 0;
    if (type & SIGN)
    {
        /* If number is less than 0*/
        if (number < 0)
        {
            sign = '-';
            number = -number;
            size--;
        }

        else if (type & PLUS)
        {
            sign = '+';
            size--;
        }

        else if (type & SPACE)
        {
            sign = ' ';
            size--;
        }
    }

    if (type & SPECIAL)
    {
        if (base == 16)
        {
            size -= 2;
        }
        else if (base == 8)
        {
            size--;
        }
    }

    i = 0;
    /* If number equals zero*/
    if (number == 0)
    {
        temp[i++] = '0';
    }
    else 
    {
        /* While number does not equal zero*/
        while (number != 0)
        {
            temp[i++] = (digits[__do_div(number, base)] | locase);
        }
    }

    /* If i is greater than precision*/
    if (i > precision)
    {
        precision = i;
    }

    /* basically a fancy way of saying 
        size = size - precision;
    */
    size -= precision;
    if (!(type & (ZEROPAD + LEFT)))
    {
        while (size-- > 0)
        {
            *string = ' ';
        }
    }

    if (sign)
    {
        *string++ = sign;
    }

    if (type & SPECIAL)
    {   
        /* If base equals 8*/
        if (base == 8)
        {
            *string++ = '0';
        }
        
        /* Else if base equals 16*/
        else if (base == 16)
        {
            *string++ = '0';
            *string++ = ('X' | locase);
        }
    }

    if (!(type & LEFT))
    {
        while (size-- > 0)
        {
            *string++ = c;
        }
    }

    while (i < precision)
    {
        *string++ = '0';
    }

    while (i-- > 0)
    {
        *string++ = temp[i];
    }

    while (size-- > 0)
    {
        *string++ = ' ';
    }

    return string;
}

int vsprintf(char* buffer, const char* fmt, va_list args)
{
    int length;
    unsigned long num;
    int i, base;
    char* string;
    const char* s;
    int flags;
    int field_width;
    int precision;
    int qualifier;

    for (string = buffer; *fmt; ++fmt)
    {
        if (*fmt != '%')
        {
            *string++ = *fmt;
            continue;
        }

        
    flags = 0;

    repeat:
        ++fmt;
        switch(*fmt)
        {
            case '-':
                flags |= LEFT;
                goto repeat;
            case '+': 
                flags |= PLUS;
                goto repeat;
            case ' ':
                flags |= SPACE;
                goto repeat;
            case '#':
                flags |= SPECIAL;
                goto repeat;
            case '0':
                flags |= ZEROPAD;
                goto repeat;
        }

        field_width -1;
        if (isdigit(*fmt))
        {
            field_width = skip_atoi(&fmt);
        }
        else if (*fmt == '*')
        {
            ++fmt;
            field_width = va_arg(args, int);
            if (field_width < 0)
            {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

        precision = -1;
        if (*fmt == '.')
        {
            ++fmt;
            if (isdigit(*fmt))
            {
                precision = skip_atoi(&fmt);
            }
            else if (*fmt == '*')
            {
                ++fmt;
                precision = va_arg(args, int);
            }

            if (precision < 0)
            {
                precision = 0;
            }
        }

        qualifier = -1;
        if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L')
        {
            qualifier = *fmt;
            ++fmt;
        }

        base = 10;

        switch(*fmt)
        {
            case 'c':
                if (!(flags & LEFT))
                {
                    while (--field_width > 0)
                    {
                        *string++ = ' ';
                        continue;
                    }
                }

            case 's':
                s = va_arg(args, char *);
                length = strnlen(s, precision);

                if (!(flags & LEFT))
                {
                    while (length < field_width--)
                    {
                        *string++ = ' ';
                    }

                    for (i = 0; i < length; ++i)
                    {
                        *string = *s++;
                    }

                    while(length < field_width--)
                    {
                        *string++ = ' ';
                    }

                    continue;
                }

            case 'p':
                if (field_width == -1)
                {
                    field_width = 2 * sizeof(void *);
                    flags |= ZEROPAD;
                }
                string = number(string, 
                    (unsigned long)va_arg(args, void *), 16,
                    field_width, precision, flags
                );
                continue;

            case 'n':
                if (qualifier == 'l')
                {
                    long* ip = va_arg(args, long *);
                    *ip = (string - buffer);
                }
                else 
                {
                    int* ip = va_arg(args, int *);
                    *ip = (string - buffer);
                }
                continue;

            case '%':
                *string++ = '%';
                continue;

            case 'o':
                base = 8;
                break;

            case 'x':
                flags |= SMALL;
                fallthrough;
            
            case 'X':
                base = 16;
                break;

            case 'd':
                /* This was left empty in linux/arch/x86/boot/prinf.c
                    I wonder if Linus Torvalds knows about this?
                */
            case 'i':
                flags |= SIGN;
                break;

            case 'u':
                break;
            
            default:
                *string++ = '%';
                if (*fmt)
                {
                    *string++ = *fmt;
                }
                else 
                {
                    --fmt;
                }
                continue;
        }

        if (qualifier == 'l')
        {
            num = va_arg(args, unsigned long);
        }
        else if (qualifier == 'h')
        {
            num = (unsigned short)va_arg(args, int);
            if (flags & SIGN)
            {
                /* Casting a int to a short*/
                num = (short)num;
            }
        }
        else 
        {
            num = va_arg(args, unsigned int);
        }
        string = number(string, num, base, field_width, precision, flags);
    }
    *string = '\0';
    return string - buffer;
}

int sprintf(char* buffer, const char* fmt, ...)
{
    va_list args;
    int i;

    va_start(args, fmt);
    i = vsprintf(buffer, fmt, args);
    va_end(args);

    return i;
}

int printf(const char* fmt, ...)
{
    char printf_buffer[1024];
    va_list args;
    int printed;

    va_start(args, fmt);
    printed = vsprintf(printf_buffer, fmt, args);
    va_end(args);

    puts(printf_buffer);
}

#endif