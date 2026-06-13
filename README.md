<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8" />
<meta name="viewport" content="width=device-width, initial-scale=1.0" />
<title>Generalized Tic-Tac-Toe — README</title>
<link href="https://fonts.googleapis.com/css2?family=JetBrains+Mono:wght@400;700&family=Orbitron:wght@700;900&family=Inter:wght@400;500;600&display=swap" rel="stylesheet" />
<style>
  *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

  :root {
    --bg:       #0a0c10;
    --surface:  #111520;
    --card:     #161b27;
    --border:   #1e2a40;
    --cyan:     #00e5ff;
    --purple:   #b57bff;
    --green:    #39ff6e;
    --amber:    #ffcc00;
    --red:      #ff4d6d;
    --blue:     #4d9eff;
    --text:     #d0daf0;
    --muted:    #6b7a99;
    --white:    #ffffff;
  }

  body {
    background: var(--bg);
    color: var(--text);
    font-family: 'Inter', sans-serif;
    font-size: 16px;
    line-height: 1.7;
    min-height: 100vh;
  }

  /* ── SCANLINE OVERLAY ── */
  body::before {
    content: '';
    position: fixed; inset: 0;
    background: repeating-linear-gradient(
      0deg,
      transparent,
      transparent 2px,
      rgba(0,0,0,0.07) 2px,
      rgba(0,0,0,0.07) 4px
    );
    pointer-events: none;
    z-index: 9999;
  }

  /* ── HERO ── */
  .hero {
    position: relative;
    text-align: center;
    padding: 72px 24px 56px;
    overflow: hidden;
    border-bottom: 1px solid var(--border);
  }

  .hero-grid {
    position: absolute; inset: 0;
    background-image:
      linear-gradient(rgba(0,229,255,0.05) 1px, transparent 1px),
      linear-gradient(90deg, rgba(0,229,255,0.05) 1px, transparent 1px);
    background-size: 48px 48px;
    animation: gridpulse 6s ease-in-out infinite;
  }

  @keyframes gridpulse {
    0%, 100% { opacity: 0.5; }
    50%       { opacity: 1; }
  }

  .hero-glow {
    position: absolute; inset: 0;
    background: radial-gradient(ellipse 60% 50% at 50% 0%, rgba(0,229,255,0.12), transparent 70%);
    pointer-events: none;
  }

  .hero-tag {
    display: inline-block;
    font-family: 'JetBrains Mono', monospace;
    font-size: 11px;
    letter-spacing: 3px;
    text-transform: uppercase;
    color: var(--cyan);
    border: 1px solid var(--cyan);
    padding: 4px 14px;
    border-radius: 2px;
    margin-bottom: 24px;
    position: relative;
  }

  .hero h1 {
    font-family: 'Orbitron', sans-serif;
    font-size: clamp(32px, 6vw, 68px);
    font-weight: 900;
    line-height: 1.05;
    letter-spacing: -1px;
    position: relative;
  }

  .hero h1 .line1 { color: var(--white); }
  .hero h1 .line2 {
    background: linear-gradient(90deg, var(--cyan), var(--purple));
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
  }

  .hero-sub {
    margin-top: 20px;
    font-size: 17px;
    color: var(--muted);
    position: relative;
    max-width: 520px;
    margin-inline: auto;
  }

  .badge-row {
    display: flex;
    flex-wrap: wrap;
    justify-content: center;
    gap: 10px;
    margin-top: 32px;
    position: relative;
  }

  .badge {
    font-family: 'JetBrains Mono', monospace;
    font-size: 12px;
    padding: 5px 14px;
    border-radius: 2px;
    border: 1px solid;
    letter-spacing: 0.5px;
  }

  .badge-cyan   { color: var(--cyan);   border-color: var(--cyan);   background: rgba(0,229,255,0.08); }
  .badge-purple { color: var(--purple); border-color: var(--purple); background: rgba(181,123,255,0.08); }
  .badge-green  { color: var(--green);  border-color: var(--green);  background: rgba(57,255,110,0.08); }
  .badge-amber  { color: var(--amber);  border-color: var(--amber);  background: rgba(255,204,0,0.08); }

  /* ── LAYOUT ── */
  .container { max-width: 900px; margin: 0 auto; padding: 0 24px; }

  section { padding: 56px 0; border-bottom: 1px solid var(--border); }
  section:last-child { border-bottom: none; }

  .section-label {
    font-family: 'JetBrains Mono', monospace;
    font-size: 11px;
    letter-spacing: 3px;
    text-transform: uppercase;
    color: var(--cyan);
    margin-bottom: 8px;
  }

  h2 {
    font-family: 'Orbitron', sans-serif;
    font-size: 24px;
    font-weight: 700;
    color: var(--white);
    margin-bottom: 28px;
  }

  h3 {
    font-size: 15px;
    font-weight: 600;
    color: var(--white);
    margin-bottom: 8px;
  }

  p { color: var(--text); margin-bottom: 12px; }

  /* ── BOARD VISUAL ── */
  .board-demo {
    display: flex;
    justify-content: center;
    margin: 40px 0;
  }

  .board {
    display: grid;
    grid-template-columns: repeat(3, 1fr);
    gap: 6px;
    background: var(--border);
    padding: 6px;
    border-radius: 4px;
    border: 1px solid var(--border);
  }

  .cell {
    width: 72px; height: 72px;
    background: var(--card);
    border-radius: 3px;
    display: flex; align-items: center; justify-content: center;
    font-family: 'Orbitron', sans-serif;
    font-size: 26px;
    font-weight: 900;
    border: 1px solid var(--border);
    transition: all 0.2s;
  }

  .cell-x { color: var(--purple); border-color: rgba(181,123,255,0.4); background: rgba(181,123,255,0.05); }
  .cell-o { color: var(--cyan);   border-color: rgba(0,229,255,0.4);   background: rgba(0,229,255,0.05); }
  .cell-w { color: var(--green);  border-color: rgba(57,255,110,0.5);  background: rgba(57,255,110,0.08); box-shadow: 0 0 16px rgba(57,255,110,0.15); }
  .cell-e { color: transparent; }

  /* ── FEATURE CARDS ── */
  .cards-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(240px, 1fr));
    gap: 16px;
  }

  .feature-card {
    background: var(--card);
    border: 1px solid var(--border);
    border-radius: 4px;
    padding: 24px;
    position: relative;
    overflow: hidden;
    transition: border-color 0.2s, transform 0.2s;
  }

  .feature-card::before {
    content: '';
    position: absolute;
    top: 0; left: 0; right: 0;
    height: 2px;
  }

  .fc-cyan::before   { background: var(--cyan); }
  .fc-purple::before { background: var(--purple); }
  .fc-green::before  { background: var(--green); }
  .fc-amber::before  { background: var(--amber); }
  .fc-red::before    { background: var(--red); }
  .fc-blue::before   { background: var(--blue); }

  .card-icon {
    font-size: 28px;
    margin-bottom: 12px;
  }

  /* ── MODES ── */
  .modes-grid {
    display: grid;
    grid-template-columns: 1fr 1fr;
    gap: 16px;
  }

  @media (max-width: 600px) {
    .modes-grid { grid-template-columns: 1fr; }
  }

  .mode-card {
    background: var(--card);
    border: 1px solid var(--border);
    border-radius: 4px;
    padding: 28px;
    position: relative;
    overflow: hidden;
  }

  .mode-card.player { border-color: rgba(0,229,255,0.3); }
  .mode-card.cpu    { border-color: rgba(181,123,255,0.3); }

  .mode-card .mode-icon {
    font-size: 40px;
    margin-bottom: 16px;
  }

  .mode-title {
    font-family: 'Orbitron', sans-serif;
    font-size: 16px;
    font-weight: 700;
    margin-bottom: 10px;
  }

  .player .mode-title { color: var(--cyan); }
  .cpu    .mode-title { color: var(--purple); }

  .mode-tag {
    display: inline-block;
    font-family: 'JetBrains Mono', monospace;
    font-size: 10px;
    letter-spacing: 1px;
    text-transform: uppercase;
    padding: 3px 10px;
    border-radius: 2px;
    margin-top: 12px;
  }

  .player .mode-tag { background: rgba(0,229,255,0.1);   color: var(--cyan);   border: 1px solid rgba(0,229,255,0.3); }
  .cpu    .mode-tag { background: rgba(181,123,255,0.1); color: var(--purple); border: 1px solid rgba(181,123,255,0.3); }

  /* ── CODE BLOCK ── */
  .code-block {
    background: #090c14;
    border: 1px solid var(--border);
    border-radius: 4px;
    padding: 0;
    overflow: hidden;
    margin: 16px 0;
  }

  .code-header {
    display: flex;
    align-items: center;
    gap: 8px;
    padding: 10px 16px;
    background: var(--surface);
    border-bottom: 1px solid var(--border);
  }

  .dot { width: 10px; height: 10px; border-radius: 50%; }
  .dot-r { background: var(--red); }
  .dot-y { background: var(--amber); }
  .dot-g { background: var(--green); }

  .code-lang {
    margin-left: auto;
    font-family: 'JetBrains Mono', monospace;
    font-size: 11px;
    color: var(--muted);
    letter-spacing: 1px;
    text-transform: uppercase;
  }

  pre {
    font-family: 'JetBrains Mono', monospace;
    font-size: 13px;
    line-height: 1.7;
    padding: 20px 20px;
    overflow-x: auto;
    color: var(--text);
  }

  .kw  { color: var(--purple); }
  .fn  { color: var(--cyan); }
  .str { color: var(--amber); }
  .cm  { color: var(--muted); font-style: italic; }
  .num { color: var(--green); }

  /* ── AI LOGIC ── */
  .logic-steps {
    display: flex;
    flex-direction: column;
    gap: 0;
    margin-top: 8px;
  }

  .logic-step {
    display: flex;
    align-items: flex-start;
    gap: 20px;
    padding: 20px 0;
    border-bottom: 1px solid var(--border);
  }

  .logic-step:last-child { border-bottom: none; }

  .step-num {
    font-family: 'Orbitron', sans-serif;
    font-size: 22px;
    font-weight: 900;
    min-width: 44px;
    line-height: 1;
  }

  .s1 .step-num { color: var(--red); }
  .s2 .step-num { color: var(--amber); }
  .s3 .step-num { color: var(--green); }

  .step-content h3 { margin-bottom: 4px; }

  /* ── WIN CONDITIONS ── */
  .win-grid {
    display: grid;
    grid-template-columns: repeat(4, 1fr);
    gap: 12px;
    margin-top: 8px;
  }

  @media (max-width: 560px) {
    .win-grid { grid-template-columns: repeat(2, 1fr); }
  }

  .win-card {
    background: var(--card);
    border: 1px solid var(--border);
    border-radius: 4px;
    padding: 20px 16px;
    text-align: center;
  }

  .win-icon { font-size: 32px; margin-bottom: 10px; }
  .win-label {
    font-family: 'JetBrains Mono', monospace;
    font-size: 12px;
    color: var(--muted);
    letter-spacing: 1px;
    text-transform: uppercase;
  }

  /* ── FILE STRUCTURE ── */
  .tree {
    font-family: 'JetBrains Mono', monospace;
    font-size: 14px;
    line-height: 1.9;
    padding: 20px 24px;
    background: #090c14;
    border: 1px solid var(--border);
    border-radius: 4px;
  }

  .tree-dir  { color: var(--amber); }
  .tree-file { color: var(--cyan); }
  .tree-ns   { color: var(--purple); }
  .tree-fn   { color: var(--green); }
  .tree-dim  { color: var(--muted); }

  /* ── REQUIREMENTS ── */
  .req-list {
    list-style: none;
    display: flex;
    flex-direction: column;
    gap: 10px;
  }

  .req-list li {
    display: flex;
    align-items: center;
    gap: 12px;
    background: var(--card);
    border: 1px solid var(--border);
    border-radius: 4px;
    padding: 14px 18px;
    font-size: 15px;
  }

  .req-icon {
    font-size: 20px;
    flex-shrink: 0;
  }

  /* ── AUTHOR ── */
  .author-card {
    background: var(--card);
    border: 1px solid rgba(0,229,255,0.2);
    border-radius: 4px;
    padding: 32px;
    display: flex;
    align-items: center;
    gap: 24px;
    flex-wrap: wrap;
  }

  .author-avatar {
    width: 72px; height: 72px;
    border-radius: 50%;
    background: linear-gradient(135deg, var(--cyan), var(--purple));
    display: flex; align-items: center; justify-content: center;
    font-family: 'Orbitron', sans-serif;
    font-size: 22px;
    font-weight: 900;
    color: var(--bg);
    flex-shrink: 0;
  }

  .author-name {
    font-family: 'Orbitron', sans-serif;
    font-size: 18px;
    font-weight: 700;
    color: var(--white);
    margin-bottom: 4px;
  }

  .author-id {
    font-family: 'JetBrains Mono', monospace;
    font-size: 13px;
    color: var(--cyan);
    margin-bottom: 6px;
  }

  /* ── FOOTER ── */
  .footer {
    text-align: center;
    padding: 40px 24px;
    border-top: 1px solid var(--border);
  }

  .footer p {
    font-family: 'JetBrains Mono', monospace;
    font-size: 12px;
    color: var(--muted);
    letter-spacing: 1px;
  }

  .footer-title {
    font-family: 'Orbitron', sans-serif;
    font-size: 15px;
    color: var(--cyan);
    margin-bottom: 8px;
  }

  /* ── DIVIDER ── */
  .divider {
    display: flex;
    align-items: center;
    gap: 12px;
    margin: 8px 0 28px;
  }

  .divider-line { flex: 1; height: 1px; background: var(--border); }
  .divider-dot  { width: 6px; height: 6px; border-radius: 50%; background: var(--cyan); }

  /* ── TABLE ── */
  table {
    width: 100%;
    border-collapse: collapse;
    font-size: 14px;
  }

  th {
    font-family: 'JetBrains Mono', monospace;
    font-size: 11px;
    letter-spacing: 2px;
    text-transform: uppercase;
    color: var(--cyan);
    border-bottom: 1px solid var(--border);
    padding: 10px 14px;
    text-align: left;
  }

  td {
    padding: 12px 14px;
    border-bottom: 1px solid rgba(30,42,64,0.6);
    color: var(--text);
  }

  tr:last-child td { border-bottom: none; }
  tr:hover td { background: rgba(0,229,255,0.03); }

  .tag-mono {
    font-family: 'JetBrains Mono', monospace;
    font-size: 13px;
    background: rgba(0,229,255,0.08);
    color: var(--cyan);
    padding: 2px 8px;
    border-radius: 2px;
    border: 1px solid rgba(0,229,255,0.2);
  }
