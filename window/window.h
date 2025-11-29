#pragma once

//------  window.h  ------

#include<Windows.h>
#include<string>

class window final
{
public:
	window() = default;
	~window() = default;

	//ウィンドウ作成
	[[nodiscard]] bool crate(HINSTANCE instance, int width, int height, std::string_view name)noexcept;

	//メッセージループ
	[[nodiscard]] bool messegeLoop()const noexcept;
	
	//ウィンドウハンドル取得
	[[nodiscard]] HWND getHandle()const noexcept;

	//ウィンドウサイズ取得
	[[nodiscard]] std::pair<UINT, UINT> getSize()const noexcept;

private:
	HWND handle_{};	//ウィンドウ
	UINT Width_{};	//ウィンドウの横幅
	UINT Height_{};	//ウィンドウの縦幅
};
