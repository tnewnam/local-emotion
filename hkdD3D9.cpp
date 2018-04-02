#pragma once
#include "stdafx.h"
using namespace std;

HWND GameHWND = NULL;
int WINAPI SetHWND();

bool showItems = false;
bool showDroppedItems = false;
bool showDead = true;
bool speedRun = false;
bool escapeUp = false;
bool comeBack = false;
bool noRecoil = true;
bool goW = false;
bool goS = false;
bool goA = false;
bool goD = false;
bool goUp = false;
bool goDown = false;
bool vibrate = false; //deprecated
bool vibrateDir = false; //deprecated
bool bulletMag = false;
bool showBulletTrails = true;
float warpSpeed = 1.0f;

bool itemSelect = true;
bool itemGrab = false;

int followID = -20;
bool highlight = false;
bool lock = false;
bool follow = false;
bool warpHere = false;

bool showCamera = false;
bool sCRunOnce = true;
bool sCToggle = true;
DEntity* tempMe;
DPlayer* tempPe;

int timeTest = 0;
bool pauseTime = false;
bool pTRunOnce = false;

bool filterOnly = false;

bool stupidBulletShit = false;
D3DXVECTOR3 bulletVelocity = { 0.f, 0.f, 0.f };

D3DCOLOR Red = D3DCOLOR_XRGB(255, 0, 0);
D3DCOLOR RedT = D3DCOLOR_ARGB(0xBB, 255, 0, 0);
D3DCOLOR Green = D3DCOLOR_XRGB(0, 255, 0);
D3DCOLOR GreenT = D3DCOLOR_ARGB(0xCC, 0, 255, 0);
D3DCOLOR GreenTT = D3DCOLOR_ARGB(0x44, 0, 255, 0);
D3DCOLOR Blue = D3DCOLOR_XRGB(0, 0, 255);
D3DCOLOR Cyan = D3DCOLOR_XRGB(0, 255, 255);
D3DCOLOR Black = D3DCOLOR_XRGB(1, 1, 1);
D3DCOLOR White = D3DCOLOR_XRGB(255, 255, 255);
D3DCOLOR Yellow = D3DCOLOR_XRGB(255, 255, 0);
D3DCOLOR LightYellow = D3DCOLOR_XRGB(240, 240, 0);
D3DCOLOR LightGrey = D3DCOLOR_XRGB(185, 200, 185);
D3DCOLOR Grey = D3DCOLOR_XRGB(171, 171, 171);
D3DCOLOR DarkGrey = D3DCOLOR_XRGB(84, 84, 84);
D3DCOLOR DarkerGrey = D3DCOLOR_XRGB(52, 52, 52);
D3DCOLOR Orange = D3DCOLOR_XRGB(225, 170, 0);
D3DCOLOR Magenta = D3DCOLOR_XRGB(255, 0, 255);
D3DCOLOR CyanBlue = D3DCOLOR_XRGB(0, 190, 255);
D3DCOLOR Salmon = D3DCOLOR_XRGB(255, 118, 118);
D3DCOLOR LightOrange = D3DCOLOR_XRGB(255, 180, 100);
D3DCOLOR LightGreen = D3DCOLOR_XRGB(212, 240, 100);
D3DCOLOR HeatherBlue = D3DCOLOR_XRGB(128, 159, 255);

char desiredItemsGuns[][30] = {
		{ "Mosin" },
		{ "Sporter" },
		{ "Shotgun" },
		{ "AK" }, 
		{ "Mag" },
		{ "mag" },
		{ "SKS" },
		{ "1911" },
		{ "M4A1" },
		{ "Long Range" },
		{ "Rnd" }
};

char desiredItemsAmmo[][30] = {
		{ "9mm" },
		{ ".22" },
		{ "7.62" },
		{ "5.56" },
		{ "00 " },
		{ "12 Gauge" },
		{ ".45" },
		{ ".357" }
};

char desiredItemsMisc[][30] = {
		{ "Gorka" },
		{ "First Aid" },
		{ "Morphine" },
		{ "High" },
		//{ "Epin" },
		{ "harcoal" }
};

char desiredItemsRare[][30] = {
		{ "PM73" },
		{ "Tent" },
		{ "bang" },
		{ "nade" },
		{ "PSO" },
		{ "MP5" },
		{ "AK74" },
		{ "AKS-74U" },
		{ "AK-74" },
		{ "Amphibia" },
		{ "Suppressor" }
};



template <typename T>
T Read(DWORD offset)
{
	return *(T*)(offset);
}



int Hooked_D3D9::GetDistance(D3DXVECTOR3 one, D3DXVECTOR3 two)
{
	float dx, dy, dz;
	char pad[] = "Distance";
	dx = one.x - two.x;
	dy = one.y - two.y;
	dz = one.z - two.z;

	return (int)abs(sqrt(dx*dx + dy*dy + dz*dz));
}

void Hooked_D3D9::Render()
{
	static bool RunOnce = true;
	if (RunOnce)
	{
		char pad2[] = "Render";
		RunOnce = false;
	}

	this->HandleInput();

	if (showItems)
	{
		this->RenderItemEsp();
	}

	if (showDroppedItems)
	{
		this->RenderDroppedItemEsp();
	}

	if (showDead)
	{
		this->RenderDeadEsp();
	}

	this->RenderEsp();

	this->RenderCoords();

	if (speedRun)
	{
		this->SpeedRun();
	}

	if (escapeUp)
	{
		this->EscapeUp();
	}

	if (comeBack)
	{
		this->ComeBack();
	}

	if ((goUp || goDown) && speedRun)
	{
		this->Elevate();
	}

	if (noRecoil)
	{
		this->NoRecoil();
	}
}

