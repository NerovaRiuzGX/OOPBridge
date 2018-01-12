# Statement Code Table

## Regular Statement Code

| First Digit       | Second Digit | Content                            | Server's Behavior    | Client's Behavior    |
| ----------------- | ------------ | ---------------------------------- | -------------------- | -------------------- |
| `0` - *SET*       | `0`          | Connected, Wait for other players  | Waiting              | Waiting              |
|                   | `1`          | The table is full                  | Generates table data | Waiting              |
|                   | `2`          | Sharing table information          | Send table data      | Retrieve table data  |
|                   | `3`          | Sharing players' positions         | Send positions       | Retrieve positions   |
|                   | `4`          | *SET* Done                         | Waiting              | Set player data      |
| ----------------- | ------------ | ---------------------------------- | -------------------- | -------------------- |
| `1` - *AUCTION*   | `0`          | N player bids                      | Push auction_log     | (N) Enter bid        |
|                   | `1`          | E player bids                      | Push auction_log     | (E) Enter bid        |
|                   | `2`          | S player bids                      | Push auction_log     | (S) Enter bid        |
|                   | `3`          | W player bids                      | Push auction_log     | (W) Enter bid        |
|                   | `4`          | *AUCTION* Done                     | Send contract        | Retrieve contract    |
| ----------------- | ------------ | ---------------------------------- | -------------------- | -------------------- |
| `2` - *PLAY*      | `0`          | N player plays                     | Push trick_log       | (N) Play a card      |
|                   | `1`          | E player plays                     | Push trick_log       | (E) Play a card      |
|                   | `2`          | S player plays                     | Push trick_log       | (S) Play a card      |
|                   | `3`          | W player plays                     | Push trick_log       | (W) Play a card      |
|                   | `4`          | *PLAY* Done                        | Generate results     | Waiting              |
|                   | `5`~`9`      | Round Finished                     | Redirect statement   | Waiting              |
| ----------------- | ------------ | ---------------------------------- | -------------------- | -------------------- |
| `3` - *RESULT*    | `0`          | Sharing round results              | Send results         | Show results         |
|                   | `1`          | Table reset                        | Reset table data     | Reset table data     |
|                   | `2`          | *RESULT* Done                      | Send table data      | Retrieve table data  |
| ----------------- | ------------ | ---------------------------------- | -------------------- | -------------------- |
| `4` - *CLAIM*     | `0`          | NS-Claim                           | Ask EW if accept     | Waiting / Response   |
|                   | `1`          | EW-Claim                           | Ask NS if accept     | Waiting / Response   |

## Error Code
WIP