</style>
</head>
<body>

<!-- ═══════════════════  HERO  ═══════════════════ -->
<div class="hero">
  <div class="hero-grid"></div>
  <div class="hero-glow"></div>

  <div class="hero-tag">C++ Console Game</div>

  <h1>
    <div class="line1">Generalized</div>
    <div class="line2">Tic-Tac-Toe</div>
  </h1>

  <p class="hero-sub">A fully customizable, multi-player Tic-Tac-Toe engine built for Windows — play on any grid size with any win condition.</p>

  <div class="badge-row">
    <span class="badge badge-cyan">Windows Console</span>
    <span class="badge badge-purple">C++ 11+</span>
    <span class="badge badge-green">Mouse Input</span>
    <span class="badge badge-amber">AI Opponent</span>
  </div>
</div>

<!-- ═══════════════════  BOARD DEMO  ═══════════════════ -->
<div class="container">
  <div class="board-demo">
    <div class="board">
      <div class="cell cell-o">O</div>
      <div class="cell cell-x">X</div>
      <div class="cell cell-e">-</div>
      <div class="cell cell-x">X</div>
      <div class="cell cell-w">O</div>
      <div class="cell cell-e">-</div>
      <div class="cell cell-e">-</div>
      <div class="cell cell-x">X</div>
      <div class="cell cell-w">O</div>
    </div>
  </div>
