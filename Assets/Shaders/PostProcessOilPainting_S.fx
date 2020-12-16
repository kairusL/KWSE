// Description: Post Processing shader.
// Renfrence : https://danielilett.com/2019-05-18-tut1-6-smo-painting/
// Renfrence : https://programmersought.com/article/63044668179/
 
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
	// samples->calculating mean value -> the number of samples going to take later.
	//float n = (((radius - 1) / 2) +1.0f )*(((radius - 1) / 2) +1.0f);
	float n = (radius+1.0f )*(radius+1.0f);
	// mean values
	float3 m[4];
	m[0] = float3(0.0f, 0.0f, 0.0f);
	m[1] = float3(0.0f, 0.0f, 0.0f);
	m[2] = float3(0.0f, 0.0f, 0.0f);
	m[3] = float3(0.0f, 0.0f, 0.0f);
	float3 squrColor[4];
	squrColor[0] = float3(0.0f, 0.0f, 0.0f);
	squrColor[1] = float3(0.0f, 0.0f, 0.0f);
	squrColor[2] = float3(0.0f, 0.0f, 0.0f);
	squrColor[3] = float3(0.0f, 0.0f, 0.0f);
	float3 color = screenColor.rgb;


	for (int j = (int)-radius; j <= 0; ++j)
	{
		for (int k = (int)-radius; k <= 0; ++k)
		{
			color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
			m[0] += color;
			squrColor[0] += color * color;
		}
	}
	for (int j = (int)-radius; j <= 0; ++j)
	{
		for (int k = 0; k <= (int)radius; ++k)
		{
			color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
			m[1] += color;
			squrColor[1] += color * color;
		}
	}

	for (int j = 0; j <= (int)radius; ++j)
	{
		for (int k	 = 0; k <= (int)radius; ++k)
		{
			color = (float3)textureMap.Sample(textureSampler, uv +float2(k,j)*size).rgb;
			m[2] += color;
			squrColor[2] += color * color;
		}
	}
	for (int j =0; j <= (int)radius; ++j)
	{
		for (int k = (int)-radius; k <= 0; ++k)
		{
			color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
			m[3] += color;
			squrColor[3] += color * color;
		}
	}
	
	
	float4 finalColor = float4(color,0.0f);

	// use sigma to sum up colour values then get the mean values
	float min_sigma2 = minSigma;
	for (int i = 0; i < 4; ++i)
	{
		m[i] /= n;
		//mean of the squares minus- the square of the means
		squrColor[i] = abs(squrColor[i] / n - m[i] * m[i]); 
		float sigma2 = (squrColor[i].r + squrColor[i].g + squrColor[i].b);
		if (sigma2 < min_sigma2)
		{
			min_sigma2 = sigma2;
			finalColor = float4(m[i], 1.0f);
		}
	}
	
	return finalColor;
}

