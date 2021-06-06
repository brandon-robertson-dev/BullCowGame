// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordList/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArrayWithPredicate(Isograms, *WordListPath, [](const FString& Word)
    {
        return Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word);
    });

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

    int32 RandomWordNumber = FMath::RandRange(0, Isograms.Num() - 1);

    HiddenWord = Isograms[RandomWordNumber];
    Lives = HiddenWord.Len() * 2;
    bGameOver = false;

    PrintLine(FString::Printf(TEXT("Guess the %i letter long word"), HiddenWord.Len()));
    PrintLine(FString::Printf(TEXT("The word is %s"), *HiddenWord)); //Debug
    PrintLine(TEXT("The word has no repeating letters"));
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

    if (Guess.Len() == 0)
    {
        PrintLine(TEXT("Please make a guess and try again"));
        PrintLine(FString::Printf(TEXT("The word is %i letters long"), HiddenWord.Len()));
        PrintLine(FString::Printf(TEXT("Hint: The first letter is %c"), HiddenWord[0]));

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

    RandomNum = FMath::RandRange(0, HiddenWord.Len() - 1);

    PrintLine(FString::Printf(TEXT("Hint: Letter number %i is %c"), RandomNum + 1, HiddenWord[RandomNum]));

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(FString::Printf(TEXT("Guess the %i letter long word"), HiddenWord.Len()));
        PrintLine(FString::Printf(TEXT("You have %i lives left"), Lives));

        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters"));
        PrintLine(FString::Printf(TEXT("You have %i lives left"), Lives));

        return;
    }

    PrintLine(FString::Printf(TEXT("You have %i lives left"), Lives));

    int32 Bulls, Cows;

    GetBullCows(Guess, Bulls, Cows);

    PrintLine(FString::Printf(TEXT("You have %i Bulls and %i Cows"), Bulls, Cows));
}

bool UBullCowCartridge::IsIsogram(const FString& Word)
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

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    BullCount = 0;
    CowCount = 0;

    for (int32 BullIndex = 0; BullIndex < Guess.Len(); BullIndex++)
    {
        if (Guess[BullIndex] == HiddenWord[BullIndex])
        {
            BullCount++;
            continue;
        }
        for (int32 CowIndex = 0; CowIndex < HiddenWord.Len(); CowIndex++)
        {
            if (Guess[BullIndex] == HiddenWord[CowIndex])
            {
                CowCount++;
                break;
            }
        }
        
    }
    
}