attribute vec3 a_vertex;
attribute vec3 a_normal;
attribute vec2 a_uv;
attribute vec4 a_color;

//this will store the color for the pixel shader
varying vec3 v_position;
varying vec2 v_uv;
varying vec4 v_color;

varying vec3 Normal;
varying vec3 Vertex;
uniform mat4 modelView,viewprojection;
	
void main(void)  
{     
   Normal = (modelView * vec4( a_normal, 0.0) ).xyz;
   v_position = a_vertex;
   Vertex = (modelView * vec4( v_position, 1.0) ).xyz;
   gl_Position = viewprojection * vec4( Vertex, 1.0 );
   v_color = a_color;
   v_uv = a_uv;
}