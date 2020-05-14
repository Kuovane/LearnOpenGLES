
#version 110
uniform mat4 Modle;
uniform mat4 View;
uniform mat4 Project;
attribute vec3 vPos;
attribute vec2 a_texCoord;
attribute vec3 vNormal;


varying vec3 FragPos;
varying vec3 Normal;

varying vec2 v_texCoord;

void main()
{
	 FragPos = vec3(Modle * vec4(vPos, 1.0));

    gl_Position = Project*View * vec4(FragPos, 1.0);
   //gl_Position = Project*View * Modle* vec4(vPos, 1.0);
    v_texCoord = a_texCoord;
    Normal = vNormal;

    //Normal = mat3(transpose(inverse(Modle))) * vNormal;  
}

