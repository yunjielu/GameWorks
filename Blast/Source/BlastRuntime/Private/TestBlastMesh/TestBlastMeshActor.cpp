#include "TestBlastMeshActor.h"

ATestBlastMeshActor::ATestBlastMeshActor()
{
	bReplicates = true;
}

void ATestBlastMeshActor::CrossServerApplyDamage_Implementation(FVector Origin, float MinRadius, float MaxRadius, float Damage, float ImpulseStrength, bool bImpulseVelChange)
{
	FString WorkerId = GetWorld()->GetGameInstance()->GetSpatialWorkerId();
	FString WorkerType = GetWorld()->GetGameInstance()->GetSpatialWorkerType().ToString();
	FString WorkerLabel = GetWorld()->GetGameInstance()->GetSpatialWorkerLabel();
	FString IsServer = GetWorld()->GetGameInstance()->IsDedicatedServerInstance() ? "YES" : "NO";
	FString Authority = this->HasAuthority() ? "YES" : "NO";

	UE_LOG(LogBlast, Warning, TEXT("%s - WorkerId:[%s] WorkerType:[%s] WorkerLabel:[%s] Name:[%s] IsServer:[%s] Authority:[%s]"),
		*FString(__FUNCTION__), *WorkerId, *WorkerType, *WorkerLabel, *GetFName().ToString(), *IsServer, *Authority);

	BlastMeshComponent->ApplyRadialDamage(Origin, MinRadius, Damage, ImpulseStrength, bImpulseVelChange);
}
