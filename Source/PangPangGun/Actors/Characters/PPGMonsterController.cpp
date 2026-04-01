#include "Actors/Characters/PPGMonsterController.h"

APPGMonsterController::APPGMonsterController()
{
    PrimaryActorTick.bCanEverTick = false;
}

FGenericTeamId APPGMonsterController::GetGenericTeamId() const
{
    if (IGenericTeamAgentInterface* TeamAgentInterface = Cast<IGenericTeamAgentInterface>(GetPawn()))
    {
        return TeamAgentInterface->GetGenericTeamId();
    }

    return FGenericTeamId();
}
