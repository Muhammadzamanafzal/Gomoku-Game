<div align="center">

<img src="https://readme-typing-svg.demolab.com?font=Orbitron&weight=900&size=40&pause=1000&color=00E5FF&center=true&vCenter=true&width=600&height=80&lines=Gomoku-Game" alt="Typing SVG" />

<br/>

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Console](https://img.shields.io/badge/Console_App-1e2a40?style=for-the-badge&logo=windowsterminal&logoColor=00E5FF)
![Mouse Input](https://img.shields.io/badge/Mouse_Driven-39ff6e?style=for-the-badge&logoColor=black)
![AI](https://img.shields.io/badge/AI_Opponent-b57bff?style=for-the-badge&logoColor=white)

<br/>

> **A fully customizable, multi-player Gomoku-Game engine built for the Windows Console.**  
> Play on any grid size, with any number of players, and any win condition.

</div>

---

## 🎮 &nbsp;What Is This?

This is a **Gomoku-Game** game written in C++ that runs entirely in the Windows console. Unlike classic 3×3 Tic-Tac-Toe, every parameter is configurable — the board dimensions, number of players, and how many symbols in a row are needed to win.

The game supports **two modes** selectable from a colorized menu. Mouse clicks are captured directly from the console for cell selection — no coordinate typing required.

---

## ✨ &nbsp;Features

| Feature | Description |
|---|---|
| 🎮 **Any Grid Size** | Define custom R×C boards, from tiny 3×3 to massive 100×100 arenas |
| 👥 **Multi-Player** | HvH mode supports multiple human players, each with unique name & symbol |
| 🖱️ **Mouse-Driven UI** | Left-click directly on the console board to place your symbol |
| 🤖 **AI Opponent** | Computer detects win threats, blocks the human, and plays strategically |
| 🏆 **Win Count Control** | Configure how many consecutive symbols are needed to win |
| 🎨 **Colored Console** | Windows Console API colors distinguish players, turns, and game state |

---

## 🕹️ &nbsp;Game Modes

<table>
<tr>
<td width="50%" valign="top">

### 👤👤 &nbsp;Human vs Human
```
namespace HvH
```
Two or more local players take turns clicking cells. Each player configures their own **name** and **symbol** at startup. Turn order is **randomized** each game.

</td>
<td width="50%" valign="top">

### 👤🤖 &nbsp;Human vs Computer
```
namespace HvC
```
The human plays as `O`, the computer as `X`. The AI uses a **priority-based strategy** — attack first, defend second, then place randomly.

</td>
</tr>
</table>

---

## 🏆 &nbsp;Win Detection — Four Directions

After every move, the game checks **all four axes** for N consecutive matching symbols in both directions:

```
  ➡️  Horizontal    ──────────    HL()
  ⬇️  Vertical      │││││││││    VL()
  ↘️  Diagonal      ╲╲╲╲╲╲╲╲╲   DUL()
  ↙️  Anti-Diagonal ╱╱╱╱╱╱╱╱╱   DLL()
```

```cpp
bool iswin(Board, R, C, r, c, PSYM, winC) {
    return HL(...)  // horizontal
        || VL(...)  // vertical
        || DUL(...) // diagonal ↘↖
        || DLL(...) // diagonal ↙↗
}
```

---

## 🤖 &nbsp;AI Strategy

The computer (`namespace HvC`) uses a **3-priority decision tree**:

```
┌─────────────────────────────────────────────────────────┐
│  01 🔴  WIN IF POSSIBLE                                  │
│         Scan every empty cell → simulate X there        │
│         → if iswin() triggers → PLAY THAT CELL          │
├─────────────────────────────────────────────────────────┤
│  02 🟡  BLOCK THE HUMAN                                  │
│         Simulate O on every empty cell                  │
│         → if human would win next turn → BLOCK IT       │
├─────────────────────────────────────────────────────────┤
│  03 🟢  RANDOM PLACEMENT                                 │
│         No win or threat found?                         │
│         → Pick a random valid empty cell                │
└─────────────────────────────────────────────────────────┘
```

---

## 🚀 &nbsp;Getting Started

### Prerequisites

- ✅ **Windows OS** — uses `<windows.h>`, `<conio.h>`, and Win32 Console API
- ✅ **C++11 or later** — compile with g++ (MinGW) or MSVC
- ✅ **Native Console** — run from `cmd.exe`, **not** VS Code's integrated terminal
- ✅ **No external libraries** — only C++ standard library + Windows SDK

### Compile & Run

```bash
# MinGW / g++
g++ BSAI25022-PROJECT-2-MERGED.cpp -o tictactoe.exe
./tictactoe.exe

# MSVC (Developer Command Prompt)
cl BSAI25022-PROJECT-2-MERGED.cpp /Fe:tictactoe.exe
tictactoe.exe
```

### Configuration at Startup

| Mode | Console Prompt | Example Input | Meaning |
|---|---|---|---|
| **HvH** | `NOP WinCount Rows Cols` | `2 3 5 5` | 2 players, 3-in-a-row wins, 5×5 board |
| **HvC** | `WinCount Rows Cols` | `3 4 4` | 3-in-a-row wins, 4×4 board vs CPU |

After setup — **left-click any empty cell** to place your symbol. The game announces the winner or draw automatically.

---

## 🗂️ &nbsp;Code Architecture

```
BSAI25022-PROJECT-2-MERGED.cpp
│
├── Global Constants
│   ├── MAXROW, MAXCOL      = 100
│   └── Capacity            = 100
│
├── Shared Utilities (global scope)
│   ├── showMenu()              → colored start menu
│   ├── getRowColbyLeftClick()  → raw Win32 mouse input
│   ├── gotoRowCol()            → console cursor positioning
│   └── color()                 → SetConsoleTextAttribute wrapper
│
├── namespace HvH  ──────────────── Human vs Human
│   ├── input()         → reads NOP, winCount, grid size, names, symbols
│   ├── displayboard()  → prints current board state
│   ├── iswin()         → delegates to HL · VL · DUL · DLL
│   ├── isDraw()        → checks if all cells are filled
│   ├── turnchange()    → cycles turn through NOP players
│   └── run()           → main game loop
│
├── namespace HvC  ──────────────── Human vs Computer
│   ├── input()                   → reads winCount + grid size
│   ├── displayboard()            → space-separated grid output
│   ├── getRowColbyLeftClick()    → X÷2 offset for spaced grid
│   ├── computer()                → AI: win → block → random
│   ├── iswin() · isDraw()        → rewritten continuous checkers
│   └── run()                     → main game loop
│
└── main()  → menu loop → dispatches HvH::run() or HvC::run()
```

---

## 📋 &nbsp;How to Play

```
1. Launch tictactoe.exe in cmd.exe
2. Select mode: [1] Human vs Human  [2] Human vs Computer  [3] Exit
3. Enter board configuration when prompted
4. Board appears — LEFT-CLICK a cell to place your symbol
5. First to get WinCount symbols in a row wins!
6. Board full with no winner = DRAW
```

---

## 🧩 &nbsp;Sample Gameplay

```
  Turn: Player1 (O)

  O X -
  X O -
  - X O     ← O wins diagonally!

  Player1(O) wins the game!
```

---

<div align="center">

---

** Muhammad Zaman Afzal** &nbsp;·&nbsp; BS Artificial Intelligence &nbsp;·&nbsp; first semseterProject 2

*Built with `<windows.h>` &nbsp;·&nbsp; No dependencies &nbsp;·&nbsp; Mouse-driven console game*

![Visitors](https://visitor-badge.laobi.icu/badge?page_id=BSAI25022.tictactoe&style=flat-square&color=00e5ff)

</div>
