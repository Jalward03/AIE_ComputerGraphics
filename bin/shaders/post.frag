// A simple flat-color shader 
#version 410

in vec2 vTexCoord;

uniform sampler2D colorTarget;
uniform int postProcessTarget;
uniform int windowWidth;
uniform int windowHeight;


out vec4 FragColor;

vec4 Default(vec2 texCoord)
{
    return texture(colorTarget, texCoord);
}

vec4 BoxBlur(vec2 texCoord)
{
    vec2 texel = 1.0f/ textureSize(colorTarget, 0);

    vec4 color = texture(colorTarget, texCoord);
    color += texture(colorTarget, texCoord + texel * vec2(-1, 1));
    color += texture(colorTarget, texCoord + texel * vec2(-1, 0));
    color += texture(colorTarget, texCoord + texel * vec2(-1, -1));

    color += texture(colorTarget, texCoord + texel * vec2(0, 1));
    color += texture(colorTarget, texCoord + texel * vec2(0, -1));

    color += texture(colorTarget, texCoord + texel * vec2(1, 1));
    color += texture(colorTarget, texCoord + texel * vec2(1, 0));
    color += texture(colorTarget, texCoord + texel * vec2(1, -1));

    return color / 9;

}

vec4 Distort(vec2 texCoord)
{
    vec2 mid = vec2(0.5f);
    float distanceFromTheCenter = distance(texCoord, mid);
    vec2 normalizeCoord = normalize(texCoord - mid);
    float bias = distanceFromTheCenter + sin(distanceFromTheCenter * 15) * 0.05;
    vec2 newCoord = mid + bias * normalizeCoord;

    return texture(colorTarget, newCoord);

}

vec4 EdgeDetection(vec2 texCoord)
{
     float w = 1.0f / windowWidth;
     float h = 1.0f / windowHeight;

     vec4 k[9];

     k[0] = texture(colorTarget, texCoord + vec2(-w, -h)); 
     k[1] = texture(colorTarget, texCoord + vec2( 0, -h)); 
     k[2] = texture(colorTarget, texCoord + vec2( w, -h)); 
     k[3] = texture(colorTarget, texCoord + vec2(-w,  0)); 
     k[4] = texture(colorTarget, texCoord); 
     k[5] = texture(colorTarget, texCoord + vec2( w,  0)); 
     k[6] = texture(colorTarget, texCoord + vec2(-w,  h)); 
     k[7] = texture(colorTarget, texCoord + vec2( 0,  h)); 
     k[8] = texture(colorTarget, texCoord + vec2( w,  h));

     vec4 sobelEdgeH = k[2] + (2.0f * k[5]) + k[8] - (k[0] + (2.0f * k[3]) + k[6]);
     vec4 sobelEdgeV = k[0] + (2.0f * k[1]) + k[2] - (k[6] + (2.0f * k[7]) + k[8]);

     vec4 sobel = sqrt((sobelEdgeH * sobelEdgeH) + (sobelEdgeV * sobelEdgeV));
     return vec4(1.0f - sobel.rgb, 1.0f);
}


vec4 Sepia(vec2 texCoord)
{

   vec4 texColor = texture(colorTarget, texCoord);
   vec4 sepiaColor;

   sepiaColor.r = (texColor.r * 0.393) + (texColor.g * 0.769) + (texColor.b * 0.189);
   sepiaColor.g = (texColor.r * 0.349) + (texColor.g * 0.686) + (texColor.b * 0.168);
   sepiaColor.b = (texColor.r * 0.272) + (texColor.g * 0.534) + (texColor.b * 0.131);


   return vec4(sepiaColor.rgb, 1.0f); 
}


vec4 GreyScale(vec2 texCoord)
{

   vec4 texColor = texture(colorTarget, texCoord);
   vec4 greyScaleColor;

   
   greyScaleColor.r = (texColor.r / 3) + (texColor.g / 3) + (texColor.b  / 3);
   greyScaleColor.g = (texColor.r / 3) + (texColor.g / 3) + (texColor.b / 3);
   greyScaleColor.b = (texColor.r / 3) + (texColor.g / 3) + (texColor.b / 3);


   return vec4(greyScaleColor.rgb, 1.0f); 
}

void main() 
{
    // This will calculate the texel size

    vec2 texSize = textureSize(colorTarget, 0);
    vec2 texelSize = 1.0f / texSize;

    // Then we will adjust the coordinate
    vec2 scale = (texSize - texelSize) / texSize;
    vec2 texCoord = vTexCoord / scale + texelSize * 0.5f;

    switch(postProcessTarget)
    {
        default: // Default
        {
            // Output post processing effect here
             FragColor = Default(texCoord);
             break;
        }
        case 0 : // BoxBlur
        {
             FragColor = BoxBlur(texCoord);
             break;
        }
        case 1 : // Distort
        {
             FragColor = Distort(texCoord);
             break;
        }
        case 2 : // Edge Detection
        {
             FragColor = EdgeDetection(texCoord);
             break;
        }
        case 3 : // Sepia
        {
             FragColor = Sepia(texCoord);
             break;
        }
        case 4 : // Scanlines
        {
             FragColor = Default(texCoord);
             break;
        }
        case 5 : // Grey Scale
        {
             FragColor = GreyScale(texCoord);
             break;
        }
         case 6 : // Invert
        {
             FragColor = Default(texCoord);
             break;
        }
         case 7 : // Pixelizer
        {
             FragColor = Default(texCoord);
             break;
        }
         case 8 : // Posterization
        {
             FragColor = Default(texCoord);
             break;
        }
         case 9 : // Distance Fog
        {
             FragColor = Default(texCoord);
             break;
        }
         case 10 : // Depth Of Field
        {
             FragColor = Default(texCoord);
             break;
        }
    }

    



}