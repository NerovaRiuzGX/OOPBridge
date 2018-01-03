# OOPBridge
## 架構

## 使用者介面
- bridge_player-table.txt

## 變數
+ define position: N(桌主) = 0, E = 1, S = 2, W = 3
+ define suit: Club = 0, Diamond = 1, Heart = 2, Spade = 3
+ class Player
  - card[13]: Card
  - posistion: int
  - showTable()
  - bid()
  - playCard()
  - claim()
  - undo()
+ class Team
  - vulnerable: bool
  - win_trick: int
  - point: int
+ class Server
  - round: int
  - auction_log: vector
  - contract_suit:
