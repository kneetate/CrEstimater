// CrEstimater.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

//Low Path Fileter
double LPF(double Rawdata, double gain)
{
    static double LPF = 0;
    static double preLPF = 0;
    LPF = gain * Rawdata + (1 - gain) * preLPF;
    return LPF;
    preLPF = LPF;
}

//Speed(m/s) ,MG2Torque(not final torque), Pitch(degree)
void CrEstimater(double &Cr,double Speed, double MG2Torque,double Pitch)
{

    double M = 700; //Mass
    double R = 0.24; //WheelRadius
    double dt = 0.1;
    double G = 9.81;
    const double DegtoRad = 0.01745329;
    static double preSpeed = 0;
    double dVdt = Speed - preSpeed / dt; //Accel
    double Filtered_dVdt = LPF(dVdt, 0.2);
    Cr = ((MG2Torque * 4.113 / (M * R)) - Filtered_dVdt - G * sin(DegtoRad * Pitch)) / (G * cos(DegtoRad * Pitch));
    if (Cr < 0)
    {
        Cr = 0.1;
    }
    preSpeed = Speed;
}




int main()
{
    int V = 1;
    int T = 0;
    int Pitch = 1;
    int i = 0;
    double Cr = 0;
    while (1)
    {

        CrEstimater(Cr, V, T, Pitch);
        cout << Cr << endl;
    }
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
