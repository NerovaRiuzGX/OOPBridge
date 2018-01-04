# OOPBridge

## 小組成員
+ A1055508 李孟叡: Nerova
+ A1055516 賴冠穎
+ A1055536 廖敏翔: Ridost
+ A1055538 吳凱倫: kkrun

## 注意事項
+ 需要輸入字串資料，請統一使用 getline (cin, [變數名稱]);

## 架構

## 使用者介面
- bridge_player-table.txt

## 變數
+ define position: N(桌主) = 0, E = 1, S = 2, W = 3
+ define card: 
+ define bid: ps

+ class Host
  - round: int
  - auction_log: vector<string>
  - contract_suit: int
  - contract_trick: int
  - declarer_position: int
  - ns_trick: int
  - ew_trick: int
  - ns_point: int
  - ew_point: int
  - vulner()//設定本局身價
  - shuffle()//洗牌&發牌階段
  - auction()//喊牌階段
  - play()//出牌階段
  - score()//計算分數階段
  - pkgrcv()//接收封包解析
  - pkgsnd()//打包送出封包
+ class Player: inherit from class Host
  - card[13]: int
  - position: int
  - vulnerable: bool
  - printTable()
  - bid()
  - playCard()
  - claim()
  - undo()
+ class TCPServer
  - serverSocket: int
  - serverInfo: struct sockaddr_in
  - clientInfo: struct sockaddr_in
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
