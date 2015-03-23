cbuffer ConstandBuffer
{
	float redLevel;
	float blueLevel;
}

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

// Vertex Shader
VOut main(float4 position : POSITION, float4 color : COLOR)
{
	// create a VOut struct
	VOut output;

	// set the output values
	output.position = position;
	output.position.xy *= 0.5f;
	output.color = color;

	// return the output values
	return output;
}