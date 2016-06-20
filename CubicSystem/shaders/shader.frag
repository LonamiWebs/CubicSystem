#version 330 core

in vec3 Normal;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D image;

// This must be NORMALIZED and given
// FROM the fragment TOWARDS the light source!
uniform vec3 sunlightDir;

void main()
{
    // Ambient (default a low value so it's never dark)
    vec3 ambient = vec3(0.1) * vec3(texture(image, TexCoord));

    // Diffuse
    float diff = max(dot(Normal, sunlightDir), 0.0);
    vec3 diffuse = diff * vec3(texture(image, TexCoord));

    color = vec4(ambient + diffuse, 1.0);
}