#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPPGTeamID : uint8
{
    Player = 0,
    Monster = 1,

    NoTeam = 255
};