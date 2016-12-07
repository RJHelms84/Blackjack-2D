#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <string>
#include "Card.h"
#include <ctime>
#include <vector>
#include <sstream>

using namespace std;

//global variables
HINSTANCE hInst;
HWND wndHandle;
LPDIRECT3D9 pD3D = NULL; // the direct3d object
LPDIRECT3DDEVICE9 pd3dDevice = NULL; // the direct3d device
IDirect3DSurface9* fileSurface = NULL; //surface for cards image
IDirect3DSurface9* fileSurface2 = NULL; //surface for background image

//ai function globals
double frameCount = 0;
bool aiStays = false;

//switch to enable AI turn
bool aiSwitch = false;

//switch to disable input
bool disableInput = false;

//switch for game over
bool gameOver = false;

//switch for Retry
bool retrySwitch = false;

//text to display on screen
std::string defaultText = "Type F1 to hit, or F2 to stay."; //so screenText can be simply set back to default
std::string screenText = defaultText;

std::ostringstream tempString;

//scores
int playerOneScore = 0;
int playerTwoScore = 0;

//stretchrect card switches

int cardCount = 0;
int cardCountAI = 0;
std::vector<bool> cardSwitch;
std::vector<bool> cardSwitchAI;

//card deck
std::vector<Card> startDeck;

//hands
std::vector<Card> playerOneHand;
std::vector<Card> playerTwoHand;

const int ACE_CLUBS = 0;
const int TWO_CLUBS = 1;
const int THREE_CLUBS = 2;
const int FOUR_CLUBS = 3;
const int FIVE_CLUBS = 4;
const int SIX_CLUBS = 5;
const int SEVEN_CLUBS = 6;
const int EIGHT_CLUBS = 7;
const int NINE_CLUBS = 8;
const int TEN_CLUBS = 9;
const int JACK_CLUBS = 10;
const int QUEEN_CLUBS = 11;
const int KING_CLUBS = 12;

const int ACE_SPADES = 13;
const int TWO_SPADES = 14;
const int THREE_SPADES = 15;
const int FOUR_SPADES = 16;
const int FIVE_SPADES = 17;
const int SIX_SPADES = 18;
const int SEVEN_SPADES = 19;
const int EIGHT_SPADES = 20;
const int NINE_SPADES = 21;
const int TEN_SPADES = 22;
const int JACK_SPADES = 23;
const int QUEEN_SPADES = 24;
const int KING_SPADES = 25;

const int ACE_HEARTS = 26;
const int TWO_HEARTS = 27;
const int THREE_HEARTS = 28;
const int FOUR_HEARTS = 29;
const int FIVE_HEARTS = 30;
const int SIX_HEARTS = 31;
const int SEVEN_HEARTS = 32;
const int EIGHT_HEARTS = 33;
const int NINE_HEARTS = 34;
const int TEN_HEARTS = 35;
const int JACK_HEARTS = 36;
const int QUEEN_HEARTS = 37;
const int KING_HEARTS = 38;

const int ACE_DIAMONDS = 39;
const int TWO_DIAMONDS = 40;
const int THREE_DIAMONDS = 41;
const int FOUR_DIAMONDS = 42;
const int FIVE_DIAMONDS = 43;
const int SIX_DIAMONDS = 44;
const int SEVEN_DIAMONDS = 45;
const int EIGHT_DIAMONDS = 46;
const int NINE_DIAMONDS = 47;
const int TEN_DIAMONDS = 48;
const int JACK_DIAMONDS = 49;
const int QUEEN_DIAMONDS = 50;
const int KING_DIAMONDS = 51;

//stuff for drawing text
RECT lineRect;
D3DCOLOR defaultFontColor = D3DCOLOR_ARGB(255, 255, 255, 255);

