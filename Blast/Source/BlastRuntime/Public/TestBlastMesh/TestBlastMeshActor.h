#pragma once

#include "CoreMinimal.h"
#include "BlastMeshComponent.h"
#include "GameFramework/Actor.h"
#include "BlastMeshActor.h"
#include "TestBlastMeshComponent.h"
#include "TestBlastMeshActor.generated.h"

#define DEBRIS_LIFETIME_QUICK_MIN			1
#define DEBRIS_LIFETIME_QUICK_MAX			2
#define DEBRIS_LIFETIME_NORMAL_MIN			10
#define DEBRIS_LIFETIME_NORMAL_MAX			20
#define DEBRIS_LIFETIME_FOREVER_MIN			-1
#define DEBRIS_LIFETIME_FOREVER_MAX			-1

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

	void SetDebrisLifetime(int32 min, int32 max);
	static void SetAllDebrisLifeTime(UWorld* world, int32 min, int32 max);

	UFUNCTION(CrossServer, Reliable)
	void CrossServerSetAllDebrisLifetime(int32 min, int32 max);

protected:
	uint32						BlastCount = 0;
};

