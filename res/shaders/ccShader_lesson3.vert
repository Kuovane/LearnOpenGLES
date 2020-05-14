
#version 110

attribute vec3 vPos;
attribute vec3 aColor;

varying vec3 fColor; // 向片段着色器输出一个颜色

void main()
{
    gl_Position = vec4(vPos, 1.0);
    fColor = aColor;
}

