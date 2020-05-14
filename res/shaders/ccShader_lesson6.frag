
#version 110

uniform sampler2D CC_Texture0;
uniform sampler2D CC_Texture1;
//uniform vec4 ourColor; // 在OpenGL程序代码中设定这个变量

varying vec3 fColor;
varying vec2 v_texCoord;

void main()
{
    // gl_FragColor = texture2D(CC_Texture0, v_texCoord)* vec4(fColor, 1.0);
    vec2 v;
    v.x = 1.0-v_texCoord.x;
    v.y = v_texCoord.y;
    gl_FragColor = mix(texture2D(CC_Texture0, v_texCoord), texture2D(CC_Texture1, v), 0.2);

}

