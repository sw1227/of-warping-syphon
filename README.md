#  GLSL & openFrameworks & Syphon

参考: https://github.com/Hiroki11x/openFrameworksSample/tree/master/ofxSyphon_Sample


Syphon対応のためにプロジェクトを用意し直した関係上、以下のレポジトリとは別管理にした。
https://github.com/sw1227/of-domain-warping


## 注意点
- [旧ver](https://github.com/sw1227/of-domain-warping)の各種注意点や前提を継承する。
- ビルド時のGLUTのエラーを回避するため、`ofxSyphon` -> `Build Phases` -> `Run Script`以下の`rsync -aved ../../../libs/glut/lib/osx/GLUT.framework "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Frameworks/"`をコメントアウトする必要があった。


## 確認方法
`ofApp.cpp`の`setup()`関数内で指定されている通り、`Main`という名前でpublishしている。

これを確認するには、例えば[Syphon Simple Apps](https://github.com/Syphon/Simple/releases/tag/5)をダウンロードし、`Simple Client.app`を起動する。その状態で本プロジェクトをBuildしてDomain Warpingの画面を表示すると、`Simple Client.app`側でも全く同じ画面が表示されていることが確認できる。

