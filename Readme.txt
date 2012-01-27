ofxMpplr v0.1 beta

ofxMpplrは、弊社で使用しているプロジェクションマッピング用のクラスを汎用的にまとめ、UIを付加したものです。
オープンソースにし、誰もが改変できる事でより使いやすいツールへと昇華できるようなフィードバックを得られる事を期待し、公開に至りました。

Openframeworks v007以降にアドオンとして追加することができます。(別途ofxXmlSettingsをインクルードしてください)

【概要】
ofxMpplrは、以下のクラスで構成されています。

ofxMpplrScreen		- マッピングソースを実際に調整・投影するためのクラス
ofxMpplrController	- ofxMpplrScreenクラスをコントロールするためのUIクラス

Screenが保持するFboに直接描画することで、動画や静止画、生成系の映像等、汎用性の高いプロジェクションマッピングを可能にします。

【サンプルの操作方法】
1.　Pointボタン及びRectボタンで、使用するソースの領域を作成します。
2.　Plateボタン及びMagnetボタンでソースの取得位置を調整します。
3.　ソース位置を修正した後、画面右側のビューから投影する図形を調整します。

5番目のDebugボタンを解除すると、グリッド・ガイドラインが非表示になります。
※投影する画面を調整した後、戻ってソースを修正する場合、fixボタンで座標の同期を解除ことをおすすめします。

【主なメソッド】
[ofxMpplrScreen]
void ofxMpplrScreen::setup(int width,int height);
	スクリーンを初期化します。引数は、使用するフレームバッファの大きさを指定します。

void ofxMpplrScreen::draw(float x,float y,float width,float height);
	投影する映像を描画します。bDebugがtrueの時、編集可能な状態になります。

void ofxMpplrScreen::drawBuffer(float x,float y,float width,float height);
	投影する映像のソースを描画します。bDebugがtrueの時、編集可能な状態になります。

void ofxMpplrScreen::Begin();
	Fboに描画を開始します。内部的には、スクリーンが保持しているFboのbegin()を呼び出します。

void ofxMpplrScreen::End();
	Fboへの描画を終了します。

void ofxMpplrScreen::LoadXML(int num);
	XMLから、マッピングのデータを読み込みます。0〜9番まで、10種類のプリセットを読み書きできます。

void ofxMpplrScreen::SaveXML(int num);
	XMLから、マッピングのデータを保存します。0〜9番まで、10種類のプリセットを読み書きできます。

[ofxMpplrController]
void ofxMpplrController::setup(ofxMpplrScreen* _child);
	コントローラを初期化します。引数には、操作したいスクリーンのポインタを渡します。

void ofxMpplrController::draw(int x,int y);
	コントローラを描画します。


【リリースノート】
1/27 - v0.1　アドオンを公開

-----

ofxMpplr by maxilla inc. is licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License.

The MIT License

Copyright (c) 2009 openFrameworks,mpplr

Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the “Software”), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in

all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN

THE SOFTWARE.
