# A Performance Study of Crypto-Hardware in the Low-end IoT (EWSN 2021)

[![Paper][paper-badge]][paper-link]
[![Preprint][preprint-badge]][preprint-link]

This repository contains code and documentation to reproduce experimental results of the paper **"[A Performance Study of Crypto-Hardware in the Low-end IoT][preprint-link]"** published in Proc. of the EWSN Conference 2021.

* Peter Kietzmann, Lena Boeckmann, Leandro Lanzieri, Thomas C. Schmidt, Matthias Wählisch,
**A Performance Study of Crypto-Hardware in the Low-end IoT**,
In: International Conference on Embedded Wireless Systems and Networks (EWSN), ACM: New York, USA, February 2021.

 **Abstract**
 > In this paper, we contribute a comprehensive resource analysis for widely used cryptographic primitives across different off-the-shelf IoT platforms, and quantify the performance impact of crypto-hardware. This work builds on the newly designed crypto-subsystem of the IoT operating system RIOT, which provides seamless crypto support across software and hardware components. Our evaluations show that (i) hardware-based crypto outperforms software by considerably over 100 %, which is crucial for nodal lifetime. Despite, the memory consumption typically increases moderately. (ii) Hardware diversity, driver design, and software implementations heavily impact resource efficiency. (iii) External crypto-chips operate slowly on symmetric crypto-operations, but provide secure write-only memory for private credentials, which is unavailable on many platforms.

Please follow our [Getting Started](getting_started.md) instructions for further information how to compile and execute the code.

<!-- TODO: update URLs -->
[paper-link]:https://dl.acm.org/doi/10.5555/3451271.3451279
[preprint-link]:https://eprint.iacr.org/2021/058
[paper-badge]: https://img.shields.io/badge/Paper-ACM%20DL-green
[preprint-badge]: https://img.shields.io/badge/Preprint-IACR-green