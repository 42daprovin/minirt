/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:33:39 by daprovin          #+#    #+#             */
/*   Updated: 2020/02/20 11:24:13 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define SP 1
# define PL 2
# define SQ 3
# define CY 4
# define TR 5
# define E 1e-12
# define MAX_DEPTH 3

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
	double			x;
	double			y;
}				t_res;

typedef struct	s_ray
{
	t_pt			pt;
	t_vct			vct;
}				t_ray;

typedef struct	s_cam
{
	t_pt			o;
	t_vct			n;
	double			fov;
	struct s_cam	*next;
	struct s_cam	*back;
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
	int				spec;
	double			rcf;
}				t_obj;

typedef struct	s_data
{
	t_obj			*obj;
	t_lgt			*lgt;
	t_cam			*cam;
	t_res			*res;
	t_algt			*algt;
	void			*w_ptr;
	void			*mlx;
	int				spec;
	int				depth;
}				t_data;

typedef struct	s_h
{
	int				r;
	t_vct			n;
}				t_h;//esto es de prueba

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
double			ft_dist(t_pt p1, t_pt p2);
int				ft_close(void);
t_ray			ft_rotx(t_ray ray, t_data *data, double ct);
t_ray			ft_roty(t_ray ray, t_data *data, double ca);
t_ray			ft_rotray(t_ray ray, t_data *data);
t_ray			ft_camrays(double x, double y, t_data *data);
t_h				ft_objtype(t_data ndata, t_ray ray, int *clr, t_pt *intpt);
int				ft_intersect(t_ray ray, t_data *data, int *clr);
int				ft_minirt(t_data *data);
int				ft_interlgt(t_pt lgto, t_ray lr, t_data *data);
void			ft_3dshadow(int *clr, double cf);
double			ft_changecf(double cf, t_vct lv, t_vct n, t_data data);
void			ft_shadding(int *clr, t_vct n, t_pt ip, t_data *data);
int				ft_checklgt(t_pt ipt, t_pt lgto, t_ray lr);
t_vct			ft_setclrsp(t_data data, int *clr, t_pt intpt);
int				ft_intersp2(double *h, t_data data, t_ray ray, double *t_co);
t_h				ft_intersp(t_data data, t_ray ray, int *clr, t_pt *intpt);
int				ft_interlgtsp(t_sp *sp, t_ray lr, t_pt lgto);
t_h				ft_interpl(t_data data, t_ray ray, int *clr, t_pt *intpt);
t_vct			ft_setclrpl(t_data data, int *clr, t_pt ipt, t_ray ray);
int				ft_interlgtpl(t_pl *pl, t_ray lr, t_pt lgto);
int				ft_changecam(int key, t_data *data);
t_vct			ft_addvect(t_vct v, t_vct u);
t_vct			ft_normalize(t_vct v);
double			ft_dotprod(t_vct v, t_vct u);
t_vct			ft_escprod(double k, t_vct v);
t_vct			ft_vctatob(t_pt a, t_pt b);

#endif
