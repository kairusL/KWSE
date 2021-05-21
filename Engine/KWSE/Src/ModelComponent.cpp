#include "Precompiled.h"
#include "ModelComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

using namespace KWSE;

MEMPOOL_DEFINE(ModelComponent, 1000)

void ModelComponent::Initialize()
{
	mModel.Initialize(mFileName);
}

void ModelComponent::Terminate()
{
	mModel.Terminate();
}
