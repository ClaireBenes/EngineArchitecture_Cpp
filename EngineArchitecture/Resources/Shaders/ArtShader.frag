#version 330 core

in vec2 fragTexCoord;
out vec4 outColor;

uniform float uTime;
uniform vec3 uDimensions;

float rayStrength(vec2 raySource, vec2 rayRefDirection, vec2 coord, float seedA, float seedB, float speed)
{
    vec2 sourceToCoord = coord - raySource;
    float cosAngle = dot(normalize(sourceToCoord), rayRefDirection);

    return clamp(
        (0.45 + 0.15 * sin(cosAngle * seedA + uTime * speed)) +
        (0.3 + 0.2 * cos(-cosAngle * seedB + uTime * speed)),
        0.0, 1.0) *
        clamp((uDimensions.x - length(sourceToCoord)) / uDimensions.x, 0.5, 1.0);
}

void main()
{
    vec2 fragCoord = fragTexCoord * uDimensions.xy;
    vec2 coord = vec2(fragCoord.x, uDimensions.y - fragCoord.y);

    // Sun rays parameters
    vec2 rayPos1 = vec2(uDimensions.x * 0.7, uDimensions.y * -0.4);
    vec2 rayRefDir1 = normalize(vec2(1.0, -0.116));

    vec2 rayPos2 = vec2(uDimensions.x * 0.8, uDimensions.y * -0.6);
    vec2 rayRefDir2 = normalize(vec2(1.0, 0.241));

    // Calculate ray strength
    float rays =
        rayStrength(rayPos1, rayRefDir1, coord, 36.2214, 21.11349, 0.8) * 0.5 +
        rayStrength(rayPos2, rayRefDir2, coord, 22.3991, 18.0234, 0.4) * 0.4;

    // Attenuate brightness towards the bottom
    float brightness = 1.0 - (coord.y / uDimensions.y);

    vec3 rayColor;
    rayColor.b = rays * (0.9 + brightness * (0.5 - 0.1));
    rayColor.r = rays * (0.5 + brightness * (0.8 - 0.1));
    rayColor.g = rays * (0.7 + brightness * (0.8 - 0.1));

    // Output transparent background + rays
    outColor = vec4(rayColor, rays); // alpha = ray strength for translucency
}
