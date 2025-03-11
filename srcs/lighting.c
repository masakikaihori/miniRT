#include "../includes/mini_rt.h"

t_xyz   cylinder_normal_vec(t_hit *hit, t_cylinder obj)
{
    double  t;
    t_xyz   normal_vec;

    t = innner_product(vec_subtraction(hit->intersection, obj.coord), obj.vec);
    normal_vec = vec_subtraction(hit->intersection, vec_multiplied(t, obj.vec));
    return (normal_vec);
}

void    sphere_light(t_xyz ray, t_mini *mini, t_hit *hit, t_sphere obj)
{
    t_xyz   camera;
    t_xyz   light;
    t_xyz   normal_vec;
    t_xyz   light_vec;

    camera = mini->camera->coord;
    light = mini->light->coord;
    normal_vec = vec_subtraction(hit->intersection, obj.coord);
    light_vec = vec_subtraction(light, hit->intersection);
    normalize(&normal_vec);
    normalize(&light_vec);
    (void)camera;
    (void)ray;
    return ;
}

void    plane_light(t_xyz ray, t_mini *mini, t_hit *hit, t_plane obj)
{
    t_xyz   camera;
    t_xyz   light;
    t_xyz   normal_vec;
    t_xyz   light_vec;

    camera = mini->camera->coord;
    light = mini->light->coord;
    normal_vec = obj.vec;
    light_vec = vec_subtraction(light, hit->intersection);
    normalize(&light_vec);
    (void)normal_vec;
    (void)camera;
    (void)ray;
    return ;
}

void    cylinder_light(t_xyz ray, t_mini *mini, t_hit *hit, t_cylinder obj)
{
    t_xyz   camera;
    t_xyz   light;
    t_xyz   normal_vec;
    t_xyz   light_vec;

    camera = mini->camera->coord;
    light = mini->light->coord;
    if (hit->cylinder == CYL_UP)
        normal_vec = obj.vec;
    else if (hit->cylinder == CYL_DOWN)
        normal_vec = vec_multiplied(-1.0, obj.vec);
    else
        normal_vec = cylinder_normal_vec(hit, obj);
    light_vec = vec_subtraction(light, hit->intersection);
    normalize(&normal_vec);
    normalize(&light_vec);
    (void)ray;
    (void)camera;
    return ;
}
