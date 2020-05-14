
#version 110

attribute vec3 vPos;
attribute vec3 aColor;
attribute vec2 vTex;

varying vec3 fColor; // 向片段着色器输出一个颜色
varying vec2 v_texCoord;

uniform mat4 aTransform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
   // gl_Position = aTransform*vec4(vPos, 1.0);
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    fColor = aColor;
    v_texCoord = vTex;
}

