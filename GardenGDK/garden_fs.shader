#version 430 core

struct LightProperties{
    int isEnabled;
	int isPoint;
	int isSpot;
	int isDirectional;
    int isHemisphere;
	vec3 ambient;
	vec3 color;
	vec3 position;
	vec3 coneCenter;
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

uniform float shininess;
uniform float strength;
uniform vec3 material;
//uniform vec3 eyePos;
vec3 eyePos=vec3(0.0,0.0,0.0);//when use view_matrix, eyePos always be zero :)

out vec4 fragColor;

void main(){
    fragColor = vec4(0.0, 0.0, 0.0, 1.0);
    for(int i = 0; i < MaxLights; i++){
        if(lightsArray[i].isEnabled == 0)
            continue;
        vec3 rgb;
        if(lightsArray[i].isDirectional == 1){
            vec3 lightf = vec3(fs_view_matrix * vec4(lightsArray[i].lightFrom, 1.0f));
            vec3 lightt = vec3(fs_view_matrix * vec4(lightsArray[i].lightTo, 1.0f));
            vec3 lightDirect = lightf - lightt;
            float diffuse = max(0.0, dot(normal, normalize(lightDirect)));
            float specular = max(0.0, dot(normalize(1.414 * normal - normalize(lightDirect)), normalize(eyePos - position)));
            if(diffuse == 0.0)
                specular = 0.0;
            else
                specular = pow(specular, shininess);
            vec3 scatteredLight = lightsArray[i].ambient + lightsArray[i].color * diffuse;
            vec3 reflectedLight = lightsArray[i].color * specular * strength;
            rgb = min(material.rgb * scatteredLight + reflectedLight, vec3(1.0));

        }
        else if(lightsArray[i].isPoint == 1){
            vec3 lightPos = vec3(fs_view_matrix * vec4(lightsArray[i].position, 1.0));
            vec3 lightDirect = lightPos - position;
            float lightDistance = length(lightDirect);
            lightDirect /= lightDistance;

            float attenuation = 1.0 / (lightsArray[i].constantAttenuation + 
                                       lightsArray[i].linearAttenuation * lightDistance + 
                                       lightsArray[i].quadraticAttenuation * lightDistance * lightDistance);
            vec3 reflect = normalize(1.414 * normal - lightDirect);
            float diffuse = max(0.0, dot(normal, lightDirect));
            float specular = max(0.0, dot(reflect, normalize(eyePos - position)));
            if(diffuse == 0.0)
                specular = 0.0;
            else
                specular = pow(specular, shininess);
            vec3 scatteredLight = lightsArray[i].ambient + lightsArray[i].color * diffuse * attenuation;
            vec3 reflectedLight = lightsArray[i].color * specular * attenuation;
            rgb = min(material.rgb * scatteredLight + reflectedLight, vec3(1.0));
        }
        else if(lightsArray[i].isSpot == 1){
            vec3 lightPos = vec3(fs_view_matrix * vec4(lightsArray[i].position, 1.0));
            vec3 coneCenter = vec3(fs_view_matrix * vec4(lightsArray[i].coneCenter, 1.0));
            vec3 coneDirection = normalize(lightPos - coneCenter);
            vec3 lightDirect = lightPos - position;   
            float lightDistance = length(lightDirect);        
            lightDirect /= lightDistance;

            float attenuation = 1.0 / (lightsArray[i].constantAttenuation + 
                                       lightsArray[i].linearAttenuation * lightDistance + 
                                       lightsArray[i].quadraticAttenuation * lightDistance * lightDistance);
            float spotCos = dot(lightDirect, coneDirection);
            if(spotCos < lightsArray[i].spotCosCutoff)
                attenuation = 0.0;
            else
                attenuation *= pow(spotCos, lightsArray[i].spotExponent);  
            vec3 reflect = normalize(1.414 * normal - lightDirect);
            float diffuse = max(0.0, dot(normal, lightDirect));
            float specular = max(0.0, dot(reflect, normalize(eyePos - position)));
            if(diffuse == 0.0)
                specular = 0.0;
            else
                specular = pow(specular, shininess) * strength;
            vec3 scatteredLight = lightsArray[i].ambient + lightsArray[i].color * diffuse * attenuation;
            vec3 reflectedLight = lightsArray[i].color * specular * attenuation;
            rgb = min(material.rgb * scatteredLight + reflectedLight, vec3(1.0));
        }
        else if(lightsArray[i].isHemisphere == 1){
            vec3 lightf = vec3(fs_view_matrix * vec4(lightsArray[i].lightFrom, 1.0f));
            vec3 lightt = vec3(fs_view_matrix * vec4(lightsArray[i].lightTo, 1.0f));
            vec3 lightDirect = normalize(lightf - lightt);
            float cos = dot(lightDirect, normal);
            float a = 0.5 + 0.5 * cos;
            rgb = min(vec3(1.0), material.rgb * (a * lightsArray[i].color + (1 - a) * lightsArray[i].ambient));
        }

        fragColor = min(vec4(1.0), fragColor + vec4(rgb, 1.0));
    }
}