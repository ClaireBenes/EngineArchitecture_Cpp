#version 330

in vec2 fragTexCoord;
out vec4 outColor;

uniform float uTime;
uniform vec3 uDimensions;
uniform float uSpeed;
uniform float uBrightness;
uniform float uSunriseMix;
uniform float uCloudScale;

uniform int uClouds;

void main()
{
    // --- Setup & coordinate normalization ---
    float i, d, s, t = uTime * uSpeed;
    vec3 dimension = uDimensions;
    vec2 fragCoord = fragTexCoord * dimension.xy;
    float sunrise = uSunriseMix;
    fragCoord = (fragCoord - dimension.xy / 2.0) / dimension.y;

    // --- Cloud accumulation loop ---
    for (outColor *= i; i++ < uClouds;
         d += s = 0.05 + 0.2 * abs(8.0 + dimension.y),
         outColor += 1.0 / s + 1.0 / length(fragCoord + fragCoord - 0.8))
    {
        // --- Turbulence / distortion loop ---
        for (dimension = vec3(fragCoord * d, d + t),
             s = 0.01; s < 2.0; s += s)
        {
            dimension.yz -= abs(dot(
                sin(0.2 * t + uCloudScale * dimension / s),
                dimension - dimension + s
            ));
        }
    }

    // --- Tone mapping ---
    vec3 clouds = tanh(outColor.rgb / uBrightness);

    // --- Sky gradient (bottom warm -> top cool) ---
    float grad = clamp(fragTexCoord.y, 0.0, 1.0);
    vec3 skyColor = mix(
        vec3(0.95, 0.6, 0.3),   // orange near horizon
        vec3(0.3, 0.6, 1.1),    // blue higher up
        grad
    );

    // --- Day / Night cycle ---
    //sunrise = sin(uTime * 0.8) * 0.8 + 0.5;

    // --- Warm cloud tint ---
    vec3 warmTint = mix(vec3(1.0), vec3(0.8, 0.8, 0.8), sunrise);
    clouds *= warmTint;

    // --- Combine clouds with sky ---
    vec3 finalColor = mix(skyColor, clouds, 0.6 + 0.4 * sunrise);

    outColor = vec4(finalColor, 1.0);

    //outColor = tanh(outColor / uBrightness);
}