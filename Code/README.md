## AXI_IP/
- contains code used to package AES core into AXI4-Lite IP.

## SDK/
- contains C++ code used in Xilinx SDK for benchmarking.

## rtl_code/ 
- contains all verilog AES encryption modules used.
- all verilog modules in this folder were originally created by Rudolf Usselmann from https://github.com/freecores/aes_core .
- aes_cipher_top.v was modified by our group, see comments. 

## testbench/
- contains our tenchbench used to verify that the AES algorithm written in verilog works properly. 
