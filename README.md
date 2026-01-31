
# OFDM Physical Layer Simulation in C

## Abstract

This repository implements a **baseband Orthogonal Frequency Division Multiplexing (OFDM) physical-layer (PHY) simulation** written in **C**, with the objective of providing a **technically rigorous, transparent, and extensible reference implementation**. The project focuses on **signal processing fundamentals**, **algorithmic correctness**, and **progressive extension toward real-time Software-Defined Radio (SDR) systems**.

The implementation follows a **from-first-principles design philosophy**, avoiding black-box abstractions and emphasizing mathematical clarity, modularity, and verifiability.

---

## Motivation

OFDM is the dominant modulation scheme in modern wireless communication standards such as **LTE, 5G NR, Wi‑Fi (IEEE 802.11), and DVB**. While many high-level simulations exist, fewer projects provide a **low-level C-based PHY implementation** suitable for:

- Algorithm verification and validation  
- Embedded and real-time execution  
- SDR deployment  
- Performance analysis under realistic channel impairments  

This project aims to bridge that gap by offering a **clean, educational, yet professional OFDM PHY reference**.

---

## System Model

### Discrete-Time OFDM Signal

Let  
- $N$ be the number of subcarriers  
- $X[k]$ be the complex QAM symbol mapped to the $k$-th subcarrier  

The discrete-time OFDM symbol is generated using the IFFT:

```math
x[n] = \frac{1}{\sqrt{N}} \sum_{k=0}^{N-1} X[k] e^{j \frac{2\pi}{N} kn}, \quad n = 0,1,\dots,N-1
```

---

### Cyclic Prefix (CP)

To mitigate inter-symbol interference (ISI) caused by multipath channels, a cyclic prefix of length $N_{cp}$ is prepended:

```math
x_{cp}[n] =
\begin{cases}
x[n + N], & -N_{cp} \le n < 0 \\
x[n], & 0 \le n < N
\end{cases}
```

---

### Channel Model

The received signal is modeled as:

```math
y[n] = (x_{cp}[n] * h[n]) + w[n]
```

where:
- $h[n]$ is the discrete-time channel impulse response  
- $w[n] \sim \mathcal{CN}(0, \sigma^2)$ is complex AWGN  

After CP removal and FFT:

```math
Y[k] = H[k] X[k] + W[k]
```

---

### Equalization

#### Zero-Forcing (ZF)

```math
\hat{X}_{ZF}[k] = \frac{Y[k]}{H[k]}
```

#### MMSE

```math
\hat{X}_{MMSE}[k] =
\frac{H^*[k]}{|H[k]|^2 + \frac{\sigma^2}{E_s}} Y[k]
```

where $E_s$ is the average symbol energy.

---

## Modulation

Supported modulation schemes:
- **16-QAM**
- **32-QAM**
- **64-QAM**

Each constellation uses:
- Gray coding  
- Average power normalization:
```math
E[|X[k]|^2] = 1
```

---

## Transceiver Architecture

### Transmitter (TX)

1. Random bitstream generation  
2. M-QAM mapping  
3. Subcarrier allocation  
4. IFFT-based OFDM modulation  
5. Cyclic prefix insertion  
6. Frame construction  

---

### Receiver (RX)

1. Cyclic prefix removal  
2. FFT-based OFDM demodulation  
3. Channel estimation  
4. Frequency-domain equalization  
5. QAM demapping  
6. Bitstream reconstruction  

---

## Performance Metrics

### Bit Error Rate (BER)

```math
\text{BER} = \frac{N_{error}}{N_{total}}
```

### Error Vector Magnitude (EVM)

```math
\text{EVM}_{rms} =
\sqrt{\frac{E[|X - \hat{X}|^2]}{E[|X|^2]}}
```

---

## Roadmap

### 1. OFDM Transmitter
- QAM (16 / 32 / 64)  
- IFFT processing  
- CP insertion  
- Power normalization  

### 2. OFDM Receiver
- FFT processing  
- Demapping  
- Bit recovery  

### 3. Channel Modeling
- AWGN  
- Multipath fading  
- CFO and phase noise (optional)  

### 4. Channel Estimation & Equalization
- Pilot-based estimation  
- ZF and MMSE equalizers  

### 5. Performance Evaluation
- BER vs. SNR  
- SER and EVM  

### 6. SDR Integration
- Real-time I/Q streaming  
- Over-the-air testing  

---

## Implementation Philosophy

- Pure **C language** for portability and performance  
- Modular DSP blocks  
- Minimal external dependencies  
- Designed for unit testing and verification  

---

## Verification Strategy

- MATLAB reference models  
- AWGN validation against theoretical BER  
- Incremental block-level testing  

---

## Status

🚧 **Work in Progress**

Core transmitter modules are under active development. Receiver processing, channel models, and equalization will follow.

---

## Intended Audience

- Graduate students in communications  
- Wireless PHY engineers  
- SDR developers  
- DSP researchers  

---

## Future Extensions

- Time/frequency synchronization  
- PAPR reduction  
- MIMO-OFDM  
- LTE / 5G NR numerology  
- Fixed-point optimization  

---

## License


This project is licensed under the **GNU General Public License v3.0 (GPL-3.0)**.

You are free to use, study, modify, and distribute this software under the terms
of the GPL-3.0 license. Any derivative work must also be released under the same
license.

See the `LICENSE` file for full details.

---

## Author Notes

This project serves as both a **learning framework** and a **technical OFDM reference implementation**. Contributions and discussions are welcome.