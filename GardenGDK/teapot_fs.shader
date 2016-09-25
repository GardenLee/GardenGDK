#version 430 core

struct LightProperties{
    bool isEnabled;
	bool isPoint;
	bool isSpot;
	bool isDirectional;
	vec3 ambient;
	vec3 color;
	vec3 position;
	vec3 coneDirection;
	vec3 lightFrom;
	vec3 lightTo;
	float spotCosCutoff;
	float spotExponent;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

const int MaxLights = 12;
uniform LightProperties lightsArray[MaxLights];

in vec3 normal;
in vec3 position;
in mat4 fs_view_matrix;
//vec3 color = vec3(0.9,0.9,0.9);

uniform vec3 material;
uniform vec3 ambient;
uniform vec3 lightColor;

uniform vec3 eyePos;
uniform float shininess;
uniform float strength;

uniform vec3 lightFrom;
uniform vec3 lightTo;

out vec4 fragColor;

void main(){
    vec3 lightf = vec3(fs_view_matrix * vec4(lightFrom, 1.0f));
    vec3 lightt = vec3(fs_view_matrix * vec4(lightTo, 1.0f));
    vec3 lightDirect = lightf - lightt;

    //vec3 halfVector = normalize(eyePos - position - lightDirect);
    float diffuse = max(0.0, dot(normal, normalize(lightDirect)));
    //float specular = max(0.0, dot(normal, halfVector));
    float specular = max(0.0, dot(normalize(1.414 * normal - normalize(lightDirect)), normalize(eyePos - position)));

    if(diffuse == 0.0)
        specular = 0.0;
    else
        specular = pow(specular, shininess);
    
    vec3 scatteredLight = ambient + lightColor * diffuse;
    vec3 reflectedLight = lightColor * specular * strength;

    vec3 rgb = min(material.rgb * scatteredLight + reflectedLight, vec3(1.0));
    fragColor = vec4(rgb, 1.0);
}