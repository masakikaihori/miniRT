#include "../includes/mini_rt.h"

double	spec_light(double ratio, t_xyz reflight_vec, t_xyz ray)
{
	return (SPE_REF * ratio
		* pow(inner_pro(reflight_vec, vec_mul(-1.0, ray)), SHINE));
}

t_xyz	reflection_vec(t_xyz normal_vec, t_xyz light_vec)
{
	return (vec_sub(vec_mul(2 * inner_pro(normal_vec, light_vec), normal_vec),
			light_vec));
}

t_xyz	cylinder_normal_vec(t_hit *hit, t_cylinder obj)
{
	double	t;
	t_xyz	normal_vec;

	t = inner_pro(vec_sub(hit->intersection, obj.coord), obj.vec);
	normal_vec = vec_sub(hit->intersection, vec_mul(t, obj.vec));
	return (normal_vec);
}
