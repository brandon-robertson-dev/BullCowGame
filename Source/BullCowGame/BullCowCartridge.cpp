// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        CheckGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to the game"));
    HiddenWord = TEXT("cake");
    Lives = 5;
    bGameOver = false;
    // PrintLine(TEXT(""));
    PrintLine(FString::Printf(TEXT("Guess the %i letter long word"), HiddenWord.Len()));
    PrintLine(FString::Printf(TEXT("You have %i lives left"), Lives));
    PrintLine(TEXT("Type a word and press enter to guess"));
}

void UBullCowCartridge::GameOver()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again"));
}

void UBullCowCartridge::CheckGuess(const FString& Guess)
{
    ClearScreen();

    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have won"));
        GameOver();
        return;
    }
    
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(FString::Printf(TEXT("Guess the %i letter long word"), HiddenWord.Len()));
        PrintLine(FString::Printf(TEXT("You have %i lives left"), Lives));
        return;
    }

    PrintLine(TEXT("You lost a life, try again"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("No lives left"));
        PrintLine(FString::Printf(TEXT("The hidden word was %s"), *HiddenWord));
        GameOver();
        return;
    }
}