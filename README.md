![image](https://github.com/user-attachments/assets/efcf8fbb-b116-4a66-8510-5b91da7726e3) RISC-V 裸机 LeNet-5 推理系统
Bare-metal LeNet-5 Inference System on RISC-V
本项目实现了 LeNet-5 卷积神经网络在裸机 RISC-V SystemC 模拟器中的推理运行，支持双架构 RV32IMAC 与 RV64IMAC，适用于系统级建模、指令集对比、AI 推理性能分析等研究任务。
This project implements the forward inference of the LeNet-5 CNN on a bare-metal RISC-V SystemC simulator, supporting both RV32IMAC and RV64IMAC architectures. It is suitable for research on system-level modeling, ISA comparison, and AI inference performance evaluation.

主要文件结构 | Project Structure

├── main.cpp               // 推理主控程序 | Main entry and inference loop
├── lenet_layer.cpp        // LeNet 各层实现 | Layer functions (conv, pool, FC)
├── trace_io.cpp/.h        // 裸机输出支持 | Bare-metal trace output library
├── timer.h                // 时间统计模块 | Cycle-based timing utilities
├── *_weight.h, *_bias.h   // 训练权重头文件 | Trained weights and biases
├── train_images.h         // 测试样本（头文件形式）| Embedded test image samples
├── link.ld.txt            // 自定义链接脚本 | Custom linker script
├── Makefile.txt           // 支持架构切换的构建脚本 | Makefile for build and hex generation
└── _start.S               // 程序入口汇编文件 | Bare-metal program entry (startup code)
⚙️ 构建方法 | Build Instructions
环境要求 | Requirements
RISC-V GNU Toolchain: riscv64-unknown-elf-g++  （构建时启用交叉编译的选项）

SystemC 2.3.3+

支持 .hex 加载的 SystemC-TLM 模拟器（如 mariusmm/RISC-V-TLM）

编译步骤 | Build Steps

# 构建 RV64IMAC /RV32IMAC 版本

make clean && make TARGET_ARCH=rv64imac / TARGET_ARCH=rv32imac
按照makefile运行并输出hex文件用于模拟
Output file: main.hex, ready to be loaded into the simulator.

运行说明 | How to Run
本项目（ 在mariusmm/RISC-V-TLM模拟器中）运行时需指定启用xterm来读取数据，所以运行代码为：
To run this project using the mariusmm/RISC-V-TLM simulator, you must explicitly enable xterm to read output data from the simulator. The command to execute is:

xterm -hold  -e your/simulator/address/RISCV_TLM -R 64  your/hex/file/address/main.hex

Attention: "-R 64 " 可能是特定对于mariusmm/RISC-V-TLM模拟器，其作用是指定模拟器生成64/32位模拟器，按需修改。
Attention："-R 64 " may specificly for mariusmm/RISC-V-TLM simulator to generate 64/32-bit simulators ， modify them as needed.

数据集：MNIST 手写数字集（前100张）
Dataset: MNIST handwritten digits (first 100 samples)

权重来源：PyTorch 训练模型转为 .h 数组
Weights: Extracted from PyTorch-trained model and exported as C++ headers

作者信息 | Author
学生姓名 | Name：穆泰宇 (Taiyu Mu)

指导教师 | Supervisor：刘屹秋 (YiQiu Liu)

学校 | School：华南理工大学 微电子学院 (SCUT School of Microelectronics)

毕业设计方向 | Thesis Topic：基于 SystemC 的 RISC-V 架构建模与推理性能分析
System-level modeling of RISC-V processors and performance benchmarking with CNN tasks

📄 许可协议 | License
本项目仅用于教学和研究用途，未经许可请勿商业使用。
For academic and educational use only. Commercial use without permission is prohibited.
