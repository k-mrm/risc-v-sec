#include "rv32m.h"
#include "log.h"

void rv32m_mul(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t a = regread(cpu, rs1) * regread(cpu, rs2);
  regwrite(cpu, rd, a);
}

void rv32m_mulh(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  sreg_t src1 = (sreg_t)regread(cpu, rs1);
  sreg_t src2 = (sreg_t)regread(cpu, rs2);
  sreg_t src = (src1 * src2) >> XLEN;
  regwrite(cpu, rd, src);
}

void rv32m_mulhsu(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  sreg_t src1 = (sreg_t)regread(cpu, rs1);
  sreg_t src = (sreg_t)(src1 * regread(cpu, rs2)) >> XLEN;
  regwrite(cpu, rd, src);
}

void rv32m_mulhu(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t a = (regread(cpu, rs1) * regread(cpu, rs2)) >> XLEN;
  regwrite(cpu, rd, a);
}

void rv32m_div(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  sreg_t src1 = (sreg_t)regread(cpu, rs1);
  sreg_t src2 = (sreg_t)regread(cpu, rs2);
  sreg_t res;
  log_dbg("%ld", src2);
  if(src2 == 0)
    res = -1;
  else if(src1 == -2147483648 && src2 == -1)
    res = -2147483648;
  else
    res = src1 / src2;
  regwrite(cpu, rd, res);
}

void rv32m_divu(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t src1 = regread(cpu, rs1);
  reg_t src2 = regread(cpu, rs2);
  reg_t res;
  if(src2 == 0)
    res = 0xffffffff;
  else
    res = src1 / src2;
  regwrite(cpu, rd, res);
}

void rv32m_rem(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  sreg_t src1 = (sreg_t)regread(cpu, rs1);
  sreg_t src2 = (sreg_t)regread(cpu, rs2);
  sreg_t res;
  if(src2 == 0)
    res = src1;
  else if(src1 == -2147483648 && src2 == -1)
    res = 0;
  else
    res = src1 % src2;
  regwrite(cpu, rd, res);
}

void rv32m_remu(struct cpu *cpu, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  reg_t src1 = regread(cpu, rs1);
  reg_t src2 = regread(cpu, rs2);
  reg_t res;
  if(src2 == 0)
    res = src1;
  else
    res = src1 % src2;
  regwrite(cpu, rd, res);
}
