// Description: Simple shader that does texturing.

cbuffer ConstantBuffer : register(b0)
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

Texture2D textureMap : register(t0);
Texture2D cloud : register(t1);

SamplerState textureSampler : register(s0);

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
	float3 dirToView : TEXCOORD1;
};

VS_OUTPUT VS(VS_INPUT input)
{
	//float3 position = input.position + (input.normal);
	//float3 worldPosition = mul(float4(position, 1.0f), world).xyz;
	float3 worldPosition = mul(float4(input.position, 1.0f), world).xyz;

	float3 worldNormal = mul(input.normal, (float3x3)world);

	VS_OUTPUT output;
	output.position = mul(float4(input.position, 1.0f), wvp);
	output.normal = worldNormal;
	output.dirToView = normalize(viewPosition - worldPosition);
	output.texCoord = input.texCoord;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 dirToView = normalize(input.dirToView);
	float3 normal = normalize(input.normal);

	float4 ambient = lightAmbient * materialAmbient;

	float3 dirToLight = -lightDirection;
	float diffuseIntensity = saturate(dot(normal, dirToLight));
	float4 diffuse = diffuseIntensity * lightDiffuse * materialDiffuse;

	float3 reflected = normalize(reflect(lightDirection, normal));
	float specularBase = saturate(dot(reflected, dirToView));
	float specularIntensity = pow(specularBase, specularPower);
	float4 specular = specularIntensity * lightSpecular * materialSpecular;

	float4 cloudMap = textureMap.Sample(textureSampler, input.texCoord);
	return (ambient + diffuse + specular)*cloudMap;
}