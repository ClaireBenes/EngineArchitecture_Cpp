#version 330

in vec2 fragTexCoord;
out vec4 outColor;

uniform vec2 uDimensions; 
uniform float uTime;
uniform float uSpeed;
uniform float uPatternRepetition;
uniform float uShapeSize;
uniform float uShapeRepetition;
uniform float uBrightness;

void main()
{
	vec2 uv = fragTexCoord * 2.0 - 1.0; 
	uv.x *= uDimensions.x / uDimensions.y; //Make sure value always range from 0 to 1 regardless of the windows size
	//"* 2.0 - 1.0" Equivalent to "uv = (uv - 0.5) * 2.0;"
	//with -0.5 that center the shader now at (0,0) instead of (0.5,0.5)
	//with * 2.0 that keep the coordinates as (-1,1) instead of (-0.5,0.5)

	vec4 finalColor = vec4(0.0);
	float d = uTime * uSpeed;
	float o, s, n;

	for (finalColor *= n; n++ < 1e2;) 
	{
		vec3 q = o * normalize(vec3(uv, uShapeSize)); 
		q.z += d + d;
		q.xy *= mat2(cos(d / uShapeRepetition + vec4(0,33,11,0)));

		s = length(q = abs(mod(q + 1.0, 2.0) - 1.0));

		q = q * uShapeRepetition + d + d;

		s = abs(s - 1.1 + sin(d) * 0.1 - sin(q.x) * cos(q.y) * sin(q.z) * 0.2) + 0.025;

		o += s * 0.5;

		finalColor += uBrightness * (1.0 + cos(o * uPatternRepetition + length(uv) * 4.0 - d + vec4(0,1,2,0))) 
					  / s * pow((sin(o * uPatternRepetition + length(uv) * 4.0 + d * 2.0) * 0.5 + 0.5), 1.5); 
	}

	outColor = vec4(finalColor);
}
