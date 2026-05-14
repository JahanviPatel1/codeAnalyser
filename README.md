# CodeAnalyser 🧠

![Architecture](https://img.shields.io/badge/Architecture-Static%20Analysis-blue)
![Frontend](https://img.shields.io/badge/Frontend-React%20%2B%20Vite-61DAFB)
![Backend](https://img.shields.io/badge/Backend-Node.js%20%7C%20Express-green)
![Engine](https://img.shields.io/badge/Engine-C%2B%2B-orange)
![Database](https://img.shields.io/badge/Database-SQLite3-lightgrey)
![Authentication](https://img.shields.io/badge/Auth-JWT%20%7C%20Bcrypt-red)

CodeAnalyser is a full-stack static code analysis platform built to help developers detect and understand "spaghetti code" before execution. The platform analyzes C++ source files and provides structural insights such as cyclomatic complexity, maintainability concerns, and code organization metrics.

Designed with performance and modularity in mind, CodeAnalyser combines a modern React frontend with a powerful C++ analysis engine connected through a Node.js backend.

---

# ✨ Features

* 🔍 Static analysis of C++ codebases
* 📊 Cyclomatic complexity detection
* 🧩 Structural code insights and maintainability analysis
* ⚡ Fast execution using native C++ processing
* 🔐 Secure authentication with JWT & Bcrypt
* 🎨 Responsive frontend built with React + Vite
* 🗄️ Lightweight SQLite3 database integration
* 🔗 Backend-engine communication using child processes

---

# 🏗️ Tech Stack

## Frontend

* React
* Vite
* Context API
* CSS

## Backend

* Node.js
* Express.js
* JWT Authentication
* Bcrypt

## Analysis Engine

* C++
* Static Code Parsing
* Cyclomatic Complexity Analysis

## Database

* SQLite3

---

# 📂 Project Structure

```bash
codeAnalyser/
│
├── backend/           # Express backend APIs
├── frontend/          # React + Vite frontend
├── include/           # Header files for C++ engine
├── src/               # Core C++ source files
├── obj/               # Compiled object files
├── bin/               # Generated binaries
├── node_modules/      # Node dependencies
│
├── monster_code.cpp   # Sample analysis file
├── test_code.cpp      # Testing source file
├── test_integration.js
│
├── Makefile           # C++ build automation
├── package.json
├── package-lock.json
├── build.gradle
│
└── README.md
```

---

# ⚙️ How It Works

1. The user uploads or submits C++ code through the frontend.
2. The Node.js backend receives the request.
3. The backend spawns the C++ static analysis engine using child processes.
4. The engine parses the source code and calculates metrics such as:

   * Cyclomatic Complexity
   * Function Structure
   * Conditional Depth
   * Maintainability Indicators
5. Results are returned to the frontend and displayed visually.

---

# 🚀 Getting Started

## Prerequisites

Make sure you have the following installed:

* Node.js
* npm
* g++ compiler
* Make

---

## Installation

### 1. Clone the repository

```bash
git clone https://github.com/your-username/codeAnalyser.git
cd codeAnalyser
```

### 2. Install frontend & backend dependencies

```bash
npm install
```

### 3. Build the C++ analysis engine

```bash
make
```

### 4. Start the development server

```bash
npm run dev
```

---

# 🧪 Sample Analysis Goals

The platform is designed to identify:

* Excessive nested conditionals
* Highly coupled functions
* Complex branching structures
* Poor maintainability patterns
* Potentially unreadable logic flows

---

# 🔒 Authentication

CodeAnalyser uses:

* JWT for secure session handling
* Bcrypt for password hashing

---

# 📈 Future Improvements

* Multi-language static analysis support
* AI-generated code quality suggestions
* Real-time editor integration
* Visualization dashboards
* GitHub repository scanning
* Exportable analysis reports

---

# 🌐 Deployment

Frontend deployment can be done using:

* Vercel
* Netlify

Backend deployment options:

* Render
* Railway
* Docker

---

# 👩‍💻 Author

**Jahanvi Patel**

Built with a passion for developer tools, performance engineering, and clean code analysis