</div>

<!-- ═══════════════════  OVERVIEW  ═══════════════════ -->
<section>
  <div class="container">
    <div class="section-label">// overview</div>
    <h2>What is this?</h2>
    <div class="divider"><div class="divider-line"></div><div class="divider-dot"></div><div class="divider-line"></div></div>

    <p>This project is a <strong style="color:var(--white)">Generalized Tic-Tac-Toe</strong> game written in C++ that runs entirely in the Windows console. Unlike classic 3×3 Tic-Tac-Toe, every parameter is configurable — the board dimensions, the number of players, and how many symbols in a row are needed to win.</p>
    <p>The game supports two modes — Human vs. Human and Human vs. Computer — selectable from a colorized menu. Mouse clicks are captured directly from the console for cell selection.</p>

    <div class="cards-grid" style="margin-top: 28px;">
      <div class="feature-card fc-cyan">
        <div class="card-icon">🎮</div>
        <h3>Any Grid Size</h3>
        <p style="font-size:14px; color:var(--muted);">Define custom R×C boards, from tiny 3×3 to massive 100×100 arenas.</p>
      </div>
      <div class="feature-card fc-purple">
        <div class="card-icon">👥</div>
        <h3>Multi-Player</h3>
        <p style="font-size:14px; color:var(--muted);">HvH mode supports multiple human players, each with a unique name and symbol.</p>
      </div>
      <div class="feature-card fc-green">
        <div class="card-icon">🖱️</div>
        <h3>Mouse-Driven UI</h3>
        <p style="font-size:14px; color:var(--muted);">Cells are selected by left-clicking directly on the console board — no coordinate typing.</p>
      </div>
      <div class="feature-card fc-amber">
        <div class="card-icon">🤖</div>
        <h3>AI Opponent</h3>
        <p style="font-size:14px; color:var(--muted);">The computer opponent detects win threats, blocks the human, and plays strategically.</p>
      </div>
      <div class="feature-card fc-red">
        <div class="card-icon">🏆</div>
        <h3>Win Count Control</h3>
        <p style="font-size:14px; color:var(--muted);">Set how many consecutive symbols win the game — in any direction.</p>
      </div>
      <div class="feature-card fc-blue">
        <div class="card-icon">🎨</div>
        <h3>Colored Console</h3>
        <p style="font-size:14px; color:var(--muted);">Windows Console API colors distinguish players, turns, and game state visually.</p>
      </div>
    </div>
  </div>
