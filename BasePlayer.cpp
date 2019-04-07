#include "BasePlayer.h"

// Sets default values
ABasePlayer::ABasePlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//��� �������� ����������� ����� ������������ CreateDefaultSubobject<Type>("InternalName")

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	/*��� ������� ��������� ������� ����, � ����� �������� �� ����� � ������ ���������� ����������. 
	��������-������ ����� ���������� ������ ����������, ������������ ������� */

	RootComponent = Mesh; //������� Mesh �������� �����������
	SpringArm->SetupAttachment(Mesh); //��������� SpringArm � Mesh
	Camera->SetupAttachment(SpringArm); //��������� Camera � SpringArm

	//��������� ������

	Mesh->SetSimulatePhysics(true); //�������� �������������� �� Mesh ���������� �����
	MovementForce = 100000; /*����������� MovementForce �������� 100000. ��� ������, ��� ��� �������� ���� ����� ���������� 100 000 ����.
							�.�. ��� �� ��������� 110 �� => ����� ����� ����*/
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

	//M� ������ �������� ���� MoveUp � MoveRight � MoveUp() � MoveRight()
	InputComponent->BindAxis("MoveUp", this, &ABasePlayer::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);

	//������ �������� Jump � Jump(). ��� ����� ����������� ������ ��� ������� ������� ������
	InputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);
	
}

void ABasePlayer::MoveUp(float Value)
{
	/*MoveUp() ��������� ���������� ���� ��� Mesh �� ��� X. �������� ���� ������� MovementForce*/
	FVector ForceToAdd = FVector(1, 0, 0) * MovementForce * Value;
	Mesh->AddForce(ForceToAdd);
}

void ABasePlayer::MoveRight(float Value)
{
	/*MoveRight() ������ �� �� �����, ��� � MoveUp(), �� �� ��� Y*/
	FVector ForceToAdd = FVector(0, 1, 0) * MovementForce * Value;
	Mesh->AddForce(ForceToAdd);
}