/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:14:53 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/01 16:50:22 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	return (c == 32 || (9 <= c && c <= 13));
}

static int	ft_isdigit(int c)
{
	return (48 <= c && c <= 57);
}

static double	get_fraction(const char *str)
{
	int		i;
	double	fraction;
	double	divisor;

	i = 0;
	fraction = 0.0;
	divisor = 10.0;
	while (ft_isdigit(str[i]))
	{
		fraction += (str[i] - '0') / divisor;
		divisor *= 10.0;
		i++;
	}
	return (fraction);
}

double	ft_atof(const char *str)
{
	double	result;
	double	sign;
	int		i;

	i = 0;
	result = 0.0;
	sign = 1.0;
	while (ft_isspace(str[i]))
		i ++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1.0;
		i ++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10.0 + (str[i] - '0');
		i ++;
	}
	if (str[i] == '.')
		i++;
	return ((result + get_fraction(&str[i])) * sign);
}
