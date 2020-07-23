#pragma once

#include "CoreMinimal.h"
#include "NvBlastTypes.h"
#include "NvBlastExtDamageShaders.h"
#include "BlastMesh.h"
#include "BlastAsset.h"
#include "Components/SkinnedMeshComponent.h"
#include "Components/LineBatchComponent.h"
#include "SkeletalMeshTypes.h"
#include "PhysicsEngine/BodySetup.h"
#include "BoneContainer.h"
#include "BlastBaseDamageComponent.h"
#include "BlastBaseDamageProgram.h"
#include "BlastMeshComponent.h"
#include "TestBlastMeshComponent.generated.h"

struct NvBlastActor;
struct NvBlastFamily;
class AVolume;
class ABlastExtendedSupportStructure;

namespace Nv
{
namespace Blast
{
class ExtStressSolver;
}
}

namespace physx
{
class PxScene;
}

UCLASS(ClassGroup=Blast, editinlinenew, hidecategories=(Object, Mesh), meta=(BlueprintSpawnableComponent))
class BLASTRUNTIME_API UTestBlastMeshComponent : public UBlastMeshComponent
{
	GENERATED_BODY()
public:
	UTestBlastMeshComponent(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;

	int32 CanBeFracturedCount();

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};

