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
+ 程式編譯運行平台使用 Visual Studio 2010
+ 需要輸入字串資料，請統一使用 getline (cin, [變數名稱]);
+ TCP傳輸資料使用string，編寫方式如下： `[資料編號]>[資料名稱]>[資料內容]\n`
  - 範例：
  ```C++
  0>EMPTY_PACKAGE>0\n //是否為空封包
  15>position>1\n //玩家座位方向
  16>bid>7N\n //玩家喊牌
  19>pkgnum>23\n //封包編號
  ```

## 架構
![Bridge](https://github.com/NerovaRiuzGX/OOPBridge/blob/master/Bridge_0104.PNG)

## 使用者介面
- bridge_player-table.txt

## 變數
+ define position: (Host)N = 0, E = 1, S = 2, W = 3
+ define suit: Club = 0, Diamond = 1, Heart = 2, Spade = 3
+ define bid: Club = c, Diamond = d, Heart = h, Spade = s, NT = n
+ define CardToInt(): C2 = 0, C3 = 1, CA = 12, ..., SK = 50, S = 51

+ class Host
  - round: int
  - ns_vulnerable: bool
  - ew_vulnerable: bool
  - Card[4]: vector string
  - turn: int
  - auction_log: vector string
  - contract_suit: int
  - contract_trick: int
  - declarer_position: int
  - trick_log: vector string
  - ns_trick: int
  - ew_trick: int
  - ns_point: int
  - ew_point: int
  - vulner()    //設定本局身價
  - shuffle()   //洗牌發牌階段
  - sortCard(string, string): bool  //洗牌後排序
  - auction()   //喊牌階段
  - play()    //出牌階段
  - score()    //計算分數階段
  - CardToInt(string)  //撲克牌字串轉整數0~51
  - IntToCard(int)  //整數轉撲克牌字串
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
