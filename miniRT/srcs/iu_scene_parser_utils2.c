/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iu_scene_parser_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaria-p <mfaria-p@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:29:40 by mfaria-p          #+#    #+#             */
/*   Updated: 2024/12/02 23:30:37 by mfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void *ft_realloc(void *ptr, size_t size) {
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    if (ptr == NULL) {
        return malloc(size);
    }

    void *new_ptr = malloc(size);
    if (new_ptr == NULL) {
        return NULL;
    }

    // Copy the old data to the new memory block
    ft_memcpy(new_ptr, ptr, size);
    free(ptr);

    return new_ptr;
}

int	array_length(char *arr[])
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void	free_array(char *arr[])
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

int is_float(char *str) {
    int i = 0;
    int has_decimal_point = 0;

    // Check for optional sign at the beginning
    if (str[i] == '-' || str[i] == '+') {
        i++;
    }
    // Ensure there is at least one digit or decimal point
    if (!str[i]) {
        return 0;
    }
    // Check the rest of the string for digits and a single decimal point
    while (str[i]) {
        if (ft_isdigit(str[i])) {
            i++;
        } else if (str[i] == '.') {
            if (has_decimal_point) {
                return 0; // More than one decimal point
            }
            has_decimal_point = 1;
            i++;
        } else {
            return 0; // Invalid character
        }
    }
    return 1;
}

int	is_int(char *str)
{
	int	i;

	i = 0;
	// Check for optional sign at the beginning
    if (str[i] == '-' || str[i] == '+') {
        i++;
    }

    // Ensure there is at least one digit
    if (!str[i]) {
        return 0;
    }

    // Check the rest of the string for digits
    while (str[i]) {
        if (ft_isdigit(str[i]) == 0)
            return 0;
        i++;
    }

    return 1;
}
