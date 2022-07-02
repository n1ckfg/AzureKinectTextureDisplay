#version 150

// this is how we receive the texture
uniform sampler2DRect uColorTex;
uniform sampler2DRect uDepthTex;
uniform ivec2 uFrameSize;

in vec2 texCoordVarying;

out vec4 outputColor;

float map(float value, float min1, float max1, float min2, float max2) {
	return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}
 
void main() {
	if (texCoordVarying.x < uFrameSize.x / 2) {
		vec4 col = texture(uColorTex, vec2(map(texCoordVarying.x, 0, uFrameSize.x/2, 0, uFrameSize.x), texCoordVarying.y));
		outputColor = col;
	} else {
		vec4 col = texture(uDepthTex, vec2(map(texCoordVarying.x, uFrameSize.x/2, uFrameSize.x, 0, uFrameSize.x), texCoordVarying.y));
		float r = 1.0 - map(col.r, 0, 0.1, 0, 1);
		r *= mix(1.0, 0, step(0.999, r));
		r = pow(r, 3);
	    outputColor = vec4(r, r, r, 1.0);
	}
}