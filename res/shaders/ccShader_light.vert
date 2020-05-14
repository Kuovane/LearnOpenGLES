
#version 110
uniform mat4 Modle;
uniform mat4 View;
uniform mat4 Project;
attribute vec3 vlPos;
//attribute vec2 a_texCoord;
//attribute vec3 vCol;


varying vec3 color;
varying vec2 v_texCoord;

void main()
{
    gl_Position = Project*View *Modle* vec4(vlPos, 1.0);
    //gl_Position =  vec4(vlPos, 1.0);
   // v_texCoord = a_texCoord;
   // color = vCol;
}
