// Description: Post Processing shader.
// Renfrence : https://danielilett.com/2019-05-18-tut1-6-smo-painting/
 
Texture2D textureMap : register(t0);
SamplerState textureSampler : register(s0);

cbuffer OilSetting: register(b0)
{
	float screenSizeScale;
	float paintRadius;
	float minSigma;
	float sizeWeight;

}

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
	//float2 size = 2.0f / textureSampler;
	float4 screenColor = textureMap.Sample(textureSampler, input.texCoord);
	float rt_w = 1080.0;
	float rt_h = 720.0;
	float2 size = sizeWeight !=0.0f ? (screenSizeScale / float2(rt_h, rt_w)) : (screenSizeScale / float2(rt_w, rt_h));
	float radius = paintRadius;

	float2 uv = input.texCoord.xy;
	float n = (radius+1.0f )*(radius+1.0f);
	float3 m0 = float3(0.0f, 0.0f, 0.0f);
	float3 m1 = float3(0.0f, 0.0f, 0.0f);
	float3 m2 = float3(0.0f, 0.0f, 0.0f);
	float3 m3 = float3(0.0f, 0.0f, 0.0f);
	float3 squrColor0 = float3(0.0f, 0.0f, 0.0f);
	float3 squrColor1 = float3(0.0f, 0.0f, 0.0f);
	float3 squrColor2 = float3(0.0f, 0.0f, 0.0f);
	float3 squrColor3 = float3(0.0f, 0.0f, 0.0f);
	float3 color = screenColor.rgb;


	for (int j = (int)-radius; j <= 0; ++j)
	{
		for (int k = (int)-radius; k <= 0; ++k)
		{
			color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
			m0 += color;
			squrColor0.r += color.r * color.r  ;
			squrColor0.g += (color.g * color.g);
			squrColor0.b += (color.b * color.b);
		}
	}
	for (int j = (int)-radius; j <= 0; ++j)
	{
		for (int k = 0; k <= (int)radius; ++k)
		{
			color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
			m1 += color;
			squrColor1.r += color.r * color.r;
			squrColor1.g += (color.g * color.g);
			squrColor1.b += (color.b * color.b);
		}
	}

	for (int j = 0; j <= (int)radius; ++j)
	{
		for (int k	 = 0; k <= (int)radius; ++k)
		{
			color = (float3)textureMap.Sample(textureSampler, uv +float2(k,j)*size).rgb;
			m2 += color;
			squrColor2.r += color.r * color.r;
			squrColor2.g += (color.g * color.g) ;
			squrColor2.b += (color.b * color.b) ;
		}
	}
	for (int j =0; j <= (int)radius; ++j)
	{
		for (int k = (int)-radius; k <= 0; ++k)
		{
			color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
			m3 += color;
			squrColor3.r += color.r * color.r;
			squrColor3.g += (color.g * color.g);
			squrColor3.b += (color.b * color.b);
		}
	}
	
	
	float4 finalColor = float4(color,0.0f);
	float min_sigma2 = minSigma;
	m0 /= n;
	squrColor0 = abs(squrColor0 / n - m0 * m0); // getting middle color
	float sigma2 = (squrColor0.r + squrColor0.g + squrColor0.b);
	if (sigma2 < min_sigma2)
	{
		min_sigma2 = sigma2;
		finalColor = float4(m0, 1.0f);
	}
	m1 /= n;
	squrColor1 =  abs(squrColor1 / n - m1 * m1);
	sigma2 = (squrColor1.r + squrColor1.g + squrColor1.b);
	if (sigma2 < min_sigma2)
	{
		min_sigma2 = sigma2;
		finalColor = float4(m1, 1.0f);
	}
	m2 /= n;
	squrColor2 = abs(squrColor2 / n - m2 * m2);
	sigma2 = (squrColor2.r + squrColor2.g + squrColor2.b);
	if (sigma2 < min_sigma2)
	{
		min_sigma2 = sigma2;
		finalColor = float4(m2, 1.0f);
	}
	m3 /= n;
	squrColor3 = abs(squrColor3 / n - m3 * m3);
	sigma2 = (squrColor3.r + squrColor3.g + squrColor3.b);
	if (sigma2 < min_sigma2)
	{
		min_sigma2 = sigma2;
		finalColor = float4(m3, 1.0f);
	}
	
	return finalColor;
}

