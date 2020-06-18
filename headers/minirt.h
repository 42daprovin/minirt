/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <daprovin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:33:39 by daprovin          #+#    #+#             */
/*   Updated: 2020/06/18 05:09:15 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../headers/mlx.h"
# define SP 1
# define PL 2
# define SQ 3
# define CY 4
# define TR 5
# define E 1e-11
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
	void			*imptr;
	int				*imdt;
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
	t_pt			a;
	t_pt			b;
	t_pt			c;
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
	void			*imptr;
	int				*imdt;
	int				size_line;
	int				bpp;
	int				spec;
	int				depth;
	int				line;
	char			clrtext;
}				t_data;

typedef struct	s_mlximg
{
	int			bpp;
	int			sl;
	int			nd;
}				t_mlximg;

typedef struct	s_h
{
	int				r;
	t_vct			n;
}				t_h;

typedef struct	s_supp
{
	double		h;
	double		d;
}				t_supp;

typedef struct	s_structsupp
{
	t_pt		intpt;
	t_h			h;
}				t_structsupp;

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
void			ft_3dshadow(int *clr, double cf[3]);
void			ft_changecf(double (*cf)[3], t_vct lv, t_vct n, t_data data);
void			ft_shadding(int *clr, t_vct n, t_pt ip, t_data *data);
int				ft_checklgt(t_pt ipt, t_pt lgto, t_ray lr);
t_vct			ft_setclrsp(t_data data, int *clr, t_pt intpt);
int				ft_intersp2(t_supp *s, t_data data, t_ray ray, double *t_co);
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
t_h				ft_intersq(t_data data, t_ray ray, int *clr, t_pt *intpt);
int				ft_interlgtsq(t_sq *sq, t_ray lr, t_pt lgto);
t_vct			ft_crossprod(t_vct v, t_vct u);
t_h				ft_intertr(t_data data, t_ray ray, int *clr, t_pt *intpt);
int				p_is_outside_tr(t_tr tr, t_pt p);
double			ft_intertr2(t_tr tr, t_ray ray);
int				ft_interlgttr(t_tr *tr, t_ray lr, t_pt lgto);
double			ft_dotprod2(t_vct v, t_vct u);
t_vct			ft_subsvct(t_vct v, t_vct u);
t_h				ft_intercy(t_data data, t_ray ray, int *clr, t_pt *intpt);
int				ft_interlgtcy(t_cy *cy, t_ray lr, t_pt lgto);
int				ft_checkint(char *str);
int				ft_checkcolor(char *str);
int				ft_checkcf(char *str);
void			init_mlx(t_data *data);
void			ft_errorcheckermalloc(void);
void			ft_checkerror(int	error, int line);
void			ft_checkinput(int ac, char **av);
void			ft_checkdata(t_data *data);
char			*bmp_filename(char *file, int i);
void			ft_save_image(t_data d, int ac, char *file);
void			export_bmp(char *filename, t_data *d);
void			header_bmp(char **data, t_data *d);
void			fill_bmp(char **data, t_data *d);
int				ft_samesquare(t_sq *sq, t_ray lr);
int				ft_clr(int clr[3], double spec, int clr2);
int				ft_refclr(int clr1, int clr, double crf);
int				ft_supersampling(double x, double y, t_data *data);
void			ft_chess(t_pt ipt, int *clr, double nb);
int				ft_clrtext(char **split, t_data *data);
int				ft_cu(char **scu, t_data *data);

#endif
