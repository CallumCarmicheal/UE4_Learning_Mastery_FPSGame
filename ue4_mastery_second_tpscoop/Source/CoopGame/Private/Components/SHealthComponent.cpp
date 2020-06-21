// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
USHealthComponent::USHealthComponent()
{
	DefaultHealth = 100;
}


// Called when the game starts
void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	AActor* MyOwner = GetOwner();
	if (MyOwner) 
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &USHealthComponent::HandleTakeAnyDamage);

	Health = DefaultHealth;
}

void USHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, 
	AController* InstigatedBy, AActor* DamageCauser) 
{
	if (Damage <= 0.0f)
		return;

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
	
	UE_LOG(LogTemp, Log, TEXT("Health Changed: %s"), *FString::SanitizeFloat(Health));

	// USHealthComponent*, HealthComp, float, Health, float, HealthDelta, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser
	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);

	
}

