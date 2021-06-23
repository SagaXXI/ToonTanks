// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameState.h"


ATanksGameState::ATanksGameState()
{
    Score = 0.f;
}

float ATanksGameState::GetScore()
{
    return Score;
}

void ATanksGameState::IncrementScore()
{
    Score += 25.f;
}