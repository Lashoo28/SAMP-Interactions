# SAMP-Interactions
Interaction Positions

## Include:
```pawn
#include <interact.inc>
```

### Callback:
```pawn
public OnPlayerInteract(playerid, interactid)
```

### Example:
```pawn
new test_interact;
public OnGameModeInit()
{
    	test_interact = CreateInteraction(1210, "Interaction\nPress ALT", KEY_WALK, 1154.1750, -1769.1215, 16.5938);
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
```
