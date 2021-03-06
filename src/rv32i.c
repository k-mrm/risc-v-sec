#include "rv32i.h"
#include "security.h"

void rv32i_lui(struct cpu *cpu, uint8_t rd, int32_t imm) {
  regwrite(cpu, rd, imm);
}

void rv32i_auipc(struct cpu *cpu, uint8_t rd, int32_t imm) {
  regwrite(cpu, rd, cpu->pc + imm);
}

void rv32i_jal(struct cpu *cpu, uint8_t rd, int32_t off) {
  reg_t nextop_pc = cpu->pc + 4;
  regwrite(cpu, rd, nextop_pc);
  if(rd == 1) { /* ra register */
    shstk_push(cpu, nextop_pc);
  }

  cpu->nextpc = cpu->pc + off;
}

void rv32i_jalr(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t t = cpu->pc + 4;
  cpu->nextpc = (regread(cpu, rs1) + off) & ~1;
  if(rd == 0 && rs1 == 1 && off == 0) { /* ret */
    shstk_check(cpu, cpu->nextpc);
  }
  if(rd == 1) { /* maybe function call */
    shstk_push(cpu, t);
  }
  regwrite(cpu, rd, t);
}

void rv32i_beq(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  if(regread(cpu, rs1) == regread(cpu, rs2)) {
    cpu->nextpc = cpu->pc + off;
  }
}

void rv32i_bne(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  if(regread(cpu, rs1) != regread(cpu, rs2)) {
    cpu->nextpc = cpu->pc + off;
  }
}

void rv32i_blt(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  if((sreg_t)regread(cpu, rs1) < (sreg_t)regread(cpu, rs2)) {
    cpu->nextpc = cpu->pc + off;
  }
}

void rv32i_bge(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  if((sreg_t)regread(cpu, rs1) >= (sreg_t)regread(cpu, rs2)) {
    cpu->nextpc = cpu->pc + off;
  }
}

void rv32i_bltu(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  if(regread(cpu, rs1) < regread(cpu, rs2)) {
    cpu->nextpc = cpu->pc + off;
  }
}

void rv32i_bgeu(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  if(regread(cpu, rs1) >= regread(cpu, rs2)) {
    cpu->nextpc = cpu->pc + off;
  }
}

void rv32i_lb(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint8_t m = cpuread8(cpu, addr);
  regwrite(cpu, rd, (sreg_t)(int8_t)m);
}

void rv32i_lh(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint16_t m = cpuread16(cpu, addr);
  regwrite(cpu, rd, (sreg_t)(int16_t)m);
}

void rv32i_lw(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint32_t m = cpuread32(cpu, addr);
  regwrite(cpu, rd, (sreg_t)(int32_t)m);
}

void rv32i_lbu(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint8_t m = cpuread8(cpu, addr);
  regwrite(cpu, rd, (reg_t)m);
}

void rv32i_lhu(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint16_t m = cpuread16(cpu, addr);
  regwrite(cpu, rd, (reg_t)m);
}

void rv32i_sb(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint8_t src = (uint8_t)regread(cpu, rs2);
  cpuwrite8(cpu, addr, src);
}

void rv32i_sh(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint16_t src = (uint16_t)regread(cpu, rs2);
  cpuwrite16(cpu, addr, src);
}

void rv32i_sw(struct cpu *cpu, uint8_t rs1, uint8_t rs2, int32_t off) {
  reg_t addr = regread(cpu, rs1) + off;
  uint32_t src = (uint32_t)regread(cpu, rs2);
  cpuwrite32(cpu, addr, src);
}

void rv32i_addi(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t imm) {
  reg_t a = regread(cpu, rs1) + imm;
  regwrite(cpu, rd, a);
}

void rv32i_slti(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t imm) {
  reg_t a = (sreg_t)regread(cpu, rs1) < imm;
  regwrite(cpu, rd, a);
}

void rv32i_sltiu(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t imm) {
  reg_t a = regread(cpu, rs1) < imm;
  regwrite(cpu, rd, a);
}

void rv32i_xori(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t imm) {
  reg_t a = regread(cpu, rs1) ^ imm;
  regwrite(cpu, rd, a);
}

void rv32i_ori(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t imm) {
  reg_t a = regread(cpu, rs1) | imm;
  regwrite(cpu, rd, a);
}

