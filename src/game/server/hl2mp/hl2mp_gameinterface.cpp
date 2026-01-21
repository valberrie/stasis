//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "gameinterface.h"
#include "mapentities.h"
#include "hl2mp_gameinterface.h"
#include "tier0/icommandline.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// -------------------------------------------------------------------------------------------- //
// Mod-specific CServerGameClients implementation.
// -------------------------------------------------------------------------------------------- //

void CServerGameClients::GetPlayerLimits( int& minplayers, int& maxplayers, int &defaultMaxPlayers ) const
{
	minplayers = 1;

    ConVarRef lnbd{ "cl_localnetworkbackdoor" };
    if ( lnbd.GetBool() )
    {
        Warning( "cl_localnetworkbackdoor is enabled. You WILL crash if maxplayers is set to 1.\n" );
	}

	if ( false /*!steamapicontext->SteamApps()*/ )
    {
        Warning( "FIXME: SteamApps not connected. maxplayers above 1 will crash. Setting maxplayers to 1 and cl_localnetworkbackdoor to false.\n" );
		maxplayers = 1;
        lnbd.SetValue( false );
		return;
	}

#ifdef PLATFORM_64BITS
	maxplayers = MAX_PLAYERS;
#else
	if ( CommandLine()->HasParm("-unrestricted_maxplayers") )
	{
		static bool s_bWarned = false;
		if ( !s_bWarned )
		{
			Warning( "The use of -unrestricted_maxplayers is NOT supported and definitely NOT recommended and may be unstable.\n" );
			s_bWarned = true;
		}
		maxplayers = MAX_PLAYERS;
	}
	else
		maxplayers = 33;
#endif
	defaultMaxPlayers = 16; // misyl: Was 2... but why would the default be 2?! Is there some very intimate HL2DM going on?
}

// -------------------------------------------------------------------------------------------- //
// Mod-specific CServerGameDLL implementation.
// -------------------------------------------------------------------------------------------- //

void CServerGameDLL::LevelInit_ParseAllEntities( const char *pMapEntities )
{
}

