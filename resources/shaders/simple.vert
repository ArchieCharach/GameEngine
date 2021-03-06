uniform mat4 in_Projection;
uniform mat4 in_Model;
uniform mat4 in_Camera;

attribute vec3 in_Position;
attribute vec4 in_Color;
attribute vec2 in_TexCoord;

varying vec4 ex_Color;
varying vec2 out_TexCoord;

void main()
{
  gl_Position = in_Projection * in_Camera * in_Model * vec4(in_Position, 1.0);
  ex_Color = in_Color;
	out_TexCoord = in_TexCoord;
}

