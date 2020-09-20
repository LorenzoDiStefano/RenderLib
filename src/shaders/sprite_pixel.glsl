#version 410 core

out vec4 color;
//in vec3 out_color;

in vec4 out_normal;
uniform vec3 light_direction;

// PHONG (diffuse, specular, ambient)

void main()
{
	//color = vec4(out_color.rgb, 1);
	float lambert = clamp(dot(normalize(-light_direction), normalize(out_normal.xyz)), 0, 1);
	vec3 base_color = vec3(1, 0, 0);
	color = vec4((base_color.rgb * lambert) + vec3(0.0, 0.0, 0.3), 1);
}