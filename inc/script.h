/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/29 17:01:15 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/04 17:37:00 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCRIPT_H
# define SCRIPT_H
# define OUTPUT_BUFFER 32768
# include <termios.h>

typedef struct		s_script
{
	int				ptymst;
	int				ptyslv;
	char			*file;
	char			**envp;
	char			*shell;
	int				opt_a;
	int				opt_q;
	struct winsize	ws;
	char			*cmd;
	int				time;
}					t_script;

int					getpty(int *ptyslv, int *ptymst);
char				*get_env(char **envp, char *get);
void				script(t_script data);

void				get_result(int ptymst, int fd, int tl);
void				send_cmd(int ptymst);
void				put_footer(int fd, t_script data);
void				put_header(int fd, t_script data);

int					init_term(struct termios *termios);
int					restaure_term(struct termios *termios);

void				output_buffer(int fd, char *buf, int size, int tl);

#endif