</section>

<!-- ═══════════════════  GAME MODES  ═══════════════════ -->
<section>
  <div class="container">
    <div class="section-label">// game modes</div>
    <h2>Two Modes of Play</h2>
    <div class="divider"><div class="divider-line"></div><div class="divider-dot"></div><div class="divider-line"></div></div>

    <div class="modes-grid">
      <div class="mode-card player">
        <div class="mode-icon">👤👤</div>
        <div class="mode-title">Human vs Human</div>
        <p style="font-size:14px; color:var(--muted); margin-bottom:4px;">Two or more local players take turns clicking cells. Each player sets their own name and symbol at startup. Turn order is randomized each game.</p>
        <div class="mode-tag">namespace HvH</div>
      </div>
      <div class="mode-card cpu">
        <div class="mode-icon">👤🤖</div>
        <div class="mode-title">Human vs Computer</div>
        <p style="font-size:14px; color:var(--muted); margin-bottom:4px;">The human plays as <span class="tag-mono">O</span>, the computer as <span class="tag-mono">X</span>. The AI uses a priority-based strategy — attack first, defend second, then place randomly.</p>
        <div class="mode-tag">namespace HvC</div>
      </div>
    </div>
  </div>
</section>

<!-- ═══════════════════  WIN CONDITIONS  ═══════════════════ -->
<section>
  <div class="container">
    <div class="section-label">// win detection</div>
    <h2>Four-Directional Win Checking</h2>
    <div class="divider"><div class="divider-line"></div><div class="divider-dot"></div><div class="divider-line"></div></div>

    <p>After every move, the game checks all four axes for <strong style="color:var(--white)">N consecutive matching symbols</strong> (where N is your configured win count). Both forward and backward directions are checked for each axis.</p>

    <div class="win-grid">
      <div class="win-card">
        <div class="win-icon">➡️</div>
        <div style="font-size:15px; font-weight:600; color:var(--white); margin-bottom:4px;">Horizontal</div>
        <div class="win-label">HL()</div>
      </div>
      <div class="win-card">
        <div class="win-icon">⬇️</div>
        <div style="font-size:15px; font-weight:600; color:var(--white); margin-bottom:4px;">Vertical</div>
        <div class="win-label">VL()</div>
      </div>
      <div class="win-card">
        <div class="win-icon">↘️</div>
        <div style="font-size:15px; font-weight:600; color:var(--white); margin-bottom:4px;">Diagonal ↘↖</div>
        <div class="win-label">DUL()</div>
      </div>
      <div class="win-card">
        <div class="win-icon">↙️</div>
        <div style="font-size:15px; font-weight:600; color:var(--white); margin-bottom:4px;">Diagonal ↙↗</div>
        <div class="win-label">DLL()</div>
      </div>
    </div>
  </div>
