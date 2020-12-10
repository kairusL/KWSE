// Description: Simple shader that does transform and lighting.


cbuffer TransformBuffer : register(b0)
{
	matrix world;
	matrix wvp;
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
}

Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D displacementMap : register(t2);
Texture2D normalMap : register(t3);
Texture2D nightMap : register(t4);

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
	float4 position : SV_Position;
	float3 normal : NORMAL;
	float3 dirToView : TEXCOORD0;
	float2 texCoord : TEXCOORD1;
	float3 binormal : TEXCOORD2;
	float3 tangent : TEXCOORD3;
};

VS_OUTPUT VS(VS_INPUT input)
{
	float displacement = displacementMap.SampleLevel(textureSampler, input.texCoord, 0).x;
	float3 position = input.position + (input.normal * displacement * displacementWeight);

	float3 worldPosition = mul(float4(position, 1.0f), world).xyz;

	float3 worldNormal = mul(input.normal, (float3x3)world);
	float3 worldTangent = mul(input.tangent, (float3x3)world);

	float3 worldBinormal = cross(worldNormal, worldTangent);

	VS_OUTPUT output;
	output.position = mul(float4(position, 1.0f), wvp);
	output.normal = worldNormal;
	output.tangent = worldTangent;
	output.binormal = worldBinormal;
	output.dirToView = normalize(viewPosition - worldPosition);
	output.texCoord = input.texCoord;
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
	float dayMode = dot(normal, dirToLight);
	float diffuseIntensity = saturate(dot(normal, dirToLight));
	float4 diffuse = diffuseIntensity * lightDiffuse * materialDiffuse;

	float3 reflected = normalize(reflect(lightDirection, normal));
	float specularBase = saturate(dot(reflected, dirToView));
	float specularIntensity = pow(specularBase, specularPower);
	float4 specular = specularIntensity * lightSpecular * materialSpecular;


	float4 diffuseMapColor = diffuseMap.Sample(textureSampler, input.texCoord);
	float4 specularMapColor = specularMap.Sample(textureSampler, input.texCoord);

	//if (dayMode >0.f)
	//	return (ambient + diffuse) * diffuseMapColor + (specular * specularMapColor.r);
	//else
	//{
	//	float4 nightMapColor = nightMap.Sample(textureSampler, input.texCoord);
	//	return nightMapColor * 0.4f;
	//}
	if (dayMode < 0)
	{
		float4 nightMapColor = nightMap.Sample(textureSampler, input.texCoord);
		return (ambient + diffuse) * diffuseMapColor + (nightMapColor*-dayMode);// *specular* (specularWeight != 0.0f ? specularMapColor.r : 1.0f));
	
	}
	else
	{
		return (ambient + diffuse) * diffuseMapColor + (specular* (specularWeight != 0.0f ? specularMapColor.r : 1.0f));
	}
}