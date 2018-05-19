
#include "printf.h"
#include <inttypes.h>  // for linux

int	my_countdigits(intmax_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i = 1;
		n = -n;
	}
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}