// Description: Simple shader that does transform and lighting.


cbuffer TransformBuffer : register(b0)
{
	matrix world;
	matrix wvp[2];
	float3 viewPosition;
}

cbuffer LightBuffer : register(b1)
{
	float3 lightDirection;
	float4 lightAmbient;
	float4 lightDiffuse;
	float4 lightSpecular;
}

cbuffer MaterialBuffer : register(b2)
{
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
	float specularPower;
}
cbuffer SettingBuffer : register(b3)
{
	float displacementWeight;
	float normalWeight;
	float specularWeight;
	float depthBias;
	//int useShadow;
}

Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D displacementMap : register(t2);
Texture2D normalMap : register(t3);
Texture2D shadowMap : register(t4);
SamplerState textureSampler : register(s0);

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
	float3 tangent : TANGENT;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;  // use for resterizer
	float3 normal : NORMAL;
	float3 dirToView : TEXCOORD0;
	float2 texCoord : TEXCOORD1;
	float3 binormal : TEXCOORD2;
	float3 tangent : TEXCOORD3;
	float4 lightNdcPosition : TEXCOORD4;
};

VS_OUTPUT VS(VS_INPUT input)
{
	float displacement = displacementMap.SampleLevel(textureSampler, input.texCoord, 0).x;
	float3 position = input.position + (input.normal *(float3)displacement * displacementWeight); //displacement*0.2f);

	float3 worldPosition = mul(float4(position, 1.0f), world).xyz;

	float3 worldNormal = mul(input.normal, (float3x3)world);
	float3 worldTangent = mul(input.tangent, (float3x3)world);

	float3 worldBinormal = cross(worldNormal, worldTangent);

	VS_OUTPUT output;
	output.position = mul(float4(position, 1.0f), wvp[0]);
	output.normal = worldNormal;
	output.tangent = worldTangent;
	output.binormal = worldBinormal;
	output.dirToView = normalize(viewPosition - worldPosition);
	output.texCoord = input.texCoord;
	output.lightNdcPosition = mul(float4(position, 1.0f), wvp[1]);
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	
	float3 normal = normalize(input.normal);

	float3 dirToView = normalize(input.dirToView);
	float3 sampledNormal = normalMap.Sample(textureSampler, input.texCoord).xyz;//[0,1]
	float3 unpackedNormal = (sampledNormal * 2) - 1; //[ -1,1]  


	float3 n = normalize(input.normal);
	float3 b = normalize(input.binormal);
	float3 t = normalize(input.tangent);
	float3x3 tbnw = float3x3(t, b, n);

	if (normalWeight != 0.0f)
	{
		normal = mul(unpackedNormal, tbnw);
	}


	float4 ambient = lightAmbient * materialAmbient;
	
	float3 dirToLight = -lightDirection;
	float diffuseIntensity = saturate(dot(normal, dirToLight));
	float4 diffuse = diffuseIntensity * lightDiffuse * materialDiffuse;

	float3 reflected = normalize(reflect(lightDirection, normal));
	float specularBase = saturate(dot(reflected, dirToView));
	float specularIntensity = pow(specularBase, specularPower);
	float4 specular = specularIntensity * lightSpecular * materialSpecular;


	float4 diffuseMapColor = diffuseMap.Sample(textureSampler, input.texCoord);
	float4 specularMapColor = specularMap.Sample(textureSampler, input.texCoord);

	float realDepth = 1.0f - input.lightNdcPosition.z / input.lightNdcPosition.w;

	// NDC has x and y from [-1,1] and [-1,1]
	// covert to UV , we need to convert to [0,1] and [1,0]

	//NDC UV
	float2 shadowUV = input.lightNdcPosition.xy/ input.lightNdcPosition.w; // convert into 3d coordinates before use it 
	shadowUV = (shadowUV + 1.0f)*0.5f;
	shadowUV.y = 1.0f - shadowUV.y;

	float recordedDepth = shadowMap.Sample(textureSampler, shadowUV).x; // .x / .r  ;
	float4 finalColor;

	if (realDepth + depthBias < recordedDepth)
	{
		finalColor = ambient * diffuseMapColor;
	}
	else
	{
		finalColor = (ambient + diffuse) * diffuseMapColor + (specular* (specularWeight != 0.0f ? specularMapColor.r : 1.0f));
	}
	return finalColor;
}