</section>

<!-- ═══════════════════  AI LOGIC  ═══════════════════ -->
<section>
  <div class="container">
    <div class="section-label">// ai strategy</div>
    <h2>Computer Decision Logic</h2>
    <div class="divider"><div class="divider-line"></div><div class="divider-dot"></div><div class="divider-line"></div></div>

    <div class="logic-steps">
      <div class="logic-step s1">
        <div class="step-num">01</div>
        <div class="step-content">
          <h3 style="color:var(--red)">Win if Possible</h3>
          <p style="font-size:14px; color:var(--muted);">Scan every empty cell. Simulate placing <span class="tag-mono">X</span> there. If it triggers a win condition, play that cell immediately.</p>
        </div>
      </div>
      <div class="logic-step s2">
        <div class="step-num">02</div>
        <div class="step-content">
          <h3 style="color:var(--amber)">Block the Human</h3>
          <p style="font-size:14px; color:var(--muted);">If no winning move exists, scan again — this time simulating the human's <span class="tag-mono">O</span>. If the human can win on their next turn, block that cell.</p>
        </div>
      </div>
      <div class="logic-step s3">
        <div class="step-num">03</div>
        <div class="step-content">
          <h3 style="color:var(--green)">Random Placement</h3>
          <p style="font-size:14px; color:var(--muted);">If neither a win nor a threat is found, pick a random valid empty cell. This keeps the game unpredictable on larger boards.</p>
        </div>
      </div>
    </div>
  </div>
