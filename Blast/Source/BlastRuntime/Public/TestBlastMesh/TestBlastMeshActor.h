#pragma once

#include "CoreMinimal.h"
#include "BlastMeshComponent.h"
#include "GameFramework/Actor.h"
#include "BlastMeshActor.h"
#include "TestBlastMeshComponent.h"
#include "TestBlastMeshActor.generated.h"

UCLASS(Blueprintable, ComponentWrapperClass, ConversionRoot, meta = (ChildCanTick))
class BLASTRUNTIME_API ATestBlastMeshActor : public ABlastMeshActor
{
	GENERATED_BODY()
public:
	ATestBlastMeshActor();
};

