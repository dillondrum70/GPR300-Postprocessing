#version 450                          
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D _ColorTex;

uniform float _AberrationAmount;

void main(){         
     float red = texture(_ColorTex, TexCoord + vec2(_AberrationAmount, 0)).r;
     float green = texture(_ColorTex, TexCoord).g;
     float blue = texture(_ColorTex, TexCoord + vec2(_AberrationAmount, 0)).b;

     FragColor = vec4(red, green, blue, 1);
}