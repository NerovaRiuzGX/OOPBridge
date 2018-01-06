# OOPBridge # 
   **從C++、OOP與TCP出發設計的橋牌遊戲**
  

## 小組成員與分工
+ A1055508 李孟叡 (Nerova)
  * class `TCPServer`, `TCPClient`, `FileControl`
  * TCP連線，檔案讀寫與傳輸
+ A1055516 賴冠穎 (jeffreylai0130)
  * class `Interface`
  * 單人遊戲AI
+ A1055536 廖敏翔 (Ridost)
  * class `Player`
  * 玩家資料輸入輸出，規則整合判斷
+ A1055538 吳凱倫 (kkrun)
  * class `Host`
  * 牌桌資訊整理與訊息交換

## 注意事項
+ 養成好習慣，先 Pull Request，再做 Commit
+ 程式編譯運行平台使用 Visual Studio 2010
+ 需要輸入字串資料，請統一使用 getline (cin, [變數名稱]);
+ 用來傳輸用的變數，如非處於使用階段或狀態，string 變數設為 "00"，int 變數設為 -1，以用來表示不在使用中
+ TCP傳輸資料使用string，編寫方式如下： `[資料編號]>[資料名稱]>[資料內容]\n`
  - 範例：
  ```
  0>EMPTY_PACKAGE>0 //是否為空封包
  1>round>1 //目前回合
  2>ns_vulnerable>1 //南北身價
  3>ew_vulnerable>1 //東西身價
  4>Card>C2 C4 C6 C8 C9 CT CJ D4 D8 H5 HA SJ SK-C5 D2 D3 D6 D9 DQ DA H4 HT HJ HK S7 ST-C3 CK H2 H8 H9 HQ S3 S4 S5 S6 S8 S9 SA-C7 CQ CA D5 D7 DT DJ DK H3 H6 H7 S2 SQ //四家手牌
  5>turn>0 //目前輪次
  6>auction_log> //喊牌紀錄
  7>contract_suit>-1 //合約花色
  8>contract_trick>-1 //合約礅數
  9>declarer_position>-1 //莊家方向
  10>trick_log>   -   -   -   -   -   -   -   -   -   -   -   -   //單局遊戲紀錄
  11>ns_trick>0 //南北已吃礅數
  12>ew_trick>0 //東西已吃礅數
  13>ns_point>0 //南北累積點數
  14>ew_point>0 //東西累積點數
  31>contract_dbl>-1 //合約賭倍
  19>pkgnum>0 //封包編號
  20>statement>00 //狀態代碼
  ```
## 系統架構流程圖
![Bridge](https://github.com/NerovaRiuzGX/OOPBridge/blob/master/FlowChart.png)

## 使用者介面 (文字版)
+ [bridge_player-table.txt](https://github.com/NerovaRiuzGX/OOPBridge/blob/master/bridge_player-table.txt)

## 系統狀態碼一覽表
+ [Statement code.md](https://github.com/NerovaRiuzGX/OOPBridge/blob/master/Statement%20code.md)

## Class 變數與函式
+ define position: (Host)N = 0, E = 1, S = 2, W = 3
+ define suit: Club = 0, Diamond = 1, Heart = 2, Spade = 3, NT = 4
+ define bid: Club = C, Diamond = D, Heart = H, Spade = S, NT = N, Dbl = X, Rdb = XX, pass = PS
+ define CardToInt(): C2 = 0, C3 = 1, CA = 12, ..., SK = 50, SA = 51
+ define Dbl: X= 1 ,Dbl= 2  Rdbl= 4
+ **class Host**
  - round: int
  - ns_vulnerable: bool
  - ew_vulnerable: bool
  - Card[4]: vector string
  - turn: int
  - auction_log: vector string
  - contract_suit: int
  - contract_trick: int
  - contract_dbl: int 
  - declarer_position: int  //莊家位置
  - trick_log[13][4]: string
  - ns_trick: int
  - ew_trick: int
  - ns_point: int
  - ew_point: int
  - statement: int
  - reset()  //下一局
  - vulner()    //設定本局身價
  - shuffle()   //洗牌發牌階段
  - sortCard(string, string): static bool  //洗牌後排序
  - auction()   //喊牌階段
  - play()    //出牌階段
  - score()    //計算分數階段
  - CardToInt(string): static int //撲克牌字串轉整數0~51
  - IntToCard(int): static string  //整數轉撲克牌字串
  - class FileControl
  - friend class Interface
  - friend class FileControl
+ **class Player**: 繼承 class Host
  - myCard: vector string
  - dummyCard: vector string 
  - position: int
  - vulnerable: bool
  - reset()  //下一局
  - printTable()    //印出牌桌資訊
  - bid()   //喊牌
  - playCard()    //出牌
  - claim()   //放入playcard()
  - undo()    //待加入
  - MySuits() //判斷花色
  - friend class Interface
  - friend class FileControl
+ **class TCPServer**
  - serverSocket: int
  - serverInfo: struct sockaddr_in
  - clientInfo: struct sockaddr_in
  - serverIP: string
  - setup(port)
  - sendMessage(data, sock)
  - detach()
  - getIP()
  - acceptConn(): int
+ **class TCPClient**: 繼承 class TCPServer
  - sock: int
  - server: struct sockaddr_in
  - TCPClient()
  - setup(ip, port): bool
  - sendMessage(data): bool
  - receive(size): bool
+ **class FileControl**
  - FileControl(name)
  - read()
  - write()
  - pkgrcv()    //接收封包解析
  - pkgsnd()    //打包送出封包
