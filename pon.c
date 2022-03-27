#include "DxLib.h"
#define MAP_HEIGHT 600//画面縦長さ
#define MAP_WIDTH 1200//画面横長さ
#define SPEED 20//MAXSpeed
// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE  hInstance,_In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{
	unsigned int Cr,Cr2;
	double speed = 4.0;//初期スピード
	double ball_x= MAP_WIDTH/2, ball_y= MAP_HEIGHT/2;//初期位置
	double angl_x = speed,angl_y = speed;
	int p_long1 = 150, p_long2 = 150;

	SetGraphMode(MAP_WIDTH, MAP_HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	Cr = GetColor(0, 0, 255);    // 青色の値を取得
	Cr2 = GetColor(121, 121, 121);    // 灰色の値を取得
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		if (CheckHitKey(KEY_INPUT_A) == 1 && (MAP_HEIGHT / 2) - p_long1 >= 0) {
			p_long1 += 5;
			p_long2 -= 5;
		}
		if (CheckHitKey(KEY_INPUT_Z) == 1 && (MAP_HEIGHT / 2) + p_long2 <= MAP_HEIGHT) {
			p_long1 -= 5;
			p_long2 += 5;
		}


		ball_x+= angl_x;
		ball_y+= angl_y;
		if (ball_y >= MAP_HEIGHT- SPEED || ball_y <= SPEED) //上下の壁に当たったら反射
		{
			if (angl_x <= SPEED && angl_x >= -SPEED && angl_y <= SPEED && angl_y >= -SPEED) {
				angl_x *= 1.2;
				angl_y *= 1.2;
			}
			angl_y = -angl_y;	//ここ、バグ上から下に直、右から左に直
		}
		if ((ball_x >= MAP_WIDTH- SPEED && ball_x <= MAP_WIDTH && ball_y >= (MAP_HEIGHT / 2) - p_long1 && ball_y <= (MAP_HEIGHT / 2)+ p_long2)
			|| (ball_x <= SPEED && ball_x >= 0 && ball_y >= (MAP_HEIGHT / 2) - p_long1 && ball_y <= (MAP_HEIGHT / 2) + p_long2))//左右の壁に当たったら反射
		{
			if (angl_x <= SPEED && angl_x >= -SPEED && angl_y <= SPEED && angl_y >= -SPEED) {
				angl_x *= 1.2;
				angl_y *= 1.2;
			}
			angl_x = -angl_x;
		}

		else if (ball_x <= 0) {//左の壁に当たると初期位置へ
			ball_x = MAP_WIDTH / 2, ball_y = MAP_HEIGHT / 2;
			angl_x = speed;
			angl_y = speed;
		}
		else if (ball_x >= MAP_WIDTH) {//右の壁に当たると初期位置へ
			ball_x = MAP_WIDTH / 2, ball_y = MAP_HEIGHT / 2;
			angl_x = -speed;
			angl_y = -speed;
		}
		DrawFormatString(300, 200, Cr, "x: %f y:%f ", ball_x, ball_y);
		DrawCircle(ball_x, ball_y, 10, Cr, TRUE);
		DrawBox(0, 0, MAP_WIDTH, 10, Cr2, TRUE);    // 壁上
		DrawBox(0, 590, MAP_WIDTH, 600, Cr2, TRUE);    // 壁下
		DrawBox(0, (MAP_HEIGHT/2)- p_long1, 10, (MAP_HEIGHT/2)+ p_long2, Cr2, TRUE);    // 壁上
		DrawBox(MAP_WIDTH-10, (MAP_HEIGHT/2)-p_long1, MAP_WIDTH, (MAP_HEIGHT/2)+ p_long2, Cr2, TRUE);    // 壁上
		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	

	//WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
