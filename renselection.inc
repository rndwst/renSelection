/*
    $$$$$$$\                             $$$$$$\            $$\                       $$\     $$\                     
    $$  __$$\                           $$  __$$\           $$ |                      $$ |    \__|                    
    $$ |  $$ | $$$$$$\  $$$$$$$\        $$ /  \__| $$$$$$\  $$ | $$$$$$\   $$$$$$$\ $$$$$$\   $$\  $$$$$$\  $$$$$$$\  
    $$$$$$$  |$$  __$$\ $$  __$$\       \$$$$$$\  $$  __$$\ $$ |$$  __$$\ $$  _____|\_$$  _|  $$ |$$  __$$\ $$  __$$\ 
    $$  __$$< $$$$$$$$ |$$ |  $$ |       \____$$\ $$$$$$$$ |$$ |$$$$$$$$ |$$ /        $$ |    $$ |$$ /  $$ |$$ |  $$ |
    $$ |  $$ |$$   ____|$$ |  $$ |      $$\   $$ |$$   ____|$$ |$$   ____|$$ |        $$ |$$\ $$ |$$ |  $$ |$$ |  $$ |
    $$ |  $$ |\$$$$$$$\ $$ |  $$ |      \$$$$$$  |\$$$$$$$\ $$ |\$$$$$$$\ \$$$$$$$\   \$$$$  |$$ |\$$$$$$  |$$ |  $$ |
    \__|  \__| \_______|\__|  \__|       \______/  \_______|\__| \_______| \_______|   \____/ \__| \______/ \__|  \__|


    Credit :
        Reno Dwi Setyangga (me)

    see any problem/bug on this include? (Dm my discord rndwst#1595)
    This include inpired by Salim's Selection
*/

#if !defined _samp_included
	#error You need a_samp include
#endif
#if defined renselection_included
	#endinput
#endif
#define renselection_included

#define MAX_SELECTION 300

new // Textdraw
	PlayerText:ren_SelectionBackground[MAX_PLAYERS],
	PlayerText:ren_SelectionHeader[MAX_PLAYERS],
	PlayerText:ren_SelectionPage[MAX_PLAYERS],
	PlayerText:ren_SelectionPreviewModel[MAX_PLAYERS],
	PlayerText:ren_SelectionDescription[MAX_PLAYERS],
	PlayerText:ren_SelectionButton1[MAX_PLAYERS],
	PlayerText:ren_SelectionButton2[MAX_PLAYERS],
	PlayerText:ren_SelectionLeftButton[MAX_PLAYERS],
	PlayerText:ren_SelectionRightButton[MAX_PLAYERS],
	// Player Data
	ren_PLayerSelectionID[MAX_PLAYERS],
	ren_PlayerSelectionPage[MAX_PLAYERS],
	ren_PlayerSelectionMaxPage[MAX_PLAYERS],
	ren_PlayerSelectionModel[MAX_PLAYERS][MAX_SELECTION],
	ren_PlayerSelectionDescription[MAX_PLAYERS][MAX_SELECTION][150],
	ren_PlayerSelectionVehColor[MAX_PLAYERS][MAX_SELECTION][2],
	bool:ren_PlayerSelectionShow[MAX_PLAYERS],
	ren_PlayerSelectionShowID[MAX_PLAYERS],
	// Server Data
	ren_SelectionBoxColor = 125,
	ren_SelectionModelColor = -131,
	ren_SelectionButtonColor = -131;

