#include "BlastActorFactory.h"
#include "BlastMesh.h"
#include "BlastMeshActor.h"
#include "BlastMeshComponent.h"
#include "TestBlastMeshActor.h"
#include "TestBlastMeshComponent.h"

#define LOCTEXT_NAMESPACE "Blast"

/*-----------------------------------------------------------------------------
UActorFactoryBlastMesh
-----------------------------------------------------------------------------*/
UActorFactoryBlastMesh::UActorFactoryBlastMesh(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DisplayName = LOCTEXT("BlastMeshDisplayName", "Blast Mesh");

	// yunjie: replace with macro
	// NewActorClass = ABlastMeshActor::StaticClass();
	NewActorClass = REAL_BLAST_MESH_ACTOR::StaticClass();
	bUseSurfaceOrientation = true;
}

bool UActorFactoryBlastMesh::CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg)
{
	if (!AssetData.IsValid() ||
		(!AssetData.GetClass()->IsChildOf(UBlastMesh::StaticClass()))
		)
	{
		OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoBlastMesh", "A valid blast mesh must be specified.");
		return false;
	}

	return true;
}

UObject* UActorFactoryBlastMesh::GetAssetFromActorInstance(AActor* ActorInstance)
{
	// yunjie: replace with macro
	if (REAL_BLAST_MESH_ACTOR* BlastActorInstance = Cast<REAL_BLAST_MESH_ACTOR>(ActorInstance))
	{
		return BlastActorInstance->GetBlastMeshComponent()->GetBlastMesh();
	}
	return nullptr;
}

void UActorFactoryBlastMesh::PostSpawnActor(UObject* Asset, AActor* NewActor)
{
	Super::PostSpawnActor(Asset, NewActor);

	UBlastMesh* BlastMesh = Cast<UBlastMesh>(Asset);
	// yunjie: replace with macro
	// UBlastMeshComponent* BlastComponent = Cast<ABlastMeshActor>(NewActor)->GetBlastMeshComponent();
	UBlastMeshComponent* BlastComponent = Cast<REAL_BLAST_MESH_ACTOR>(NewActor)->GetBlastMeshComponent();
	
	// Change properties
	BlastComponent->SetBlastMesh(BlastMesh);
}

void UActorFactoryBlastMesh::PostCreateBlueprint(UObject* Asset, AActor* CDO)
{
	Super::PostCreateBlueprint(Asset, CDO);

	if (Asset != NULL && CDO != NULL)
	{
		UBlastMesh* BlastMesh = Cast<UBlastMesh>(Asset);
		// yunjie: replace with macro
		// UBlastMeshComponent* BlastComponent = Cast<ABlastMeshActor>(CDO)->GetBlastMeshComponent();
		UBlastMeshComponent* BlastComponent = Cast<REAL_BLAST_MESH_ACTOR>(CDO)->GetBlastMeshComponent();
		// Change properties
		BlastComponent->SetBlastMesh(BlastMesh);
	}
}

#undef LOCTEXT_NAMESPACE