// *************************************************************************
//
// Copyright (c) 2020 Andrei Gramakov. All rights reserved.
//
// This file is licensed under the terms of the MIT license.
// For a copy, see: https://opensource.org/licenses/MIT
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include <stdint.h>

class VirtualRegs {
protected:
    bool inited;
    uint32_t regs_ammount;
    uint32_t selected_reg;
    uint8_t *registers;

public:
    VirtualRegs() = default;
    VirtualRegs(uint32_t regs_num);
    void Init(uint32_t regs_num);
    void Deinit(void);
    uint8_t *GetRegs(void);
    uint32_t GetRegsAmmount(void);
    void SelectReg(uint32_t num);
    void SelectNextReg(void);
    uint32_t GetSelectedRegNum(void);
    void SetReg(uint8_t val);
    void SetRegAndNext(uint8_t val);
    uint8_t GetReg(void);
    uint8_t GetRegAndNext(void);
};

void RegistersRequest(VirtualRegs *regs);
void RegistersRecieve(VirtualRegs *regs);