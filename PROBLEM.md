# 資料結構作業：Stack、Function Pointer 與 Event-Driven Calculator

## 一、作業目的

本作業目的在於練習下列程式設計與資料結構概念：

- Stack（堆疊）資料結構之實作與應用。
- Infix Expression（中序算式）之解析與計算。
- Function Pointer（函式指標）之使用。
- Linux 環境下之 Event-Driven Programming。
- 使用 libev 建立 Non-blocking Event Loop。
- Callback Function 與非阻塞式輸入處理。

請使用 C 語言完成本作業。

## 二、作業說明

請設計並實作一支可於 Linux 環境執行的「事件驅動算術表示式計算器」。

程式啟動後須持續執行，並同時進行以下兩項工作：

- 在終端畫面的固定位置持續顯示目前系統時間。
- 接受使用者輸入算術表示式並計算結果。

上述兩項工作必須以 Non-blocking 方式執行。亦即，即使使用者尚未完成輸入，畫面上的時間仍必須持續更新。

## 三、算式計算要求

程式須接受使用者輸入的中序算式，例如：
```
3+5*2
```

並輸出：
```
13
```

程式至少須支援下列四種運算：`+`  `-`  `*`  `/`

其中：

`*` `/` 

優先順序高於：

`+` `-`

相同優先順序的運算須依照由左至右的順序執行。

例如：

```
100/5/2
```

應計算為：

```
(100/5)/2 = 10
```

不得計算為：

```
100/(5/2)
```

程式須支援多位數整數，例如：

```
123+45*6
```

並應忽略輸入中的空白，例如：

```
10 + 20 * 3
```
與：
```
10+20*3
```

應得到相同結果。

## 四、Stack 實作要求

算式求值必須使用兩個自行實作的 Stack：

- Operand Stack：儲存運算元。
- Operator Stack：儲存運算子。

Stack 至少必須提供下列操作：

- `push`
- `pop`
- `top`
- `isEmpty`

不得使用其他現成的 Stack Library 取代自行實作之 Stack。

在處理算式時，應依照 Operator 優先順序決定何時從 Stack 中取出運算元與運算子進行計算。

## 五、Function Pointer 要求

四則運算必須分別實作成四個獨立函式，例如：

```c
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
```

並使用 Function Pointer 呼叫對應的函式。

例如可定義：

```c
typedef double (*Operation)(double, double);
```

當程式需要執行某個運算時，必須先根據 Operator 取得對應的 Function Pointer，再透過該 Function Pointer 呼叫相對應的運算函式。

概念如下：

```
'+' -> add
'-' -> subtract
'*' -> multiply
'/' -> divide
```

例如，若 Operator Stack 取出：

```
*
```

且 Operand Stack 取出：

```
5
2
```

則程式應透過指向 multiply() 的 Function Pointer 完成：
```
5 * 2 = 10
```

主要計算流程中不可直接以：
```c
result = a * b;
```
完成對應運算。

可以使用 if-else、switch、Function Pointer Array 或 Function Pointer Table 選擇對應函式，但實際四則運算必須由上述四個函式完成。

## 六、libev 與 Event-Driven Programming

本作業必須使用 libev 建立 Event Loop。

程式至少須建立以下兩種 Event Watcher：

### 1. Timer Watcher

使用 libev Timer Event 定期更新系統時間。

Timer 應約每一秒觸發一次 Callback Function，取得目前時間並更新終端畫面。

時間格式須至少包含：

```
YYYY-MM-DD HH:MM:SS
```

例如：
```
Current Time: 2026-10-01 14:25:30
```

時間必須持續更新於畫面的固定位置，不得每秒增加一行新的時間資訊。

### 2. I/O Watcher

使用 libev I/O Event 監控標準輸入：
```
stdin
```

當使用者完成一行輸入並按下 Enter 時，應由 I/O Callback Function 取得算式並進行計算。

程式流程概念如下：

```
                libev Event Loop
                       |
          +------------+------------+
          |                         |
      Timer Event                 stdin Event
          |                         |
          v                         v
   Timer Callback             I/O Callback
          |                         |
          v                         v
     更新目前時間              讀取輸入算式
                                    |
                                    v
                            使用兩個 Stack 計算
                                    |
                                    v
                           Function Pointer
                                    |
                                    v
                              顯示計算結果
```