void Hooked_D3D9::HandleInput()
{
	int f1_press = GetAsyncKeyState(VK_F1)&LSB;
	int f4_press = GetAsyncKeyState(VK_F4)&LSB;
	int shift_press = GetAsyncKeyState(VK_LSHIFT)&LSB;
	int num8_press = GetAsyncKeyState(VK_NUMPAD8)&LSB;
	int num5_press = GetAsyncKeyState(VK_NUMPAD5)&LSB;
	int w_press = GetAsyncKeyState(0x57)&LSB;
	int s_press = GetAsyncKeyState(0x53)&LSB;
	int a_press = GetAsyncKeyState(0x41)&LSB;
	int d_press = GetAsyncKeyState(0x44)&LSB;
	int num2_press = GetAsyncKeyState(VK_NUMPAD2)&LSB;
	int num0_press = GetAsyncKeyState(VK_NUMPAD0)&LSB;
	int num4_press = GetAsyncKeyState(VK_NUMPAD4)&LSB; //adjust speed
	int num6_press = GetAsyncKeyState(VK_NUMPAD6)&LSB;
	int num3_press = GetAsyncKeyState(VK_NUMPAD3)&LSB;
	int num1_press = GetAsyncKeyState(VK_NUMPAD1)&LSB;
	int num7_press = GetAsyncKeyState(VK_NUMPAD7)&LSB;
	int num9_press = GetAsyncKeyState(VK_NUMPAD9)&LSB; //lock
	int numDel_press = GetAsyncKeyState(VK_DELETE)&LSB;
	int numDivide_press = GetAsyncKeyState(VK_DIVIDE)&LSB; //follow
	int numMultiply_press = GetAsyncKeyState(VK_MULTIPLY)&LSB;

	if (f1_press)
	{
		showItems = !showItems;
	}
	
	if (f4_press)
	{
		//showDroppedItems = !showDroppedItems;
		showDead = !showDead;
	}

	if (shift_press)
	{
		speedRun = !speedRun;
	}

	if (speedRun)
	{
		if (w_press)
		{
			goW = true;
		}
		else
		{
			goW = false;
		}

		if (s_press)
		{
			goS = true;
		}
		else
		{
			goS = false;
		}

		if (a_press)
		{
			goA = true;
		}
		else
		{
			goA = false;
		}

		if (d_press)
		{
			goD = true;
		}
		else
		{
			goD = false;
		}
	}

	if (num0_press) //Escape Up
	{
		comeBack = false;
		escapeUp = !escapeUp;
	}

	if (num2_press) //Come Back
	{
		escapeUp = false;
		comeBack = !comeBack;
	}

	if (num5_press)
	{
		goDown = true;
	}
	else
	{
		goDown = false;
	}

	if (num8_press)
	{
		goUp = true;
	}
	else
	{
		goUp = false;
	}

	if (num6_press)
	{
		warpSpeed += 0.1f;
		if (warpSpeed > 4) warpSpeed = 4.0f;
	}
	
	if (num4_press)
	{
		warpSpeed -= 0.1f;
		if (warpSpeed < 0.1f) warpSpeed = 0.1f;
	}

	if (num3_press)
	{
		//pTRunOnce = true;
		//pauseTime = !pauseTime;
		warpHere = !warpHere;
		//noRecoil = !noRecoil;
	}

	if (num7_press)
	{
		showCamera = !showCamera;
	}

	/*
	if (num1_press)
	{
		itemGrab = true;
	}
	else
	{
		itemGrab = false;
	}
	*/

	if (num1_press)
	{
		filterOnly = !filterOnly;
	}

	if (numDivide_press)
	{
		highlight = !highlight;
		lock = false;
	}

	if (numMultiply_press)
	{
		lock = !lock;
		highlight = false;
	}

	if (num9_press)
	{
		stupidBulletShit = !stupidBulletShit;
		//showBulletTrails = !showBulletTrails;
		//follow = !follow
	}
	if (numDel_press)
	{
		bulletMag = !bulletMag;
	}
}

void Hooked_D3D9::RenderCoords()
{
	//this->_DrawText(m_textFont, "Hooked", 10, 0, Green);
	if (dMain->dMain)
	{
		if (dMain->dMain->LocalPlayer)
		{
			if (dMain->dMain->LocalPlayer->dPlayer)
			{
				if (dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition)
				{
					char buf[60] = { 0 };
					D3DXVECTOR3 temp = dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords;
					sprintf_s(buf, "X: %d Y: %d", (int)temp.x, (int)(15360-temp.z));
					this->_DrawText(m_textFont, buf, 10, 10, Yellow);
				}
			}
			/*
			if (dMain->dMain->LocalPlayer->dPlayer->isDead)
			{
				escapeUp = true;
			}
			*/
		}
	}
}


void Hooked_D3D9::SpeedRun()
{
	if (dMain->dMain)
	{
		if (dMain->dMain->LocalPlayer)
		{
			if (dMain->dMain->LocalPlayer->dPlayer)
			{
				if (dTrans->dTrans)
				{
					if (dTrans->dTrans->dTransData)
					{
						if (dTrans->dTrans->dTransData->InvView_forward && dTrans->dTrans->dTransData->InvView_right)
						{
							char bufSpeed[40] = { 0 };
							sprintf_s(bufSpeed, "Speed: %2.1f", warpSpeed);
							this->_DrawText(m_textFont, bufSpeed, 120, 10, Red);

							dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVelocity1.y = 0;
							//dMain->dMain->LocalPlayer->dPlayer->landContact = 1;
							dMain->dMain->LocalPlayer->dPlayer->isStopped = 1;

							if (vibrate && !dMain->dMain->LocalPlayer->dPlayer->landContact)
							{
								this->_DrawText(m_textFont, "Vibrate", 120, 30, Red);
								if (vibrateDir)
								{
									dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords.y += -0.01f;
									vibrateDir = false;
								}
								else
								{
									dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords.y += 0.01f;
									vibrateDir = true;
								}
							}
						
							if (goW)
							{
								dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords += dTrans->dTrans->dTransData->InvView_forward * warpSpeed;
							}
							if (goS)
							{
								dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords += dTrans->dTrans->dTransData->InvView_forward * -warpSpeed;
							}
							if (goA)
							{
								dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords += dTrans->dTrans->dTransData->InvView_right * -warpSpeed;
							}
							if (goD)
							{
								dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords += dTrans->dTrans->dTransData->InvView_right * warpSpeed;
							}
						}
					}
				}
				
			}
		}
	}
}

void Hooked_D3D9::EscapeUp()
{
	_DrawText(m_textFont, "Escaping!", 200, 10, Red);
	if (dMain->dMain)
	{
		if (dMain->dMain->LocalPlayer)
		{
			if (dMain->dMain->LocalPlayer->dPlayer)
			{
				dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords.y = 2000;
			}
		}
	}
}

void Hooked_D3D9::ComeBack()
{
	_DrawText(m_textFont, "Coming Back", 200, 20, Red);
	if (dMain->dMain)
	{
		if (dMain->dMain->LocalPlayer)
		{
			if (dMain->dMain->LocalPlayer->dPlayer)
			{
				dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVelocity1 = { 0, 0, 0 };
				dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->yVelocity2 = 0;

				dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords.y = 0;
			}
		}
	}
}

