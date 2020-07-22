#include "TestBlastMeshComponent.h"

UTestBlastMeshComponent::UTestBlastMeshComponent(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
	
}

void UTestBlastMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.RemoveAll(this);
	OnComponentHit.AddDynamic(this, &UTestBlastMeshComponent::OnCompHit);
}


INT UTestBlastMeshComponent::CanBeFracturedCount()
{
	INT result = 0;

	for (int32 actorIndex = BlastActorsBeginLive; actorIndex < BlastActorsEndLive; actorIndex++)
	{
		if (!BlastActors.IsValidIndex(actorIndex))
		{
			continue;
		}

		FActorData& ActorData = BlastActors[actorIndex];

		NvBlastActor* Actor = ActorData.BlastActor;
		if (!Actor)
		{
			continue;
		}

		if (!NvBlastActorCanFracture(Actor, NULL))
		{
			continue;
		}

		result++;
	}

	return result;
}

void UTestBlastMeshComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (
		GetOwner()->HasAuthority()		// offloading worker
		|| !GetWorld()->GetGameInstance()->IsDedicatedServerInstance()		// client
		)
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	}
}

void UTestBlastMeshComponent::OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FString WorkerId = GetWorld()->GetGameInstance()->GetSpatialWorkerId();
	FString WorkerType = GetWorld()->GetGameInstance()->GetSpatialWorkerType().ToString();
	FString WorkerLabel = GetWorld()->GetGameInstance()->GetSpatialWorkerLabel();
	FString IsServer = GetWorld()->GetGameInstance()->IsDedicatedServerInstance() ? "YES" : "NO";
	FString Authority = this->GetOwner()->HasAuthority() ? "YES" : "NO";
	
	if (
		GetOwner()->HasAuthority()		// offloading worker
		// || !GetWorld()->GetGameInstance()->IsDedicatedServerInstance()		// client
		)
	{
		/**
		UE_LOG(LogBlast, Warning, TEXT("%s - WorkerId:[%s] WorkerType:[%s] WorkerLabel:[%s] Name:[%s] OtherActorName:[%s] IsServer:[%s] Authority:[%s]"),
			*FString(__FUNCTION__), *WorkerId, *WorkerType, *WorkerLabel, *GetFName().ToString(), *OtherActor->GetFName().ToString(), *IsServer, *Authority);
			*/

		Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	}
}

