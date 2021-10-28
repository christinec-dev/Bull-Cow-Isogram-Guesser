// Copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FWinLoseCount {
	int32 Wins = 0;
	int32 Loses = 0;
};

//GLOBAL SCOPE to be used within multiple function instances
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	//Function Declarations
	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void InitGame();
	void EndGame();
	void ProcessGuess(const FString& Guess);
	bool IsIsogram(const FString& Word) const;
	TArray<FString> GetValidWords(const TArray<FString>& WordList) const;
	FWinLoseCount GetScores(const FString& Guess) const;

	// Member Variable Declarations
	private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
	TArray<FString> IsoGrams;
};
