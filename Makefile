PWD = $(shell pwd)
SRCS = $(shell find $(PWD) | grep -xPo '.*\.(cpp|c|S)')
INC_PATH = $(PWD) firrtl-sig
NAME = essent
BIN ?= program/microbench-rv64gc
ARCH=riscv64-mycpu
CXXFLAGS += -Wno-error=unused-but-set-variable
ASFLAGS += -DBIN=\"$(BIN).bin\"

include $(AM_HOME)/Makefile
