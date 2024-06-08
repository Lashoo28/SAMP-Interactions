#include <a_samp>
#include <interact>
main (){}

new test_interact;

public OnGameModeInit()
{
    test_interact = CreateInteraction(1210, "Interaction\nPress ALT", KEY_WALK, 1154.1750, -1769.1215, 16.5938);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	SetPlayerPos(playerid, 1156.1750, -1769.1215, 16.5938);
	return 1;
}

public OnPlayerInteract(playerid, interactid)
{
	if(interactid == test_interact)
	{
		SendClientMessage(playerid, -1, "test message");
		DestoryInteraction(test_interact);
	}
	return 1;
}
