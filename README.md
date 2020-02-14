# 概要
このリポジトリは2019年度後期プログラミング演習の課題です。  

# 課題要件
- [x] コンビニエンスストア運営側が画面上で、商品の価格、在庫数等の入力できるか。 
- [x] コンビニエンスストア運営側が画面上でSALE等よって、一部の商品の価格を変更できるか。 
- [ ] お釣りが不足しないようレジ現金残高の管理できているか。 
- [x] 機械を電源オフにし、再起動したとき商品の最新の価格、在庫数と販売歴等が必要によって確認できるか。 
- [x] 必要によってセキュリティ関連捜査等のため、販売明細を販売時間、販売明細件(伝票番号、処理番号等を用いて)ごとに出力ができるか。 

# 実行するには
まず、このリポジトリをcloneする。

```terminal
$ git clone https://github.com/Takana-Norimasa/selfregi.git
```
Makefileを用いてコンパイルする。
```terminal
$ make
```

以下にmanagerとselfregiという実行ファイルが生成される。

```terminal
$ ls
LICENSE  README.md  a.out  data  manager  manager.c  selfregi  selfregi.c  struct_data.h
```

# 全体の構成

```terminal
.
├── LICENSE
├── Makefile
├── README.md
├── data
│   ├── create_data.pl
│   ├── product_data.csv
│   └── sales_log.csv
├── manager.c
├── selfregi.c
└── struct_data.h
```
各ファイルについて説明する
作成したプログラムは主に```selfregi.c```と```manager.c```の二つに分けられる。  

## selfregi.c
ユーザ（顧客）が直接操作するセルフレジのプログラム。
顧客が商品を選択してカートに入れて購入することができる。  

## manager.c
主に店舗側がデータを操作するときに使用する。   
具体的には後述する```product_data.csv```のデータを操作して、各商品のデータをインタラクティブに変更できるプログラムになっている。

## struct_data.h
共通して使用する構造体やそれらを使った関数をまとめたヘッダファイル。  
```selfregi.c```と```manager.c```でインクルードされている。


必要なログやデータは```data```ディレクトリにまとめて格納されている。  
## sales_log.csv
販売したデータの記録が格納されている。

## product_data.csv
商品の名前や値段のデータが格納されている。  

## create_data.pl
適当な商品データをランダムに生成するperlスクリプト。  

## Makefile
実行ファイルを生成するMakefile。

```terminal
$ make
```

でmanagerとselfregiという二つの実行ファイルを生成できる。  
両方を削除する場合は、

```terminal
$ make clean
```
と実行する。

## LICENSE
githubで公開するためにライセンスを付与した。  
今回はMIT Licenseを採用した。

# 主な機能



# 工夫した点


