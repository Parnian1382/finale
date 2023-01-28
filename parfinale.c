/**
 * Include File
 * @brief includes
 **/
/**
 * @file projectpr.c
 * @file regs.txt
 * @file in.txt
 * @brief term project
 * @version: V1.09
 * @date 28 january 2023
 * @author parnian bahrami
 * @warning
 * Warning Test
 * @note fundamentals of programming.
 * \mainpage
 * CPU registers
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int s[32], Imm; /**Conditional Registers*/
int stack[100];
int status[8];
/**
 * PUSH
 * @brief  push stacks set value in stack[0]
 * @param int rs
 * @return void
 **/
void PUSH(int n)
{
    for (int i = 0; i < 100; i++)
    {
        stack[i + 1] = stack[i];
    }
    stack[0] = s[n];
}
/**
 * POP
 * @brief pull stacks
 * @param int rt
 * @return void
 **/
void PUP(int n)
{
    stack[0] = s[n];
    for (int i = 0; i < 100; i++)
    {
        stack[i] = stack[i + 1];
    }
}
/**
 * Parityflag
 * @brief Status[0] of the last Command
 * @param int result
 * @return void
 **/
void parity_flag(int result)
{
    int m = 0;
    while (result > 0)
    {
        if (result % 2 == 1)
            m++;
        result /= 2;
    }
    if (m % 2 == 1)
        status[0] = 1;
    else
        status[0] = 0;
}
/**
 * Zeroflag
 * @brief Status[1] of the last Command: Numbers of zeros
 * @param int result
 * @return void
 **/
void zero_flag(int result)
{
    if (result == 0)
        status[1] = 1;
    else
        status[1] = 0;
}
/**
 * Signflag
 * @brief Status[2] of the last Command: Sign
 * @param int result
 * @return void
 **/
void sign_flag(int result)
{
    if (result < 0)
        status[2] = 1;
    else
        status[2] = 0;
}
/**
 * Overflowflag add
 * @brief Status[5] of the last Command: overflow
 * @param int result
 * @return void
 **/
void overflow_flag_add(int a, int b, int c)
{
    if (b > 0 && c > 0 && a < 0 || b < 0 && c < 0 && a > 0)
        status[5] = 1;
    else
        status[5] = 0;
}
/**
 * Overflowflag Sub
 * @brief Status[5] of the last Command: overflow
 * @param int result
 * @return void
 **/
void overflow_flag_sub(int a, int b, int c)
{
    if (b > 0 && c < 0 && a < 0 || b < 0 && c > 0 && a > 0)
        status[5] = 1;
    else
        status[5] = 0;
}
/**
 * Overflowflag Mull
 * @brief Status[5] of the last Command: overflow
 * @param int result
 * @return void
 **/
void overflow_flag_mull(int a, int b, int c)
{
    if (b != 0 && (a / b) != c)
        status[5] = 1;
    else
        status[5] = 0;
}
/**
 * ADD
 * @brief adding two registers
 * @param int rd, rs & rt
 * @return void
 **/
void ADD(int rd, int rs, int rt)
{
    s[rd] = s[rs] + s[rt];
    parity_flag(s[rd]);
    zero_flag(s[rd]);
    sign_flag(s[rd]);
    overflow_flag_add(s[rd], s[rs], s[rt]);
}
/**
 * SUB
 * @brief subing two registers
 * @param int rd, rs & rt
 * @return void
 **/
void SUB(int rd, int rs, int rt)
{
    s[rd] = s[rs] - s[rt];
    parity_flag(s[rd]);
    zero_flag(s[rd]);
    sign_flag(s[rd]);
    overflow_flag_sub(s[rd], s[rs], s[rt]);
}
/**
 * AND
 * @brief AND two registers
 * @param int rd, rs, rt
 * @return void
 **/
void AND(int rd, int rs, int rt)
{
    s[rd] = s[rs] & s[rt];
    parity_flag(s[rd]);
    zero_flag(s[rd]);
    sign_flag(s[rd]);
}
/**
 * OR
 * @brief OR two registers
 * @param int number rd, rs, rt
 * @return void
 **/
void OR(int rd, int rs, int rt)
{
    s[rd] = s[rs] | s[rt];
    parity_flag(s[rd]);
    zero_flag(s[rd]);
    sign_flag(s[rd]);
}
/**
 * XOR
 * @brief XOR two registers
 * @param int rd, rs, rt
 * @return void
 **/
void XOR(int rd, int rs, int rt)
{
    s[rd] = s[rs] ^ s[rt];
    parity_flag(s[rd]);
    zero_flag(s[rd]);
    sign_flag(s[rd]);
}
/**
 * DIV
 * @brief divide two registers
 * @param int rs & rt
 * @return void
 **/
void DIV(int rt, int rs)
{
    int quotient, remain;
    quotient = s[rt] / s[rs];
    remain = s[rt] % s[rs];
    s[rt] = quotient;
    s[rs] = remain;
    parity_flag(s[rt]);
    zero_flag(s[rt]);
    sign_flag(s[rt]);
}
/**
 * MULL
 * @brief multiply two registers: 4 more bits in rt &  4 less bits in rs
 * @param int rs & rt
 * @return void
 **/
