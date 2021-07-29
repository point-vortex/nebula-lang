## Nebula Embedded language

### Code
```glsl
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