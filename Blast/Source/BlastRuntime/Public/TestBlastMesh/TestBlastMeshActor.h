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

	UFUNCTION(CrossServer, Reliable)
	void CrossServerApplyDamage(FVector Origin, float MinRadius, float MaxRadius, float Damage = 100.0f, float ImpulseStrength = 0.0f, bool bImpulseVelChange = true);

	void IncBlastCount() { BlastCount++; }
	uint32 GetBlastCount() const { return BlastCount; }

	UFUNCTION(CrossServer, Reliable)
	void CrossServerPrintCurrentBlastInfos();

	void PrintCurrentBlastInfos(const FString& Func);

protected:
	uint32						BlastCount = 0;
};