// forward declarations
bool initWindow(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
bool initDirect3D(void);
void render(void);
void cleanUp(void);
ID3DXFont* GetFont();
RECT GetSourceRect(Card cardObject);
void Retry();
void Reset();

//prototypes from console game
void Populate(std::vector<Card> &deck);
void DrawCard(std::vector<Card> &start, std::vector<Card> &hand);
int CalculateHandValue(std::vector<Card> &hand);

void aiTurn();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//seed random number generator
	srand(static_cast<unsigned int>(time(0)));

	//create switch vectors
	bool cardSwitch1 = true;
	bool cardSwitch2 = true;
	bool cardSwitch3 = false;
	bool cardSwitch4 = false;
	bool cardSwitch5 = false;
	bool cardSwitch6 = false;
	bool cardSwitch7 = false;
	bool cardSwitch8 = false;
	bool cardSwitch9 = false;
	bool cardSwitch10 = false;
	bool cardSwitch11 = false;
	bool cardSwitch12 = false;

	cardSwitch.push_back(cardSwitch1);
	cardSwitch.push_back(cardSwitch2);
	cardSwitch.push_back(cardSwitch3);
	cardSwitch.push_back(cardSwitch4);
	cardSwitch.push_back(cardSwitch5);
	cardSwitch.push_back(cardSwitch6);
	cardSwitch.push_back(cardSwitch7);
	cardSwitch.push_back(cardSwitch8);
	cardSwitch.push_back(cardSwitch9);
	cardSwitch.push_back(cardSwitch10);
	cardSwitch.push_back(cardSwitch11);
	cardSwitch.push_back(cardSwitch12);

	//for ai
	bool cardSwitchAI1 = false;
	bool cardSwitchAI2 = false;
	bool cardSwitchAI3 = false;
	bool cardSwitchAI4 = false;
	bool cardSwitchAI5 = false;
	bool cardSwitchAI6 = false;
	bool cardSwitchAI7 = false;
	bool cardSwitchAI8 = false;
	bool cardSwitchAI9 = false;
	bool cardSwitchAI10 = false;
	bool cardSwitchAI11 = false;
	bool cardSwitchAI12 = false;

	cardSwitchAI.push_back(cardSwitchAI1);
	cardSwitchAI.push_back(cardSwitchAI2);
	cardSwitchAI.push_back(cardSwitchAI3);
	cardSwitchAI.push_back(cardSwitchAI4);
	cardSwitchAI.push_back(cardSwitchAI5);
	cardSwitchAI.push_back(cardSwitchAI6);
	cardSwitchAI.push_back(cardSwitchAI7);
	cardSwitchAI.push_back(cardSwitchAI8);
	cardSwitchAI.push_back(cardSwitchAI9);
	cardSwitchAI.push_back(cardSwitchAI10);
	cardSwitchAI.push_back(cardSwitchAI11);
	cardSwitchAI.push_back(cardSwitchAI12);



	Populate(startDeck);

	//create player one's hand
	DrawCard(startDeck, playerOneHand);
	DrawCard(startDeck, playerOneHand);
	cardCount += 2;
	playerOneScore = CalculateHandValue(playerOneHand);

	//create player two's hand
	DrawCard(startDeck, playerTwoHand);
	DrawCard(startDeck, playerTwoHand);
	cardCountAI += 2;
	playerTwoScore = CalculateHandValue(playerTwoHand);


	//create window & setup directx stuff

	if (!initWindow(hInstance))
		return false;

	if(!initDirect3D())
		return false;



	//drawing text stuff
	lineRect.left = 100;
	lineRect.top = 460;
	lineRect.right = lineRect.left + 300;
	lineRect.bottom = lineRect.top + 100;


	//card surface setup

	D3DXIMAGE_INFO imageInfo;
	std::string fileName = "./cardSprite.bmp";

	// Get the width and height info from this bitmap
	D3DXGetImageInfoFromFile(fileName.c_str(), &imageInfo);

	//create offscreen surface for cards
	pd3dDevice->CreateOffscreenPlainSurface(
								imageInfo.Width,
								imageInfo.Height,
								D3DFMT_X8R8G8B8,
								D3DPOOL_DEFAULT,
								&fileSurface,
								NULL);

	//load cards texture file into global pointer
	D3DXLoadSurfaceFromFile(			fileSurface,
										NULL,
										NULL,
										fileName.c_str(),
										NULL,
										D3DX_DEFAULT,
										0,
										NULL );

	//background surface setup

	D3DXIMAGE_INFO imageInfo2;
	std::string fileName2 = "./table.bmp";

	// Get the width and height info from this bitmap
	D3DXGetImageInfoFromFile(fileName2.c_str(), &imageInfo2);

	//create offscreen surface for cards
	pd3dDevice->CreateOffscreenPlainSurface(
								imageInfo2.Width,
								imageInfo2.Height,
								D3DFMT_X8R8G8B8,
								D3DPOOL_DEFAULT,
								&fileSurface2,
								NULL);

	//load cards texture file into global pointer
	D3DXLoadSurfaceFromFile(			fileSurface2,
										NULL,
										NULL,
										fileName2.c_str(),
										NULL,
										D3DX_DEFAULT,
										0,
										NULL );


	
	// Main message loop:
    MSG msg; 
    ZeroMemory( &msg, sizeof(msg) );
    while( msg.message!=WM_QUIT )
    {
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
			TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
		else
		{
			render();
			if (aiSwitch)
			{
				frameCount++;
			}
		}
    }

	cleanUp();
		
	return (int) msg.wParam;
}

bool initWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "Blackjack";
	wcex.hIconSm		= 0;
	RegisterClassEx(&wcex);

	// create the window
	wndHandle = CreateWindow("Blackjack", 
							 "Blackjack", 
							 WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT, 
							 CW_USEDEFAULT, 
							 800, 
							 600, 
							 NULL, 
							 NULL, 
							 hInstance, 
							 NULL);
   if (!wndHandle)
      return false;
   
   ShowWindow(wndHandle, SW_SHOW);
   UpdateWindow(wndHandle);

   return true;
}

