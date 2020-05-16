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
	KWSE::Graphics::MeshPC mMesh;
	KWSE::Graphics::MeshBuffer mMeshBuffer;

	KWSE::Graphics::PixelShader mPixelShader;
	KWSE::Graphics::VertexShader mVertexShader;

};