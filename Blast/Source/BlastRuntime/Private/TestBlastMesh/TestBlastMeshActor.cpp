#include "TestBlastMeshActor.h"
#include "Kismet/GameplayStatics.h"

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

void ATestBlastMeshActor::CrossServerPrintCurrentBlastInfos_Implementation()
{
	FString WorkerId = GetWorld()->GetGameInstance()->GetSpatialWorkerId();
	FString WorkerType = GetWorld()->GetGameInstance()->GetSpatialWorkerType().ToString();
	FString WorkerLabel = GetWorld()->GetGameInstance()->GetSpatialWorkerLabel();
	FString IsServer = GetWorld()->GetGameInstance()->IsDedicatedServerInstance() ? "YES" : "NO";
	FString Authority = this->HasAuthority() ? "YES" : "NO";

	UE_LOG(LogBlast, Warning, TEXT("%s - WorkerId:[%s] WorkerType:[%s] WorkerLabel:[%s] Name:[%s] IsServer:[%s] Authority:[%s]"),
		*FString(__FUNCTION__), *WorkerId, *WorkerType, *WorkerLabel, *GetFName().ToString(), *IsServer, *Authority);

	PrintCurrentBlastInfos(FString(__FUNCTION__));
}

void ATestBlastMeshActor::PrintCurrentBlastInfos(const FString& Func)
{
	FString FuncName = Func.IsEmpty() ? FString(__FUNCTION__) : Func;

	TArray<AActor*> FoundBlastActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), REAL_BLAST_MESH_ACTOR::StaticClass(), FoundBlastActors);

	UE_LOG(LogBlast, Warning, TEXT("%s - BlastActor Total Count:[%d]"), *FuncName, FoundBlastActors.Num());

	for (INT i = 0; i < FoundBlastActors.Num(); ++i)
	{
		REAL_BLAST_MESH_ACTOR* BlastActor = Cast<REAL_BLAST_MESH_ACTOR>(FoundBlastActors[i]);
		if (BlastActor)
		{
			REAL_BLAST_MESH_COMPONENT* BlastComp = Cast<REAL_BLAST_MESH_COMPONENT>(BlastActor->GetBlastMeshComponent());
			if (BlastComp)
			{
				UE_LOG(LogBlast, Warning, TEXT("%s - Index:[%d] Fracture Count:[%d]"), *FuncName, i, BlastComp->CanBeFracturedCount());
			}
		}
	}
}
