# leapmotion_controller

Leap Motionによるコントローラ </br>

## Installation

1. LeapSDKのインストール

2. Pythonからキーボード入力とマウス入力を行うので、そのためのモジュールを取得する。</br>
```
git clone https://github.com/SavinaRoja/PyUserInput.git
```

 - 代わりに`pip install PyUserInput`と打ってインストールしてもかまわない。


3. キーボードショートカットの割り当て 

画面遷移（スワイプ）のためのショートカットを割り当てる。 </br>
[システム環境設定]->[キーボード]->[ショートカット]->[Mission Control]の </br>
左の操作スペースに移動のキーボードショートカットをControl+Lに割り当てる。右も同様に。</br>


4. Makefileの書き換え

LeapSDKのパスおよびPythonのパスを各自の環境に合わせる。その後、makeする。

```
make
```

## Execution

```
./app
```
