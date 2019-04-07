#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h" //Static Mesh: �� �������� ������� ���, ���������� ������� ������.
#include "GameFramework/SpringArmComponent.h" //Spring Arm: ���� ��������� ������������ � �������� ������� ������. ���� ����� ����� ��������� � ����, � � ������� ����� ����������� ������.
#include "Camera/CameraComponent.h" //Camera: Unreal ���������� ������ ��, ��� ����� ������.
#include "BasePlayer.generated.h" //����� ��������� ���� .generated.h ���������. ���� �� ����� �� ��������� include, �� ��� ���������� �� ������� ������.

UCLASS()
class COINCOLLECTOR_API ABasePlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//VisibleAnywhere �������� ������� ���������� ���� ������� � ��������� (� ��� ����� � � Blueprints)
	//BlueprintReadOnly �������� �������� ������ �� ��������� � ������� ����� Blueprint
	//������� ��� ������ ���������� UPROPERTY() ��� ����, ����� ������� ������ ���������� ������� ��� ������� ���������.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) 
		UStaticMeshComponent* Mesh; //5

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) 
		USpringArmComponent* SpringArm; //6

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* Camera; //7

	//���������� ��������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MovementForce;
	//�������� ������� ��������
	void MoveUp(float Value); 
	void MoveRight(float Value);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float JumpImpulse;
	/*���������� float � ������ JumpImpulse. �� ����� ������������ � ��� ���������� ������.
	��� ���������� EditAnywhere, ����� � ����� ���� �������� � ���������.
	����� � ��� ������������ BlueprintReadWrite, ����� �� ����� ��������� � ���������� � � ������� ����� Blueprint.*/

	
	UFUNCTION(BlueprintImplementableEvent)
		void Jump();
	/*������� ������. UFUNCTION() ������ Jump() ������� ��� ������� ���������. 
	BlueprintImplementableEvent ��������� Blueprints ����������� Jump()*/
};