// ----------------------------------------------------------------------------------------------------
stock ren_ShowSelectionTextdraw(playerid)
{
    PlayerTextDrawShow(playerid, ren_SelectionBackground[playerid]);
	PlayerTextDrawShow(playerid, ren_SelectionHeader[playerid]);
	PlayerTextDrawShow(playerid, ren_SelectionPage[playerid]);
	PlayerTextDrawShow(playerid, ren_SelectionPreviewModel[playerid]);
	PlayerTextDrawShow(playerid, ren_SelectionDescription[playerid]);
	PlayerTextDrawShow(playerid, ren_SelectionButton1[playerid]);
	PlayerTextDrawShow(playerid, ren_SelectionButton2[playerid]);
	PlayerTextDrawShow(playerid, ren_SelectionLeftButton[playerid]);
	PlayerTextDrawShow(playerid, ren_SelectionRightButton[playerid]);
	return 1;
}
// ----------------------------------------------------------------------------------------------------
stock ren_DestroySelectionTextdraw(playerid)
{
	PlayerTextDrawDestroy(playerid, ren_SelectionBackground[playerid]);
	PlayerTextDrawDestroy(playerid, ren_SelectionHeader[playerid]);
	PlayerTextDrawDestroy(playerid, ren_SelectionPage[playerid]);
	PlayerTextDrawDestroy(playerid, ren_SelectionPreviewModel[playerid]);
	PlayerTextDrawDestroy(playerid, ren_SelectionDescription[playerid]);
	PlayerTextDrawDestroy(playerid, ren_SelectionButton1[playerid]);
	PlayerTextDrawDestroy(playerid, ren_SelectionButton2[playerid]);
	PlayerTextDrawDestroy(playerid, ren_SelectionLeftButton[playerid]);
	PlayerTextDrawDestroy(playerid, ren_SelectionRightButton[playerid]);
	CancelSelectTextDraw(playerid);
	return 1;
}
// ----------------------------------------------------------------------------------------------------
stock ren_ShowPlayerSelection(playerid, selectionid, header[], button1[], button2[], Float:rotx = -10.000000, Float:roty = 0.000000, Float:rotz = -20.000000, Float:zoom = 1.000000)
{
	if(ren_PlayerSelectionShow[playerid] == true) return 1;
	ren_DestroySelectionTextdraw(playerid);

	ren_CreateSelectionTextdraw(playerid);
	PlayerTextDrawSetString(playerid, ren_SelectionHeader[playerid], header);
	PlayerTextDrawSetString(playerid, ren_SelectionButton1[playerid], button1);
	PlayerTextDrawSetString(playerid, ren_SelectionButton2[playerid], button2);
	PlayerTextDrawSetString(playerid, ren_SelectionDescription[playerid], ren_PlayerSelectionDescription[playerid][0]);

	PlayerTextDrawSetPreviewModel(playerid, ren_SelectionPreviewModel[playerid], ren_PlayerSelectionModel[playerid][0]);
	PlayerTextDrawSetPreviewRot(playerid, ren_SelectionPreviewModel[playerid], rotx, roty, rotz, zoom);
	PlayerTextDrawSetPreviewVehCol(playerid, ren_SelectionPreviewModel[playerid], ren_PlayerSelectionVehColor[playerid][0][0], ren_PlayerSelectionVehColor[playerid][0][1]);

	ren_PLayerSelectionID[playerid] = selectionid;
	ren_PlayerSelectionShowID[playerid] = 0;
	ren_PlayerSelectionShow[playerid] = true;
	ren_PlayerSelectionPage[playerid] = 0;

	new fmt[128];
	format(fmt, sizeof(fmt), "%d/%d", ren_PlayerSelectionPage[playerid], ren_PlayerSelectionMaxPage[playerid]);
	PlayerTextDrawSetString(playerid, ren_SelectionPage[playerid], fmt);

    SelectTextDraw(playerid, 0xDB881AFF);
	ren_ShowSelectionTextdraw(playerid);
	return 1;
}
// ----------------------------------------------------------------------------------------------------
stock ren_AddSelectionModel(playerid, modelid, description[] = "Description", carcolor1 = 1, carcolor2 = 1)
{
	ren_PlayerSelectionMaxPage[playerid] += 1;
	new i = ren_PlayerSelectionMaxPage[playerid];

	ren_PlayerSelectionVehColor[playerid][i][0] = carcolor1;
	ren_PlayerSelectionVehColor[playerid][i][1] = carcolor2;

	ren_PlayerSelectionModel[playerid][i] = modelid;
	format(ren_PlayerSelectionDescription[playerid][i], 160, description);
	return 1;
}
// ----------------------------------------------------------------------------------------------------
stock ren_SelectionSetColor(boxcolor = 125, modelcolor = -131, buttoncolor = -131)
{
	ren_SelectionBoxColor = boxcolor;
	ren_SelectionModelColor = modelcolor;
	ren_SelectionButtonColor = buttoncolor;
	return 1;
}
// ----------------------------------------------------------------------------------------------------
stock ren_CreateSelectionTextdraw(playerid)
{
	// Background
	ren_SelectionBackground[playerid] = CreatePlayerTextDraw(playerid, 325.000000, 47.000000, "_");
	PlayerTextDrawFont(playerid, ren_SelectionBackground[playerid], 2);
	PlayerTextDrawLetterSize(playerid, ren_SelectionBackground[playerid], 0.600000, 32.299983);
	PlayerTextDrawTextSize(playerid, ren_SelectionBackground[playerid], 298.500000, 280.500000);
	PlayerTextDrawSetOutline(playerid, ren_SelectionBackground[playerid], 1);
	PlayerTextDrawSetShadow(playerid, ren_SelectionBackground[playerid], 0);
	PlayerTextDrawAlignment(playerid, ren_SelectionBackground[playerid], 2);
	PlayerTextDrawColor(playerid, ren_SelectionBackground[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, ren_SelectionBackground[playerid], 255);
	PlayerTextDrawBoxColor(playerid, ren_SelectionBackground[playerid], ren_SelectionBoxColor);
	PlayerTextDrawUseBox(playerid, ren_SelectionBackground[playerid], 1);
	PlayerTextDrawSetProportional(playerid, ren_SelectionBackground[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, ren_SelectionBackground[playerid], 0);
	
	// Header Text
	ren_SelectionHeader[playerid] = CreatePlayerTextDraw(playerid, 188.000000, 51.000000, "Header Text");
	PlayerTextDrawFont(playerid, ren_SelectionHeader[playerid], 0);
	PlayerTextDrawLetterSize(playerid, ren_SelectionHeader[playerid], 0.491665, 1.799998);
	PlayerTextDrawTextSize(playerid, ren_SelectionHeader[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, ren_SelectionHeader[playerid], 1);
	PlayerTextDrawSetShadow(playerid, ren_SelectionHeader[playerid], 0);
	PlayerTextDrawAlignment(playerid, ren_SelectionHeader[playerid], 1);
	PlayerTextDrawColor(playerid, ren_SelectionHeader[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, ren_SelectionHeader[playerid], 255);
	PlayerTextDrawBoxColor(playerid, ren_SelectionHeader[playerid], 50);
	PlayerTextDrawUseBox(playerid, ren_SelectionHeader[playerid], 0);
	PlayerTextDrawSetProportional(playerid, ren_SelectionHeader[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, ren_SelectionHeader[playerid], 0);

	// Page 
	ren_SelectionPage[playerid] = CreatePlayerTextDraw(playerid, 459.000000, 55.000000, "0/300");
	PlayerTextDrawFont(playerid, ren_SelectionPage[playerid], 1);
	PlayerTextDrawLetterSize(playerid, ren_SelectionPage[playerid], 0.287499, 1.200000);
	PlayerTextDrawTextSize(playerid, ren_SelectionPage[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, ren_SelectionPage[playerid], 1);
	PlayerTextDrawSetShadow(playerid, ren_SelectionPage[playerid], 0);
	PlayerTextDrawAlignment(playerid, ren_SelectionPage[playerid], 3);
	PlayerTextDrawColor(playerid, ren_SelectionPage[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, ren_SelectionPage[playerid], 255);
	PlayerTextDrawBoxColor(playerid, ren_SelectionPage[playerid], -206);
	PlayerTextDrawUseBox(playerid, ren_SelectionPage[playerid], 0);
	PlayerTextDrawSetProportional(playerid, ren_SelectionPage[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, ren_SelectionPage[playerid], 0);

	// Preview Model
	ren_SelectionPreviewModel[playerid] = CreatePlayerTextDraw(playerid, 221.000000, 78.000000, "Preview_Model");
	PlayerTextDrawFont(playerid, ren_SelectionPreviewModel[playerid], 5);
	PlayerTextDrawLetterSize(playerid, ren_SelectionPreviewModel[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ren_SelectionPreviewModel[playerid], 214.500000, 215.000000);
	PlayerTextDrawSetOutline(playerid, ren_SelectionPreviewModel[playerid], 0);
	PlayerTextDrawSetShadow(playerid, ren_SelectionPreviewModel[playerid], 0);
	PlayerTextDrawAlignment(playerid, ren_SelectionPreviewModel[playerid], 1);
	PlayerTextDrawColor(playerid, ren_SelectionPreviewModel[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, ren_SelectionPreviewModel[playerid], ren_SelectionModelColor);
	PlayerTextDrawBoxColor(playerid, ren_SelectionPreviewModel[playerid], 255);
	PlayerTextDrawUseBox(playerid, ren_SelectionPreviewModel[playerid], 0);
	PlayerTextDrawSetProportional(playerid, ren_SelectionPreviewModel[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, ren_SelectionPreviewModel[playerid], 0);
	PlayerTextDrawSetPreviewModel(playerid, ren_SelectionPreviewModel[playerid], -1);
	PlayerTextDrawSetPreviewRot(playerid, ren_SelectionPreviewModel[playerid], -10.000000, 0.000000, -20.000000, 1.000000);

	// Description
	ren_SelectionDescription[playerid] = CreatePlayerTextDraw(playerid, 225.000000, 282.000000, "Description");
	PlayerTextDrawFont(playerid, ren_SelectionDescription[playerid], 1);
	PlayerTextDrawLetterSize(playerid, ren_SelectionDescription[playerid], 0.208332, 0.800000);
	PlayerTextDrawTextSize(playerid, ren_SelectionDescription[playerid], 396.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, ren_SelectionDescription[playerid], 1);
	PlayerTextDrawSetShadow(playerid, ren_SelectionDescription[playerid], 0);
	PlayerTextDrawAlignment(playerid, ren_SelectionDescription[playerid], 1);
	PlayerTextDrawColor(playerid, ren_SelectionDescription[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, ren_SelectionDescription[playerid], 255);
	PlayerTextDrawBoxColor(playerid, ren_SelectionDescription[playerid], 50);
	PlayerTextDrawUseBox(playerid, ren_SelectionDescription[playerid], 0);
	PlayerTextDrawSetProportional(playerid, ren_SelectionDescription[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, ren_SelectionDescription[playerid], 0);

	// button 1
	ren_SelectionButton1[playerid] = CreatePlayerTextDraw(playerid, 292.000000, 311.000000, "Button 1");
	PlayerTextDrawFont(playerid, ren_SelectionButton1[playerid], 2);
	PlayerTextDrawLetterSize(playerid, ren_SelectionButton1[playerid], 0.258332, 1.750000);
	PlayerTextDrawTextSize(playerid, ren_SelectionButton1[playerid], 16.500000, 58.000000);
	PlayerTextDrawSetOutline(playerid, ren_SelectionButton1[playerid], 1);
	PlayerTextDrawSetShadow(playerid, ren_SelectionButton1[playerid], 0);
	PlayerTextDrawAlignment(playerid, ren_SelectionButton1[playerid], 2);
	PlayerTextDrawColor(playerid, ren_SelectionButton1[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, ren_SelectionButton1[playerid], 255);
	PlayerTextDrawBoxColor(playerid, ren_SelectionButton1[playerid], ren_SelectionButtonColor);
	PlayerTextDrawUseBox(playerid, ren_SelectionButton1[playerid], 1);
	PlayerTextDrawSetProportional(playerid, ren_SelectionButton1[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, ren_SelectionButton1[playerid], 1);

	// button 2
	ren_SelectionButton2[playerid] = CreatePlayerTextDraw(playerid, 361.000000, 311.000000, "Button 2");
	PlayerTextDrawFont(playerid, ren_SelectionButton2[playerid], 2);
	PlayerTextDrawLetterSize(playerid, ren_SelectionButton2[playerid], 0.258332, 1.750000);
	PlayerTextDrawTextSize(playerid, ren_SelectionButton2[playerid], 16.500000, 58.000000);
	PlayerTextDrawSetOutline(playerid, ren_SelectionButton2[playerid], 1);
	PlayerTextDrawSetShadow(playerid, ren_SelectionButton2[playerid], 0);
	PlayerTextDrawAlignment(playerid, ren_SelectionButton2[playerid], 2);
	PlayerTextDrawColor(playerid, ren_SelectionButton2[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, ren_SelectionButton2[playerid], 255);
	PlayerTextDrawBoxColor(playerid, ren_SelectionButton2[playerid], ren_SelectionButtonColor);
	PlayerTextDrawUseBox(playerid, ren_SelectionButton2[playerid], 1);
	PlayerTextDrawSetProportional(playerid, ren_SelectionButton2[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, ren_SelectionButton2[playerid], 1);

	// left button 
	ren_SelectionLeftButton[playerid] = CreatePlayerTextDraw(playerid, 226.000000, 311.000000, "<=");
	PlayerTextDrawFont(playerid, ren_SelectionLeftButton[playerid], 2);
	PlayerTextDrawLetterSize(playerid, ren_SelectionLeftButton[playerid], 0.258332, 1.750000);
	PlayerTextDrawTextSize(playerid, ren_SelectionLeftButton[playerid], 16.500000, 58.000000);
	PlayerTextDrawSetOutline(playerid, ren_SelectionLeftButton[playerid], 1);
	PlayerTextDrawSetShadow(playerid, ren_SelectionLeftButton[playerid], 0);
	PlayerTextDrawAlignment(playerid, ren_SelectionLeftButton[playerid], 2);
	PlayerTextDrawColor(playerid, ren_SelectionLeftButton[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, ren_SelectionLeftButton[playerid], 255);
	PlayerTextDrawBoxColor(playerid, ren_SelectionLeftButton[playerid], ren_SelectionButtonColor);
	PlayerTextDrawUseBox(playerid, ren_SelectionLeftButton[playerid], 1);
	PlayerTextDrawSetProportional(playerid, ren_SelectionLeftButton[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, ren_SelectionLeftButton[playerid], 1);

	// right button
	ren_SelectionRightButton[playerid] = CreatePlayerTextDraw(playerid, 426.000000, 311.000000, "=>");
	PlayerTextDrawFont(playerid, ren_SelectionRightButton[playerid], 2);
	PlayerTextDrawLetterSize(playerid, ren_SelectionRightButton[playerid], 0.258332, 1.750000);
	PlayerTextDrawTextSize(playerid, ren_SelectionRightButton[playerid], 16.500000, 58.000000);
	PlayerTextDrawSetOutline(playerid, ren_SelectionRightButton[playerid], 1);
	PlayerTextDrawSetShadow(playerid, ren_SelectionRightButton[playerid], 0);
	PlayerTextDrawAlignment(playerid, ren_SelectionRightButton[playerid], 2);
	PlayerTextDrawColor(playerid, ren_SelectionRightButton[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, ren_SelectionRightButton[playerid], 255);
	PlayerTextDrawBoxColor(playerid, ren_SelectionRightButton[playerid], ren_SelectionButtonColor);
	PlayerTextDrawUseBox(playerid, ren_SelectionRightButton[playerid], 1);
	PlayerTextDrawSetProportional(playerid, ren_SelectionRightButton[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, ren_SelectionRightButton[playerid], 1);
	return 1;
}
// ----------------------------------------------------------------------------------------------------
public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if(playertextid == ren_SelectionLeftButton[playerid])
	{
		if(ren_PlayerSelectionPage[playerid] == 0) return 1;

		ren_PlayerSelectionPage[playerid] --;
		new i = ren_PlayerSelectionPage[playerid], fmt[123];
		PlayerTextDrawSetPreviewModel(playerid,  ren_SelectionPreviewModel[playerid], ren_PlayerSelectionModel[playerid][i]);
		PlayerTextDrawSetString(playerid, ren_SelectionDescription[playerid], ren_PlayerSelectionDescription[playerid][i]);
		PlayerTextDrawSetPreviewVehCol(playerid, ren_SelectionPreviewModel[playerid], ren_PlayerSelectionVehColor[playerid][i][0], ren_PlayerSelectionVehColor[playerid][i][1]);

		format(fmt, sizeof(fmt), "%d/%d", ren_PlayerSelectionPage[playerid], ren_PlayerSelectionMaxPage[playerid]);
		PlayerTextDrawSetString(playerid, ren_SelectionPage[playerid], fmt);

		ren_ShowSelectionTextdraw(playerid);
	}
	if(playertextid == ren_SelectionRightButton[playerid])
	{
		if(ren_PlayerSelectionPage[playerid] == ren_PlayerSelectionMaxPage[playerid]) return 1;

		ren_PlayerSelectionPage[playerid] ++;
		new i = ren_PlayerSelectionPage[playerid], fmt[929];
		PlayerTextDrawSetPreviewModel(playerid,  ren_SelectionPreviewModel[playerid], ren_PlayerSelectionModel[playerid][i]);
		PlayerTextDrawSetString(playerid, ren_SelectionDescription[playerid], ren_PlayerSelectionDescription[playerid][i]);
		PlayerTextDrawSetPreviewVehCol(playerid, ren_SelectionPreviewModel[playerid], ren_PlayerSelectionVehColor[playerid][i][0], ren_PlayerSelectionVehColor[playerid][i][1]);

		format(fmt, sizeof(fmt), "%d/%d", ren_PlayerSelectionPage[playerid], ren_PlayerSelectionMaxPage[playerid]);
		PlayerTextDrawSetString(playerid, ren_SelectionPage[playerid], fmt);

		ren_ShowSelectionTextdraw(playerid);
	}
	if(playertextid == ren_SelectionButton1[playerid])
	{
		ren_DestroySelectionTextdraw(playerid);

		new response = 1, i = ren_PlayerSelectionPage[playerid];
		CallLocalFunction("OnSelectionResponse","iiii", playerid, response, ren_PLayerSelectionID[playerid], ren_PlayerSelectionModel[playerid][i]);
		ren_PlayerSelectionMaxPage[playerid] = -1;
		ren_PlayerSelectionShow[playerid] = false;
	}
	if(playertextid == ren_SelectionButton2[playerid])
	{
		ren_DestroySelectionTextdraw(playerid);

		new response = 0, i = ren_PlayerSelectionPage[playerid];
		CallLocalFunction("OnSelectionResponse","iiii", playerid, response, ren_PLayerSelectionID[playerid], ren_PlayerSelectionModel[playerid][i]);
		ren_PlayerSelectionMaxPage[playerid] = -1;
		ren_PlayerSelectionShow[playerid] = false;
	}
	return 1;
}

#if defined _ALS_OnPlayerClickPTextDraw
	#undef OnPlayerClickPTextDraw
#else
	#define _ALS_OnPlayerClickPTextDraw
#endif
#define OnPlayerClickPlayerTextDraw OnPlayerClickPTextdraw

forward OnPlayerClickPTextdraw(playerid, PlayerText:playertextid);

public OnPlayerConnect(playerid)
{
    ren_PlayerSelectionMaxPage[playerid] = -1;
	return 1;
}

#if defined _ALS_OnPConnect
	#undef OnPConnect
#else
	#define _ALS_OnPConnect
#endif
#define OnPlayerConnect OnPConnect

forward OnPConnect(playerid, PlayerText:playertextid);
