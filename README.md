# OOPBridge # 
   **從C++、OOP與TCP出發設計的橋牌遊戲**
  

## 小組成員與分工
+ A1055508 李孟叡 (Nerova)
  * Server、Client、FileControl class
  * TCP連線，檔案讀寫與傳輸
+ A1055516 賴冠穎 (jeffreylai0130)
  * Interface class
  * 單人遊戲AI
+ A1055536 廖敏翔 (Ridost)
  * Player class
  * 玩家資料輸入輸出
+ A1055538 吳凱倫 (kkrun)
  * Host class
  * 牌桌資訊整理與訊息交換

## 注意事項
+ 養成好習慣，先 Pull Request，再做 Commit
+ 程式編譯運行平台使用 Visual Studio 2010
+ 需要輸入字串資料，請統一使用 getline (cin, [變數名稱]);
+ TCP傳輸資料使用string，編寫方式如下： `[資料編號]>[資料名稱]>[資料內容]\n`
  - 範例：
  ```
  >0>EMPTY_PACKAGE>0\n //是否為空封包
  >15>position>1\n //玩家座位方向
  >16>bid>7N\n //玩家喊牌
  >19>pkgnum>23\n //封包編號
  >?>auction>-1  //Host發送 喊牌開始、喊牌成功
  >?>bid>10  //Player發送 喊牌內容(1C = 10, 1N = 14, 7C = 70, 7N = 74)
  >?>play>-1  //Host發送 喊牌結束&打牌開始、打牌成功
  >?>play>0  //Player發送 打牌內容(define CardToInt() )
  ```
## 架構
![Bridge](https://github.com/NerovaRiuzGX/OOPBridge/blob/master/FlowChart.png)

## 使用者介面
- bridge_player-table.txt

## 變數
+ define position: (Host)N = 0, E = 1, S = 2, W = 3
+ define suit: Club = 0, Diamond = 1, Heart = 2, Spade = 3, NT = 4
+ define bid: Club = C, Diamond = D, Heart = H, Spade = S, NT = N
+ define CardToInt(): C2 = 0, C3 = 1, CA = 12, ..., SK = 50, SA = 51
+ define Dbl: X= 1 ,Dbl= 2  Rdbl= 4
+ class Host
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
  - trick_log[13][4]: vector string
  - ns_trick: int
  - ew_trick: int
  - ns_point: int
  - ew_point: int
  - statement: int
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
+ class Player: inherit from class Host
  - myCard: vector string
  - dummyCard: vector string 
  - position: int
  - vulnerable: bool
  - printTable()    //印出牌桌資訊
  - bid()   //喊牌
  - playCard()    //出牌
  - claim()   //放入playcard()
  - undo()    //待加入
  - friend class Interface
  - friend class FileControl
+ class TCPServer
  - serverSocket: int
  - serverInfo: struct sockaddr_in
  - clientInfo: struct sockaddr_in
  - serverIP: string
  - setup(port)
  - sendMessage(data, sock)
  - detach()
  - getIP()
  - acceptConn(): int
+ class TCPClient
  - sock: int
  - server: struct sockaddr_in
  - TCPClient()
  - setup(ip, port): bool
  - sendMessage(data): bool
  - receive(size): bool
+ class FileControl
  - FileControl(name)
  - read()
  - write()
  - pkgrcv()    //接收封包解析
  - pkgsnd()    //打包送出封包
