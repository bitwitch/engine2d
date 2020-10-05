#include "texture.h"
#include <vector>
#include "stb_image.h"

// TODO(shaw): cleanup textures by called glDeleteTextures or something like that 
static std::vector<GLuint> textures;

GLuint load_texture(const char* filename) {
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image
    int width, height, num_channels;
    char full_filename[100];
    sprintf(full_filename, "data/textures/%s", filename);

    unsigned char* data = stbi_load(full_filename, &width, &height, &num_channels, 0);

    if (!data) {
        printf("Failed to load texture\n");
        data = stbi_load("data/textures/missing.png", &width, &height, &num_channels, 0);
    }

    GLenum pixel_format = GL_RGB;
    if (num_channels == 4) {
        pixel_format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, pixel_format, width, height, 0, pixel_format, GL_UNSIGNED_BYTE, data);
    //glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    textures.push_back(texture_id);
    return texture_id;
}

