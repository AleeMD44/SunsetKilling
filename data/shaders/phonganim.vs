attribute vec3 a_vertex;
attribute vec3 a_normal;
attribute vec2 a_uv;
attribute vec4 a_color;
attribute vec4 a_bones;
attribute vec4 a_weights;

uniform mat4 u_bones[128];
//this will store the color for the pixel shader
varying vec3 v_position;
varying vec2 v_uv;
varying vec4 v_color;

varying vec3 Normal;
varying vec3 Vertex;
uniform mat4 modelView,viewprojection;
	
void main(void)  
{     
	vec4 v = vec4(a_vertex,1.0);
	v_position =	(u_bones[int (a_bones.x)] * a_weights.x * v + 
			u_bones[int (a_bones.y)] * a_weights.y * v + 
			u_bones[int (a_bones.z)] * a_weights.z * v + 
			u_bones[int(a_bones.w)] * a_weights.w * v).xyz;

	vec4 N = vec4(a_normal,0.0);
	vec3 v_normal =	(u_bones[int (a_bones.x)] * a_weights.x * N + 
			u_bones[int (a_bones.y)] * a_weights.y * N + 
			u_bones[int (a_bones.z)] * a_weights.z * N + 
			u_bones[int(a_bones.w)] * a_weights.w * N).xyz;
	v_normal = normalize(v_normal);

	//calcule the normal in world space
	Normal = (modelView * vec4( v_normal, 0.0) ).xyz;

   Vertex = (modelView * vec4( v_position, 1.0) ).xyz;
   gl_Position = viewprojection * vec4( Vertex, 1.0 );
   v_color = a_color;
   v_uv = a_uv;
}