# ofxGraphicEqualizer

## 環境

macOSのCatalinaのみで動作確認しています。

## openFrameworks

1. download openFrameworks0.11.0 from [website](https://openframeworks.cc/download/) according to your environment.

2. unzip openFrameworks0.11.0 and move it to your folder.

3. enter the following commands.

```sh
cd openFrameworksFolder/apps/myApps/
git clone git@github.com:mynkit/ofxGraphicEqualizer.git
cd ofxGraphicEqualizer
```

## 動かし方

※ イヤホンをつなげていないと、マイクがスピーカーの音を拾ってハウリングするので、イヤホンやAudio Interfaceを接続して実行してください

`ofxGraphicEqualizer.xcodeproj`をxcodeで開き、左上のRunボタンをタップ

イコライザーの○をクリックするとイコライザーがかかり、各周波数帯の黒枠をクリックすればgainを変更できます

[![ofxGraphicEqualizer](http://img.youtube.com/vi/2herN59f78s/0.jpg)](https://www.youtube.com/watch?v=2herN59f78s "ofxGraphicEqualizer")


