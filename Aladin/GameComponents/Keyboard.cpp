#include "Keyboard.h"
#include "Debug.h"
Keyboard *Keyboard::__instance = NULL;

int Keyboard::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}
int Keyboard::IsKeyUp(int KeyCode)
{
	return !(keyStates[KeyCode] & 0x80) > 0;
}
void Keyboard::InitKeyboard(HWND hWnd)
{
	//Khởi tạo DirectInput8
	HRESULT
		hr = DirectInput8Create
		(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);
	//Kiểm tra lỗi
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}
	//Khởi tạo device keyboard
	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	//Kiểm tra lỗi
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	//Chọn data format là bàn phím
	hr = didv->SetDataFormat(&c_dfDIKeyboard);
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] SetDataFormat failed!\n");
		return;
	}
	//Thiết lập mức độ hợp tác
	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] SetCooperativeLevel failed!\n");
		return;
	}

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size
	//Gọi hàm SetProperty để thiết lập chế độ đệm
	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);


	//Giành kiểm soát bàn phím
	hr = didv->Acquire();
	//Kiểm tra lỗi
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

void Keyboard::Poll_Keyboard()
{
	//Lấy tất cả trạng thái của bàn phím
	HRESULT hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		//Nếu bàn phím mất focus hoặc chưa giành quyền kiểm soát được thì thử giành lại quyền kiểm soát
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			//Giành lại quyền kiểm soát
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}
}
// update trạng thái nhân vật khi nhấn nút
void Keyboard::UpdateKeyStates(DWORD dt)
{
	Aladin * aladin = Aladin::GetInstance();

	if (IsKeyDown(DIK_RIGHT))
	{
			aladin->TurnRight();
			aladin->Walk();
	}
	 if (IsKeyDown(DIK_LEFT))
	{
		aladin->TurnLeft();
		aladin->Walk();
	}
	 if (IsKeyDown(DIK_C))
	{
		aladin->Jump();
	}
	 if (IsKeyDown(DIK_X))
	{
		aladin->Attack();
	}
	 if (IsKeyDown(DIK_Z))
	{
		aladin->ThrowCherryWhenStand();
	}
	 if (IsKeyDown(DIK_DOWN))
	{
		aladin->SitDown();
	}
}
void Keyboard::OnKeyDown(int KeyCode)
{
	Aladin* aladin = Aladin::GetInstance();
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	
	}
}
void Keyboard::OnKeyUp(int KeyCode)
{
	Aladin* aladin = Aladin::GetInstance();
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		aladin->Idle();
		break;
	case DIK_LEFT:
	case DIK_RIGHT:
		if (ALADIN_ANI_RUN == aladin->GetStateNumber())
		{ 
			aladin->Stop();
		}
		break;
	
	case DIK_UP:
		aladin->SetState(aladin->GetIdleState());
		break;
	case DIK_X:
		break;
	case DIK_Z:
		break;
	case DIK_C:
		break;
	}
}

void Keyboard::Update(DWORD dt)
{
	Poll_Keyboard();

	UpdateKeyStates(dt);

	//Lấy các sự kiện bàn phím được đệm
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	//Kiểm tra lỗi
	if (FAILED(hr))
	{
		DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	//Kiểm tra các phím được đệm, xem phím nào được nhấn xuống hoặc thả ra, rồi xử lí
	for (DWORD i = 0; i < dwElements; i++)
	{
		//Lấy keycode được nhấn
		int KeyCode = keyEvents[i].dwOfs;
		//Lấy trạng thái của phím đang xét
		int KeyState = keyEvents[i].dwData;
		//Kiểm tra xem phím được nhấn hay được thả ra
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}
//Hàm hủy Keyboard chính
Keyboard::~Keyboard()
{
	if (didv != NULL)
	{
		didv->Unacquire();
		didv->Release();
	}
	if (di != NULL) di->Release();
}

//Hàm lấy đối tượng
Keyboard *Keyboard::GetInstance()
{
	if (__instance == NULL) __instance = new Keyboard();
	return __instance;
}
