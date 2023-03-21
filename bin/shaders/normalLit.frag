// A phong shader 
#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;

out vec4 FragColor;
// Model Data

uniform vec3 CameraPosition;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

uniform vec3 Ka; // The ambient material color
uniform vec3 Kd; // The different material color
uniform vec3 Ks; // The specular material color
uniform float specularPower; // The specular power of the Ks

// uniform vec4 BaseColor;

// Light data
uniform vec3 AmbientColor;
uniform vec3 LightColor;
uniform vec3 LightDirection;

void main() 
{
    // Set the normal and light direction

    vec3 N = normalize(vNormal);
    vec3 T = normalize(vTangent);
    vec3 B = normalize(vBiTangent);
    vec3 L = normalize(LightDirection);

    mat3 TBN = mat3(T,B,N);

    vec3 texDiffused = texture(diffuseTexture, vTexCoord).rgb;
    vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;
    vec3 texNormal = texture(normalTexture, vTexCoord).rgb;

    N = TBN * (texNormal * 2 - 1);

    // Calculate the negative light direction (Lambert Term)
    float lambertTerm = max(0, min(1, dot(N, -L)));

    // Calculate the view vector...
    vec3 V = normalize(CameraPosition - vPosition.xyz);
    // ... and the reflection vector
    vec3 R = reflect(L, N);

    // Calculate the specular Term
    float specularTerm = pow(max(0, dot(R, V)), specularPower);

    // Calculate the properties of each color type
    vec3 ambient = AmbientColor * Ka * texDiffused;
    vec3 diffuse = LightColor * Kd * texDiffused * lambertTerm;
    vec3 specular = LightColor * Ks * texSpecular * specularTerm;

    FragColor = vec4(ambient + diffuse + specular, 1);
}