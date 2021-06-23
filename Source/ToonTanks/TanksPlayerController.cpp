// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksPlayerController.h"


void ATanksPlayerController::SetPlayerEnableState(bool State)
{
    if(State)
    {
        GetPawnOrSpectator()->EnableInput(this);
        ATanksPlayerController::bShowMouseCursor = true;
    }
    else
    {
        GetPawnOrSpectator()->DisableInput(this);
        ATanksPlayerController::bShowMouseCursor = false;
    }
}
