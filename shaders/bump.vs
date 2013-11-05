#version 330

layout(location=0) in vec3 inPos;
layout(location=1) in vec3 inNormal;
layout(location=2) in vec2 inTexCoord;
//layout(location=3) in vec3 inTangent;
//layout(location=4) in vec3 inBiTangent;

out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vPos;

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
//uniform mat4 NormalMatrix;

void main()
{
	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(inPos,1.0);
	vPos =  vec3(ModelViewMatrix * vec4(inPos,1.0)).xyz;
	vTexCoord = inTexCoord;

	// both correct
	//vNormal = vec4(NormalMatrix * vec4(inNormal,1)).xyz;

	mat4 inverseModelViewMatrix = transpose(inverse(mat4(ModelViewMatrix)));
	vNormal =  vec4(inverseModelViewMatrix * vec4(inNormal, 1.0)).xyz;	
}
