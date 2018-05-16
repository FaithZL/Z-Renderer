#version 150
/*
  VertexShader.glsl
  opengl-series

  Created by SATAN_Z on 16/6/27.

*/



in vec3 vertex;
in vec2 vertTexCoor;
in vec3 normal;

out vec2 fragTexCoor;
out vec3 Normal;
out vec3 fragPos;
out vec3 v_out;

uniform mat4 model;
uniform mat4 VxP;

// model transform
//uniform mat4 model;

void main(){
    
    Normal = normalize(vec3(model * vec4(normal , 0)));
    
//    fragPos = vec3(model * vec4(vertex , 1.0));
    
    fragPos = vec3(vec4(vertex , 1.0));
    
    v_out = vertex;
    
    fragTexCoor = vertTexCoor;
    
    gl_Position = VxP * model * vec4(vertex , 1.0);
//    gl_Position = vec4(vertex , 1.0);

}







