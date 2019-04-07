#include "BasePlayer.h"

// Sets default values
ABasePlayer::ABasePlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Для создания компонентов можно использовать CreateDefaultSubobject<Type>("InternalName")

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	/*Это создаст компонент каждого типа, а затем назначит их адрес в памяти переданной переменной. 
	Аргумент-строка будет внутренним именем компонента, используемым движком */

	RootComponent = Mesh; //сделает Mesh корневым компонентом
	SpringArm->SetupAttachment(Mesh); //прикрепит SpringArm к Mesh
	Camera->SetupAttachment(SpringArm); //прикрепит Camera к SpringArm

	//Включение физики

	Mesh->SetSimulatePhysics(true); //позволит воздействовать на Mesh физическим силам
	MovementForce = 100000; /*присваивает MovementForce значение 100000. Это значит, что при движении шару будет прибавлено 100 000 силы.
							Т.к. вес по стандарту 110 кг => нужно много силы*/
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Mы свяжем привязки осей MoveUp и MoveRight с MoveUp() и MoveRight()
	InputComponent->BindAxis("MoveUp", this, &ABasePlayer::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);

	//свяжем привязку Jump с Jump(). Она будет выполняться только при нажатии клавиши прыжка
	InputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);
	
}

void ABasePlayer::MoveUp(float Value)
{
	/*MoveUp() добавляет физическую силу для Mesh по оси X. Величина силы задаётся MovementForce*/
	FVector ForceToAdd = FVector(1, 0, 0) * MovementForce * Value;
	Mesh->AddForce(ForceToAdd);
}

void ABasePlayer::MoveRight(float Value)
{
	/*MoveRight() делает то же самое, что и MoveUp(), но по оси Y*/
	FVector ForceToAdd = FVector(0, 1, 0) * MovementForce * Value;
	Mesh->AddForce(ForceToAdd);
}