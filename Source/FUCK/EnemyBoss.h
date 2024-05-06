#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemyBoss.generated.h"

/**
 *
 */
UCLASS()
class FUCK_API AEnemyBoss : public AEnemyBase
{


	GENERATED_BODY()

public:

	AEnemyBoss();

	UPROPERTY(EditAnywhere, Category = "Animations")
	TArray<UAnimMontage*> LongAttackAnimations;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser);

protected:

	void StateChaseClose();
	void LongAttack(bool Rotate = true);
	void MoveForward();

private:
	// long range jump attack

	UPROPERTY(EditAnywhere, Category = "Combat")
	float LongAttack_Cooldown;
	float LongAttack_Timestamp;
	float LongAttack_ForwardSpeed;

	// after x consecutive hits, the enemy cannot be interrupted
	int QuickHitsTaken;
	float QuickHitsTimestamp;
};