void Hooked_D3D9::Elevate()
{
	if (dMain->dMain)
	{
		if (dMain->dMain->LocalPlayer)
		{
			if (dMain->dMain->LocalPlayer->dPlayer)
			{
				if (dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition)
				{
					if (goUp)
					{
						dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords.y += 1.0f;
					}
					if (goDown)
					{
						dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords.y += -1.0f;
					}
				}
			}
		}
	}
}

void Hooked_D3D9::NoRecoil()
{
	_DrawText(m_textFont, "No Recoil", 120, 20, Red);
	if (dMain->dMain)
	{
		if (dMain->dMain->LocalPlayer)
		{
			if (dMain->dMain->LocalPlayer->dPlayer)
			{
				dMain->dMain->LocalPlayer->dPlayer->recoil = 0.0f;
				dMain->dMain->LocalPlayer->dPlayer->fatigue_diff = 0.0f;
				dMain->dMain->LocalPlayer->dPlayer->fatigue = 1.0f;
			}
		}
	}
}

void Hooked_D3D9::RenderEsp()
{
	if (dScoreboard)
	{
		if (dScoreboard->dScoreboard)
		{
			char buf[40] = { 0 };
			sprintf_s(buf, "Scoreboard Size: %d", dScoreboard->dScoreboard->iScoreBoardSize);
			_DrawText(m_textFont, buf, 10, 20, Grey);
		}
	}

	
	if (dMain) //BULLET TRAILS
	{
		char buf11[40] = { 0 };
		if (dMain->dMain)
		{
			if (showBulletTrails)
			{
				_DrawText(m_textFont, "Trails", 280, 10, Red);
			}
			
	
			if (dMain->dMain->BulletTable && dMain->dMain->BulletTableSize && showBulletTrails)
			{
				for (size_t i = 0; i < dMain->dMain->BulletTableSize; i++)
				{
					DDroppedItemTable* bMyData = (DDroppedItemTable*)&dMain->dMain->BulletTable[i];
					if (bMyData)
					{
						if (bMyData->dItem)
						{
							if (bMyData->dItem->dItemPosition)
							{
								if (bMyData->dItem->dItemPosition->dVecPositionCoords)
								{
									D3DXVECTOR3 drawPos = dTrans->W2S(bMyData->dItem->dItemPosition->dVecPositionCoords);
									if (drawPos.z > 0.1f)
									{
										D3DXVECTOR3 abc = bMyData->dItem->dItemPosition->dVecPositionCoords + dTrans->dTrans->dTransData->InvView_up * 0.1f;
										D3DXVECTOR3 out = dTrans->W2S(abc);

										int he = (int)(drawPos.y - out.y);
										if (he < 2) he = 2;
										int wi = (int)(he);

										this->_DrawRect(m_rectLine, drawPos.x - (wi / 2), drawPos.y, (float)wi, (float)(-he), Magenta);
									}
								}
							}
						}
					}
				}
			}

			//START BULLET COLLECTOR
			if (stupidBulletShit)
			{
				sprintf_s(buf11, "Collect: %d", dMain->dMain->BulletTableSize);
				_DrawText(m_textFont, buf11, 280, 20, Red);

				if (dMain->dMain->BulletTable && dMain->dMain->BulletTableSize)
				{
					for (size_t i = 0; i < dMain->dMain->BulletTableSize; i++)
					{
						DDroppedItemTable* bMyData = (DDroppedItemTable*)&dMain->dMain->BulletTable[i];

						if (bMyData)
						{
							if (bMyData->dItem)
							{
								if (bMyData->dItem->dItemPosition)
								{
									if (bMyData->dItem->dItemPosition->dVecPositionCoords)
									{
										bulletVelocity = bMyData->dItem->dItemPosition->dVelocity1;
										bMyData->dItem->dItemPosition->dVelocity1 = { 0.f, 0.f, 0.f };
										bMyData->dItem->dBulletTimeAlive = 100.f;
										bMyData->dItem->dBulletPosition = dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dHeadPositionCoords + dTrans->dTrans->dTransData->InvView_up + dTrans->dTrans->dTransData->InvView_forward;
									}
								}
							}
						}
					}
				}
			}
			//END BULLET COLLECTOR
		}
	}
	

	int my_pID = -10;
	D3DXVECTOR3 myPos;
	float my_dY;
	float my_dX;

	if (dMain->dMain->LocalPlayer)
	{
		if (dMain->dMain->LocalPlayer->dPlayer)
		{
			if (dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition)
			{
				myPos = dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords;
				my_dY = dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dY;
				my_dX = dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dX;
				my_pID = dMain->dMain->LocalPlayer->dPlayer->pID;
				this->_DrawLine(m_rectLine, 40, 70, 40 - (my_dX * 25), 70 + (my_dY * 25), White);
				this->_DrawLine(m_rectLine, 40, 70, 40 + (my_dX * 25), 70 - (my_dY * 25), Red);

				//char buf11[40] = { 0 };
				//sprintf_s(buf11, "%d", my_pID);
				//_DrawText(m_textFont, buf11, 1000, (float)(10), Green);
			}
		}
	}


	if (dMain->dMain->dObjects)
	{
		if (dMain->dMain->dObjects->iTableSize && dMain->dMain->dObjects->dObjectList)
		{
			for (size_t i = 0; i < dMain->dMain->dObjects->iTableSize; i++)
			{
				DObjectList *pMyData = (DObjectList*)&dMain->dMain->dObjects->dObjectList[i];
				if (pMyData)
				{
					if (pMyData->dEntity)
					{
						if (pMyData->dEntity->dPlayer)
						{
							/*
							char buf11[40] = { 0 };
							sprintf_s(buf11, "%d", pMyData->dEntity->dPlayer->pID);
							_DrawText(m_textFont, buf11, 1150, (float)(10 * i), Cyan);

							sprintf_s(buf11, "%c", pMyData->dEntity->dPlayer->dObjectClass->dObjectName->iName[0]);
							_DrawText(m_textFont, buf11, 1250, (float)(10 * i), Cyan);
							*/

							if (pMyData->dEntity->dPlayer->dPlayerPosition)
							{
								D3DXVECTOR3 enemyPos = pMyData->dEntity->dPlayer->dPlayerPosition->dVecPositionCoords;
								D3DXVECTOR3 drawPos = dTrans->W2S(enemyPos);

								float e_dY = pMyData->dEntity->dPlayer->dPlayerPosition->dY;
								float e_dX = pMyData->dEntity->dPlayer->dPlayerPosition->dX;

								int e_pID = pMyData->dEntity->dPlayer->pID;
								char s_or_z = pMyData->dEntity->dPlayer->dObjectClass->dObjectName->iName[0];


								if (dMain->dMain)
								{
									if (dMain->dMain->LocalPlayer)
									{
										if (dMain->dMain->LocalPlayer->dPlayer)
										{
											if (drawPos.z > 0.1f && dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition)
											{
												D3DXVECTOR3 abc = D3DXVECTOR3(enemyPos.x - 0.5f, enemyPos.y + 1.8f, enemyPos.z);
												D3DXVECTOR3 out = dTrans->W2S(abc);

												int he = (int)(drawPos.y - out.y);
												int wi = (int)(he / 2.5f);

												if (s_or_z != 'z' && e_pID != my_pID) //not zombie and not me -old ->(e_pID != 1 && e_pID != my_pID)
												{
													//begin vector math

													float diffX = -myPos.x + enemyPos.x;
													float diffY = -myPos.z + enemyPos.z;


													D3DXVECTOR2 tDd = D3DXVECTOR2(diffX, diffY);
													D3DXVECTOR2 De = D3DXVECTOR2(e_dX, e_dY);
													D3DXVECTOR2 Dd;
													D3DXVec2Normalize(&Dd, &tDd);

													float aoutX;
													float aoutY;

													float dotP = acos(D3DXVec2Dot(&Dd, &De));
													float crossP = D3DXVec2CCW(&Dd, &De);
													if (crossP > 0)
													{
														aoutX = sin(dotP);
														aoutY = cos(dotP);
													}
													else
													{
														aoutX = -sin(dotP);
														aoutY = cos(dotP);
													}
													//end vector math

													//++++++++++++++LOGIC PART
													char outbuf[120] = { 0 };
													char distbuf[60] = { 0 };
													int distance = this->GetDistance(enemyPos, myPos);
													sprintf_s(distbuf, " [%d] ", distance);
													
													
													if (dScoreboard->dScoreboard)
													{
														int iSBSize = dScoreboard->dScoreboard->iScoreBoardSize;
														for (int j = 0; j < iSBSize; j++)
														{
															DObjectClassName* sMyData = (DObjectClassName*)(*(PDWORD)((DWORD)dScoreboard->dScoreboard->dSObjectClassName + (j * 0xE8) + 0x80));
															int s_pID = *(PDWORD)((DWORD)dScoreboard->dScoreboard->dSObjectClassName + j * 0xE8 + 0x4);

															if (s_pID == e_pID)
															{
																//readstring

																int nSize = sMyData->iNameLength;
																char namebuf[40] = { 0 };
																int m;
																for (m = 0; m < nSize - 1; m++)
																{
																	namebuf[m] = sMyData->iName[m];
																}
																namebuf[m] = '\0';

																//endreadstring
																strcpy_s(outbuf, namebuf);
															}
														}
														strcat_s(outbuf, distbuf);
													}
													else
													{
														strcpy_s(outbuf, distbuf);
													}
													
													//Weapon
													if (pMyData->dEntity->dPlayer->dWeapon)
													{
														if (pMyData->dEntity->dPlayer->dWeapon->dPlayer)
														{
															if (pMyData->dEntity->dPlayer->dWeapon->dPlayer->dObjectClass)
															{
																if (pMyData->dEntity->dPlayer->dWeapon->dPlayer->dObjectClass->dObjectCleanName)
																{
																	if (pMyData->dEntity->dPlayer->dWeapon->dPlayer->dObjectClass->dObjectCleanName->iNameLength && pMyData->dEntity->dPlayer->dWeapon->dPlayer->dObjectClass->dObjectCleanName->iName)
																	{
																		char weapbuf[40] = { 0 };
																		int g;
																		for (g = 0; g < pMyData->dEntity->dPlayer->dWeapon->dPlayer->dObjectClass->dObjectCleanName->iNameLength - 1; g++)
																		{
																			weapbuf[g] = pMyData->dEntity->dPlayer->dWeapon->dPlayer->dObjectClass->dObjectCleanName->iName[g];
																		}
																		weapbuf[g] = '\0';

																		strcat_s(outbuf, weapbuf);
																	}
																}
															}
														}
													}
													//END Weapon
													
													
													if (e_pID > 1)
													{

														this->_DrawRect(m_rectLine, drawPos.x - (wi / 2), drawPos.y, (float)wi, (float)(-he), GreenTT);
														//this->_DrawLine(m_rectLine, drawPos.x, out.y-20, (drawPos.x) - (aoutX * 30), (out.y - 20) - (aoutY * 30), Red);
														this->_DrawLine(m_rectLine, drawPos.x, out.y, (drawPos.x) - (aoutX * 30), (out.y) - (aoutY * 30), RedT);

														D3DXVECTOR3 headPos = pMyData->dEntity->dPlayer->dPlayerPosition->dHeadPositionCoords;
														D3DXVECTOR3 drawHeadPos = dTrans->W2S(headPos);

														if (drawHeadPos.z > 0.1f)
														{
															this->_DrawLine(m_rectLine, drawHeadPos.x, drawHeadPos.y, drawHeadPos.x, drawHeadPos.y + 2, Magenta);
														}

														D3DXCOLOR dispColor = Green;

														if (strlen(outbuf) > 6)
														{
															if (outbuf[0] == '[' &&
																outbuf[1] == 'W' &&
																outbuf[2] == 'T' &&
																outbuf[3] == 'W' &&
																outbuf[4] == '?' &&
																outbuf[5] == ']')
															{
																dispColor = CyanBlue;
															}
														}

														if (dTrans->dTrans) //highlight,follow, lock
														{
															if (highlight)
															{
																sCRunOnce = true;
																_DrawText(m_textFont, "Highlight", 200, 10, Red);
																_DrawRect(m_rectLine, dTrans->dTrans->dTransData->ViewPortMatrix3.x - 1, dTrans->dTrans->dTransData->ViewPortMatrix3.y - 1, 3, 3, Magenta);
																if (dTrans->dTrans->dTransData)
																{
																	if (drawHeadPos.x > dTrans->dTrans->dTransData->ViewPortMatrix3.x - 12 &&
																		drawHeadPos.x < dTrans->dTrans->dTransData->ViewPortMatrix3.x + 12 &&
																		drawHeadPos.y > dTrans->dTrans->dTransData->ViewPortMatrix3.y - 12 &&
																		drawHeadPos.y < dTrans->dTrans->dTransData->ViewPortMatrix3.y + 12)
																	{
																		dispColor = Cyan;
																		followID = pMyData->dEntity->dPlayer->pID;
																	}
																}
															}

															if (lock)
															{
																_DrawText(m_textFont, "Lock", 200, 20, Red);
																if (followID == pMyData->dEntity->dPlayer->pID)
																{
																	dispColor = Cyan;

																	//START BULLET MAG
																	if (bulletMag) //delete
																	{
																		dispColor = Red;

																		if (dMain->dMain->BulletTable && dMain->dMain->BulletTableSize)
																		{
																			for (size_t i = 0; i < dMain->dMain->BulletTableSize; i++)
																			{
																				DDroppedItemTable* bMyData = (DDroppedItemTable*)&dMain->dMain->BulletTable[i];

																				if (bMyData)
																				{
																					if (bMyData->dItem)
																					{
																						if (bMyData->dItem->dItemPosition)
																						{
																							if (bMyData->dItem->dItemPosition->dVecPositionCoords)
																							{
																								if (stupidBulletShit)
																								{
																									bMyData->dItem->dItemPosition->dVelocity1 = bulletVelocity;
																								}
																								//bMyData->dItem->dItemPosition->dVecPositionCoords = pMyData->dEntity->dPlayer->dPlayerPosition->dHeadPositionCoords;
																								bMyData->dItem->dBulletPosition = pMyData->dEntity->dPlayer->dPlayerPosition->dHeadPositionCoords;
																							}
																						}
																					}
																				}
																			}
																		}
																		stupidBulletShit = false;
																	}
																	//END BULLET MAG

																}
															}
														} //end highlight follow lock

														this->_DrawText(m_textFont, outbuf, drawPos.x - 20, out.y - 12, dispColor);
													}
													else
													{
														this->_DrawText(m_textFont, outbuf, drawPos.x - 10, out.y - 12, Salmon); //used to be out not drawpos
													}
													
													
													//++++++++++++++END LOGIC
												}
											}

											if (follow && followID == pMyData->dEntity->dPlayer->pID)
											{
												speedRun = true;
												_DrawText(m_textFont, "Follow", 200, 30, Red);

												dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords.x = pMyData->dEntity->dPlayer->dPlayerPosition->dVecPositionCoords.x - pMyData->dEntity->dPlayer->dPlayerPosition->dX;
												dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords.y = pMyData->dEntity->dPlayer->dPlayerPosition->dVecPositionCoords.y;
												dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords.z = pMyData->dEntity->dPlayer->dPlayerPosition->dVecPositionCoords.z - pMyData->dEntity->dPlayer->dPlayerPosition->dY;

												if (goW || goA || goS || goD)
												{
													follow = false;
												}
												//dMain->dMain->LocalPlayer = pMyData->dEntity;
												//dMain->dMain->RealLocalPlayer = pMyData->dEntity; //holy shit this actually works to "follow" their camera.
												//dMain->dMain->RealLocalPlayer2 = pMyData->dEntity;

												//dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dX = pMyData->dEntity->dPlayer->dPlayerPosition->dX;
												//dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dY = pMyData->dEntity->dPlayer->dPlayerPosition->dY;

											}

											if (warpHere && followID == pMyData->dEntity->dPlayer->pID)
											{
												_DrawText(m_textFont, "warpHere", 200, 40, Red);

												pMyData->dEntity->dPlayer->dPlayerPosition->dVecPositionCoords = {
													dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords.x,
													dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords.y,
													dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords.z + 2.f 
												};
				
												pMyData->dEntity->dPlayer->isStopped = 1;
												pMyData->dEntity->dPlayer->dPlayerPosition->dVelocity1 = { 0.f, 0.f, 0.f };
											}

											if (showCamera)
											{
												highlight = false;
												if (sCRunOnce)
												{
													sCToggle = true;
													tempMe = dMain->dMain->LocalPlayer;
													//tempPe = dMain->dMain->LocalPlayer->dPlayer;
													sCRunOnce = false;
												}

												if (followID == pMyData->dEntity->dPlayer->pID)
												{
													if (sCToggle)
													{
														dMain->dMain->LocalPlayer = pMyData->dEntity;
														//dMain->dMain->LocalPlayer->dPlayer = pMyData->dEntity->dPlayer;
														sCToggle = false;
													}
												}
											}
											else
											{
												if (tempMe && !sCToggle)
												{
													dMain->dMain->LocalPlayer = tempMe;
													//dMain->dMain->LocalPlayer->dPlayer = tempPe;
													sCToggle = true;
												}
												sCRunOnce = true; //do I need this?
											}
											//end showcamera
										}
									}
								}
							}
						}
					}
				} 
			}
		}
	}
	
}

