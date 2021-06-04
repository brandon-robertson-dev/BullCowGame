// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("I am an UE4 GOD!"));
    PrintLine(TEXT("...seriously"));
    HiddenWord = TEXT("cake");
    PrintLine(TEXT("Guess the word"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();    
    if (Input == TEXT("let me win") || Input == HiddenWord)
    {
        PrintLine(TEXT("you win da game"));
    }
    else
    {
        PrintLine(TEXT("You suck ass bro, try again"));
    }
}