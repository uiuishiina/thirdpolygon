
//------  window.cpp  ------

#include"window.h"
#include<cassert>


namespace {
	//ウィンドウプロシージャ
	LRESULT CALLBACK WindowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(handle,msg,wParam,lParam);
	}
};

//ウィンドウ作成
[[nodiscard]] bool window :: crate(HINSTANCE instance, int width, int height, std::string_view name)noexcept
{
	//ウィンドウクラス作成
	WNDCLASS wc{};
	wc.lpfnWndProc		= WindowProc;							//ウィンドウプロシージャ
	wc.hInstance		= instance;								//インスタンス
	wc.lpszClassName	= name.data();							//クラス名
	wc.hCursor			= LoadCursor(nullptr, IDC_ARROW);		//マウスカーソル
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);	//背景

	//ウィンドウクラス登録
	RegisterClass(&wc);

	//ウィンドウ作成
	handle_ = CreateWindow(
		wc.lpszClassName,			//ウィンドウクラス名
		wc.lpszClassName,			//ウィンドウタイトル
		WS_OVERLAPPEDWINDOW,		//ウィンドウスタイル
		CW_USEDEFAULT,CW_USEDEFAULT,//ウィンドウの位置(x,y)
		width,height,				//ウィンドウサイズ(w,h)
		nullptr,nullptr,			//(親ウィンドウ,メニュー)
		instance,					//インスタンス・・WinMain()で取得するやつ
		nullptr						//追加データ
	);

	if (!handle_) {
		assert(false && "ウィンドウハンドルの作成に失敗");
		return false;
	}

	//ウィンドウ表示処理
	ShowWindow(handle_, SW_SHOW);
	UpdateWindow(handle_);

	Width_ = width;
	Height_ = height;

	return true;
}

//メッセージループ
[[nodiscard]] bool window :: messegeLoop()const noexcept
{
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

//ウィンドウハンドルを返す
[[nodiscard]] HWND window :: getHandle()const noexcept{
	if (!handle_) {
		assert(false && "ウィンドウハンドルが未作成(handle)");
	}
	return handle_;
}

//ウィンドウのサイズを返す
[[nodiscard]] std::pair<UINT, UINT> window :: getSize()const noexcept{
	if (!handle_) {
		assert(false && "ウィンドウハンドルが未作成(size)");
	}
	return {Width_,Height_};
}