void Hooked_D3D9::RenderItemEsp()
{
	char bufff[40] = { 0 };
	this->_DrawText(m_textFont, "F1", 10, 30, Yellow);

	
	if (dMain->dMain)
	{
		if (dMain->dMain->ItemTable)
		{
			if (dMain->dMain->ItemTableSize)
			{
				size_t counter = 0;
				for (size_t i = 0; counter < dMain->dMain->ItemTableSize; i++)
				{
					DItemTable* iMyData = (DItemTable*)&dMain->dMain->ItemTable[i];

					if (iMyData && dMain->dMain)
					{
						if (iMyData->dValid == 1 && iMyData->dItem && dMain->dMain->LocalPlayer)
						{
							counter++;

							/*
							sprintf_s(bufff, "%4d:", i);
							this->_DrawText(m_textFont, bufff, 1260, 10.f*counter, Yellow);

							sprintf_s(bufff, "%x", iMyData);
							this->_DrawText(m_textFont, bufff, 1300, 10.f*counter, Cyan);

							sprintf_s(bufff, "%d, %x, %x", iMyData->dValid, iMyData->dItem, iMyData->dItem2);
							this->_DrawText(m_textFont, bufff, 1350, 10.f*counter, Cyan);

							sprintf_s(bufff, "%x / %x", iMyData->dItem->dItemPosition, iMyData->dItem->dItemPosition);
							this->_DrawText(m_textFont, bufff, 1450, 10.f*counter, Cyan);
							*/

							
							if (iMyData->dItem->dItemPosition && dMain->dMain->LocalPlayer->dPlayer)
							{

								D3DXVECTOR3 itemPos = iMyData->dItem->dItemPosition->dVecPositionCoords;
								D3DXVECTOR3 myPos = dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords;
								int distance = this->GetDistance(itemPos, myPos);

								int showDistance = 50; //filtering
								if (filterOnly)
									showDistance = 400;
								
								if (distance <= showDistance && iMyData->dItem->dObjectClass)
								{
									D3DXVECTOR3 drawPos = dTrans->W2S(itemPos);

									if (drawPos.z > 0.1f && iMyData->dItem->dObjectClass->dObjectCleanName)
									{
										D3DXVECTOR3 abc = itemPos + dTrans->dTrans->dTransData->InvView_up * 0.1f;
										D3DXVECTOR3 out = dTrans->W2S(abc);

										int he = (int)(drawPos.y - out.y);
										int wi = (int)(he*1.5f);

										char distbuf[10] = { 0 };
										sprintf_s(distbuf, " [%d]", distance);

										char heightbuf[10] = { 0 };
										sprintf_s(heightbuf, " (%d)", (int)(itemPos.y - myPos.y));
										
										int nSize = iMyData->dItem->dObjectClass->dObjectCleanName->iNameLength;
										if (nSize > 30)
											nSize = 30;

										char namebuf[100] = { 0 };
										int m;
										for (m = 0; m < nSize - 1; m++)
										{
											namebuf[m] = iMyData->dItem->dObjectClass->dObjectCleanName->iName[m];
										}
										namebuf[m] = '\0';

										strcat_s(namebuf, distbuf);
										strcat_s(namebuf, heightbuf);

										D3DCOLOR itemColor;
										itemColor = Yellow;
										bool showOnly = false; //filtering

										for (int p = 0; p < sizeof(desiredItemsAmmo) / sizeof(desiredItemsAmmo[0]); p++)
										{
											char * test = strstr(namebuf, desiredItemsAmmo[p]);
											if (test)
											{
												itemColor = Orange;
												showOnly = true;
												break;
											}
										}

										for (int p = 0; p < sizeof(desiredItemsGuns) / sizeof(desiredItemsGuns[0]); p++)
										{
											char * test = strstr(namebuf, desiredItemsGuns[p]);
											if (test)
											{
												itemColor = LightOrange;
												showOnly = true;
												break;
											}
										}

										for (int p = 0; p < sizeof(desiredItemsMisc) / sizeof(desiredItemsMisc[0]); p++)
										{
											char * test = strstr(namebuf, desiredItemsMisc[p]);
											if (test)
											{
												itemColor = LightGreen;
												showOnly = true;
												break;
											}
										}

										for (int p = 0; p < sizeof(desiredItemsRare) / sizeof(desiredItemsRare[0]); p++)
										{
											char * test = strstr(namebuf, desiredItemsRare[p]);
											if (test)
											{
												itemColor = HeatherBlue;
												showOnly = true;
												break;
											}
										}

										if (dTrans->dTrans && itemSelect)
										{
											if (dTrans->dTrans->dTransData)
											{
												if (drawPos.x > dTrans->dTrans->dTransData->ViewPortMatrix3.x - 8 &&
													drawPos.x < dTrans->dTrans->dTransData->ViewPortMatrix3.x + 8 &&
													drawPos.y > dTrans->dTrans->dTransData->ViewPortMatrix3.y - 8 &&
													drawPos.y < dTrans->dTrans->dTransData->ViewPortMatrix3.y + 8)
												{
													itemColor = Red;
													if (itemGrab)
													{
														iMyData->dItem->dItemPosition->dVecPositionCoords = dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords;
														iMyData->dItem->dItemPosition->dVecPositionCoords.y += 0.1f;
													}
												}
											}
										}


										if (!filterOnly || showOnly)
										{
											this->_DrawRect(m_rectLine, drawPos.x - (wi / 2), drawPos.y, (float)wi, (float)(-he), itemColor);
											this->_DrawText(m_textFont, namebuf, drawPos.x - 10, drawPos.y - 12, itemColor); //used to be out not drawpos
										}
										//END
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void Hooked_D3D9::RenderDroppedItemEsp()
{
	/*
	this->_DrawText(m_textFont, "F4", 10, 40, Yellow);
	
	if (dMain->dMain)
	{
		if (dMain->dMain->DroppedItemTable)
		{
			if (dMain->dMain->DroppedItemTableSize)
			{
				for (size_t i = 0; i < dMain->dMain->DroppedItemTableSize; i++)
				{
					DItemTable* iMyData = (DItemTable*)&dMain->dMain->DroppedItemTable[i];
					{
						if (iMyData && dMain->dMain)
						{
							if (iMyData->dItem && dMain->dMain->LocalPlayer)
							{
								if (iMyData->dItem->dObjectClass && iMyData->dItem->dPlayerPosition && dMain->dMain->LocalPlayer->dPlayer)
								{
									D3DXVECTOR3 itemPos = iMyData->dItem->dPlayerPosition->dVecPositionCoords;
									D3DXVECTOR3 myPos = dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords;
									int distance = this->GetDistance(itemPos, myPos);

									if (distance <= 130 && iMyData->dItem->dObjectClass->dObjectClassName)
									{
										D3DXVECTOR3 drawPos = dTrans->W2S(itemPos);

										if (drawPos.z > 0.1f && iMyData->dItem->dObjectClass->dObjectClassName->iName)
										{
											D3DXVECTOR3 abc = itemPos + dTrans->dTrans->dTransData->InvView_up * 0.1f;
											D3DXVECTOR3 out = dTrans->W2S(abc);

											int he = (int)(drawPos.y - out.y);
											int wi = (int)(he*1.5f);

											char distbuf[30] = { 0 };
											sprintf_s(distbuf, " [%d]", distance);

											char heightbuf[10] = { 0 };
											sprintf_s(heightbuf, " (%d)", (int)(itemPos.y - myPos.y));

											strcat_s(distbuf, heightbuf);

											int nSize = iMyData->dItem->dObjectClass->dObjectClassName->iNameLength;
											if (nSize > 25)
												nSize = 25;

											char namebuf[100] = { 0 };
											int m;
											for (m = 0; m < nSize - 1; m++)
											{
												namebuf[m] = iMyData->dItem->dObjectClass->dObjectClassName->iName[m];
											}
											namebuf[m] = '\0';
											strcat_s(namebuf, distbuf);

											D3DCOLOR itemColor;
											if (distance < 10)
												itemColor = Cyan;
											else
												itemColor = White;

											this->_DrawRect(m_rectLine, drawPos.x - (wi / 2), drawPos.y, (float)wi, (float)(-he), itemColor);
											this->_DrawText(m_textFont, namebuf, drawPos.x - 10, drawPos.y - 12, itemColor); //used to be out not drawpos

										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	if (dMain->dMain)
	{
		if (dMain->dMain->FarDroppedItemTable)
		{
			if (dMain->dMain->FarDroppedItemTableSize)
			{
				for (size_t i = 0; i < dMain->dMain->FarDroppedItemTableSize; i++)
				{
					DItemTable* iMyData = (DItemTable*)&dMain->dMain->FarDroppedItemTable[i];
					{
						if (iMyData && dMain->dMain)
						{
							if (iMyData->dItem && dMain->dMain->LocalPlayer)
							{
								if (iMyData->dItem->dObjectClass && iMyData->dItem->dPlayerPosition && dMain->dMain->LocalPlayer->dPlayer)
								{
									D3DXVECTOR3 itemPos = iMyData->dItem->dPlayerPosition->dVecPositionCoords;
									D3DXVECTOR3 myPos = dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords;
									int distance = this->GetDistance(itemPos, myPos);

									if (iMyData->dItem->dObjectClass->dObjectClassName)
									{
										D3DXVECTOR3 drawPos = dTrans->W2S(itemPos);

										if (drawPos.z > 0.1f && iMyData->dItem->dObjectClass->dObjectClassName->iName)
										{
											D3DXVECTOR3 abc = itemPos + dTrans->dTrans->dTransData->InvView_up * 0.1f;
											D3DXVECTOR3 out = dTrans->W2S(abc);

											int he = (int)(drawPos.y - out.y);
											int wi = (int)(he*1.5f);

											char distbuf[30] = { 0 };

											sprintf_s(distbuf, " [%d]", distance);

											char heightbuf[10] = { 0 };
											sprintf_s(heightbuf, " (%d)", (int)(itemPos.y - myPos.y));

											strcat_s(distbuf, heightbuf);

											int nSize = iMyData->dItem->dObjectClass->dObjectClassName->iNameLength;
											if (nSize > 25)
												nSize = 25;
											char namebuf[100] = { 0 };
											int m;
											for (m = 0; m < nSize - 1; m++)
											{
												namebuf[m] = iMyData->dItem->dObjectClass->dObjectClassName->iName[m];
											}
											namebuf[m] = '\0';
											strcat_s(namebuf, distbuf);

											D3DCOLOR itemColor = Grey;

											char * test1 = strstr(namebuf, "Crashed");
											char * test2 = strstr(namebuf, "Wreck");
											if (test1 || test2)
											{
												itemColor = Salmon;
											}

											this->_DrawRect(m_rectLine, drawPos.x - (wi / 2), drawPos.y, (float)wi, (float)(-he), itemColor);
											this->_DrawText(m_textFont, namebuf, drawPos.x - 10, drawPos.y - 12, itemColor); //used to be out not drawpos

										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	*/
}

void Hooked_D3D9::RenderDeadEsp()
{
	this->_DrawText(m_textFont, "F4", 10, 40, Yellow);
	//Near
	if (dMain->dMain)
	{
		if (dMain->dMain->AnimalTable && dMain->dMain->AnimalTableSize)
		{
			for (size_t i = 0; i < dMain->dMain->AnimalTableSize; i++)
			{
				DDroppedItemTable* aMyData = (DDroppedItemTable*)&dMain->dMain->AnimalTable[i];
				{
					if (aMyData && dMain->dMain)
					{
						if (aMyData->dItem && dMain->dMain->LocalPlayer)
						{
							if (aMyData->dItem->dObjectClass && aMyData->dItem->dItemPosition && dMain->dMain->LocalPlayer->dPlayer)
							{
								D3DXVECTOR3 itemPos = aMyData->dItem->dItemPosition->dVecPositionCoords;
								D3DXVECTOR3 myPos = dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords;
								int distance = this->GetDistance(itemPos, myPos);

								if (aMyData->dItem->dObjectClass->dObjectClassName)
								{
									D3DXVECTOR3 drawPos = dTrans->W2S(itemPos);

									if (drawPos.z > 0.1f && aMyData->dItem->dObjectClass->dObjectClassName->iName[0] == 'S' && aMyData->dItem->isDead)
									{
										D3DXVECTOR3 abc = itemPos + dTrans->dTrans->dTransData->InvView_up * 0.1f;
										D3DXVECTOR3 out = dTrans->W2S(abc);

										int he = (int)(drawPos.y - out.y);
										int wi = (int)(he*2.f);

										char distbuf[30] = { 0 };

										sprintf_s(distbuf, " [%d]", distance);


										int nSize = aMyData->dItem->dObjectClass->dObjectClassName->iNameLength;
										if (nSize > 25)
											nSize = 25;

										char namebuf[100] = { 0 };
										//comment out for no names
										/*
										int m;
										for (m = 0; m < nSize - 1; m++)
										{
											namebuf[m] = aMyData->dItem->dObjectClass->dObjectClassName->iName[m];
										}
										namebuf[m] = '\0';
										*/
										//end
										strcat_s(namebuf, distbuf);


										D3DCOLOR itemColor = LightGrey;
										//this too
										//this->_DrawRect(m_rectLine, drawPos.x - (wi / 2), drawPos.y, (float)wi, (float)(-he), itemColor);
										this->_DrawText(m_textFont, namebuf, drawPos.x - 10, drawPos.y - 12, itemColor); //used to be out not drawpos

									}
								}
							}
						}
					}
				}
			}
		}
	}
	//Far

	if (dMain->dMain)
	{
		if (dMain->dMain->FarAnimalTable && dMain->dMain->FarAnimalTableSize)
		{
			for (size_t i = 0; i < dMain->dMain->FarAnimalTableSize; i++)
			{
				DDroppedItemTable* faMyData = (DDroppedItemTable*)&dMain->dMain->FarAnimalTable[i];
				{
					if (faMyData && dMain->dMain)
					{
						if (faMyData->dItem && dMain->dMain->LocalPlayer)
						{
							if (faMyData->dItem->dObjectClass && faMyData->dItem->dItemPosition && dMain->dMain->LocalPlayer->dPlayer)
							{
								D3DXVECTOR3 itemPos = faMyData->dItem->dItemPosition->dVecPositionCoords;
								D3DXVECTOR3 myPos = dMain->dMain->LocalPlayer->dPlayer->dPlayerPosition->dVecPositionCoords;
								int distance = this->GetDistance(itemPos, myPos);

								if (faMyData->dItem->dObjectClass->dObjectClassName)
								{
									D3DXVECTOR3 drawPos = dTrans->W2S(itemPos);

									if (drawPos.z > 0.1f && faMyData->dItem->dObjectClass->dObjectClassName->iName[0] == 'S' && faMyData->dItem->isDead)
									{
										D3DXVECTOR3 abc = itemPos + dTrans->dTrans->dTransData->InvView_up * 0.1f;
										D3DXVECTOR3 out = dTrans->W2S(abc);

										int he = (int)(drawPos.y - out.y);
										int wi = (int)(he*2.f);

										char distbuf[30] = { 0 };

										sprintf_s(distbuf, " [%d]", distance);


										int nSize = faMyData->dItem->dObjectClass->dObjectClassName->iNameLength;
										if (nSize > 25)
											nSize = 25;

										char namebuf[100] = { 0 };
										/*
										int m;
										for (m = 0; m < nSize - 1; m++)
										{
											namebuf[m] = faMyData->dItem->dObjectClass->dObjectClassName->iName[m];
										}
										namebuf[m] = '\0';
										*/
										
										strcat_s(namebuf, distbuf);

										D3DCOLOR itemColor = LightGrey;

										//this->_DrawRect(m_rectLine, drawPos.x - (wi / 2), drawPos.y, (float)wi, (float)(-he), itemColor);
										this->_DrawText(m_textFont, namebuf, drawPos.x - 10, drawPos.y - 12, itemColor); //used to be out not drawpos

									}
								}
							}
						}
					}
				}
			}
		}
	}
}


BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	static DWORD dwProcessId = GetCurrentProcessId();

	int len = GetWindowTextLength(hWnd);
	if (len == 0) return TRUE;
	char padE[] = "Enum";
	DWORD tmp = 0;
	GetWindowThreadProcessId(hWnd, &tmp);
	if (tmp == dwProcessId)
	{
		GameHWND = hWnd; // this is primarily for being in windowed mode.
		return FALSE;
	}
	return TRUE;
}

int WINAPI SetHWND()
{
	char padS[] = "SetHWND";
	do
	{
		EnumWindows(EnumWindowsProc, NULL);
		Sleep(250);
	} while (GameHWND == NULL);
	return 0;
}

void Hooked_D3D9::Reset()
{
	// Release your d3d9 objects here and make them NULL.
	if (m_textFont)
	{
		m_textFont->Release();
		m_textFont = NULL;
	}
	if (m_rectLine)
	{
		m_rectLine->Release();
		m_rectLine = NULL;
	}

}

// Initializes your stuff
void Hooked_D3D9::Initialize(LPDIRECT3DDEVICE9 pDevice)
{
	// Initialize your d3d9 objects here.
	if (!m_device) m_device = pDevice;
	//if (!m_menuFontSmall)D3DXCreateFontA(pDevice, 12, 0, 4, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial", &m_menuFontSmall);
	//if (!m_menuFontBig)D3DXCreateFontA(pDevice, 16, 0, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial", &m_menuFontBig);
	if (!m_textFont)D3DXCreateFontA(pDevice, 12, 0, 4, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial", &m_textFont);
	if (!m_rectLine)D3DXCreateLine(pDevice, &m_rectLine);
}

// Draws some text
void Hooked_D3D9::_DrawText(ID3DXFont* pFont, const char* text, float x, float y, D3DCOLOR color)
{
	char padDT[] = "drawText";
	RECT posx = { posx.left = (long)(x-1), posx.top = (long)y, 0, 0 };
	RECT posxx = { posxx.left = (long)(x+1), posxx.top = (long)y, 0, 0 };
	RECT posy = { posy.left = (long)x, posy.top = (long)(y-1), 0, 0 };
	RECT posyy = { posyy.left = (long)x, posyy.top = (long)(y+1), 0, 0 };
	
	RECT pos = { pos.left = (long)x, pos.top = (long)y, 0, 0 };
	
	pFont->DrawTextA(NULL, text, strlen(text), &posx, DT_NOCLIP | FF_DONTCARE, D3DCOLOR_XRGB(1, 1, 1));
	pFont->DrawTextA(NULL, text, strlen(text), &posxx, DT_NOCLIP | FF_DONTCARE, D3DCOLOR_XRGB(1, 1, 1));
	pFont->DrawTextA(NULL, text, strlen(text), &posy, DT_NOCLIP | FF_DONTCARE, D3DCOLOR_XRGB(1, 1, 1));
	pFont->DrawTextA(NULL, text, strlen(text), &posyy, DT_NOCLIP | FF_DONTCARE, D3DCOLOR_XRGB(1, 1, 1));
	
	pFont->DrawTextA(NULL, text, strlen(text), &pos, DT_NOCLIP | FF_DONTCARE, color);
}

// Draw a line
void Hooked_D3D9::_DrawLine(ID3DXLine* pLine, float x1, float y1, float x2, float y2, D3DCOLOR color)
{
	D3DXVECTOR2 Vector2[2];
	char padDL[] = "drawLine";
	Vector2[1].x = x2;
	Vector2[1].y = y2;
	Vector2[0].x = x1;
	Vector2[0].y = y1;
	pLine->Draw(Vector2, 2, color);
}

// Draw a rectangle
void Hooked_D3D9::_DrawRect(ID3DXLine* pLine, float x, float y, float width, float height, D3DCOLOR color) //top left is x,y
{
	char padDR[] = "drawRect";
	// left line, left bottom to left top
	this->_DrawLine(pLine, x, y + height, x, y, color);
	// right line, right top to right bottom
	this->_DrawLine(pLine, x + width, y, x + width, y + height, color);
	// top line, left top to right top
	this->_DrawLine(pLine, x, y, x + width, y, color);
	// bottom line, right bottom to left bottom
	this->_DrawLine(pLine, x + width, y + height, x, y + height, color);
	
}

// Draw a filled rectangle
void Hooked_D3D9::_DrawRectFilled(LPDIRECT3DDEVICE9 pDevice, int x, int y, int width, int height, D3DCOLOR color)
{
	D3DRECT rect = { x, y, x + width, y + height };
	char padDRF[] = "drawRectFilled";
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
}