bool initDirect3D(void)
{
	pD3D = NULL;
	pd3dDevice = NULL;

	//create the directx object
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return false;
	}

	//fill the presentation parameters structure
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferWidth = 800;
	d3dpp.hDeviceWindow = wndHandle;

	//create a default directx device
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, wndHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice)))
	{
		return false;
	}
	return true;
}

ID3DXFont* GetFont()
{

	ID3DXFont* pDefaultFont;

	D3DXCreateFont(pd3dDevice, 30,
	0, FW_BOLD, 0, FALSE,
	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
	DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
	TEXT("Calibri"), &pDefaultFont );

	return pDefaultFont;
}

//could create new data member of card class (from console version game) called card_id, which could be passed into GetSourceRect
//then checked in the if statements
RECT GetSourceRect(Card cardObject) //returns rect data for specific card, to be passed to stretchrect function as source rectangle parameter
{
	const int WIDTH = 46;
	const int HEIGHT = 61;
	RECT final = {0,0,0,0};//useless, no longer used

	//clubs
	for(int a = 0; a<13; a++)
	{
		if(cardObject.GetID() == a)
		{
			RECT src;
			src.top = HEIGHT * 0;
			src.left = (a * WIDTH);
			src.right = (src.left + WIDTH);
			src.bottom = (src.top + HEIGHT);

			return src;
			
		}
	}

	//spades
	for(int b = 0; b<13; b++)
	{
		if(cardObject.GetID() == (b+13))
		{
			RECT src;
			src.top = HEIGHT * 1;
			src.left = (b * WIDTH);
			src.right = (src.left + WIDTH);
			src.bottom = (src.top + HEIGHT);

			return src;
			
		}
	}
	
	//hearts
	for(int c = 0; c<13; c++)
	{
		if(cardObject.GetID() == (c+26))
		{
			RECT src;
			src.top = HEIGHT * 2;
			src.left = (c * WIDTH);
			src.right = (src.left + WIDTH);
			src.bottom = (src.top + HEIGHT);

			return src;
			
		}
	}

	//diamonds
	for(int d = 0; d<13; d++)
	{
		if(cardObject.GetID() == (d+39))
		{
			RECT src;
			src.top = HEIGHT * 3;
			src.left = (d * WIDTH);
			src.right = (src.left + WIDTH);
			src.bottom = (src.top + HEIGHT);

			return src;
			
		}
	}


	return final;

}

void render(void)
{
	//retry stuff
	if(gameOver)
	{
		if (retrySwitch = FALSE)
		{
			frameCount = 0;
		}
		retrySwitch = TRUE;
		Retry();
	}

	//begin ai turn, if it's time
	if ((aiSwitch) && (!gameOver))
	{
		aiTurn();
	}

	//pointer to back buffer
	IDirect3DSurface9* backbuffer = NULL;

	//check to make sure you have a valid direct3d device
	if(NULL == pd3dDevice)
		return;
	//clear the back buffer to a blue colour
	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(14, 148, 40), 1.0f, 0);

	//fill pointer to back buffer
	pd3dDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&backbuffer);

	//const int for spacing between cards
	const int SPACING = 66; //20 for space, 46 for card width

	//need to create 12 different rects and do 12 stretchrect calls, but use if statements
	//with global variables being used as on/off switches, so the extra cards can be turns on and off
	//warning: if you switch on a cardSwitch, before the hand vector has a card in that slot, game will crash


	//source rect1
	RECT src1;
	//rect for first card in hand
	RECT dest1;
	if (cardSwitch[0])
	{
		src1 = GetSourceRect(playerOneHand[0]);
		dest1.top = 100; //used to be 20, when in 640 by 480 res
		dest1.left = 100; //used to be 20, when in 640 by 480 res
		dest1.right = dest1.left + 46; //46 is card width
		dest1.bottom = dest1.top + 61; //61 is card width
	}


	//source rect2
	RECT src2;
	//rect for second card in hand
	RECT dest2;
	if (cardSwitch[1])
	{
		src2 = GetSourceRect(playerOneHand[1]);
		dest2.top = 100;
		dest2.left = 100 + (SPACING*1);
		dest2.right = dest2.left + 46; //46 is card width
		dest2.bottom = dest2.top + 61; //61 is card width
	}


	//source rect3
	RECT src3;
	//rect for third card in hand
	RECT dest3;
	if (cardSwitch[2])
	{
		src3 = GetSourceRect(playerOneHand[2]);
		dest3.top = 100;
		dest3.left = 100 + (SPACING*2);
		dest3.right = dest3.left + 46; //46 is card width
		dest3.bottom = dest3.top + 61; //61 is card width
	}

	//source rect4
	RECT src4;
	//rect for fourth card in hand
	RECT dest4;
	if (cardSwitch[3])
	{
		src4 = GetSourceRect(playerOneHand[3]);
		dest4.top = 100;
		dest4.left = 100 + (SPACING*3);
		dest4.right = dest4.left + 46; //46 is card width
		dest4.bottom = dest4.top + 61; //61 is card width
	}

	//source rect5
	RECT src5;
	//rect for fifth card in hand
	RECT dest5;
	if (cardSwitch[4])
	{
		src5 = GetSourceRect(playerOneHand[4]);
		dest5.top = 100;
		dest5.left = 100 + (SPACING*4);
		dest5.right = dest5.left + 46; //46 is card width
		dest5.bottom = dest5.top + 61; //61 is card width
	}

	//source rect6
	RECT src6;
	//rect for sixth card in hand
	RECT dest6;
	if (cardSwitch[5])
	{
		src6 = GetSourceRect(playerOneHand[5]);
		dest6.top = 100;
		dest6.left = 100 + (SPACING*5);
		dest6.right = dest6.left + 46; //46 is card width
		dest6.bottom = dest6.top + 61; //61 is card width
	}

	//source rect7
	RECT src7;
	//rect for seventh card in hand
	RECT dest7;
	if (cardSwitch[6])
	{
		src7 = GetSourceRect(playerOneHand[6]);
		dest7.top = 100;
		dest7.left = 100 + (SPACING*6);
		dest7.right = dest7.left + 46; //46 is card width
		dest7.bottom = dest7.top + 61; //61 is card width
	}

	//source rect8
	RECT src8;
	//rect for eighth card in hand
	RECT dest8;
	if (cardSwitch[7])
	{
		src8 = GetSourceRect(playerOneHand[7]);
		dest8.top = 100;
		dest8.left = 100 + (SPACING*7);
		dest8.right = dest8.left + 46; //46 is card width
		dest8.bottom = dest8.top + 61; //61 is card width
	}

	//source rect9
	RECT src9;
	//rect for ninth card in hand
	RECT dest9;
	if (cardSwitch[8])
	{
		src9 = GetSourceRect(playerOneHand[8]);
		dest9.top = 100;
		dest9.left = 100 + (SPACING*8);
		dest9.right = dest9.left + 46; //46 is card width
		dest9.bottom = dest9.top + 61; //61 is card width
	}




