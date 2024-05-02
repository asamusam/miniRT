/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:07:52 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/02 15:08:32 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/minirt.h"

int	parse_ambient(char *line, t_data *data)
{
	static int	n;
	int			i;

	if (n)
		error_and_fail(AMB_NUM_ERR);
	i = 0;
	skip_space(&line[i], &i, NOT_REQUIRED);
	if (parse_float(&data->scene.ambient.intensity, &line[i], &i) == FAIL)
		return (error_and_fail(AMB_FRM_ERR));
	if (parse_color(&data->scene.ambient.color, &line[i], &i) == FAIL)
		return (error_and_fail(AMB_FRM_ERR));
	n ++;
	return (SUCCESS);
}

int	parse_light(char *line, t_data *data)
{
	static int	n;

	(void)line;
	(void)data;
	if (n)
		error_and_fail("More than one light is present in the file.");
	n ++;
	return (SUCCESS);
}

int	parse_camera(char *line, t_data *data)
{
	static int	n;

	(void)line;
	(void)data;
	if (n)
		return (error_and_fail("More than one camera is present in the file."));
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

int	parse(t_data *data, char *scene_file)
{
	char	*line;
	int		fd;

	fd = open(scene_file, O_RDONLY);
	if (fd == -1)
	{
		perror("minirt: parser");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (parse_line(line, data) == FAIL)
		{
			free_scene(data);
			return (FAIL);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (SUCCESS);
}

// TO-DO:
// 0) check files with no info
// 1) check range in ambient
// 2) parse_tuple
// 3) parse camera and light
// 4) parse shapes
// 5) makefile
