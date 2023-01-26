/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 05:43:59 by atchougo          #+#    #+#             */
/*   Updated: 2023/01/26 23:10:48 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include "./libft.h"
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_fprintf(int fd, const char *s, ...);
void	ft_fputnbr_printf(int n, int *r, int fd);
void	ft_fputadr(unsigned long p, int *r, int fd);
void	ft_fputnbr_u(unsigned int n, int *r, int fd);
void	ft_fputhexa_low(int n, int *r, int fd);
void	ft_fputhexa_up(int n, int *r, int fd);
void	ft_fputchar_printf(char c, int *r, int fd);

#endif
