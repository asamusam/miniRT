/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:07:52 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/03 13:05:34 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_ambient(char *line, t_data *data)
{
	static int	n;
	int			i;

	if (n)
		return (error_and_fail(AMB, NULL, NUM_ERR));
	i = 0;
	skip_space(&line[i], &i, NOT_REQUIRED);
	if (parse_float(&data->scene->ambient.intensity, &line[i], &i) == FAIL)
		return (error_and_fail(AMB, "Intensity", FORMAT_ERR));
	if (skip_space(&line[i], &i, REQUIRED) == FAIL)
		return (error_and_fail(AMB, "Intensity", FORMAT_ERR));
	if (check_intensity(data->scene->ambient.intensity) == FAIL)
		return (error_and_fail(AMB, "Intensity", RANGE_ERR));
	if (parse_color(&data->scene->ambient.color, &line[i], &i) == FAIL)
		return (error_and_fail(AMB, "Color", FORMAT_ERR));
	if (check_color(&data->scene->ambient.color) == FAIL)
		return (error_and_fail(AMB, "Color", RANGE_ERR));
	if (line[i])
		return (error_and_fail(AMB, NULL, EXTRA_ERR));
	n ++;
	return (SUCCESS);
}

int	parse_camera(char *line, t_data *data)
{
	static int	n;
	int			i;

	if (n)
		return (error_and_fail(CAM, NULL, NUM_ERR));
	i = 0;
	skip_space(&line[i], &i, NOT_REQUIRED);
	if (parse_tuple(&data->scene->camera.position, POINT, &line[i], &i) == FAIL \
		|| skip_space(&line[i], &i, REQUIRED) == FAIL)
		return (error_and_fail(CAM, "Position", FORMAT_ERR));
	if (parse_tuple(&data->scene->camera.rotation, VECTOR, &line[i], &i))
		return (error_and_fail(CAM, "Rotation", FORMAT_ERR));
	if (check_normalized_vector(&data->scene->camera.rotation) == FAIL)
		return (error_and_fail(CAM, "Rotation", RANGE_ERR));
	if (skip_space(&line[i], &i, REQUIRED) == FAIL)
		return (error_and_fail(CAM, "Rotation", FORMAT_ERR));
	if (parse_float(&data->scene->camera.fov, &line[i], &i) == FAIL)
		return (error_and_fail(CAM, "Field of view", FORMAT_ERR));
	if (check_fov(data->scene->camera.fov) == FAIL)
		return (error_and_fail(CAM, "Field of view", RANGE_ERR));
	skip_space(&line[i], &i, NOT_REQUIRED);
	if (line[i])
		return (error_and_fail(CAM, NULL, EXTRA_ERR));
	n ++;
	return (SUCCESS);
}

int	parse_light(char *line, t_data *data)
{
	static int	n;
	int			i;

	if (n)
		return (error_and_fail(LIGHT, NULL, NUM_ERR));
	i = 0;
	skip_space(&line[i], &i, NOT_REQUIRED);
	if (parse_tuple(&data->scene->light.position, POINT, &line[i], &i) == FAIL \
		|| skip_space(&line[i], &i, REQUIRED) == FAIL)
		return (error_and_fail(LIGHT, "Position", FORMAT_ERR));
	if (parse_float(&data->scene->light.intensity, &line[i], &i) == FAIL \
		|| skip_space(&line[i], &i, REQUIRED) == FAIL)
		return (error_and_fail(LIGHT, "Intensity", FORMAT_ERR));
	if (check_intensity(data->scene->light.intensity) == FAIL)
		return (error_and_fail(LIGHT, "Intensity", RANGE_ERR));
	if (parse_color(&data->scene->light.color, &line[i], &i) == FAIL)
		return (error_and_fail(LIGHT, "Color", FORMAT_ERR));
	if (check_color(&data->scene->light.color) == FAIL)
		return (error_and_fail(LIGHT, "Color", RANGE_ERR));
	if (line[i])
		return (error_and_fail(LIGHT, NULL, EXTRA_ERR));
	n ++;
	return (SUCCESS);
}

int	parse_line(char *line, t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (ft_isspace(line[i]))
		i ++;
	if (!line[i])
		return (SUCCESS);
	else if (line[i] == 'A' && ft_isspace(line[i + 1]))
		status = parse_ambient(&line[i + 2], data);
	else if (line[i] == 'L' && ft_isspace(line[i + 1]))
		status = parse_light(&line[i + 2], data);
	else if (line[i] == 'C' && ft_isspace(line[i + 1]))
		status = parse_camera(&line[i + 2], data);
	else if (line[i] == 's' && line[i + 1] == 'p' && ft_isspace(line[i + 2]))
		status = parse_sphere(&line[i + 3], data);
	else if (line[i] == 'c' && line[i + 1] == 'y' && ft_isspace(line[i + 2]))
		status = parse_cylinder(&line[i + 3], data);
	else if (line[i] == 'p' && line[i + 1] == 'l' && ft_isspace(line[i + 2]))
		status = parse_plane(&line[i + 3], data);
	else
		status = unknown_identifier(&line[i]);
	return (status);
}

void	parse(t_data *data, char *scene_file)
{
	char	*line;
	int		fd;

	fd = open(scene_file, O_RDONLY);
	if (fd == -1)
	{
		perror("minirt: parse");
		free_data(data);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (parse_line(line, data) == FAIL)
		{
			close(fd);
			free(line);
			free_data(data);
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
