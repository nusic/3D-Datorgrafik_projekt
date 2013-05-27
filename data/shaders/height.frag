#version 120

void main(){
	gl_FragColor = vec4(1,1,1,1) - vec4(gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z, 0);
}