#version 330 core
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;

out vec4 fragment_color;
out vec3 normal;
out vec3 fragment_position;

uniform mat4 MVP;
uniform mat4 Model;

void main() {
    gl_Position = MVP * vec4(vertex_position, 1.0f);

    fragment_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    fragment_position = vec3(Model * vec4(vertex_position, 1.0f));

    normal = vertex_normal;
}