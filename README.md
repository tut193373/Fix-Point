# Fix-Point
programming test

# 出力画面
 ![キャプチャ](https://user-images.githubusercontent.com/58971155/151766564-068169a4-6c00-44df-a5ff-194888d4ce69.JPG)
各設問に応じて、メッセージを出力させます。
(設問1)span (year)/(month)/(day) (hour):(minutes):(seconds)
(設問2)recovery
(設問3)overload (year)/(month)/(day) (hour):(minutes):(seconds)
(設問4)There may be a switch failure on this network.
 
# 特徴
 
C++でプログラムを組みました。
実行の際はコマンドライン引数に「n m t」の順番で渡す必要があります。

構成は以下のようになっています。  
.  
├── main.cpp  
├── log_structure.cpp  
├── log_structure.h  
└── network_log.txt  
 
 *main.cpp*  
 ログの読み込みや日付の処理など、全体の処理を記述しています。
 
 *log_structure.cpp*  
 ログデータを保持するクラス構造体のコンストラクタなどを定義しています。
 
 *log_structure.h*  
 ログをクラスとして扱ったほうが楽だと考えたため、クラスを用意しました。
 
 *network_log.txt*  
 ログがどのような形式で記録されているのか指定がなかったので、テキストファイルとしました。
 
# 動作環境

以下の環境で動作を確認しました。  
* 言語：C++ 1.7  
* 開発環境：Visual Studio 2019  
* OS：Windows 10  
 
# テスト
 
例題のログファイルと同様のフォーマットで、ランダムなデータを用意して動作速度などを確認した。  
フォーマットは以下のようにした。  
* (4桁年)(2桁月)(2桁日)(2桁時)(2桁分)(2桁秒),(8bit)(8bit)(8bit)(8bit)/(プレフィックス),(ランダム値)  
- 前半は年月日、処理の都合上桁数は固定とした。  
- IPv4はサブネットを2パターン（"192.168.1.◯"と"10.20.◯◯"）のものと、ホスト部を1～3で変化させたもので用意した。  
- プレフィックスはサブネットマスクに合わせて設定した。
- ランダム値は10～40の値、もしくは"-"を与えるように設定した。


 
```bash
pip install huga_package
```
 
# Usage
 
DEMOの実行方法など、"hoge"の基本的な使い方を説明する
 
```bash
git clone https://github.com/hoge/~
cd examples
python demo.py
```
 
# Note
 
注意点などがあれば書く
 
# Author
 
作成情報を列挙する
 
* 作成者
* 所属
* E-mail
 
# License
ライセンスを明示する
 
"hoge" is under [MIT license](https://en.wikipedia.org/wiki/MIT_License).
 
社内向けなら社外秘であることを明示してる
 
"hoge" is Confidential.
