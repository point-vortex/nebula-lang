## Nebula Embedded language

## Command line interface
Fllowing command will compile ```program.neb``` source code file and write pitput to ```program.nebc``` file.
```bash
nebula program.neb -o program
```

### Flags:
|Short|Long|Scheme|Description|
|-|-|-|-|
|```-o```|```--output```|```--output <file>```|Output file name|
||```--stdout```|```--stdout```|Output will be passed to ___stdout___ stream encoded to base64|
|```-s```|```--source```|```--source <source code>```|Source code from input string|
|```-sb64```|```--source-base64```|```--source-base64```|If set - input will be interpreted as base64 string| 
|```-in```|```--in```|```--in <statement>```|Declares global input variable|
|```-out```|```--out```|```--out <statement>```|Declares global output variable|

## Native types
|Specifier|Description|
|-|-|
|int|Integer value type|
|long|Long integer value type|
|float|Floating point value type|
|vec2|2 floats vector|
|vec3|3 floats vector|
|vec4|4 floats vector|
|mat2|2x2 float matrix|
|mat3|3x3 float matrix|
|mat4|4x4 float matrix|
|string|ascii string type|



## Example code
```glsl
struct Flow1 {
    dict foo;
    spreadsheet bar;
};
inflow1 Flow1 in1;

in vec3 normal;
in float grayscale = 0.2f;// Default value is 0.2f
in int brightness;
out vec3 vertexColor;
out vec3 color;

vec3 getColor(float grayscale) {
    return vec3(grayscale, grayscale, grayscale);
}

float calculateBrightness(int inBrighness, float factor);

void main() {
    color = getColor(grayscale * 2) * vertexColor;
    if (color.x < 0) color.x = 0;
    if (color.y < 0) color.y = 0;
    if (color.z < 0) color.z = 0;
    vec3 vColorBright = vec3(
        calculateBrightness(brightness, 0.1f),
        calculateBrightness(brightness, 0.3f),
        calculateBrightness(brightness, 0.6f)
    );
    vertexColor = cross(normal, vColorBright);
}

float calculateBrightness(int inBrighness, float factor) {
    return float(inBrighness) + factor;
}

```
