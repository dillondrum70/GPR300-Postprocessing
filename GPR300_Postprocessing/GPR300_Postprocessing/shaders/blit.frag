#version 450                          
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec2 TexCoord;

uniform sampler2D _ColorTex;

void main(){         
    FragColor = texture(_ColorTex, TexCoord);
    //FragColor = vec4(TexCoord, 0, 1);
}