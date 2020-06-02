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

#include <stdio.h>
#include <stdlib.h>
#include "VirtualRegs.h"

VirtualRegs::VirtualRegs(uint32_t regs_num) : regs_ammount(0),
                                              selected_reg(0),
                                              registers(NULL) {
    Init(regs_num);
}

void VirtualRegs::Init(uint32_t regs_num) {
    this->regs_ammount = regs_num;
    this->registers = (uint8_t *)(calloc(regs_num, sizeof(uint8_t)));
}

void VirtualRegs::DeInit(void){
    if(this->registers){
        free(this->registers);
    }
    this->regs_ammount = 0;
    this->selected_reg = 0;
}

uint8_t *VirtualRegs::GetRegs(void) {
    return this->registers;
}

uint32_t VirtualRegs::GetRegsAmmount(void) {
    return this->regs_ammount;
}

void VirtualRegs::SelectReg(int num) {
    if (num >= regs_ammount)
        this->selected_reg = (this->regs_ammount - 1); // select the last reg
    else
        this->selected_reg = num;
}

void VirtualRegs::SelectNextReg(void) {
    if (this->selected_reg < (this->regs_ammount - 1)) // if not the last one
        this->selected_reg++;
}

uint32_t VirtualRegs::GetSelectedRegNum(void) {
    return selected_reg;
}

void VirtualRegs::SetReg(uint8_t val) {
    this->registers[this->selected_reg] = val;
}

void VirtualRegs::SetRegAndNext(uint8_t val) {
    SetReg(val);
    SelectNextReg();
}

uint8_t VirtualRegs::GetReg(void) {
    return this->registers[this->selected_reg];
}

uint8_t VirtualRegs::GetRegAndNext(void) {
    uint8_t val = GetReg();
    SelectNextReg();
    return val;
}