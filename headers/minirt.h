/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:33:39 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/07 16:19:23 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define SP 1
# define PL 2
# define SQ 3
# define CY 4
# define TR 5

typedef struct	s_pt
{
	double			x;
	double			y;
	double			z;
}				t_pt;

typedef struct	s_vct
{
	double			a;
	double			b;
	double			c;
}				t_vct;

typedef struct	s_res
{
	int				x;
	int				y;
}				t_res;

typedef struct	s_cam
{
	t_pt			o;
	t_vct			n;
	double			fov;
	struct s_cam	*next;
}				t_cam;

typedef	struct	s_algt
{
	double			br;
	int				clr[3];
}				t_algt;

typedef struct	s_lgt
{
	t_pt			o;
	double			br;
	int				clr[3];
	struct s_lgt	*next;
}				t_lgt;

typedef struct	s_sp
{
	t_pt			c;
	double			d;
	int				clr[3];
}				t_sp;

typedef struct	s_pl
{
	t_pt			pt;
	t_vct			n;
	int				clr[3];
}				t_pl;

typedef struct	s_sq
{
	t_pt			c;
	t_vct			n;
	double			l;
	int				clr[3];
}				t_sq;

typedef struct	s_cy
{
	t_pt			pt;
	t_vct			n;
	double			d;
	double			h;
	int				clr[3];
}				t_cy;

typedef struct	s_tr
{
	t_pt			A;
	t_pt			B;
	t_pt			C;
	int				clr[3];
}				t_tr;

typedef struct	s_obj
{
	int				id;
	void			*fig;
	struct s_obj	*next;
}				t_obj;

typedef struct	s_data
{
	t_obj			*obj;
	t_lgt			*lgt;
	t_cam			*cam;
	t_res			*res;
	t_algt			*algt;
}				t_data;

int				ft_strstrlen(char **str);
double			ft_doubatoi(char *str);
int				ft_checkdoub(char *str);
int				ft_checkargs(char *str);
int				ft_pl(char **spl, t_data *data);
int				ft_sp(char **ssp, t_data *data);
int				ft_sq(char **ssq, t_data *data);
int				ft_cy(char **scy, t_data *data);
int				ft_tr(char **str, t_data *data);
int				ft_reso(char **split, t_data *data);
int				ft_algt(char **split, t_data *data);
int				ft_cam(char **split, t_data *data);
int				ft_lgt(char **split, t_data *data);
void			ft_addbackcam(t_cam **dcam, t_cam *cam);
void			ft_addbacklgt(t_lgt **dlgt, t_lgt *lgt);
void			ft_addbackobj(t_obj **dobj, t_obj *obj);
int				ft_fpt(char *spl, t_pt *pt);
int				ft_fvct(char *spl, t_vct *n);
int				ft_fclr(char *spl, int (*clr)[3]);

#endif
