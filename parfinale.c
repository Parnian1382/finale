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