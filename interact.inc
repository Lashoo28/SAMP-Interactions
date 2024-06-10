// SA:MP Interact Positions (C) 2024 | Lashoo28

#if defined intractions_included
	#endinput
#endif
 
#define intractions_included

#define MAX_INTERACTIONS (32)

#if defined _streamer_included
    #define lip_USESTREAMER true
#else
    #define lip_USESTREAMER false
#endif

#define Interact:

forward OnPlayerInteract(playerid, Interact:interactid);

enum E_INETRACTION
{
    bool:IP_AVALIABLE,
    IP_ID,
    Float:IP_POS[3],
    Text3D:IP_TEXT[64],
    IP_MODEL,
    IP_PICKUP,
    IP_KEY,
    IP_WORLDID,
    IP_INTERIORID
}
new InteractData[MAX_INTERACTIONS][E_INETRACTION];

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    for(new i = 0; i < MAX_INTERACTIONS; i ++) {
        if(!InteractData[i][IP_AVALIABLE]) continue;
        if(newkeys == InteractData[i][IP_KEY]) {
            if(
                IsPlayerInRangeOfPoint(playerid, 2.0, InteractData[i][IP_POS][0], InteractData[i][IP_POS][1], InteractData[i][IP_POS][2])) {
                CallRemoteFunction("OnPlayerInteract", "dd", playerid, i);
		return true;
            }
        }
    }
    #if defined lip_OnPlayerKeyStateChange
		return lip_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange lip_OnPlayerKeyStateChange
#if defined lip_OnPlayerKeyStateChange
	forward lip_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

stock Interact:CreateInteraction(model, text[], keyid, Float:x, Float:y, Float:z, world=-1, interior=-1)
{
    if(strlen(text) > 64) printf("[debug-interact]: text size is too large"); 
    for(new i = 0; i < MAX_INTERACTIONS; i ++)
    {
        if(!InteractData[i][IP_AVALIABLE]) {
            InteractData[i][IP_AVALIABLE] = true;
            InteractData[i][IP_ID] = i;
            InteractData[i][IP_POS][0] = x;
            InteractData[i][IP_POS][1] = y;
            InteractData[i][IP_POS][2] = z;
            //strmid(InteractData[i][IP_TEXT], text, 0, strlen(text), 64);
            InteractData[i][IP_MODEL] = model;
            InteractData[i][IP_KEY] = keyid;
            
            #if lip_USESTREAMER == true
                InteractData[i][IP_PICKUP] = CreateDynamicPickup(
            #else
                InteractData[i][IP_PICKUP] = CreatePickup(
            #endif
            model, 23, Float:x, Float:y, Float:z, world);
            #if lip_USESTREAMER == true
                InteractData[i][IP_TEXT] = CreateDynamic3DTextLabel(text, 0xFFFFFFFF, x, y, z, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, world, interior);
            #else
                InteractData[i][IP_TEXT] = Create3DTextLabel(text, 0xFFFFFFFF, x, y, z, 6.0, world, 0);
            #endif
            InteractData[i][IP_WORLDID] = world;
            InteractData[i][IP_INTERIORID] = interior;
            return i;
        }
    }
    return -1;
}
stock Interact:DestoryInteraction(interactid)
{
    if(!(0 <= interactid < MAX_INTERACTIONS)) return -1;
    if(!InteractData[interactid][IP_AVALIABLE]) return printf("[debug-interact]: invalid interact id");
    InteractData[interactid][IP_AVALIABLE] = false;
    InteractData[interactid][IP_ID] = -1;
    InteractData[interactid][IP_POS][0] = 0;
    InteractData[interactid][IP_POS][1] = 0;
    InteractData[interactid][IP_POS][2] = 0;
    InteractData[interactid][IP_MODEL] = -1;
    InteractData[interactid][IP_KEY] = -1;
    #if lip_USESTREAMER == true
        if(IsValidDynamicPickup(InteractData[interactid][IP_PICKUP])) DestroyDynamicPickup(InteractData[interactid][IP_PICKUP]);
        if(IsValidDynamic3DTextLabel(InteractData[interactid][IP_TEXT])) DestroyDynamic3DTextLabel(InteractData[interactid][IP_PICKUP]);
    #else
        DestroyPickup(InteractData[interactid][IP_PICKUP]);
        Delete3DTextLabel(InteractData[interactid][IP_TEXT]);
    #endif
    InteractData[interactid][IP_WORLDID] = -1;
    InteractData[interactid][IP_INTERIORID] = -1;
    return interactid;
}
