#version 330

in vec2 fragTexCoord;
out vec4 outColor;

uniform vec3 uDimensions; 
uniform float uTime;
uniform float uSpeed;
uniform float uBrightness;
uniform float uExposure;
uniform float uBallSize;
uniform float uZDistance;

uniform int uPalette;

#define R(a) mat2(cos(a + vec4(0,33,11,0)))
#define smin(a,b) a + (b-a) / (1.0 - exp2((b-a)/0.05));

vec3 palette( float t ) 
{
     vec3 a, b, c, d;

    if(uPalette == 0) // White and soft Purple
    {       
        a = vec3(0.6, 0.55, 0.65);
        b = vec3(0.3, 0.25, 0.3);
        c = vec3(1.0);
        d = vec3(0.2, 0.3, 0.5);
    } 
    else if(uPalette == 1) // Sand
    {  
        a = vec3(0.65, 0.55, 0.4);   
        b = vec3(0.2, 0.2, 0.15);  
        c = vec3(1.0);
        d = vec3(0.0, 0.05, 0.1);
    }
    else if(uPalette == 2) // White and Grey
    {  
        a = vec3(0.85, 0.85, 0.85); 
        b = vec3(0.15, 0.15, 0.15); 
        c = vec3(1.0);
        d = vec3(0.02, 0.05, 0.08);
    }

    return a + b * cos(6.28318 * (c * t + d));
}

void main()
{
    vec3 O, r, b = uDimensions;
    
    float B, o, u, n, c, e, s = uTime * uSpeed;
    
    vec2 fragCoord = fragTexCoord * b.xy;

    for(outColor *= e; e++ < 100.0;)
    {
        O = n * normalize(vec3(((fragCoord + fragCoord - b.xy) / b.y) * R(s / 4.0), 1.0));
        O.xz *= R(n * uZDistance);
        O.z += s - 1.0;
        
        for(o = -3.0, c = 9.0; ++o < 4.0;) //10.0
        {
            r = O;
            r.z = fract(r.z) - 0.3 - o;
            B = floor(O.z) + o;
            
            r.xy *= R(B * 0.75);
            r.x += smoothstep(-1.0, 1.0, sin((B - s) * 0.4)) * 4.0 - 2.5;
            c = min(c, u = length(r) - uBallSize);
            
            
            float t = O.z * 0.1 + s * 0.1; 
            vec3 col = palette(t);

            //outColor += uBrightness * (2.0 + cos(O.z/4.0 + s + vec4(0,1,2,0))) / abs(u);

            outColor.rgb += col * uBrightness / abs(u);
        }
        
        n += smin(c, 1.2 + sin(O.x) * cos(O.y) * cos (O.y + O.z) - length(O.xy));
    }

    vec3 color = vec3(1.0) - exp(-outColor.rgb * uExposure);
    color = pow(color, vec3(1.0/2.2));

    outColor = vec4(color, 1.0);
}
