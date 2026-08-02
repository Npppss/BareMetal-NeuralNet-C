# 🧠 Bare-Metal Neural Network in pure C

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Dependencies](https://img.shields.io/badge/Dependencies-None-brightgreen.svg)
![Focus](https://img.shields.io/badge/Focus-AI_Research_%26_Math-orange.svg)

## 📌 Overview
This repository contains a from-scratch implementation of an Artificial Neural Network (ANN) written entirely in **pure C**. 

While modern Deep Learning frameworks like PyTorch and TensorFlow abstract away the underlying mathematics and memory management, this project takes a *bare-metal* approach. The goal is to build a profound understanding of the core mechanics that drive machine learning algorithms—from dynamic memory allocation for matrices to implementing the Chain Rule for backpropagation by hand.

This project was built as a foundational stepping stone towards advanced AI research and a future M.Phil degree in Machine Learning.

## ✨ Features
* **Zero External ML Libraries:** No PyTorch, no TensorFlow, not even NumPy. Everything is built from the ground up.
* **Custom Matrix Engine:** Features a bespoke 2D matrix structure utilizing `malloc` and `calloc` for dynamic memory management, completely avoiding memory leaks.
* **Math Operations from Scratch:** Implements $O(n^3)$ matrix dot products, matrix transposition, and element-wise operations.
* **Modular Layer Architecture:** Utilizes C `structs` to encapsulate layer properties (Weights, Biases, Outputs) mimicking the behavior of PyTorch's `nn.Linear`.
* **Manual Backpropagation:** Calculates loss gradients (MSE) and propagates errors backwards through the Sigmoid activation derivative using raw calculus.

## 🧰 Project Architecture

The engine is divided into core logical components:
1. `Matrix Infrastructure`: Handles creation, multiplication (`dot_product`), and safe destruction (`free_matrix`) of 2D arrays.
2. `Dense Layer Struct`: Encapsulates weights, biases, and caches intermediate states ($Z$ and $A$) required for backpropagation.
3. `Activation Functions`: Implements Sigmoid and its derivative.
4. `Training Loop`: Executes the Forward Pass, Loss calculation, Backward Pass, and Weight/Bias updates via Gradient Descent.

## 🚀 How to Compile and Run

Because this project uses the standard math library (`<math.h>`) for exponential calculations, it requires the `-lm` flag when compiling with GCC on Linux/macOS.

**1. Clone the repository:**
```bash
git clone [https://github.com/Npppss/BareMetal-NeuralNet-C.git](https://github.com/Npppss/BareMetal-NeuralNet-C.git)
cd BareMetal-NeuralNet-C