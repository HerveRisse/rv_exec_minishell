
#include "../parser/parser.h"
#include "../execution/execution.h"

void	ft_itoa_buf(int n, char *buf)
{
	int		i;
	int		len;
	long	nb;

	nb = n;
	len = (nb <= 0);
	while (n != 0 && ++len)
		n /= 10;
	i = len;
	buf[i--] = '\0';
	if (nb < 0)
	{
		buf[0] = '-';
		nb = -nb;
	}
	else if (nb == 0)
		buf[0] = '0';
	while (nb > 0)
	{
		buf[i--] = (nb % 10) + '0';
		nb /= 10;
	}
}