## 七、Non-blocking 要求

本作業的核心要求之一為：程式不得因等待使用者輸入而停止其他事件的處理。

例如，下列設計不符合本作業要求：

```c
while (1) {
    scanf(...);
    calculate(...);
    sleep(1);
}
```

因為當程式停在 `scanf()` 等待使用者輸入時，時間更新將無法繼續進行。

正確設計應由 libev Event Loop 統一管理輸入事件與 Timer Event。

即使使用者在下列提示畫面停留 30 秒：
```
Expression >
```
時間仍必須每秒持續更新。

## 八、連續輸入要求

程式不得在完成一個算式後結束。

使用者必須能連續輸入多組算式，例如：

```
Expression > 3+5*2
Result     = 13

Expression > 100/5/2
Result     = 10

Expression > 8*4-6
Result     = 26

Expression >
```

完成一次算式求值後，應重新初始化或清除相關 Stack，並繼續等待下一筆輸入。

## 九、畫面顯示要求
程式執行畫面可參考下列形式：

```
==================================================
 Current Time: 2026-10-01 14:25:30
==================================================

Expression > 3+5*2
Result     = 13

Expression > 100/5/2
Result     = 10

Expression >
```

一秒後，時間應更新為：
```
==================================================
 Current Time: 2026-10-01 14:25:31
==================================================
```
但先前的計算結果與使用者目前的輸入狀態不應被破壞。

可自行研究並使用 ANSI Terminal Escape Sequence 控制游標位置與終端顯示。

## 十、程式結束
請設計適當的結束指令，例如： `exit` 或 `quit`

當使用者輸入結束指令後，程式應：

- 停止 libev Watcher。
- 正常結束 Event Loop。
- 正常結束程式。

## 十一、錯誤處理

程式至少應處理基本錯誤狀況，例如：

```
3++5
10/
10/0
```

當輸入不合法時，應顯示適當錯誤訊息，例如：
```
Invalid expression
```
或：
```
Division by zero
```

發生錯誤時，程式不得直接結束，應繼續等待下一筆輸入。

十二、進階功能
完成基本要求後，可自行加入下列功能：

- 支援括號 `(`、`)`。
- 支援負數。
- 支援小數。
- 支援更多 Operator。
- 改善 Terminal UI 顯示。
- 加入歷史運算紀錄。
例如：
```
Expression > (3+5)*2
Result     = 16
```

## 十三、編譯與執行
程式必須可在 Linux 環境下使用 GCC 編譯。

例如：
```bash
gcc calculator.c -o calculator -lev
```

執行：
```bash
./calculator
```
建議使用 Makefile 管理編譯流程。

十四、繳交內容
請繳交以下內容：

- 完整 C 語言原始碼。
- Makefile。
- 至少五組不同算式的測試結果。
- Operand Stack 與 Operator Stack 的設計說明。
- 四個運算函式的設計說明。
- Function Pointer 的設計與使用方式。
- libev Event Loop 的架構說明。
- Timer Callback Function 與 I/O Callback Function 的功能說明。
- Non-blocking 程式設計方式說明。
- 程式如何維持時間更新且同時接受使用者輸入之說明。
- 算式長度為 n 時之時間複雜度與空間複雜度分析。

## 十五、評分重點

本作業將依下列項目進行評分：

- Stack 是否正確自行實作。
- 算式解析與運算結果是否正確。
- Operator 優先順序是否正確處理。
- 是否正確使用四個獨立運算函式。
- 是否確實透過 Function Pointer 呼叫運算函式。
- 是否正確使用 libev Event Loop。
- 是否使用 Callback Function 處理 Timer 與 stdin Event。
- 程式是否符合 Non-blocking 要求。
- 時間是否可持續在固定位置更新。
- 是否可連續輸入並計算多個算式。
- 程式結構、可讀性與錯誤處理是否適當。

本作業重點在於整合 Stack、Function Pointer 與 Event-Driven Programming。程式除了必須正確計算算式外，也必須利用 libev 與 Callback Function，使時間更新與使用者輸入能在同一個 Event Loop 中以 Non-blocking 方式運作。
