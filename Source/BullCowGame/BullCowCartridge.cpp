// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordList/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
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
    HiddenWord = Words[rand() % Words.Num()];
    Lives = 5;
    bGameOver = false;
    int32 RandomNum = rand() % HiddenWord.Len(); 
    PrintLine(FString::Printf(TEXT("Guess the %i letter long word"), HiddenWord.Len()));
    PrintLine(FString::Printf(TEXT("Hint: Letter number %i is %c"), RandomNum + 1, HiddenWord[RandomNum]));
    PrintLine(TEXT("The word has no repeating letters"));
    PrintLine(FString::Printf(TEXT("You have %i lives left"), Lives));
    PrintLine(TEXT("Type a word and press enter to guess"));
}

void UBullCowCartridge::GameOver()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again"));
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for(int32 Index1 = 0; Index1 < Word.Len(); Index1++)
    {
        for (int32 Index2 = Index1 + 1; Index2 < Word.Len(); Index2++)
        {
            if(Word[Index1] == Word[Index2])
            {
                return false;
            }
        }
    }
    return true;
}

void UBullCowCartridge::CheckGuess(FString Guess)
{
    ClearScreen();

    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have won"));
        GameOver();
        return;
    }

    PrintLine(TEXT("You lost a life, try again"));
    --Lives;

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters"));
        PrintLine(FString::Printf(TEXT("You have %i lives left"), Lives));
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(FString::Printf(TEXT("Guess the %i letter long word"), HiddenWord.Len()));
        PrintLine(FString::Printf(TEXT("You have %i lives left"), Lives));
        return;
    }

    if (Guess.Len() == HiddenWord.Len())
    {
        int32 RandomNum = rand() % HiddenWord.Len(); 
        PrintLine(FString::Printf(TEXT("Hint: Letter number %i is %c"), RandomNum + 1, HiddenWord[RandomNum]));
        PrintLine(FString::Printf(TEXT("You have %i lives left"), Lives));
    }

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("No lives left"));
        PrintLine(FString::Printf(TEXT("The hidden word was %s"), *HiddenWord));
        GameOver();
        return;
    }
}