</section>

<!-- ═══════════════════  HOW TO PLAY  ═══════════════════ -->
<section>
  <div class="container">
    <div class="section-label">// how to play</div>
    <h2>Getting Started</h2>
    <div class="divider"><div class="divider-line"></div><div class="divider-dot"></div><div class="divider-line"></div></div>

    <p style="margin-bottom: 20px;">Compile and run the program in a Windows environment. The game launches a menu — choose your mode, configure parameters, and start clicking.</p>

    <div class="code-block">
      <div class="code-header">
        <span class="dot dot-r"></span><span class="dot dot-y"></span><span class="dot dot-g"></span>
        <span class="code-lang">Compile · MSVC / MinGW</span>
      </div>
      <pre><span class="cm">// MinGW (g++)</span>
g++ <span class="str">BSAI25022-PROJECT-2-MERGED.cpp</span> -o tictactoe.exe

<span class="cm">// MSVC (Developer Command Prompt)</span>
cl <span class="str">BSAI25022-PROJECT-2-MERGED.cpp</span> /Fe:tictactoe.exe</pre>
    </div>

    <p style="margin-top: 20px; margin-bottom: 12px;">When prompted, enter the configuration values:</p>

    <table>
      <thead>
        <tr>
          <th>Mode</th>
          <th>Prompt</th>
          <th>Example</th>
          <th>Meaning</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>HvH</td>
          <td><span class="tag-mono">NOP WinCount Rows Cols</span></td>
          <td><span class="tag-mono">2 3 5 5</span></td>
          <td>2 players, 3-in-a-row wins, 5×5 board</td>
        </tr>
        <tr>
          <td>HvC</td>
          <td><span class="tag-mono">WinCount Rows Cols</span></td>
          <td><span class="tag-mono">3 4 4</span></td>
          <td>3-in-a-row wins, 4×4 board vs CPU</td>
        </tr>
      </tbody>
    </table>

    <p style="margin-top: 20px;">After setup, the board is drawn in the console. <strong style="color:var(--white)">Left-click any empty cell</strong> to place your symbol. The game announces the winner or a draw automatically.</p>
  </div>
</section>

<!-- ═══════════════════  FILE STRUCTURE  ═══════════════════ -->
<section>
  <div class="container">
    <div class="section-label">// project structure</div>
    <h2>Code Architecture</h2>
    <div class="divider"><div class="divider-line"></div><div class="divider-dot"></div><div class="divider-line"></div></div>

    <div class="tree">