//AI RECTS


	//source rect1
	RECT srcAI1;
	//rect for first card in hand
	RECT destAI1;
	if (cardSwitchAI[0])
	{
		srcAI1 = GetSourceRect(playerTwoHand[0]);
		destAI1.top = 100 + (61*3);
		destAI1.left = 100;
		destAI1.right = destAI1.left + 46; //46 is card width
		destAI1.bottom = destAI1.top + 61; //61 is card width
	}


	//source rect2
	RECT srcAI2;
	//rect for second card in hand
	RECT destAI2;
	if (cardSwitchAI[1])
	{
		srcAI2 = GetSourceRect(playerTwoHand[1]);
		destAI2.top = 100 + (61*3);
		destAI2.left = 100 + (SPACING*1);
		destAI2.right = destAI2.left + 46; //46 is card width
		destAI2.bottom = destAI2.top + 61; //61 is card width
	}


	//source rect3
	RECT srcAI3;
	//rect for third card in hand
	RECT destAI3;
	if (cardSwitchAI[2])
	{
		srcAI3 = GetSourceRect(playerTwoHand[2]);
		destAI3.top = 100 + (61*3);
		destAI3.left = 100 + (SPACING*2);
		destAI3.right = destAI3.left + 46; //46 is card width
		destAI3.bottom = destAI3.top + 61; //61 is card width
	}

	//source rect4
	RECT srcAI4;
	//rect for fourth card in hand
	RECT destAI4;
	if (cardSwitchAI[3])
	{
		srcAI4 = GetSourceRect(playerTwoHand[3]);
		destAI4.top = 100 + (61*3);
		destAI4.left = 100 + (SPACING*3);
		destAI4.right = destAI4.left + 46; //46 is card width
		destAI4.bottom = destAI4.top + 61; //61 is card width
	}

	//source rect5
	RECT srcAI5;
	//rect for fifth card in hand
	RECT destAI5;
	if (cardSwitchAI[4])
	{
		srcAI5 = GetSourceRect(playerTwoHand[4]);
		destAI5.top = 100 + (61*3);
		destAI5.left = 100 + (SPACING*4);
		destAI5.right = destAI5.left + 46; //46 is card width
		destAI5.bottom = destAI5.top + 61; //61 is card width
	}

	//source rect6
	RECT srcAI6;
	//rect for sixth card in hand
	RECT destAI6;
	if (cardSwitchAI[5])
	{
		srcAI6 = GetSourceRect(playerTwoHand[5]);
		destAI6.top = 100 + (61*3);
		destAI6.left = 100 + (SPACING*5);
		destAI6.right = destAI6.left + 46; //46 is card width
		destAI6.bottom = destAI6.top + 61; //61 is card width
	}

	//source rect7
	RECT srcAI7;
	//rect for seventh card in hand
	RECT destAI7;
	if (cardSwitchAI[6])
	{
		srcAI7 = GetSourceRect(playerTwoHand[6]);
		destAI7.top = 100 + (61*3);
		destAI7.left = 100 + (SPACING*6);
		destAI7.right = destAI7.left + 46; //46 is card width
		destAI7.bottom = destAI7.top + 61; //61 is card width
	}

	//source rect8
	RECT srcAI8;
	//rect for eighth card in hand
	RECT destAI8;
	if (cardSwitchAI[7])
	{
		srcAI8 = GetSourceRect(playerTwoHand[7]);
		destAI8.top = 100 + (61*3);
		destAI8.left = 100 + (SPACING*7);
		destAI8.right = destAI8.left + 46; //46 is card width
		destAI8.bottom = destAI8.top + 61; //61 is card width
	}

	//source rect9
	RECT srcAI9;
	//rect for ninth card in hand
	RECT destAI9;
	if (cardSwitchAI[8])
	{
		srcAI9 = GetSourceRect(playerTwoHand[8]);
		destAI9.top = 100 + (61*3);
		destAI9.left = 100 + (SPACING*8);
		destAI9.right = destAI9.left + 46; //46 is card width
		destAI9.bottom = destAI9.top + 61; //61 is card width
	}





