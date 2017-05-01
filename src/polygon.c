int		in_poligon(t_poly poly, структура)
{
	int		c;
	int		i;

	c = 0;
	i = -1;
	while (++i + 1 != poly->count)
		c += line_intersect( точка , plane_coords(new_v3d(0, 0, 1),
			poly->poly[i]), plane_coords(new_v3d(0, 0, 1) , poly->poly[i + 1]));
	c += line_intersect( точка , plane_coords(new_v3d(0, 0, 1) , poly->poly[0]),
		plane_coords(new_v3d(0, 0, 1) , poly->poly[poly->count]));
	if (c % 2 == 0 && c != 0)
		return (1);
	return (0);
}

int		line_intersect(t_p2d point, t_p2d a, t_p2d b)
{
	if (((a.y <= point.y) && (point.y < b.y))
		|| ((b.y <= point.y) && (point.y < a.y))) &&
			(point.x > (b.x - a.x) * (point.y - a.y / (b.y - a.y) + a.x))
		return (1);
  }
  return (0);
}
