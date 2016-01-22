#include "Core\Window.cpp"
#include <iostream>

Window window;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SETFOCUS:
		window.confineMouse();
		break;
	case WM_KILLFOCUS:
		window.releaseMouse();
		break;
	case WM_SIZE:
		window.Resize();
		break;
	case WM_CLOSE:
		window.releaseMouse();
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int main(int argc, char** argv) {

	window.createWindow(L"Dickbutt!", glm::vec2(400, 360), glm::vec2(100, 100), L"Resources/favicon.ico", L"Resources/Cursor.ico", ENGINE_WINDOWED, WndProc);
	window.InitOpenGL();

	float VertexPositions[] =
	{
		0.0f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f,
	};

	window.SetSize(glm::vec2(1024, 768));

	while (window.IsOpen()) {

		glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glVertexAttribPointer(0, 4, GL_FLOAT, 0, 0, VertexPositions);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

		SwapBuffers(window.hdc());

		window.getMessage();
	}

	window.Uninit();
	return 0;
}