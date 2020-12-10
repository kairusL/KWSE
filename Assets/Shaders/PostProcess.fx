// Description: Post Processing shader.
// Renfrence : https://www.geeks3d.com/20101029/shader-library-pixelation-post-processing-effect-glsl/
// Renfrence : https://www.geeks3d.com/20101123/shader-library-predators-thermal-vision-post-processing-filter-glsl/
 
Texture2D textureMap : register(t0);
SamplerState textureSampler : register(s0);

struct VS_INPUT
{
	float3 position : POSITION;
	float2 texCoord : TEXCOORD;
	
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position = float4(input.position, 1.0f);
	output.texCoord = input.texCoord;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 screenColor = textureMap.Sample(textureSampler, input.texCoord);

	float2 uv = input.texCoord.xy;

	float3 tc = float3(1.0, 0.9, 0.5);
	float vx_offset =0.5;
	float pixel_w = 15.0;
	float pixel_h = 10.0f;
	float rt_w = 1080.0;
	float rt_h = 720.0;

	if (uv.x < (vx_offset - 0.005))
	{
		float dx = pixel_w * (1. / rt_w);
		float dy = pixel_h * (1. / rt_h);
		float2 coord = float2(dx*floor(uv.x / dx),
			dy*floor(uv.y / dy));
		tc = (float3)textureMap.Sample(textureSampler, coord).rgb;
	}
	else if (uv.x >= (vx_offset + 0.005))
	{
		float3 pixcol = screenColor;
		float3 colors[3];
		colors[0] = float3(0, 0, 1);
		colors[1] = float3(1, 1, 0);
		colors[2] = float3(1, 0, 0);
		float lum = dot(float3(0.30f, 0.59f, 0.11f), pixcol.rgb);
		int ix = (lum < 0.5) ? 0 : 1;
		tc = lerp(colors[ix], colors[ix + 1], (lum - float(ix)*0.5f) / 0.5f);
	}

		//tc = (float3)screenColor.rgb;
	return float4(tc,1);//float4(screenColor.b, screenColor.g, screenColor.r, 1)*;
}

