#pragma once
#include<KWSE/Inc/KWSE.h>


class GameState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;


	void Update(float deltaTime) override;
	void Render() override;
private:
	struct Vertex
	{
		KWSE::Math::Vector3 position;
		KWSE::Graphics::Color color;
	};

	std::vector<Vertex> mVertices;

	ID3D11Buffer* mVertexBuffer = nullptr;

	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;

	ID3D11PixelShader* mPixelShader = nullptr;



};