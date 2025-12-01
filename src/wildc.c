/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:09:54 by imutavdz          #+#    #+#             */
/*   Updated: 2025/12/01 18:10:44 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
For every argument containing a * (and not protected by single quotes),
 open the directory, compare filenames, 
 and replace the single argument (*.c) 
 with multiple new arguments (file1.c, file2.c).
*/
 #include "shell.h"