// Copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

// Function Initialises Game Start
void UBullCowCartridge::BeginPlay() 
{
    //necessary when game starts - everything goes beneath this
    Super::BeginPlay();

    //Sets Game Status
    InitGame();
    IsoGrams = GetValidWords(Words);

    /* 
    Debug Lines (%s = string, %i = int)
    PrintLine(TEXT("Total Hidden Words Are: %i"), Words.Num());
    PrintLine(TEXT("The Hidden Word Is: %s"), *HiddenWord); 
    */
}

// Function Initialises Player Guess Check
void UBullCowCartridge::OnInput(const FString& PlayerInput) 
{
    //conditional to check if game is over
    if (bGameOver)
    {
        //clears all previous attempts
        ClearScreen();

        //Resets Game Status
        InitGame();
    }
    else {
        ProcessGuess(PlayerInput);
    }
}

//Sets Game Status Upon Initialisation
void UBullCowCartridge::InitGame()
{
    //Game Intro
    PrintLine(TEXT("Welcome to Bull Cows!"));
   
    //Declared in Header File
    HiddenWord = IsoGrams[FMath::RandRange(0, IsoGrams.Num() - 1)];
    Lives = HiddenWord.Len();

    //Player Guess Prompt
    PrintLine(TEXT("Guess The %i Characters Long Word."), HiddenWord.Len()); //Adds pointer to the defined hidden word to get its length
    PrintLine(TEXT("You Have %i Lives."), Lives); //Adds pointer to the defined num of lives
    PrintLine(TEXT("Enter Your Guess To Continue..."));

    // Initial Game Over State
    bGameOver = false;

    IsIsogram(HiddenWord);
}

//Sets Game Actions Upon Word Guess
void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    //conditional for win/lose scenario to check player game status
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You Won"));
        EndGame();
        //an early return eliminates unnecessary nesting
        return;
    }

    //runs check if the guessed word is an Isogram
    if (!IsIsogram(Guess)) {
       PrintLine(TEXT("No Repeating Letters, Guess Again!"));
       return;
     }

    //checks if correct length 
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Try Again. Lives Remaining: %i."), Lives);
        return;
    }

    if (Lives > 0 ) {
    //Deducts Lives by 1
    --Lives;
    PrintLine(TEXT("You Lost A Life. Remaining: %i."), Lives);
    }

    //If We No Lives left
    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("The Hidden Word Was: %s"), *HiddenWord);
        PrintLine(TEXT("You Have No Lives Left. Game Over."));
        EndGame();
        return;
    }

    //Returns Player Scores After Each Round
    FWinLoseCount Score = GetScores(Guess);
    PrintLine(TEXT("Win: %i - Lose: %i"), Score.Wins, Score.Loses);
}

//Checks if Game Is Isogram
bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 Index = 0; Index < Word.Len(); Index++) {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

//Filters Through Hidden Word List TRo Get Valid Words
TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    //Find valid words from  words array
    TArray<FString> ValidWords;

    //Range Based For Loop To Iterate Through Word Collection
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8)
        {         
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

//Sets Game Win/Lose Status 
FWinLoseCount UBullCowCartridge::GetScores(const FString& Guess) const
{
    FWinLoseCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        //if word is correct, increase win count
        if (Guess == HiddenWord)
        {
           Count.Wins++;
           continue;
        }

        //if word is incorrect, increase lose count
        if (Guess != HiddenWord)
        {
           Count.Loses++;
           break;
        }
    }
    return Count;
}

//Sets Game Actions Upon Game End
void UBullCowCartridge::EndGame()
{
    bGameOver = true;    
    PrintLine(TEXT("Press Enter To Play Again."));
}
