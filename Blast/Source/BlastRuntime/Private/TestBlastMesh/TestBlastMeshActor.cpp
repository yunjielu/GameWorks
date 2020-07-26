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

	for (int32 i = 0; i < FoundBlastActors.Num(); ++i)
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

void ATestBlastMeshActor::SetDebrisLifetime(int32 min, int32 max)
{
	REAL_BLAST_MESH_COMPONENT* BlastComp = Cast<REAL_BLAST_MESH_COMPONENT>(GetBlastMeshComponent());
	if (BlastComp)
	{
		const FBlastDebrisProperties& DebrisProperties = BlastComp->GetUsedDebrisProperties();
		for (int32 j = 0; j < DebrisProperties.DebrisFilters.Num(); ++j)
		{
			FBlastDebrisFilter& DebrisFilter = const_cast<FBlastDebrisFilter&>(DebrisProperties.DebrisFilters[j]);
			if (min == -1 || max == -1)
			{
				DebrisFilter.DebrisDepth = INT_MAX;
				DebrisFilter.DebrisLifetimeMin = INT_MAX;
				DebrisFilter.DebrisLifetimeMax = INT_MAX;
				continue;
			}

			DebrisFilter.DebrisDepth = 1;
			DebrisFilter.DebrisLifetimeMin = min;
			DebrisFilter.DebrisLifetimeMax = max;
		}
	}
}

void ATestBlastMeshActor::SetAllDebrisLifeTime(UWorld* world, int32 min, int32 max)
{
	FString WorkerId = world->GetGameInstance()->GetSpatialWorkerId();
	FString WorkerType = world->GetGameInstance()->GetSpatialWorkerType().ToString();
	FString WorkerLabel = world->GetGameInstance()->GetSpatialWorkerLabel();
	FString IsServer = world->GetGameInstance()->IsDedicatedServerInstance() ? "YES" : "NO";
	FString Authority;

	TArray<AActor*> FoundBlastActors;
	UGameplayStatics::GetAllActorsOfClass(world, REAL_BLAST_MESH_ACTOR::StaticClass(), FoundBlastActors);

	int32 num = 0;

	if (FoundBlastActors.Num())
	{
		for (int32 i = 0; i < FoundBlastActors.Num(); ++i)
		{
			REAL_BLAST_MESH_ACTOR* BlastActor = Cast<REAL_BLAST_MESH_ACTOR>(FoundBlastActors[i]);
			if (BlastActor)
			{
				Authority = BlastActor->HasAuthority() ? "YES" : "NO";
				BlastActor->SetDebrisLifetime(min, max);
				num++;
			}
		}
	}

	UE_LOG(LogBlast, Warning, TEXT("%s - [%d] blast actors set the lifetime to debris. WorkerId:[%s] WorkerType:[%s] WorkerLabel:[%s] IsServer:[%s] Authority:[%s]"),
		*FString(__FUNCTION__), num, *WorkerId, *WorkerType, *WorkerLabel, *IsServer, *Authority);
}

void ATestBlastMeshActor::CrossServerSetAllDebrisLifetime_Implementation(int32 min, int32 max)
{
	UE_LOG(LogBlast, Warning, TEXT("%s - min:[%d], max:[%d]"), *FString(__FUNCTION__), min, max);

	SetAllDebrisLifeTime(GetWorld(), min, max);
}

void ATestBlastMeshActor::CrossServerDestroyAllActors_Implementation()
{
	FString WorkerId = GetWorld()->GetGameInstance()->GetSpatialWorkerId();
	FString WorkerType = GetWorld()->GetGameInstance()->GetSpatialWorkerType().ToString();
	FString WorkerLabel = GetWorld()->GetGameInstance()->GetSpatialWorkerLabel();
	FString IsServer = GetWorld()->GetGameInstance()->IsDedicatedServerInstance() ? "YES" : "NO";
	FString Authority;

	TArray<AActor*> FoundBlastActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), REAL_BLAST_MESH_ACTOR::StaticClass(), FoundBlastActors);

	int32 num = 0;

	if (FoundBlastActors.Num())
	{
		for (int32 i = 0; i < FoundBlastActors.Num(); ++i)
		{
			REAL_BLAST_MESH_ACTOR* BlastActor = Cast<REAL_BLAST_MESH_ACTOR>(FoundBlastActors[i]);
			if (BlastActor)
			{
				Authority = BlastActor->HasAuthority() ? "YES" : "NO";
				BlastActor->Destroy();
				num++;
			}
		}
	}

	UE_LOG(LogBlast, Warning, TEXT("%s - [%d] blast actors destroied. WorkerId:[%s] WorkerType:[%s] WorkerLabel:[%s] IsServer:[%s] Authority:[%s]"),
		*FString(__FUNCTION__), num, *WorkerId, *WorkerType, *WorkerLabel, *IsServer, *Authority);
}

