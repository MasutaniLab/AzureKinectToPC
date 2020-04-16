# Point Cloud Grabber RTC for Microsoft Azure Kinect DK

大阪電気通信大学  
升谷 保博  
2020年4月16日

## はじめに

- Microsoft社の深度カメラAzure Kinect DKから深度画像と色画像を取得し，RTC:PCLのPointCloud型（`PointCloudTypes::PointCoud`）を
出力するRTコンポーネントです．
- 以下の環境で開発，動作確認しています．
  - Windows 10 64bit版
  - Visual Studio 2019 x64
  - OpenRTM-aist 1.2.1 64bit版
  - Eigen 3.3.7
  - Azure Kinect SDK v1.4.0
- CMakeでAzure Kinect SDKを見つけるモジュール[`cmake/Findk4a.cmake`](cmake/Findk4a.cmake)は，
[杉浦司氏 (UnaNancyOwen) が公開しているもの](https://gist.github.com/UnaNancyOwen/90b898366eb908d29cb4c2b509ab6cfa#file-findk4a-cmake)を利用しました．
- [`pointcloud.idl`](idl/pointcloud.idl) は，Geoffrey Biggs (gbiggs)氏の
[RT-Components for the Point Cloud Library](https://github.com/gbiggs/rtcpcl/)
に[含まれているもの](https://github.com/gbiggs/rtcpcl/blob/master/pc_type/pointcloud.idl)
をそのまま使っています．
- 座標変換のためにEigenは使っていますが，PCL（Point Cloud Library）は使っていません．
- 出力する点群を表す座標系は，y軸は上向きが正，z軸は後ろ向きが正です（それぞれAzure Kinect DKの座標系と逆向き，x軸はどちらも右向きが正）．
Choeonoidの深度センサのモデルに合わせるためにこのようにしています．

## 準備

- [OpenRTM-aist](http://www.openrtm.org/openrtm/)をインストール．
- [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)をインストール．PCL AllInOneパッケージに付属のものでも構わない．
- [Azure Kinect Sensor SDK download](https://docs.microsoft.com/ja-jp/azure/Kinect-dk/sensor-sdk-download)からWindows用インストーラ`Azure Kinect SDK X.X.X.exe` をダウンロードし実行．
- 環境変数 
  - `K4A_DIR=C:\Program Files\Azure Kinect SDK v1.4.0` を追加
  - `Path`の値の並びに`%K4A_DIR%\sdk\windows-desktop\amd64\release\bin`を追加．

# ビルド
- [AzureKinectToPC](https://github.com/MasutaniLab/AzureKinectToPC)をクローン．
- CMake
  - ビルドディレクトリはトップ直下の`build`
  - ConfigureはVisual Studioのバージョンとプラットフォームに合わせる．
  - 必要に応じて変数EIGEN_DIRの値を設定する．
- `build\AzureKinectToPC.sln`をVisual Studioで開く．
- Releaseでビルドする．

## 使い方

- Azure Kinect DKは，USB3のポートに接続する．
- 出力されるデータ量が多いので，CORBAのデフォルトの設定ではエラーになります．
rtc.confに`corba.args: -ORBgiopMaxMsgSize`の設定が必要です．
トップディレクトリのrtc.confでは`corba.args: -ORBgiopMaxMsgSize 20971520`
にしています（デフォルト値の10倍）．
- コンポーネントを起動するバッチファイル[`AzureKinectToPC.bat`](AzureKinectToPC.bat)を用意しています．
  - ビルドディレクトリがトップ直下の`build`であることを仮定しています．
  - 環境変数`RTM_VC_CONFIG`を`Debug`か`Release`に設定してください．
- 動作確認のための接続相手として，
[PointCloudViewer](https://github.com/MasutaniLab/PointCloudViewer)
を使ってください．そのためのバッチファイル[`TestAzureKinectToPC.bat`](TestAzureKinectToPC.bat)を用意しています．

## 仕様

- height: 下記
- width: 下記
- type: "xyzrgb"
- is_bigendian: 0
- point_step: 16
- row_step: 下記
- is_dense: 0
- fields (name,offset,data_type,count)
  - 0: "x",0,6,4
  - 1: "y",4,6,4
  - 2: "z",8,6,4
  - 3: "b",12,1,1
  - 4: "g",13,1,1
  - 5: "r",14,1,1

|alignTo|depthMode|colorResolution|cameraFps|height|width|row_step|
|:-:|:-:|--:|--:|--:|--:|--:|
|depth|NFOV_2X2BINNED|720P|30|288|320|5120|
|depth|NFOV_UNBINNED|720P|30|576|640|10240|
|depth|WFOV_2X2BINNED|720P|30|512|512|8192|
|depth|WFOV_UNBINNED|720P|15|1024|1024|16384|
|color|NFOV_2X2BINNED|720P|30|720|1280|20480|
|color|NFOV_UNBINNED|720P|30|720|1280|20480|
|color|WFOV_2X2BINNED|720P|30|720|1280|20480|
|color|WFOV_UNBINNED|720P|15|720|1280|20480|

### 入力ポート
- command
  - 説明： 外部からの指令を受け付ける
    - stop 処理を停止
    - start 処理を開始
  - 型： RTC::TimedString

### 出力ポート
- pc
  - 説明： 点群データ
  - 型： PointCloudTypes::PointCloud

### コンフィギュレーション
- deviceId
  - 説明： デバイスの番号（0～）
  - 型： short
  - デフォルト値： 0

- depthMode
  - 説明： 深度画像のモード（OFF, NFOV_2X2BINNED, NFOV_UNBINNED, WFOV_2X2BINNED, WFOV_UNBINNED, PASSIVE_IR）
  - 型： string
  - デフォルト値： WFOV_2X2BINNED

- alignTo
  - 説明： color 深度画像の画素数をカラー画像に合わせる，depth カラー画像の画素数を深度画像に合わせる
  - 型： string
  - デフォルト値： depth

- colorResolution
  - 説明： カラー画像の解像度（OFF,720P,1080P,1440P,1536P,2160P,3072P）
  - 型： string
  - デフォルト値： 720P

- cameraFps
  - 説明： フレームレート（5, 15, 30）
  - 型： short
  - デフォルト値： 30

- transX 
  - 説明： 座標変換の並進x成分 [m]
  - 型： float
  - デフォルト値： 0.0
- transY
  - 説明： 座標変換の並進y成分 [m]
  - 型： float
  - デフォルト値： 0.0
- transZ
  - 説明： 座標変換の並進z成分 [m]
  - 型： float
  - デフォルト値： 0.0
- rotX
  - 説明： 座標変換の回転x成分 [deg]
  - 型： float
  - デフォルト値： 0.0
  - 説明： 座標変換の回転y成分 [deg]
  - 型： float
  - デフォルト値： 0.0
- rotZ
  - 説明： 座標変換の回転z成分 [deg]
  - 型： float
  - デフォルト値： 0.0

## 既知の問題・TODO

- type "xyzrgb"しか出力できません．
- PointCloudViewerで確認するとレイテンシが大きい．
- alignTo: depthの場合にカラーがずれている．
- `replace_sample(). capturesync_drop, releasing capture early due to full queue TS ...` というエラーが出て動作しないことが時々あります．再実行すると直ります．

## 参考

- [Azure Kinect DK hardware specifications](https://docs.microsoft.com/en-us/azure/kinect-dk/hardware-specification)
- [Azure Kinect Sensor SDK](https://microsoft.github.io/Azure-Kinect-Sensor-SDK/master/index.html)

## 覚書（2020/4/16）
- 性能評価
  - Panasonic CF-SZ5
  - Firmware 1.6
  - SDK v1.4.0
  - 1秒当たりの出力回数をプログラムで1秒間隔で計算．

|alignTo|depthMode|colorResolution|cameraFps|単体実行 [fps]|組み合わせ実行*1[fps]|
|:-:|:-:|--:|--:|--:|--:|--:|
|depth|NFOV_2X2BINNED|720P|30|30|30|
|depth|NFOV_UNBINNED|720P|30|30|30|
|depth|WFOV_2X2BINNED|720P|30|30|30|
|depth|WFOV_UNBINNED|720P|15|15|11-13|
|color|NFOV_2X2BINNED|720P|30|30|16-18|
|color|NFOV_UNBINNED|720P|30|30|13-14|
|color|WFOV_2X2BINNED|720P|30|30|16-18|
|color|WFOV_UNBINNED|720P|15|15|13-14|

*1 同じPCでPointCloudViewerに接続し表示させながら実行．

