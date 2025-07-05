# 🔐 Perceptron-Based Dynamic Firewall Rule Classifier in C

> A fun little project born from curiosity and code experiments 💡

---

## 📌 About This Project

This project is a **Perceptron-based packet classifier**, handcrafted in pure C.

It started with a simple thought:  
💭 *"What if I built my first machine learning model — but from scratch, in C?"*

And so, this project was born.  
Not for production. Not for perfection.  
Just for me — to **revise my Data Structures concepts**, play with **pointers**, **structs**, and feel the beauty of low-level machine learning.

---

## 🎯 What It Does

- Simulates a **single-layer perceptron**
- Trains it to classify packets as **malicious (1)** or **safe (0)**
- Each packet is represented by 5 simple features:
  - Source IP Class
  - Destination Port
  - Protocol
  - Packet Size
  - Flags

---

## 💡 Why I Made This

- I wanted to **build something ML-like** without libraries.
- I wanted to **sharpen my C skills**.
- I wanted a small, complete, self-contained project I could smile back at someday.
- And mostly — because it was fun.

---

## 🧠 What I Learned

- How the **Perceptron algorithm** really works (mathematically and programmatically)
- How to manage memory using `malloc` / `free`
- Using **structs** to represent real-world data
- Applying **dot product**, weight updates, and bias tweaks manually
- The joy of watching predictions change as weights learn 📈

---

## 📂 File Structure
