Mafia Nights
Real-time multiplayer social deduction game for Android built with Qt 6.5.3 QML & Firebase Realtime Database.

A real-time social deduction game for 8+ players. Day phase is discussion and voting, night phase is using role abilities. Single-message chat system to increase mystery.

🎭 Roles
Mafia Team:

Boss - Kills at night
Mafia - Blocks one player's ability at night
Silencer - Silences a player for the next day
City Team:

Mayor - Vote counts as 2
Sniper - If he kills a non-mafia, he dies too
Medic - Saves one player at night
Kid - Can reveal any player's role
Citizen - Votes during day
✨ Features
Unlimited rooms by room name
Prevents joining after game started (started.json check)
Real-time chat (one active message per player for more mystery)
Smart voting system + Mayor x2 vote
Automatic 60s Day/Night cycle
Automatic win detection checkWin()
Mafia team can see each other only
Smooth QML UI with Flickable chat
🛠️ Tech Stack
Frontend: Qt 6.5.3 QML / Qt Quick
Backend: C++ Backend class with QNetworkAccessManager
Database: Firebase Realtime Database (REST API)
Platform: Android arm64-v8a
🔥 Firebase Structure
roomName/
  ├── count: int
  ├── started: 0/1
  ├── isNight: 0/1
  ├── players/{name}: {name, count}
  ├── roles/{name}: string
  ├── chat/{name}: {name, message}
  ├── votes/{name}: int
  ├── killed/{name}: "true"
  └── nightState/
      ├── blocked/{name}: "true"
      ├── saved/{name}: "true"
      └── silenced/{name}: "true"
🚀 How to Run
Replace base in backend.h with your Firebase URL:
cpp

QString base = "https://YOUR-PROJECT.firebaseio.com/";

2. In Qt Creator select Kit: `Android Qt 6.5.3 Clang arm64-v8a`
3. In Build Settings set: `ANDROID_ABIS = arm64-v8a`
4. Build & Run

### 🎮 How to Play

1. Join the same room name (min 8 players)
2. First player (count == 1) auto distributes roles via `distributeRoles()`
3. Day: Discuss and vote
4. Night: Use your role ability
5. Win: Mafia == 0 => City Wins, Mafia >= City => Mafia Wins

---
Made with ❤️ by Amin - Qt QML Mafia Project
