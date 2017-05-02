/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:41:57 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/01 18:22:46 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifdef linux
#  define XK_LATIN1
#  define XK_MISCELLANY
#  define XK_TECHNICAL
#  include <X11/keysymdef.h>
#  define K_ESC XK_Escape
#  define K_W XK_w
#  define K_S XK_s
#  define K_A XK_a
#  define K_D XK_d
#  define K_LA XK_Left
#  define K_RA XK_Right
#  define K_UA XK_Up
#  define K_DA XK_Down
#  define K_E XK_e
#  define K_M XK_m
#  define K_T XK_t
#  define K_Q XK_q
#  define K_SP XK_space
#  define K_ENT XK_Return
# else
#  define K_ESC 53
#  define K_W 13
#  define K_S 1
#  define K_A 0
#  define K_D 2
#  define K_E 14
#  define K_M 46
#  define K_T 17
#  define K_Q 12
#  define K_LA 123
#  define K_RA 124
#  define K_UA 126
#  define K_DA 125
#  define K_SP 49
#  define K_ENT 36
# endif
