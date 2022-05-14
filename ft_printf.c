#include <stdarg.h>
#include <unistd.h>

int  g_var = 0;

void	write_number(unsigned long l, unsigned long base, char *str)
{
	if (l < base)
	{
		write (1, &str[l], 1);
		g_var += 1;
	}
	else
	{
		write_number(l / base, base, str);
		write_number(l % base, base, str);
	}
}

void	write_number_x(unsigned int l, unsigned int base, char *str)
{
	if (l < base)
	{
		write (1, &str[l], 1);
		g_var += 1;
	}
	else
	{
		write_number(l / base, base, str);
		write_number(l % base, base, str);
	}
}

int ft_printf(const char *fmt, ...)
{
	va_list		ap;
	long long	d;
	char		*str;
	int			len;
	int			x;

	g_var = 0;
	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt == 's')
			{
				len = 0;
				str = va_arg(ap, char *);
				if (!str)
					str = "(null)";
				while (str[len])
					len++;
				g_var += len;
				write(1, str, len);
			}
			else if (*fmt == 'd')
			{
				d = va_arg(ap, int);
				if (d < 0)
				{
					write(1, "-", 1);
					g_var++;
					d = -d;
				}
				write_number(d, 10, "0123456789");
			}
			else if (*fmt == 'x')
			{
				x = va_arg(ap, int);
				write_number_x(x, 16, "0123456789abcdef");
			}
			fmt++;
		}
		else
			g_var += write(1, fmt++, 1);
	}
	va_end(ap);
	return(g_var);
}
