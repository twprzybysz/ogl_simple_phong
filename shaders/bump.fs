#version 330
in vec3 vPos;
in vec2 vTexCoord;
in vec3 vNormal;

out vec4 vColor;

uniform sampler2D diffuse;
uniform sampler2D normal; 

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

uniform vec4 light;

void main() {
	vec3 lightPos = normalize(light.xyz - vPos.xyz);
	vec3 normal = normalize(vNormal);
	float nl = dot(lightPos,normal); 

	vec4 diffuseTex = texture2D( diffuse, vTexCoord );
	vec3 diffuseColor = clamp(nl, 0.0f, 1.0f) * diffuseTex.xyz; 
    vec3 specularColor = vec3(0.0);
	
	if (nl > 0.0f) {
		float spec = pow(clamp(dot(reflect(-lightPos,normal), -normalize(vPos.xyz)), 0, 1), 64.0f);
		specularColor = vec3(1.0)*max(spec, 0.0);
	}
	vColor = vec4(diffuseColor+specularColor, 1.0);
}