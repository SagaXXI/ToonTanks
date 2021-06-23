// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameMode.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/TanksPlayerController.h"
#include "ToonTanks/TanksGameState.h"

/* GameInstance (an object spawned when you launch the application and that remains the same until you close it)
GameMode (spawned when a level is loaded)
GameState (spawned by the gameMode)
PlayerState (spawned when a PlayerController is spawned = when a player arrives in the game)

You have to pay close attention to what you do and where you do it when coding a multiplayer game. When it comes to singleplayer, you can’t really “have it wrong” except for GameInstance stuff.

But here are the general guidelines I follow:
GameInstance - Holds any non-pointer persistent variables (persistent means that you need to store in between two levels and that you don’t need to store in a SaveGame)

GameMode - The overall game manager - starts and stops the current game space you’re in, handles the GameStates and how they rotate - an example might be “King of the Hill”

GameState - Keeps track of every data relative to the current state of the game (timers, scores, winning team) that all players in the game need to know about, handles scripted events related to the state
For instance:
PregameState: Prevents player from performing any action, starts a timer and display it to everyone. When timer expires, ask KotH (KingOfTheHill game mode) to rotate to IngameState
IngameState: Enable player input, spawn a big loud noise and open players’ spawn gates. Open the Capture Point and store the amount of capture time both teams have. When one of the team reaches max score, asks KotH to switch to EndgameState.
EndgameState: Destroy every player’s characters and starts a cinematic showing the PlayOfTheGame then asks KotH to rotate to ScoreGameState etc.

PlayerController - HUD, Camera, Mouse, Keyboard, Gamepad, Inputs calling actions on the Character.

PlayerCharacter - Actions in response of Controller’s input + Holds personal infos and stats (Health, Ammo - but Ammo might on your Weapon Class if you can switch Weapons).

PlayerState - Holds every variable non related to the PlayerCharacter that needs to be known by everyone (best scores, current killing streak, player name…). */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Think of the constructor as when the object/actor is built. Use this for all the default settings and so on.

The BeginPlay function is called when the game actually starts or after the object/actor is spawned and in the game world while the game is
running from my understanding and this is where you want to put in any spawning you need to do or anything game related.
For example if you need to get a pointer to the player controller in your character class you would do that here and not in the constructor.
In the constructor it wouldn’t know anything about the player controller that is possessing the character/pawn as it isn’t possessed yet.
Not really sure when PostInitialize gets called in comparison to the other 2 functions. */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//I think, there is no permission for gamemodes, to change the score, and do some stuff like this,
//because HandleGameStart didn't work in TreasureHunt (WTF)
// Я думаю что это происходит, потому что как написано сверху, GameMode (spawned when a level is loaded)
//GameState (spawned by the gameMode). Так что геймстэйт просто не существует пока.





void ATanksGameMode::BeginPlay()
{
    
    TargetTurrets = GetCurrentTurretsCount();

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    PlayerControllerRef = Cast<ATanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    HandleGameStart();
    Super::BeginPlay();
}

void ATanksGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == PlayerPawn)
    {
        PlayerPawn->PawnDestroyed();
        HandleGameOver(false);

        if(PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnableState(false);
        }
    }
    else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->PawnDestroyed();
        TargetTurrets--;
        if(ATanksGameState* GS = GetGameState<ATanksGameState>())
        {
            UE_LOG(LogTemp, Warning, TEXT("Score : %i"), GS->GetScore())
            GS->IncrementScore();
            UE_LOG(LogTemp, Warning, TEXT("Score : %i"), GS->GetScore())
        }
        if(TargetTurrets == 0)
        {
            HandleGameOver(true);
        }
        
    }
}

void ATanksGameMode::HandleGameStart()
{
    GameStart();
    if(PlayerControllerRef)
    {
        PlayerControllerRef->SetPlayerEnableState(false);

        FTimerHandle PlayerEnableHandle;
        //This one is another way, of how to set timers in ue4. By this we can store the function, that we want to call.
        //This is helpful, when the function is outside of this class (It is in TanksPlayerController)
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &ATanksPlayerController::SetPlayerEnableState, true);
        int Delay = StartDelay + 2;
        GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, Delay, false);
    }
}

void ATanksGameMode::HandleGameOver(bool PlayerWon)
{
    GameOver(PlayerWon);
}

int32 ATanksGameMode::GetCurrentTurretsCount()
{
    //This class will be used to find in the world
    TSubclassOf <APawnTurret> ClassToFind;
    ClassToFind = APawnTurret::StaticClass();
    //Array in which all of the turrets will be stored
    TArray<AActor*> TurretActors;
    //Will find every actor of given class, and write it in the array
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TurretActors);
    //Get the number of all of the turrets
    return TurretActors.Num();
}
