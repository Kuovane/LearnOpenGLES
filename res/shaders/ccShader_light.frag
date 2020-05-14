
#version 110
uniform sampler2D CC_Texture0;
uniform vec3 objectColor;
uniform vec3 lightColor;
varying vec2 v_texCoord;
varying vec3 color;

void main()
{
    //gl_FragColor = vec4(color, 1.0);
     //gl_FragColor =  texture2D(CC_Texture0, v_texCoord)* vec4(color, 1.0f);
     gl_FragColor = vec4(1.0,1.0,1.0,1.0); 
}