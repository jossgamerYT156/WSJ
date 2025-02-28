# WSJ
Windows Subsystem for J-Kernel

WindowsホストでJのコンテナ化されたバージョンを実行するための基本的なサブシステム。J-OSに完全に移行する前に、まず試してみるためのものです（実際には完全に移行することはないかもしれませんが、笑）。

___

# ビルド方法

___
> これらの手順は、すでにVisual Studio Community Build Tools 2022がインストールされていることを前提としています。
>
> LillyのVisual Studio Build Toolsインストールの例:
> PowerShell: Visual Studio 2022 Developer PowerShell v17.14.0-pre.1.0
>
> コンパイラ: Microsoft (R) C/C++最適化コンパイラ バージョン 19.44.34823.2 for x64
>
> リンカ: Microsoft (R) インクリメンタルリンカ バージョン 14.44.34823.2

WSJは以下の環境でコンパイルされました：
> OS: Windows 11 Pro 24H2 B.NO: 26100.3194
>
> CPU: AMD Ryzen 7 PRO 4750U(16) x64 プロセッサ
>
> RAM: 16GB LDDR4

___
1.- Visual Studio PowerShellプログラムを開始し、[CD](https://ja.wikipedia.org/wiki/CD_(コマンド))でプロジェクトのルートディレクトリ（make.batがある場所）に移動します。

2.- `make.bat`バッチスクリプトを実行します（Visual Studio XXXX Developer PowerShell内で）。これにより、必要な.objファイルが`bin\*`内に生成され、[リンカ](https://ja.wikipedia.org/wiki/%E3%83%AA%E3%83%B3%E3%82%AB)によって`subsystem.exe`ファイルにリンクされます。ソースをビルドする予定がある場合は、これを実行することをお勧めします。個別にファイルをコンパイルするのは時間がかかるためです。

## 必要な場合

- コンパイルしたサブシステムをクリーンアップする場合は、`clean.bat`（プロジェクトのルートディレクトリから）を実行します。これにより、`bin\*`内のすべてのファイルや、必要に応じて`rootDir\J\*`が削除されます。もちろん、`.\rootDir\J\`が存在している前提です。

# 既知の問題

> `rootDir\J`にcdできない

通常、この問題は`subsystem.exe`を`$PRJ_ROOT\`以外のディレクトリから実行した場合に発生します。実行前に`.\`内に`rootDir\J`ディレクトリを作成しておくことをお勧めします。これにより、サブシステムのバイナリが適切にコンテナ環境をセットアップできます。

> コンパイル時の警告:
<codeblock> 
src\sys.c(37): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(39): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(41): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(43): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(44): warning C4113: 'void (__cdecl *)(HANDLE,HANDLE,DWORD)' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(45): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(46): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
</codeblock>

これらの警告は「正常」であり、バイナリの動作には直接影響しません。これらは、Windowsの機能を使用した関数宣言のタイプミスです。

> `ECOD`略語について

`ECOD`は「**`ERROR_CODE`**」を指し、通常はコマンドが正しく処理できなかった場合（存在しないディレクトリにcdしようとした場合など）に出力されます。これはWindowsのエラーコードを返し、デバッグが必要な場合はGoogleで検索できます。

> 現在の版ではLillyが他の問題を発見していないとのことです。

---

# 機能：

## 多目的コマンド：

- *`hlt`*      : プログラムを停止する（CORE）
- *`cd`*       : 指定されたパスにディレクトリを変更する（CORE）
- *`osi`*      : OSとターゲットの情報を表示する（CORE）
- *`pcd`*      : 現在のディレクトリを表示する（CORE）
- *`pwd`*      : `pcd`と同じ、互換性のために追加（CORE.*INUXCOMPAT）

## ファイル管理：

- *`mkd`*    : 指定されたパスのディレクトリを削除する（CORE）
- *`rmd`*    : 指定されたパスのディレクトリを削除する（CORE）
- *`mkf`*    : 指定された名前とパスでファイルを作成する（CORE）
- *`rmf`*    : 指定されたファイルを削除する（CORE）
- *`ls`*     : 現在のディレクトリの内容をリスト表示（CORE）

## Windowsとのやり取り

- *`dir`*    : `ls`と同じ（WINCOMPAT.WINDOWSUTILS.sysapp）
- *`open`*   : WindowsのSTARTディレクティブを使用して、指定されたファイルを開く（WINCOMPAT.WINDOWSUTILS.sysapp）
- *`clt`*    : ターミナルをクリアする（WINDOWS.WINDOWSUTILS.sysapp）

## J-Lang スクリプト

- `write` : `write "sometext!" を使用して画面に文字を書き込みます (CORE)
- `wait` : 指定された時間待機します (CORE.JLANG)
- `**` : コメント文字列 (CORE.JLANG)
- `jrun` : jlang 形式のスクリプト ファイルを実行します (CORE.JLANG)

## プロセスロジック

- *`cproc`*  : プロセスを作成する（CORE）
- *`killall`* : すべてのプロセスを終了する（CORE）
- *`addproc`* : プロセスリストにプロセスを追加する（CORE）


# プロジェクト構成：
---
<codeblock> // 注意、これらはプレースホルダーです。これを使用してください、Markdownを使うと出力が壊れます。
$PROJ_ROOTDIR\ [dir]                    // gitクローンコマンドから、WSJという名前のディレクトリです。
├── LICENSE [file]                      // MITライセンス、リポジトリに同梱
├── README.md [file]                    // このREADMEファイル
├── .gitignore [file]                   // `git commit`で無視するファイルやディレクトリのリスト
├── rootDir\ [dir]                      // コンテナ操作用JのROOT
│   └── J\ [dir]                        // 実際のJ ROOT、これがJにとっての`C:\`パスとして扱われます
│       └── * [dir or files]            // J内で作成したものはここに保存されます
├── src\ [dir]                          // J用のソースファイル
│   ├── include\ [dir]                  // プロジェクト用のインクルードディレクトリ。もし自分で作成した.hファイルも含まれます
│   │   └── prototypes.h [file]         // `extern`宣言を含むファイル、プログラムが関数を認識するために必要
│   ├── fs.c [file]                     // ファイルシステムの操作
│   ├── io.c [file]                     // 基本的なI/O操作
│   ├── jutils.c [file]                 // CORE, *INUXCOMPAT、WINDOWSCOMPATモジュール
│   ├── kernel.c [file]                 // カーネルロジック（開発中）
│   └── sys.c [file]                    // コマンドリストなどのシステム機能
├── bin\ [dir]                          // make.bat `/Fe:bin\subsystem.exe`の出力ディレクトリ
│   └── subsystem.exe [WINDOWS BINARY]  // Jバイナリ
├── make.bat [ビルドバッチスクリプト]   // VS Dev PowerShell用のビルドスクリプト
└── clean.bat [クリーンアップバッチスクリプト]    // すべての生成されたファイルを削除し、パス構造を再作成するクリーンスクリプト（rootDir\Jがまだ作成されていない場合にも役立ちます）
</codeblock> 

___

# 予想されること

Jは**1人**で作成・維持されているプロジェクトです。つまり、Lillyの手が回らないことが多いです。

- 小さなバグや機能が壊れることがあるかもしれません。Lillyは20分おきにやり方を変えながら試しているからです。
- リポジトリの更新が頻繁にはありません。Lillyにも生活があります。
- WindowsがOOBで提供するものを再実装することがあります。Lillyは理由もなく車輪を再発明する習性があるからです。
- 不要なコメントや自己解釈のコメントを入れることがよくあります。Lillyはまだプログラミング経験が3〜4年しかない初心者です。
- [J-Lang](https://github.com/jossgamerYT156/J-Lang)スクリプト言語の再発明と再実装が期待されます。Lillyはそのプロジェクトに非常に愛着があり、自分を苦しめるのが好きです。
- [*Techlm77*](https://github.com/Techlm77)、*Hugh P. Hulme*、[Tiadrop](https://github.com/tiadrop)の助けがいつでも必要になります。Lillyは彼らに常にアドバイスを求めて頼みます。

___

# ライセンス
___

## MITライセンス
> 本ソフトウェアは、「現状のまま」提供され、明示的または黙示的な保証は一切ありません。商業性、特定の目的への適合性、非侵害の保証を含みますが、これに限りません。著者または著作権者は、本ソフトウェアまたはその使用に関連して発生したいかなる請求、損害、またはその他の責任についても責任を負いません。

___

___

## 開発者: Lilly Aizawa (2022 - 2025) LDS LLC

___

___

[J-OSについてのLilly Aizawaによる簡単な説明](https://lillydevstudios.neocities.org/home/about/J-OS/)

[LinuxベースのJ](https://techlm77.co.uk/J-OS/) by [Techlm77](https://www.github.com/Techlm77/)

## この翻訳は不完全です。

改善にご協力いただけませんか? 修正内容を [Issue](https://github.com/jossgamerYT156/WSj/issues) に記入していただければ、Lilly が確認いたします！

> 読んでくれてありがとう
- 相澤リリー❤️
