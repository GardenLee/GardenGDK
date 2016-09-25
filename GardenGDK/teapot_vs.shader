#version 430 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;


out vec3 normal;
out vec3 position;
out mat4 fs_view_matrix;

void main(){
    //先把model和view截断成mat3。in_Normal表示向量的终点，是不能平移的
    normal = normalize(mat3(view_matrix * model_matrix) * in_Normal);
    vec4 pos = view_matrix * model_matrix * vec4(in_Position, 1.0f);
    position = vec3(pos);
    gl_Position = projection_matrix * pos;
    fs_view_matrix = view_matrix;
}
