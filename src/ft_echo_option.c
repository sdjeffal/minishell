#include "../inc/minishell.h"

static	void ft_putcharbackslash(int c)
{
	if (c == '\\')
		ft_putchar('\\');
	else if (c == 'a')
		ft_putchar('\a');
	else if (c == 'b')
		ft_putchar('\b');
	else if (c == 'f')
		ft_putchar('\f');
	else if (c == 'n')
		ft_putchar('\n');
	else if (c == 'r')
		ft_putchar('\r');
	else if (c == 't')
		ft_putchar('\t');
	else if (c == 'v')
		ft_putchar('\v');
}

static int	ft_atoct(int octal)
{
	long int dec;
	int tmp;
	int	i;

	dec = 0;
	i = 0;
	while (octal != 0)
	{
		tmp = octal % 10;
		octal /= 10;
		dec += tmp * ft_pow(8, i++); 
	}
	return (dec);
}

static int	ft_putcharoctal(char *str)
{
	int n;
	int v;
	char val[4];

	n = 0;
	bzero(val, 4);
	while (str[n] && ft_isdigit(str[n]) && n < 3)
	{
		val[n] = str[n];
		n++;
	}
	v = ft_atoi(val);
	if (v == 0)
		ft_putchar(' ');
	else
		ft_putchar(ft_atoct(v));
	return (n);
}

static int	ft_putcharhex(char *str)
{
	int n;
	int v;
	int i;
	char val[3];

	n = 0;
	i = 0;
	v = 0;
	bzero(val, 3);
	while (str[n] && ft_ishex(str[n]) && n < 2)
	{
		val[n] = str[n];
		n++;
	}
	while (--n >= 0)
		v += ft_hextodec(val[i++], n);
	if (v == 0)
		ft_putchar(' ');
	else
		ft_putchar(v);
	return (i);
}

static int	parsingbackslash(char *s)
{
	int n;

	n = 0;
	if (ft_strchr("\\abfnrtv", *s))
		ft_putcharbackslash(*s);
	else if (*s == 'e')
		n++;
	else if (*s == '0')
		n = ft_putcharoctal(++s);
	else if (*s == 'x')
		n = ft_putcharhex(++s);
	else if (*s == 'c')
		return (-1);
	return (n);

}

void		putbackslash(char *s, char *option)
{
	int i;
	int n;

	i = -1;
	n = 0;
	while (s[++i])
	{
		if (s[i] == '\\' && s[i + 1] && ft_strchr("\\abcefnrtv0x", s[i + 1]))
		{
			n = parsingbackslash(&s[i + 1]);
			if (n == -1)
				break;
			i = i + n + 1;
		}
		else
			ft_putchar(s[i]);
	}
	if (option[0] != 'n' && n != -1)
			ft_putchar('\n');
}
