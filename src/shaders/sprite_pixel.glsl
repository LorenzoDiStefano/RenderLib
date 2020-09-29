#version 410 core

out vec3 color;
in vec2 out_texture;

in vec4 out_normal;
uniform vec3 light_direction;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

// PHONG (diffuse, specular, ambient)

void main()
{
	//color = vec4(out_color.rgb, 1);
	float lambert = clamp(dot(normalize(-light_direction), normalize(out_normal.xyz)), 0, 1);
	//vec3 base_color = vec3(1, 0, 0);
	//color = vec4((out_texture.rgb * lambert) + vec3(0.0, 0.0, 0.0), 1);
	color = texture(texture_diffuse1, out_texture).rgb;
}