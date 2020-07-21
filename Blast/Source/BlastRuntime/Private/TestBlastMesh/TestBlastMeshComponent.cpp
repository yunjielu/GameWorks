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


void UTestBlastMeshComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (GetOwner()->HasAuthority())
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	}
}

void UTestBlastMeshComponent::OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (GetOwner()->HasAuthority())
	{
		Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	}
}

