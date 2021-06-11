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
cbuffer ActiveSetting: register(b1)
{
	float oilActive;
	float heatActive;
	float mosaicActive;
	float fluorescentActive;

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

	float3 tc = float3(1.0, 0.9, 0.5);
	float vx_offset = 0.5;
	float pixel_w = 15.0;
	float pixel_h = 10.0f;
	// oil
	//float2 size = 2.0f / textureSampler;
	// samples->calculating mean value -> the number of samples going to take later.
	//float n = (((radius - 1) / 2) +1.0f )*(((radius - 1) / 2) +1.0f);
	float4 screenColor = textureMap.Sample(textureSampler, input.texCoord);
	float rt_w = 1280.0;
	float rt_h = 720.0;


	/// 1. separate out the overlapping windows 
	float2 size = sizeWeight != 0.0f ? (screenSizeScale / float2(rt_h, rt_w)) : (screenSizeScale / float2(rt_w, rt_h));
	float radius = paintRadius;
	float2 uv = input.texCoord.xy;
	//2. create mean values //collect the average pixel color.
	float3 m[4];
	m[0] = float3(0.0f, 0.0f, 0.0f);
	m[1] = float3(0.0f, 0.0f, 0.0f);
	m[2] = float3(0.0f, 0.0f, 0.0f);
	m[3] = float3(0.0f, 0.0f, 0.0f);
	///3. samples // calculate the samples/ brush taken during each loop.
	float n = (radius + 1.0f)*(radius + 1.0f);
	
	
	float3 squrColor[4];
	squrColor[0] = float3(0.0f, 0.0f, 0.0f);
	squrColor[1] = float3(0.0f, 0.0f, 0.0f);
	squrColor[2] = float3(0.0f, 0.0f, 0.0f);
	squrColor[3] = float3(0.0f, 0.0f, 0.0f);
	float3 color = screenColor.rgb;

	// performing separate loops in each region to calculate their mean 
	// sum up the colour values of all pixels
	// get the edge or bounds of each region.
	if (oilActive != 0.0f)
	{
		int j = 0;
		int k = 0;
		for (j = (int)-radius; j <= 0; ++j)
		{
			for (k = (int)-radius; k <= 0; ++k)
			{
				color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
				m[0] += color;
				squrColor[0] += color * color;
			}
		}
		for (j = (int)-radius; j <= 0; ++j)
		{
			for (k = 0; k <= (int)radius; ++k)
			{
				color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
				m[1] += color;
				squrColor[1] += color * color;
			}
		}

		for (j = 0; j <= (int)radius; ++j)
		{
			for (k = 0; k <= (int)radius; ++k)
			{
				color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
				m[2] += color;
				squrColor[2] += color * color;
			}
		}
		for (j = 0; j <= (int)radius; ++j)
		{
			for (k = (int)-radius; k <= 0; ++k)
			{
				color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
				m[3] += color;
				squrColor[3] += color * color;
			}
		}

		//First oilPainting Ver

		//////float4 finalColor = float4(color, 0.0f);

		//////// use sigma to sum up colour values then get the mean values
		//////float min_sigma2 = minSigma;
		//////for (int i = 0; i < 4; ++i)
		//////{
		//////	m[i] /= n;
		//////	//mean of the squares minus- the square of the means
		//////	squrColor[i] = abs(squrColor[i] / n - m[i] * m[i]);
		//////	float sigma2 = (squrColor[i].r + squrColor[i].g + squrColor[i].b);
		//////	if (sigma2 < min_sigma2)
		//////	{
		//////		min_sigma2 = sigma2;
		//////		finalColor = float4(m[i], 1.0f);
		//////	}
		//////}

		//////return finalColor;



		//Secound oilPainting Ver

		float4 finalColor = float4(color, 0.0f);
		float4 col_mean = float4(m[0],0.0f);
		float min_sigma2 = minSigma;

		float variance[4];
		variance[0] = 0.0f;
		variance[1] = 0.0f;
		variance[2] = 0.0f;
		variance[3] = 0.0f;
		float testVal=0.0f;

		// performing separate loops in each region to calculate their mean and variance
		// sum up the colour values of all pixels and divide by the number of samples
		// square the colour sum then / the sample i get , to make sure i get the correct part of the image.
		// even though i have 16 windows, but i just separate 4 regions in size the area t b l r.
		// and use this 4 regions to check if it getting the lower variance , 
		// if yes then set the minimun variance value and choose this value as colour 
		// if not then i will sum up the squarecolour and the edge colour then 
		// lerp this sum up colour with the mean colour in this region. 
		// to replace this pixel colour with my  clostest edge variance colour.

		for (int i = 0; i < 4; ++i)
		{
			m[i] /= n;	
			squrColor[i] = abs(squrColor[i] / n - m[i] * m[i]);
		// then get the diff between the mean value and my current part.
			float sigma2 = (squrColor[i].r + squrColor[i].g + squrColor[i].b);


			if (sigma2 < min_sigma2)
			{
				min_sigma2 = sigma2;
				finalColor = float4(m[i], 1.0f);
				variance[i] = length(finalColor.rgb);
			}
		}
		float min_var = variance[0];
		// use sigma to sum up colour values then get the mean values

		for (int c = 0; c < 4; ++c)
		{
			if (c<3)
			{
				testVal = step(variance[c], min_var);
				col_mean.rgb = lerp((col_mean.rgb), (squrColor[c].rgb+finalColor.rgb), testVal);
				min_var = lerp(min_var, variance[c], testVal);
			}
			else
			{
				testVal = step(variance[c], min_var);
				col_mean.rgb = lerp((col_mean.rgb), (squrColor[c].rgb+finalColor.rgb), testVal);
			}
		}
		// turn black & white
		//float avgC = (col_mean.r + col_mean.g + col_mean.b) /3.0f;
		//float r_d = avgC - col_mean.r;
		//float g_d = avgC - col_mean.g;
		//float b_d = avgC - col_mean.b;
		//col_mean.r += r_d;
		//col_mean.g += g_d;
		//col_mean.b += b_d;

		return col_mean;

	}
	if (fluorescentActive)
	{
		int j = 0;
		int k = 0;
		for (j = (int)-radius; j <= 0; ++j)
		{
			for (k = (int)-radius; k <= 0; ++k)
			{
				color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
				m[0] += color;
				squrColor[0] += color * color;
			}
		}
		for (j = (int)-radius; j <= 0; ++j)
		{
			for (k = 0; k <= (int)radius; ++k)
			{
				color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
				m[1] += color;
				squrColor[1] += color * color;
			}
		}

		for (j = 0; j <= (int)radius; ++j)
		{
			for (k = 0; k <= (int)radius; ++k)
			{
				color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
				m[2] += color;
				squrColor[2] += color * color;
			}
		}
		for (j = 0; j <= (int)radius; ++j)
		{
			for (k = (int)-radius; k <= 0; ++k)
			{
				color = (float3)textureMap.Sample(textureSampler, uv + float2(k, j)*size).rgb;
				m[3] += color;
				squrColor[3] += color * color;
			}
		}
			//Fluorescent effect
			float4 finalColor = float4(color, 0.0f);
			float4 col_mean = float4(m[0], 0.0f);
			float min_sigma2 = minSigma;

			float variance[4];
			variance[0] = 0.0f;
			variance[1] = 0.0f;
			variance[2] = 0.0f;
			variance[3] = 0.0f;
			float testVal = 0.0f;


			for (int i = 0; i < 4; ++i)
			{
				m[i] /= n;
				squrColor[i] = abs(squrColor[i] / n - m[i] * m[i]);
				float sigma2 = (squrColor[i].r + squrColor[i].g + squrColor[i].b);


				if (sigma2 < min_sigma2)
				{
					min_sigma2 = sigma2;
					finalColor = float4(m[i], 1.0f);
					variance[i] = length(finalColor.rgb);
				}
			}
			float min_var = variance[0];
			// use sigma to sum up colour values then get the mean values

			for (int c = 0; c < 4; ++c)
			{
				if (c < 3)
				{
					testVal = step(variance[c], min_var);
					col_mean.rgb =
						lerp(
						(col_mean.rgb),
							(squrColor[c].rgb),
							testVal);
					min_var = lerp(min_var, variance[c], testVal);
				}
				else
				{
					testVal = step(variance[c], min_var);
					col_mean.rgb =
						lerp(
						(col_mean.rgb),
							(squrColor[c].rgb),
							testVal);
				}
			}
			return col_mean;
	}

	// ex

	if (mosaicActive != 0.0f)
	{

	//if (uv.x < (vx_offset - 0.005))
	//{
		float dx = pixel_w * (1. / rt_w);
		float dy = pixel_h * (1. / rt_h);
		float2 coord = float2(dx*floor(uv.x / dx),
			dy*floor(uv.y / dy));
		tc = (float3)textureMap.Sample(textureSampler, coord).rgb;
		return float4(tc, 1);
	//}
	}
	//else if (uv.x >= (vx_offset + 0.005))
	//{
	if (heatActive != 0.0f)
	{

		float3 pixcol = screenColor.rgb;
		float3 colors[3];
		colors[0] = float3(0, 0, 1);
		colors[1] = float3(1, 1, 0);
		colors[2] = float3(1, 0, 0);
		float lum = dot(float3(0.30f, 0.59f, 0.11f), pixcol.rgb);
		int ix = (lum < 0.5) ? 0 : 1;
		tc = lerp(colors[ix], colors[ix + 1], (lum - float(ix)*0.5f) / 0.5f);
	//}

	//tc = (float3)screenColor.rgb;
	return float4(tc, 1);
	}
	return screenColor;
}

