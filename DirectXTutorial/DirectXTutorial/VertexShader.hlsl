cbuffer ConstantBuffer
{
	float3 vOffset;
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
	output.position.x += vOffset.x;
	output.position.y += vOffset.y;
	output.position.z += vOffset.z;

	// inverted color scheme
	output.color = 1.0f - color;

	// return the output values
	return output;
}