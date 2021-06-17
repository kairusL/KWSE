// Description: Post Processing shader.
// Renfrence : https://danielilett.com/2019-05-18-tut1-6-smo-painting/
// Renfrence : https://programmersought.com/article/63044668179/
 
Texture2D textureMap : register(t0);
SamplerState textureSampler : register(s0);

cbuffer OilSetting: register(b0)
{
	float screenSizeScale;
	float paintRadius;
	float sizeWeight;
	float iTime;
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

float2 mod289(float2 x) {
	return x - floor(x * (1.0f / 289.0f)) * 289.0f;
}

float3 mod289(float3 x) {
	return x - floor(x * (1.0f / 289.0f)) * 289.0f;
}

float4 mod289(float4 x) {
	return x - floor(x * (1.0f / 289.0f)) * 289.0f;
}

float3 permute(float3 x) {
	return mod289(((x*34.0f) + 1.0f)*x);
}

float4 permute(float4 x) {
	return fmod((34.0f * x + 1.0f) * x, 289.0f);
}

float cellular2x2(float2 P)
{
#define K 0.142857142857 // 1/7
#define K2 0.0714285714285 // K/2
#define jitter 0.8 // jitter 1.0 makes F1 wrong more often

	float2 Pi = fmod(floor(P), 289.0f);
	float2 Pf = frac(P);
	float4 Pfx = Pf.x + float4(-0.5f, -1.5f, -0.5f, -1.5f);
	float4 Pfy = Pf.y + float4(-0.5f, -0.5f, -1.5f, -1.5f);
	float4 p = permute(Pi.x + float4(0.0f, 1.0f, 0.0f, 1.0f));
	p = permute(p + Pi.y + float4(0.0f, 0.0f, 1.0f, 1.0f));
	float4 ox = fmod(p, 7.0f)*K + K2;
	float4 oy = fmod(floor(p*K), 7.0f)*K + K2;
	float4 dx = Pfx + jitter * ox;
	float4 dy = Pfy + jitter * oy;
	float4 d = dx * dx + dy * dy; // d11, d12, d21 and d22, squared
	// Sort out the two smallest distances

	// Cheat and pick only F1
	d.xy = min(d.xy, d.zw);
	d.x = min(d.x, d.y);
	return d.x; // F1 duplicated, F2 not computed
}

float4 PS(VS_OUTPUT input) : SV_Target
{

	float3 tc = float3(1.0, 0.9, 0.5);
	float vx_offset = 0.5;
	float pixel_w = 15.0;
	float pixel_h = 10.0f;
	float minSigma = 1.0f;
	float2 iResolution = float2(0.08f, -0.065f);
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

		//float dx = pixel_w * (1. / rt_w);
		//float dy = pixel_h * (1. / rt_h);
		//float2 coord = float2(dx*floor(uv.x / dx),
		//	dy*floor(uv.y / dy));
		//tc = (float3)textureMap.Sample(textureSampler, coord).rgb;
		//return float4(tc, 1);


		float speed = 2.0f;
		
		
		uv = uv / iResolution.xy;
		
		uv.x *= (iResolution.x / iResolution.y);
		
		
		float2 GA= float2(0.0f,0.0f);
		GA.x -= iTime * 0.5;
		GA.y += iTime * 0.3;
		GA *= speed;
		
		float F1 = 0.0f, F2 = 0.0f, F3 = 0.0f, F4 = 0.0f, F5 = 0.0f, N1 = 0.0f, N2 = 0.0f, N3 = 0.0f, N4 = 0.0f, N5 = 0.0f;
		float A =  0.0f, A1 = 0.0f, A2 = 0.0f, A3 = 0.0f, A4 = 0.0f, A5 = 0.0f;
		
		
		// Attentuation
		A = (uv.x - (uv.y*0.3f));
		A = clamp(A, 0.0f, 1.0f);
		
		// Snow layers, somewhat like an fbm with worley layers.
		F1 = 1.0f - cellular2x2((uv + (GA*0.1f))*8.0f);
		A1 = 1.0f - (A*1.0f);
		N1 = smoothstep(0.998f, 1.0f, F1)*1.0f*A1;
		
		F2 = 1.0f - cellular2x2((uv + (GA*0.2f))*6.0f);
		A2 = 1.0f - (A*0.8f);
		N2 = smoothstep(0.995f, 1.0f, F2)*0.85f*A2;
		
		F3 = 1.0f - cellular2x2((uv + (GA*0.4f))*4.0f);
		A3 = 1.0f - (A*0.6f);
		N3 = smoothstep(0.99f, 1.0f, F3)*0.65f*A3;
		
		F4 = 1.0f - cellular2x2((uv + (GA*0.6f))*3.0f);
		A4 = 1.0f - (A*1.0f);
		N4 = smoothstep(0.98f, 1.0f, F4)*0.4f*A4;
		
		F5 = 1.0f - cellular2x2((uv + (GA))*1.2f);
		A5 = 1.0f - (A*1.0f);
		N5 = smoothstep(0.98f, 1.0f, F5)*0.25f*A5;
		
		float Snowout = N5 + N4 + N3 + N2 + N1;
		
		Snowout = 0.35f + N1 + N2 + N3 + N4 + N5;
		
		float4 fragColor = float4(Snowout*0.9f*color.r, Snowout*color.g, Snowout*1.1f*color.b, 1.0f);
		return fragColor;

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

