// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Combatant.h"
#include "PauseMenu.h"
#include "XPController.h"
#include "UI/CombatantWidget.h"
#include "UI/GameOver/UGameOverWidget.h"
#include "PlayerCharacter.generated.h"
/**
 *
 */
UCLASS()
class FUCK_API APlayerCharacter : public ACombatant
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class UStaticMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class USphereComponent* EnemyDetectionCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float PassiveMovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float CombatMovementSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	TSubclassOf<class UPlayerCharacterWidget> PlayerCharacterWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUGameOverWidget> GameOverWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPauseMenu> PauseWidget;

	void CycleTarget(bool Clockwise = true);

	UFUNCTION()
	void CycleTargetClockwise();

	UFUNCTION()
	void CycleTargetCounterClockwise();

	void LookAtSmooth();

	UFUNCTION(BlueprintCallable)
	float TakeDamageProjectile(float DamageAmount);
	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser);

	UPROPERTY(EditAnywhere, Category = "Animations")
	TArray<class UAnimMontage*> Attacks;

	UPROPERTY(EditAnywhere, Category = "Animations")
	class UAnimMontage* CombatRoll;

	UPROPERTY(EditAnywhere, Category = Camera)
	TSubclassOf<class ULegacyCameraShake> CameraShakeMinor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roll")
	bool Rolling;

	FRotator RollRotation;

	int AttackIndex;
	float TargetLockDistance;

	TArray<class AActor*> NearbyEnemies;
	int LastStumbleIndex;

	FVector InputDirection;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Stamina")
	float CurrentStamina;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Stamina")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Stamina")
	float RollCostStamina;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Stamina")
	float AttackCostStamina;

	bool Sprint = false;

	UFUNCTION()
	void OnEnemyDetectionBeginOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEnemyDetectionEndOverlap(class UPrimitiveComponent*
		OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UXPController* XPController;
	
protected:

	void MoveForward(float Value);
	void MoveRight(float Value);

	void Attack();
	void Jump();

	void StartSprinting();

	void StopSprinting();

	void EndAttack();

	void Death();

	void AttackNextReady();

	void Roll();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StartRoll();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EndRoll();

	void RollRotateSmooth();
	void FocusTarget();
	void ToggleCombatMode();
	void SetInCombat(bool InCombat);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	
	void LoadGameOverScreen();
	void ShowPauseMenu();
	void OnLevelChanged(int Value);

public:

	bool Dead = false;
	class USpringArmComponent* GetCameraBoom() const
	{
		return CameraBoom;
	}

	class UCameraComponent* GetFollowCamera() const
	{
		return FollowCamera;
	}

	class UStaticMeshComponent* GetWeapon() const
	{
		return Weapon;
	}

};