<span class="tree-dir">BSAI25022-PROJECT-2-MERGED.cpp</span>
│
├── <span class="tree-dim">// Global Constants</span>
│   ├── <span class="tree-fn">MAXROW, MAXCOL</span>  <span class="tree-dim">= 100</span>
│   └── <span class="tree-fn">Capacity</span>        <span class="tree-dim">= 100</span>
│
├── <span class="tree-dim">// Shared Utilities</span>
│   ├── <span class="tree-fn">showMenu()</span>              <span class="tree-dim">colored start menu</span>
│   ├── <span class="tree-fn">getRowColbyLeftClick()</span>  <span class="tree-dim">global mouse input</span>
│   ├── <span class="tree-fn">gotoRowCol()</span>            <span class="tree-dim">console cursor control</span>
│   └── <span class="tree-fn">color()</span>                 <span class="tree-dim">console text coloring</span>
│
├── <span class="tree-ns">namespace HvH</span>  <span class="tree-dim">(Human vs Human)</span>
│   ├── <span class="tree-fn">input()</span>         <span class="tree-dim">reads players, grid, win count</span>
│   ├── <span class="tree-fn">displayboard()</span>  <span class="tree-dim">prints current grid</span>
│   ├── <span class="tree-fn">iswin()</span>         <span class="tree-dim">checks HL · VL · DUL · DLL</span>
│   ├── <span class="tree-fn">isDraw()</span>        <span class="tree-dim">all cells filled check</span>
│   ├── <span class="tree-fn">turnchange()</span>    <span class="tree-dim">cycles through NOP players</span>
│   └── <span class="tree-fn">run()</span>           <span class="tree-dim">main game loop</span>
│
├── <span class="tree-ns">namespace HvC</span>  <span class="tree-dim">(Human vs Computer)</span>
│   ├── <span class="tree-fn">input()</span>                    <span class="tree-dim">reads grid and win count</span>
│   ├── <span class="tree-fn">displayboard()</span>             <span class="tree-dim">space-separated grid</span>
│   ├── <span class="tree-fn">getRowColbyLeftClick()</span>     <span class="tree-dim">X÷2 offset for spaced grid</span>
│   ├── <span class="tree-fn">computer()</span>                 <span class="tree-dim">AI: win → block → random</span>
│   ├── <span class="tree-fn">iswin() · isDraw()</span>         <span class="tree-dim">continuous win checkers</span>
│   └── <span class="tree-fn">run()</span>                      <span class="tree-dim">main game loop</span>
│
└── <span class="tree-fn">main()</span>  <span class="tree-dim">menu loop → dispatches HvH or HvC</span>
    </div>
  </div>
</section>

<!-- ═══════════════════  REQUIREMENTS  ═══════════════════ -->
<section>
  <div class="container">
    <div class="section-label">// requirements</div>
    <h2>System Requirements</h2>
    <div class="divider"><div class="divider-line"></div><div class="divider-dot"></div><div class="divider-line"></div></div>

    <ul class="req-list">
      <li><span class="req-icon">🪟</span> <div><strong style="color:var(--white)">Windows OS</strong> — uses <span class="tag-mono">&lt;windows.h&gt;</span>, <span class="tag-mono">&lt;conio.h&gt;</span>, and Win32 Console API</div></li>
      <li><span class="req-icon">⚙️</span> <div><strong style="color:var(--white)">C++11 or later</strong> — compile with g++ (MinGW) or MSVC</div></li>
      <li><span class="req-icon">🖱️</span> <div><strong style="color:var(--white)">Mouse input enabled</strong> — the console window must support <span class="tag-mono">ENABLE_MOUSE_INPUT</span></div></li>
      <li><span class="req-icon">🖥️</span> <div><strong style="color:var(--white)">Windows Console</strong> — does <em>not</em> work in VS Code's integrated terminal; run from <span class="tag-mono">cmd.exe</span> or a native console window</div></li>
      <li><span class="req-icon">📦</span> <div><strong style="color:var(--white)">No external libraries</strong> — uses only the C++ standard library and Windows SDK headers</div></li>
    </ul>
  </div>
</section>

<!-- ═══════════════════  AUTHOR  ═══════════════════ -->
<section>
  <div class="container">
    <div class="section-label">// author</div>
    <h2>About This Project</h2>
    <div class="divider"><div class="divider-line"></div><div class="divider-dot"></div><div class="divider-line"></div></div>

    <div class="author-card">
      <div class="author-avatar">BS</div>
      <div>
        <div class="author-name">Student Project</div>
        <div class="author-id">ID: BSAI25022</div>
        <p style="font-size:14px; color:var(--muted); margin:0;">Project 2 — Generalized Tic-Tac-Toe<br>Submitted as part of a BS Artificial Intelligence curriculum.</p>
      </div>
    </div>
  </div>
</section>

<!-- ═══════════════════  FOOTER  ═══════════════════ -->
<div class="footer">
  <div class="footer-title">GENERALIZED TIC-TAC-TOE</div>
  <p>BSAI25022 · C++ Windows Console Game · Project 2</p>
  <p style="margin-top:6px;">Built with &lt;windows.h&gt; · No dependencies · Mouse-driven</p>
</div>

</body>
</html>
