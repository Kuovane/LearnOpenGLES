
#version 110


//uniform vec4 ourColor; // 在OpenGL程序代码中设定这个变量

varying vec3 fColor;

void main()
{
     gl_FragColor = vec4(fColor,1.0);
}