void MULL(int rt, int rs)
{
    int multi;
    multi = s[rt] * s[rs];
    s[rt] = multi / 16;
    s[rs] = multi % 16;
    parity_flag(multi);
    zero_flag(multi);
    sign_flag(multi);
    overflow_flag_mull(s[rt], s[rs], multi);
}
/**
 * ADDI
 * @brief adding a registers and a number
 * @param int rt, rs, Imm
 * @return void
 **/
void ADDI(int rt, int rs, int Imm)
{
    s[rt] = s[rs] + Imm;
    parity_flag(s[rt]);
    zero_flag(s[rt]);
    sign_flag(s[rt]);
    overflow_flag_add(s[rt], s[rs], Imm);
}
/**
 * SUBI
 * @brief subbing a registers and a number
 * @param int rt, rs & Imm
 * @return void
 **/
void SUBI(int rt, int rs, int Imm)
{
    s[rt] = s[rs] - Imm;
    parity_flag(s[rt]);
    zero_flag(s[rt]);
    sign_flag(s[rt]);
    overflow_flag_sub(s[rt], s[rs], Imm);
}
/**
 * ANDI
 * @brief  AND a register with a number
 * @param int rt, rs & Imm
 * @return void
 **/
void ANDI(int rt, int rs, int Imm)
{
    s[rt] = s[rs] & Imm;
    parity_flag(s[rt]);
    zero_flag(s[rt]);
    sign_flag(s[rt]);
}
/**
 * ORI
 * @brief OR a register with a number
 * @param int rt, rs & Imm
 * @return void
 **/
void ORI(int rt, int rs, int Imm)
{
    s[rt] = s[rs] | Imm;
    parity_flag(s[rt]);
    zero_flag(s[rt]);
    sign_flag(s[rt]);
}
/**
 * XORI
 * @brief XOR a register with a number
 * @param int rt, rs & Imm
 * @return void
 **/
void XORI(int rt, int rs, int Imm)
{
    s[rt] = s[rs] ^ Imm;
    parity_flag(s[rt]);
    zero_flag(s[rt]);
    sign_flag(s[rt]);
}
/**
 * MOV
 * @brief put a number in a register
 * @param[in] int (integer number rt & Imm)
 * @return void
 **/
void MOV(int rt, int Imm)
{
    s[rt] = Imm;
}
/**
 * SWP
 * @brief swap two registers
 * @param int rt & rs
 * @return void
 **/
void SWP(int rt, int rs)
{
    int help1, help2;
    help1 = s[rt];
    help2 = s[rs];
    MOV(rt, help2);
    MOV(rs, help1);
}
/**
 * DUMP_REGS
 * @brief print all register's value
 * @param void
 * @return void
 **/
void DUMP_REGS()
{
    for (int i = 0; i < 32; i++)
    {
        printf("%d  ", s[i]);
    }
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%d  ", status[i]);
    }
    printf("\n");
}
/**
 * DUMP_REGS_F
 * @brief save the value of all registers in regs.tx
 * @param void
 * @return void
 **/
void DUMP_REGS_F()
{
    FILE *file;
    file = fopen("regs.txt", "w");
    for (int i = 0; i < 32; i++)
    {
        fprintf(file, "%d ", s[i]);
    }
    fprintf(file, "\n");
    for (int i = 0; i < 8; i++)
    {
        fprintf(file, "%d ", status[i]);
    }
    fclose(file);
}
/**
 * INPUT
 * @brief getting register[0] value
 * @param void
 * @return void
 **/
void INPUT()
{
    printf("please enter your input:");
    scanf("%d", &s[0]);
}
/**
 * OUTPUT
 * @brief print register[0] value
 * @param void
 * @return void
 **/
void OUTPUT()
{
    printf("\n%d", s[0]);
}
/**
 * WRONG_COMMAND
 * @brief checking the errors of commands
 * @param int line
 * @return void
 **/
void WRONG_COMMAND(int line)
{
    printf("command %d not available!\n", line);
}
/**
 * SKIE
 * @brief jumps from the next command if s[a]=s[b]
 * @param int (a, b)
 * @return 0
 **/
int SKIE(int a, int b)
{
    if (s[a] == s[b])
    {
        return 0;
    }
}
/**
 * Error
 * @brief checking the errors for negative index and more than 31 index
 * @param int (a, b, c, z)
 * @return 1 or 2
 **/
int error(int a, int b, int c, int line)
{
    int f = 0;
    if (a < 0 || b < 0 || c < 0)
    {
        printf("negative index error in line %d \n", line);
        f = 10;
    }
    if (a > 31 || b > 31 || c > 31)
    {
        printf("value index error in line %d \n", line);
        f = 10;
    }
    if (f != 10)
        return 2;
    else
        return 1;
}
/**
 * main
 * \section main
 * @brief run all the code lines that is written in our file
 * @param int argc, *argv[]
 * @return 0
 **/
int main(int argc, char *argv[])
{
    int i = 0, rs = 0, rd = 0, rt = 0, imm = 0;
    int all_lines = 0;
    int current_line = 0;
    int count_jmp_up = 1;
    char content[1000], finish[10], chr;
    FILE *fptr;
    if (argc < 2)
    {
        fptr = fopen("y.txt", "r");
    }
    else
    {
        fptr = fopen(argv[1], "r");
    }
    while (fgets(content, 1000, fptr))
    {
        all_lines++;
    }
    rewind(fptr);