void rv32i_andi(struct cpu *cpu, uint8_t rd, uint8_t rs1, int32_t imm) {
  reg_t a = regread(cpu, rs1) & imm;
  regwrite(cpu, rd, a);
}

void rv32i_slli(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t shamt) {
  reg_t a = regread(cpu, rs1) << shamt;
  regwrite(cpu, rd, a);
}

void rv32i_srli(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t shamt) {
  reg_t a = regread(cpu, rs1) >> shamt;
  regwrite(cpu, rd, a);
}

void rv32i_srai(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t shamt) {
  reg_t a = (sreg_t)regread(cpu, rs1) >> shamt;
  regwrite(cpu, rd, a);
}


void rv32i_add(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  sreg_t a = (sreg_t)regread(cpu, rs1) + (sreg_t)regread(cpu, rs2);
  regwrite(cpu, rd, a);
}

void rv32i_sub(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  sreg_t a = (sreg_t)regread(cpu, rs1) - (sreg_t)regread(cpu, rs2);
  regwrite(cpu, rd, a);
}

void rv32i_sll(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
#if XLEN == 64
  uint8_t shift = regread(cpu, rs2) & 0x3f;
#elif XLEN == 32
  uint8_t shift = regread(cpu, rs2) & 0x1f;
#endif
  reg_t a = regread(cpu, rs1) << shift;
  regwrite(cpu, rd, a);
}

void rv32i_slt(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t a = (sreg_t)regread(cpu, rs1) < (sreg_t)regread(cpu, rs2);
  regwrite(cpu, rd, a);
}

void rv32i_sltu(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t a = regread(cpu, rs1) < regread(cpu, rs2);
  regwrite(cpu, rd, a);
}

void rv32i_xor(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t a = regread(cpu, rs1) ^ regread(cpu, rs2);
  regwrite(cpu, rd, a);
}

void rv32i_srl(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
#if XLEN == 64
  uint8_t shift = regread(cpu, rs2) & 0x3f;
#elif XLEN == 32
  uint8_t shift = regread(cpu, rs2) & 0x1f;
#endif
  reg_t a = regread(cpu, rs1) >> shift;
  regwrite(cpu, rd, a);
}

void rv32i_sra(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t a = (sreg_t)regread(cpu, rs1) >> regread(cpu, rs2);
  regwrite(cpu, rd, a);
}

void rv32i_or(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t a = regread(cpu, rs1) | regread(cpu, rs2);
  regwrite(cpu, rd, a);
}

void rv32i_and(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t a = regread(cpu, rs1) & regread(cpu, rs2);
  regwrite(cpu, rd, a);
}


void rv32i_csrrw(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint32_t csr) {
  reg_t t = csrread(cpu->csrs, csr);
  csrwrite(cpu->csrs, csr, regread(cpu, rs1));
  regwrite(cpu, rd, t);
}

void rv32i_csrrs(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint32_t csr) {
  reg_t t = csrread(cpu->csrs, csr);
  csrwrite(cpu->csrs, csr, t | regread(cpu, rs1));
  regwrite(cpu, rd, t);
}

void rv32i_csrrc(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint32_t csr) {
  reg_t t = csrread(cpu->csrs, csr);
  csrwrite(cpu->csrs, csr, t & ~regread(cpu, rs1));
  regwrite(cpu, rd, t);
}

void rv32i_csrrwi(struct cpu *cpu, uint8_t rd, uint8_t zimm, uint32_t csr) {
  regwrite(cpu, rd, csrread(cpu->csrs, csr));
  csrwrite(cpu->csrs, csr, zimm);
}

void rv32i_csrrsi(struct cpu *cpu, uint8_t rd, uint8_t zimm, uint32_t csr) {
  reg_t t = csrread(cpu->csrs, csr);
  csrwrite(cpu->csrs, csr, t | zimm);
  regwrite(cpu, rd, t);
}

void rv32i_csrrci(struct cpu *cpu, uint8_t rd, uint8_t zimm, uint32_t csr) {
  reg_t t = csrread(cpu->csrs, csr);
  csrwrite(cpu->csrs, csr, t & ~zimm);
  regwrite(cpu, rd, t);
}
