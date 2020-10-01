#include "ShaderProgram.h"
#include <stdio.h>
//#include <stdlib.h>

//
// scope file
//
GLuint load_shader(const char* filename, GLenum shader_type) {
    // read shader file into a buffer
    char *buffer = NULL;
    long length;
    FILE *fp = fopen(filename, "r");

    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        buffer = (char *)malloc(length + 1); // for null character
        if (buffer)
        {
            fread(buffer, 1, length, fp);
            buffer[length] = '\0';
        }
        fclose(fp);
    }

    if (!buffer)
    {
        printf("Error reading shader %s\n", filename);
        throw;
    }

    const GLchar* shader_source = (const GLchar *)buffer;

	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint length_info_log;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length_info_log);

		GLchar* info_log = new GLchar[length_info_log + 1];
		glGetShaderInfoLog(shader, length_info_log, NULL, info_log);

		const char* str_shader_type = NULL;
		switch(shader_type)
		{
            case GL_VERTEX_SHADER: str_shader_type = "vertex"; break;
            case GL_GEOMETRY_SHADER: str_shader_type = "geometry"; break;
            case GL_FRAGMENT_SHADER: str_shader_type = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", str_shader_type, info_log);
		delete[] info_log;
	}

	return shader;
}



//
// scope export
// 
ShaderProgram make_shader(const char* vert_path, const char* frag_path) {
    ShaderProgram p;

    // load and compile shaders

    p.vertex_shader_id = load_shader(vert_path, GL_VERTEX_SHADER);
    p.fragment_shader_id = load_shader(frag_path, GL_FRAGMENT_SHADER);

    p.program_id = glCreateProgram();
    glAttachShader(p.program_id, p.vertex_shader_id);
    glAttachShader(p.program_id, p.fragment_shader_id);
    glLinkProgram(p.program_id);
    glValidateProgram(p.program_id);

	GLint status;
	glGetProgramiv (p.program_id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint length_info_log;
		glGetProgramiv(p.program_id, GL_INFO_LOG_LENGTH, &length_info_log);

		GLchar *info_log = new GLchar[length_info_log + 1];
		glGetProgramInfoLog(p.program_id, length_info_log, NULL, info_log);
		fprintf(stderr, "Linker failure: %s\n", info_log);
		delete[] info_log;
	}

    // bind attributes

    glBindAttribLocation(p.program_id, 0, "position");
    glBindAttribLocation(p.program_id, 1, "tex_coords");
    //glBindAttribLocation(program_id, 2, "normal");

    // get uniform locations

    p.loc_transformation_matrix  = glGetUniformLocation(p.program_id, "transform");
    p.loc_projection_matrix = glGetUniformLocation(p.program_id, "projection");
    p.loc_view_matrix = glGetUniformLocation(p.program_id, "view");

    return p;
}

void start_shader(GLuint program_id) {
    glUseProgram(program_id);
}

void stop_shader() {
    glUseProgram(0);
}

void delete_shader(ShaderProgram* p) {
    stop_shader();
    glDetachShader(p->program_id, p->vertex_shader_id);
    glDetachShader(p->program_id, p->fragment_shader_id);
    glDeleteShader(p->vertex_shader_id);
    glDeleteShader(p->fragment_shader_id);
    glDeleteProgram(p->program_id);
}


