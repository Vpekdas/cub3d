/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:45:49 by ledelbec          #+#    #+#             */
/*   Updated: 2024/05/21 17:02:27 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "../cub3d.h"
#include "libft.h"

static void	read_mtl(t_vars *vars, t_mesh *mesh, char **lines, char *filename)
{
	size_t	i;
	char	*mtllib;
	char	buffer[32];
	char	*s;

	i = 0;
	mtllib = NULL;
	mesh->material = NULL;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 7 && !ft_strncmp(lines[i], "mtllib ", 7))
		{
			mtllib = lines[i] + 7;
			break ;
		}
		i++;
	}
	if (!mtllib)
		return ;
	s = ft_strrchr(filename, '/');
	if (s)
	{
		s++;
		ft_memcpy(buffer, filename, s - filename);
		ft_memcpy(buffer + (s - filename), mtllib, ft_strlen(mtllib) + 1);
	}
	else
		ft_memcpy(buffer, mtllib, ft_strlen(mtllib) + 1);
	mesh->material = mtl_load_from_file(vars, buffer);
}

/*
 * To support quad faces, they must be splitted in two triangle faces during
 * loading. So if a face has 4 vertices, count it as 2 face.
 *
 * TODO It should use a count_words function.
 */
static int	num_of_tri_faces(char *line)
{
	int	spaces;

	spaces = 0;
	while (*line)
	{
		if (*line == ' ')
			spaces++;
		line++;
	}
	if (spaces == 4)
		return (2);
	return (1);
}

static void alloc_arrays(t_mesh *mesh, char **lines)
{
	size_t	i;

	i = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 2 && !ft_strncmp(lines[i], "v ", 2))
			mesh->vertices_count++;
		else if (ft_strlen(lines[i]) > 3 && !ft_strncmp(lines[i], "vt ", 3))
			mesh->textures_count++;
		else if (ft_strlen(lines[i]) > 3 && !ft_strncmp(lines[i], "vn ", 3))
			mesh->normals_count++;
		else if (ft_strlen(lines[i]) > 2 && !ft_strncmp(lines[i], "f ", 2))
			mesh->faces_count += num_of_tri_faces(lines[i]);
		i++;
	}

	//printf("- vertices = %zu\n", mesh->vertices_count);
	//printf("- faces    = %zu\n", mesh->faces_count);
	//printf("- textures = %zu\n", mesh->textures_count);
	//printf("- normals  = %zu\n", mesh->normals_count);

	mesh->vertices = malloc(sizeof(t_v3) * mesh->vertices_count);
	mesh->faces = malloc(sizeof(t_face) * mesh->faces_count);
	if (mesh->textures_count > 0)
		mesh->textures = malloc(sizeof(t_v2) * mesh->textures_count);
	else
		mesh->textures = ft_calloc(1, sizeof(t_v2));
	if (mesh->normals_count > 0)
		mesh->normals = malloc(sizeof(t_v3) * mesh->normals_count);
	else
		mesh->normals = ft_calloc(1, sizeof(t_v3));
}

static void	read_face_nums(char *line, int index, t_face *face)
{
	const size_t	sz = ft_strlen(line);
	char			*sv;
	char			*svt;
	char			*svn;
	size_t			i;

	sv = strtok(line, "/");
	svt = strtok(NULL, "/");
	svn = strtok(NULL, "/");
	if (sv == NULL || sv[0] == '\0')
		face->v[index] = 0;
	else
		face->v[index] = ft_atoi(sv) - 1;
	if (svt == NULL || svt[0] == '\0')
		face->t[index] = 0;
	else
		face->t[index] = ft_atoi(svt) - 1;
	if (svn == NULL || svn[0] == '\0')
		face->n[index] = 0;
	else
		face->n[index] = ft_atoi(svn) - 1;
	i = 0;
	while (i < sz)
	{
		if (line[i] == '\0')
			line[i] = '/';
		i++;
	}
}

static void	read_face(t_mesh *mesh, char *line)
{
	t_face	face;
	char	*s0;
	char	*s1;
	char	*s2;
	char	*s3;

	s0 = strtok(line, " ");
	s1 = strtok(NULL, " ");
	s2 = strtok(NULL, " ");
	s3 = strtok(NULL, " ");
	if (s3 != NULL)
	{
		read_face_nums(s0, 0, &face);
		read_face_nums(s1, 1, &face);
		read_face_nums(s3, 2, &face);
		mesh->faces[mesh->faces_count++] = face;
		read_face_nums(s1, 0, &face);
		read_face_nums(s2, 1, &face);
		read_face_nums(s3, 2, &face);
		mesh->faces[mesh->faces_count++] = face;
	}
	else
	{
		read_face_nums(s0, 0, &face);
		read_face_nums(s1, 1, &face);
		read_face_nums(s2, 2, &face);
		mesh->faces[mesh->faces_count++] = face;
	}
}

static void	read_arrays(t_mesh *mesh, char **lines)
{
	size_t	i;

	mesh->vertices_count = 0;
	mesh->textures_count = 0;
	mesh->normals_count = 0;
	mesh->faces_count = 0;
	i = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 2 && !ft_strncmp(lines[i], "v ", 2))
		{
			mesh->vertices[mesh->vertices_count++] = (t_v3){{
				atof(strtok(lines[i] + 2, " ")),
				atof(strtok(NULL, " ")),
				atof(strtok(NULL, " ")),
			}};
		}
		else if (ft_strlen(lines[i]) > 3 && !ft_strncmp(lines[i], "vn ", 3))
		{
			mesh->normals[mesh->normals_count++] = v3(
				atof(strtok(lines[i] + 2, " ")),
				atof(strtok(NULL, " ")),
				atof(strtok(NULL, " "))
			);
		}
		else if (ft_strlen(lines[i]) > 3 && !ft_strncmp(lines[i], "vt ", 3))
		{
			mesh->textures[mesh->textures_count++] = (t_v2){
				atof(strtok(lines[i] + 3, " ")),
				atof(strtok(NULL, " ")),
			};
		}
		else if (ft_strlen(lines[i]) > 2 && !ft_strncmp(lines[i], "f ", 2))
		{
			read_face(mesh, lines[i] + 2);
		}
		i++;
	}
}

t_mesh	*mesh_load_from_obj(t_vars *vars, char *filename)
{
	t_mesh		*mesh;
	const char	*str = read_to_string(filename);
	char		**lines;

	mesh = ft_calloc(1, sizeof(t_mesh));
	lines = ft_split(str, '\n');
	alloc_arrays(mesh, lines);
	read_mtl(vars, mesh, lines, filename);
	read_arrays(mesh, lines);
	if (!mesh_validate(mesh))
		return (NULL);
	return (mesh);
}

bool	mesh_validate(t_mesh *mesh)
{
	(void) mesh;
	// TODO
	return (true);
}