pd3dDevice->BeginScene();

//display background

HRESULT hResultB = pd3dDevice->StretchRect(fileSurface2,NULL,backbuffer,NULL,D3DTEXF_NONE);
	if (hResultB != D3D_OK)
		MessageBox(NULL,"failed2", "error2", MB_OK);


if (cardSwitch[0])
{
	HRESULT hResult = pd3dDevice->StretchRect(fileSurface,&src1,backbuffer,&dest1,D3DTEXF_NONE); //this function will need to be called multiple times, using different versions of the src rect, for multiple cards on screen
		if (hResult != D3D_OK)
			MessageBox(NULL,"failed", "error", MB_OK);
}

if (cardSwitch[1])
{
	HRESULT hResult2 = pd3dDevice->StretchRect(fileSurface,&src2,backbuffer,&dest2,D3DTEXF_NONE);
		if (hResult2 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitch[2])
{
	HRESULT hResult3 = pd3dDevice->StretchRect(fileSurface,&src3,backbuffer,&dest3,D3DTEXF_NONE);
		if (hResult3 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitch[3])
{
	HRESULT hResult4 = pd3dDevice->StretchRect(fileSurface,&src4,backbuffer,&dest4,D3DTEXF_NONE);
		if (hResult4 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitch[4])
{
	HRESULT hResult5 = pd3dDevice->StretchRect(fileSurface,&src5,backbuffer,&dest5,D3DTEXF_NONE);
		if (hResult5 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitch[5])
{
	HRESULT hResult6 = pd3dDevice->StretchRect(fileSurface,&src6,backbuffer,&dest6,D3DTEXF_NONE);
		if (hResult6 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitch[6])
{
	HRESULT hResult7 = pd3dDevice->StretchRect(fileSurface,&src7,backbuffer,&dest7,D3DTEXF_NONE);
		if (hResult7 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitch[7])
{
	HRESULT hResult8 = pd3dDevice->StretchRect(fileSurface,&src8,backbuffer,&dest8,D3DTEXF_NONE);
		if (hResult8 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitch[8])
{
	HRESULT hResult9 = pd3dDevice->StretchRect(fileSurface,&src9,backbuffer,&dest9,D3DTEXF_NONE);
		if (hResult9 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}


//enable ai cards

if (cardSwitchAI[0])
{
	HRESULT hResultAI = pd3dDevice->StretchRect(fileSurface,&srcAI1,backbuffer,&destAI1,D3DTEXF_NONE); //this function will need to be called multiple times, using different versions of the src rect, for multiple cards on screen
		if (hResultAI != D3D_OK)
			MessageBox(NULL,"failed", "error", MB_OK);
}

if (cardSwitchAI[1])
{
	HRESULT hResultAI2 = pd3dDevice->StretchRect(fileSurface,&srcAI2,backbuffer,&destAI2,D3DTEXF_NONE);
		if (hResultAI2 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitchAI[2])
{
	HRESULT hResultAI3 = pd3dDevice->StretchRect(fileSurface,&srcAI3,backbuffer,&destAI3,D3DTEXF_NONE);
		if (hResultAI3 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitchAI[3])
{
	HRESULT hResultAI4 = pd3dDevice->StretchRect(fileSurface,&srcAI4,backbuffer,&destAI4,D3DTEXF_NONE);
		if (hResultAI4 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitchAI[4])
{
	HRESULT hResultAI5 = pd3dDevice->StretchRect(fileSurface,&srcAI5,backbuffer,&destAI5,D3DTEXF_NONE);
		if (hResultAI5 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitchAI[5])
{
	HRESULT hResultAI6 = pd3dDevice->StretchRect(fileSurface,&srcAI6,backbuffer,&destAI6,D3DTEXF_NONE);
		if (hResultAI6 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitchAI[6])
{
	HRESULT hResultAI7 = pd3dDevice->StretchRect(fileSurface,&srcAI7,backbuffer,&destAI7,D3DTEXF_NONE);
		if (hResultAI7 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitchAI[7])
{
	HRESULT hResultAI8 = pd3dDevice->StretchRect(fileSurface,&srcAI8,backbuffer,&destAI8,D3DTEXF_NONE);
		if (hResultAI8 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}

if (cardSwitchAI[8])
{
	HRESULT hResultAI9 = pd3dDevice->StretchRect(fileSurface,&srcAI9,backbuffer,&destAI9,D3DTEXF_NONE);
		if (hResultAI9 != D3D_OK)
			MessageBox(NULL,"failed2", "error2", MB_OK);
}


	//draw text from EditText function. This will be sent new text strings through a paramter when calling the function in-game
	ID3DXFont* getFontPointer = GetFont();
	getFontPointer->DrawTextA(NULL, screenText.c_str(), -1, &lineRect, DT_RIGHT, defaultFontColor);



pd3dDevice->EndScene();




	//present the back buffer contents to the display
	pd3dDevice->Present(NULL, NULL, NULL, NULL);

	//clean up back buffer pointer
	backbuffer->Release();
	getFontPointer->Release();
}

void cleanUp(void)
{
	//release the device and the direct3d object
	if(pd3dDevice != NULL)
		pd3dDevice->Release();

	if(pD3D != NULL)
		pD3D->Release();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_F1:
				//hit
				if ((!gameOver) && (!disableInput)) //only trigger is gameOver is not true
				{
					Beep(500,200);
					DrawCard(startDeck, playerOneHand);
					cardSwitch[cardCount] = true; //cardCount will be 2 initially, which accesses the third position in this vector, as the index starts at 0
											//but this is okay, as we increment the cardCount AFTER setting the switch
					cardCount++;
					playerOneScore = CalculateHandValue(playerOneHand);
			
					if (playerOneScore > 21)
					{
						tempString.str("");
						tempString << "You busted with " << playerOneScore << " cards!";
						screenText = tempString.str(); //change screen text, if busted

						//add code to end the game, or whatever
						gameOver = true;
					}
					else
					{
						tempString.str("");
						tempString << "Your cards add up to " << playerOneScore << "!!";
						screenText = tempString.str(); //change text to score current score
					}
				}
				break;
			case VK_F2:
				//stay
				if ((!gameOver) && (!disableInput)) //only trigger is gameOver is not true
				{
					Beep(500,200);
					screenText = "It's now the AI's turn.";

					//player two's turn needs to begin at this point, by switching it on in render
					disableInput = true;
					aiSwitch = true;
					cardSwitchAI[0] = true;
					cardSwitchAI[1] = true;
				}
				break;
			case VK_F3:
				//retry key
				if(retrySwitch)
				{
					//run function to reset everything
					Reset();
				}
				break;
			case VK_F4:
				//no retry and exit key
				if(retrySwitch)
				{
					//shutdown game
					PostQuitMessage(0);
				}
				break;
			default:
				break;
			}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

//functions from console game

int CalculateHandValue(std::vector<Card> &hand)
{
	int size = hand.size();
	int counter = 0;

	for (int x = 0; x < size; x++)
	{
		if (hand[x].GetNumber() == "2")
		{
			counter += 2;
		}
		else if (hand[x].GetNumber() == "3")
		{
			counter += 3;
		}
		else if (hand[x].GetNumber() == "4")
		{
			counter += 4;
		}
		else if (hand[x].GetNumber() == "5")
		{
			counter += 5;
		}
		else if (hand[x].GetNumber() == "6")
		{
			counter += 6;
		}
		else if (hand[x].GetNumber() == "7")
		{
			counter += 7;
		}
		else if (hand[x].GetNumber() == "8")
		{
			counter += 8;
		}
		else if (hand[x].GetNumber() == "9")
		{
			counter += 9;
		}
		else if (hand[x].GetNumber() == "10")
		{
			counter += 10;
		}
		else if (hand[x].GetNumber() == "j")
		{
			counter += 10;
		}
		else if (hand[x].GetNumber() == "q")
		{
			counter += 10;
		}
		else if (hand[x].GetNumber() == "k")
		{
			counter += 10;
		}
		else if (hand[x].GetNumber() == "a")
		{
			//ace is set to 11, but if there is a bust, they are reset to 1 instead
			//in the "handle aces" code below
			counter += 11;
		}
	}

	//handle aces
	if (counter > 21)
	{
		for (int y = 0; y < size; y++)
		{
			if (hand[y].GetNumber() == "a")
			{
				if (counter > 21)
				{
					counter -= 10;
				}
			}
		}
	}

	return counter;
}

void DrawCard(std::vector<Card> &start, std::vector<Card> &hand)
{
	int pick = 0;
	int cardFound = 0;
	do
	{
		pick = rand() % 51; //generates random number between 0 and 51
		
		if (start[pick].GetNumber() != "e") //checks card position is not empty
		{
			//add card to the hand
			hand.push_back(start[pick]);

			cardFound = 1;

			//add empty card to position in start deck
			start[pick].SetNumber("e");
			start[pick].SetSuit('e');

		}
	} while (cardFound == 0);
}

void Populate(std::vector<Card> &deck)
{
	//clears out anything inside the vector
	deck.clear();


	//add clubs to deck

	Card aceClubs("a", 'c', 0);
	Card clubs2("2", 'c', 1);
	Card clubs3("3", 'c', 2);
	Card clubs4("4", 'c', 3);
	Card clubs5("5", 'c', 4);
	Card clubs6("6", 'c', 5);
	Card clubs7("7", 'c', 6);
	Card clubs8("8", 'c', 7);
	Card clubs9("9", 'c', 8);
	Card clubs10("10", 'c', 9);
	Card jackClubs("j", 'c', 10);
	Card queenClubs("q", 'c', 11);
	Card kingClubs("k", 'c', 12);

	deck.push_back(aceClubs);
	deck.push_back(clubs2);
	deck.push_back(clubs3);
	deck.push_back(clubs4);
	deck.push_back(clubs5);
	deck.push_back(clubs6);
	deck.push_back(clubs7);
	deck.push_back(clubs8);
	deck.push_back(clubs9);
	deck.push_back(clubs10);
	deck.push_back(jackClubs);
	deck.push_back(queenClubs);
	deck.push_back(kingClubs);


	//add spades to deck

	Card aceSpades("a", 's', 13);
	Card spades2("2", 's', 14);
	Card spades3("3", 's', 15);
	Card spades4("4", 's', 16);
	Card spades5("5", 's', 17);
	Card spades6("6", 's', 18);
	Card spades7("7", 's', 19);
	Card spades8("8", 's', 20);
	Card spades9("9", 's', 21);
	Card spades10("10", 's', 22);
	Card jackSpades("j", 's', 23);
	Card queenSpades("q", 's', 24);
	Card kingSpades("k", 's', 25);

	deck.push_back(aceSpades);
	deck.push_back(spades2);
	deck.push_back(spades3);
	deck.push_back(spades4);
	deck.push_back(spades5);
	deck.push_back(spades6);
	deck.push_back(spades7);
	deck.push_back(spades8);
	deck.push_back(spades9);
	deck.push_back(spades10);
	deck.push_back(jackSpades);
	deck.push_back(queenSpades);
	deck.push_back(kingSpades);


	//add hearts to deck

	Card aceHearts("a", 'h', 26);
	Card hearts2("2", 'h', 27);
	Card hearts3("3", 'h', 28);
	Card hearts4("4", 'h', 29);
	Card hearts5("5", 'h', 30);
	Card hearts6("6", 'h', 31);
	Card hearts7("7", 'h', 32);
	Card hearts8("8", 'h', 33);
	Card hearts9("9", 'h', 34);
	Card hearts10("10", 'h', 35);
	Card jackHearts("j", 'h', 36);
	Card queenHearts("q", 'h', 37);
	Card kingHearts("k", 'h', 38);

	deck.push_back(aceHearts);
	deck.push_back(hearts2);
	deck.push_back(hearts3);
	deck.push_back(hearts4);
	deck.push_back(hearts5);
	deck.push_back(hearts6);
	deck.push_back(hearts7);
	deck.push_back(hearts8);
	deck.push_back(hearts9);
	deck.push_back(hearts10);
	deck.push_back(jackHearts);
	deck.push_back(queenHearts);
	deck.push_back(kingHearts);



	//add diamonds to deck

	Card aceDiamonds("a", 'd', 39);
	Card diamonds2("2", 'd', 40);
	Card diamonds3("3", 'd', 41);
	Card diamonds4("4", 'd', 42);
	Card diamonds5("5", 'd', 43);
	Card diamonds6("6", 'd', 44);
	Card diamonds7("7", 'd', 45);
	Card diamonds8("8", 'd', 46);
	Card diamonds9("9", 'd', 47);
	Card diamonds10("10", 'd', 48);
	Card jackDiamonds("j", 'd', 49);
	Card queenDiamonds("q", 'd', 50);
	Card kingDiamonds("k", 'd', 51);

	deck.push_back(aceDiamonds);
	deck.push_back(diamonds2);
	deck.push_back(diamonds3);
	deck.push_back(diamonds4);
	deck.push_back(diamonds5);
	deck.push_back(diamonds6);
	deck.push_back(diamonds7);
	deck.push_back(diamonds8);
	deck.push_back(diamonds9);
	deck.push_back(diamonds10);
	deck.push_back(jackDiamonds);
	deck.push_back(queenDiamonds);
	deck.push_back(kingDiamonds);


}

void aiTurn()
{
	//user an integer variable that increments after each frame, and use this frame count to initiate stages of the function
	//which will be called each frame, instead of using Sleep()

	

	//run ai code

	if (playerTwoScore > 21)
	{
		//ai busts, so game over
		screenText = "AI busts, you win!";
		gameOver = true;
	}
	else if (!aiStays)
	{			
		if (frameCount > 200) //edit this value to adjust ai game speed, should user delta time later
		{
				if (playerTwoScore == 21)
				{
					//ai is 21, so stays
					aiStays = true;
					screenText = "AI stays at 21";
					Beep(500,200);
				}
				else if ((playerTwoScore > 15) && (playerTwoScore >= playerOneScore))
				{
					//random chance of hitting when score is over 15 but under 18
					if (playerTwoScore > 18)
					{	
						aiStays = true;
						screenText = "AI stays!";
						Beep(500,200);
						frameCount = 0; //reset frame counter
					}	
					else	
					{	
						if (playerTwoScore >= playerOneScore)
						{	
							aiStays = true;
							screenText = "AI stays!";
							Beep(500,200);
							frameCount = 0; //reset frame counter
						}	
						else	
						{	
							//ai hits
							screenText = "AI hits!";
							Beep(500,200);
							DrawCard(startDeck, playerTwoHand);
							playerTwoScore = CalculateHandValue(playerTwoHand);
							//change switch for ai card to true
							cardSwitchAI[cardCountAI] = true;
							cardCountAI++;
							frameCount = 0; //reset frame counter
						}
					}
				}
				else
				{
					//hit
					screenText = "AI hits!";
					Beep(500,200);
					DrawCard(startDeck, playerTwoHand);
					playerTwoScore = CalculateHandValue(playerTwoHand);
					//change switch for ai card to true
					cardSwitchAI[cardCountAI] = true;
					cardCountAI++;
					frameCount = 0; //reset frame counter
				}
		}
	}



	

	//if no one has bust, continue
	if ((!gameOver) && (aiStays) && (frameCount > 200))
	{
	

		//if player has higher score than ai, player wins, as busts have already been determined
		if (playerOneScore > playerTwoScore)
		{
			//player wins
			screenText = "You win!";
			gameOver = true;
		}
		else if (playerTwoScore > playerOneScore)
		{
			//computer wins
			screenText = "You lose!";
			gameOver = true;
		}
		else if (playerOneScore == playerTwoScore)
		{
			//if scores are tied, the player with least number of cards wins
			if (playerOneHand.size() < playerTwoHand.size())
			{
				//player wins
				screenText = "You won!";
				gameOver = true;
			}
			else if (playerTwoHand.size() < playerOneHand.size())
			{
				//computer wins
				screenText = "You lost!";
				gameOver = true;
			}
			else if (playerTwoHand.size() == playerOneHand.size())
			{
				//draw game
				screenText = "It's a draw!";
				gameOver = true;
			}

		}

	}
}

void Retry()
{
	if (frameCount > 200)
	{
		screenText = "F3 - Play again, F4 - quit.";
		frameCount = 0;
	}
	frameCount++;
}

void Reset()
{
	//stuff to reset on the retry
	frameCount = 0;
	aiStays = false;
	aiSwitch = false;
	disableInput = false;
	gameOver = false;
	retrySwitch = false;
	screenText = defaultText;
	playerOneScore = 0;
	playerTwoScore = 0;
	cardCount = 0;
	cardCountAI = 0;

	cardSwitch[0] = true;
	cardSwitch[1] = true;
	cardSwitch[2] = false;
	cardSwitch[3] = false;
	cardSwitch[4] = false;
	cardSwitch[5] = false;
	cardSwitch[6] = false;
	cardSwitch[7] = false;
	cardSwitch[8] = false;
	cardSwitch[9] = false;
	cardSwitch[10] = false;
	cardSwitch[11] = false;
	cardSwitchAI[0] = false;
	cardSwitchAI[1] = false;
	cardSwitchAI[2] = false;
	cardSwitchAI[3] = false;
	cardSwitchAI[4] = false;
	cardSwitchAI[5] = false;
	cardSwitchAI[6] = false;
	cardSwitchAI[7] = false;
	cardSwitchAI[8] = false;
	cardSwitchAI[9] = false;
	cardSwitchAI[10] = false;
	cardSwitchAI[11] = false;

	startDeck.empty();
	playerOneHand.clear();
	playerTwoHand.clear();

	Populate(startDeck);

	//create player one's hand
	DrawCard(startDeck, playerOneHand);
	DrawCard(startDeck, playerOneHand);
	cardCount += 2;
	playerOneScore = CalculateHandValue(playerOneHand);

	//create player two's hand
	DrawCard(startDeck, playerTwoHand);
	DrawCard(startDeck, playerTwoHand);
	cardCountAI += 2;
	playerTwoScore = CalculateHandValue(playerTwoHand);

}