#version 450                          
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform vec3 _Color;

void main(){         
    FragColor = vec4(_Color,1.0f);
    BrightColor = FragColor;
}
