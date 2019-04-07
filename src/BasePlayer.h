#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h" //Static Mesh: он позволит выбрать меш, являющийся моделью игрока.
#include "GameFramework/SpringArmComponent.h" //Spring Arm: этот компонент используется в качестве штатива камеры. Один конец будет прикреплён к мешу, а к другому будет прикреплена камера.
#include "Camera/CameraComponent.h" //Camera: Unreal показывает игроку всё, что видит камера.
#include "BasePlayer.generated.h" //Важно добавлять файл .generated.h последним. Если он будет не последним include, то при компиляции мы получим ошибку.

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

	//VisibleAnywhere позволит каждому компоненту быть видимым в редакторе (в том числе и в Blueprints)
	//BlueprintReadOnly позволит получать ссылку на компонент с помощью нодов Blueprint
	//Добавим над каждой переменной UPROPERTY() для того, чтобы сделать каждую переменную видимой для системы рефлексии.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) 
		UStaticMeshComponent* Mesh; //5

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) 
		USpringArmComponent* SpringArm; //6

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* Camera; //7

	//Реализация движения
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MovementForce;
	//Создание функций движения
	void MoveUp(float Value); 
	void MoveRight(float Value);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float JumpImpulse;
	/*переменная float с именем JumpImpulse. Мы можем использовать её при реализации прыжка.
	Она использует EditAnywhere, чтобы её можно было изменять в редакторе.
	Также в ней используется BlueprintReadWrite, чтобы мы могли считывать и записывать её с помощью нодов Blueprint.*/

	
	UFUNCTION(BlueprintImplementableEvent)
		void Jump();
	/*функция прыжка. UFUNCTION() делает Jump() видимой для системы рефлексии. 
	BlueprintImplementableEvent позволяет Blueprints реализовать Jump()*/
};
