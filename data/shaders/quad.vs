attribute vec3 a_vertex;
varying vec2 v_uv;
	
void main(void)  
{     
   v_uv = (a_vertex * 0.5 + vec3(0.5)).xy;
   gl_Position = vec4(a_vertex.xy,0.0, 1.0 );
}