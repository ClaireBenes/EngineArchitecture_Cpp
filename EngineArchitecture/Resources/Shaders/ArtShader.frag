#version 330

in vec2 fragTexCoord;
out vec4 outColor;

uniform vec2 uDimensions; 
uniform float uTime;
uniform float uSpeed;
uniform float uPatternRepetition;
uniform float uPatternMultiplier;
uniform float uShapeRepetition;
uniform float uBrightness;
uniform float uContrast;

vec3 palette( float t ) 
{
    vec3 a = vec3(0.5, 0.5, 0.5); //0.5
    vec3 b = vec3(0.5, 0.5, 0.5); //0.5
    vec3 c = vec3(1.0, 1.0, 1.0); //1.0
    vec3 d = vec3(0.263,0.416,0.557); //0.263,0.416,0.557

    return a + b*cos( 6.28318*(c*t+d) );
}


void main()
{
	vec2 uv = fragTexCoord * 2.0 - 1.0; 
	uv.x *= uDimensions.x / uDimensions.y; //Make sure value always range from 0 to 1 regardless of the windows size
	//"* 2.0 - 1.0" Equivalent to "uv = (uv - 0.5) * 2.0;"
	//with -0.5 that center the shader now at (0,0) instead of (0.5,0.5)
	//with * 2.0 that keep the coordinates as (-1,1) instead of (-0.5,0.5)

	vec2 uv0 = uv;
	vec3 finalColor = vec3(0.0);

	for(float i = 0.0; i < uPatternRepetition; i++)
	{
		uv = fract(uv * uPatternMultiplier) - 0.5; 
		//Center the fractal function withing our desired (-1,1) with (0,0) as our center if we used * 2. Here a decimal is used to break pattern

		float d = length(uv) * exp(-length(uv0));

		vec3 col = palette(length(uv0) + i * uSpeed + uTime * uSpeed); 
		//Multiplying lenght(uv0) to break the motif (when we were using d) with Time, allows the gradient to shift and evolve over time without being repetitive

		d = sin(d * uShapeRepetition + uTime * uSpeed) / uShapeRepetition; //Sin interpolate between 0 &nd 1, creating multiple circle (adding times move the values, creating a moving illusion)
		//d -= 0.5; //Equivalent to sin function (circle of diameter 0.5). Everything bigger than the diameter is positive, smaller = negative
		d = abs(d); //Absolute of d, turning all fully negative number to positive, creating a white to black to white gradient
		//d = step(0.1,d); All Pixel with a value negative to 0.1, will be assign the color black, else white
		//d = smoothstep(0.0, 0.1,d); // All value below 0.0 will be black and all value on top of 0.1 will be white, creating a smoothless gradient
		d = pow(uBrightness / d, uContrast); //"0.01 / d" Inverse of d but town down to get out of the 0,1 threshold. Pow is used to enhance contrast

		//col *= d; //Applying color with the effect we just made
		finalColor += col * d;
	}

	outColor = vec4(finalColor, 1.0);
}
