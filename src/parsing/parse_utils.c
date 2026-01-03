/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 11:01:29 by oelmanso          #+#    #+#             */
/*   Updated: 2025/12/28 11:01:34 by oelmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub.h"

int	whitespace(char c)
{
	return (c == '\t' || c == ' ');
}

int	is_invalid(char c)
{
	return (c == '\t' || c == ' ' || c == '\0');
}

int	is_allowed(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	check_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	valide_elem(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '1'
		|| c == ' ' || c == '\t' || c == '\0')
		return (1);
	return (0);
}
