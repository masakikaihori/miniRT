#include "../includes/mini_rt.h"

void	ray_sphere(t_xyz ray, t_sphere obj, t_hit *hit, t_xyz camera)
{
	// float	t;
	float	d;

	d	= pow(2 * (innner_product(camera, ray) - innner_product(obj.coord, ray)), 2.0)
		- 4 * pow(vec_norm(ray), 2.0) * (pow(vec_norm(vec_subtraction(camera, obj.coord)), 2.0) - pow(obj.diameter, 2.0));
	if (d >= 0)
	{
		// hit->t = t;
		hit->color = obj.color;
	}
	else
	{
		hit->color = 0;
	}
	return ;
}

// void	ray_plane(t_xyz ray, t_object *tmp_obj, t_hit *hit)
// {
// 	float	t;

// 	if (t > 0 && hit->t > t)
// 	{
// 		hit->t = t;
// 		hit->colors = tmp_obj->info.plane.colors;
// 		hit->color = tmp_obj->info.plane.color;
// 	}
// 	return ;
// }

// void	ray_cylinder(t_xyz ray, t_object *tmp_obj, t_hit *hit)
// {
// 	float	t;

// 	if (t > 0 && hit->t > t)
// 	{
// 		hit->t = t;
// 		hit->colors = tmp_obj->info.cylinder.colors;
// 		hit->color = tmp_obj->info.cylinder.color;
// 	}
// 	return ;
// }
