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
    while (fgets(content, 1000, fptr))
    {
        rs = 0, rd = 0, rt = 0, imm = 0;
        current_line++;
        for (int j = 0; j < sizeof(content); j++)
        {
            content[j] = toupper(content[j]);
        }
        i = 0;
        char command[150] = {'\0'};

        while (content[i] != ' ' && content[i] != '\n' && content[i] != '/')
        {
            command[i] = content[i];
            i++;
        }
        if (strcmp(command, "EXIT") == 0)
        {
            exit(0);
        }
        else if (strcmp(command, "ADD") == 0)
        {
            sscanf(content, "ADD S%d, S%d, S%d", &rd, &rs, &rt);
            if (error(rd, rs, rt, current_line) == 2)
                ADD(rd, rs, rt);
        }
        else if (strcmp(command, "SUB") == 0)
        {
            sscanf(content, "SUB S%d, S%d, S%d", &rd, &rs, &rt);
            if (error(rt, rs, rd, current_line) == 2)
                SUB(rd, rs, rt);
        }
        else if (strcmp(command, "AND") == 0)
        {
            sscanf(content, "AND S%d, S%d, S%d", &rd, &rs, &rt);
            if (error(rt, rs, rd, current_line) == 2)
                AND(rd, rs, rt);
        }
        else if (strcmp(command, "XOR") == 0)
        {
            sscanf(content, "XOR S%d, S%d, S%d", &rd, &rs, &rt);
            if (error(rt, rs, rd, current_line) == 2)
                XOR(rd, rs, rt);
        }
        else if (strcmp(command, "OR") == 0)
        {
            sscanf(content, "OR S%d, S%d, S%d", &rd, &rs, &rt);
            if (error(rt, rs, rd, current_line) == 2)
                OR(rd, rs, rt);
        }
        else if (strcmp(command, "ADDI") == 0)
        {
            sscanf(content, "ADDI S%d, S%d, %d", &rd, &rs, &imm);
            if (error(rt, rs, rd, current_line) == 2)
                ADDI(rd, rs, imm);
        }
        else if (strcmp(command, "SUBI") == 0)
        {
            sscanf(content, "SUBI S%d, S%d, %d", &rd, &rs, &imm);
            if (error(rt, rs, rd, current_line) == 2)
                SUBI(rd, rs, imm);
        }
        else if (strcmp(command, "ANDI") == 0)
        {
            sscanf(content, "ANDI S%d, S%d, %d", &rd, &rs, &imm);
            if (error(rt, rs, rd, current_line) == 2)
                ANDI(rd, rs, imm);
        }
        else if (strcmp(command, "XORI") == 0)
        {
            sscanf(content, "XORI S%d, S%d, %d", &rd, &rs, &imm);
            if (error(rt, rs, rd, current_line) == 2)
                XORI(rd, rs, imm);
        }
        else if (strcmp(command, "ORI") == 0)
        {
            sscanf(content, "ORI S%d, S%d, %d", &rd, &rs, &imm);
            if (error(rt, rs, rd, current_line) == 2)
                ORI(rd, rs, imm);
        }
        else if (strcmp(command, "MOV") == 0)
        {
            if (content[8] == 'S' || content[9] == 'S')
            {

                sscanf(content, "MOV S%d, S%d", &imm, &rs);
                if (error(rt, rs, rd, current_line) == 2)
                    MOV(imm, s[rs]);
            }
            else
            {
                sscanf(content, "MOV S%d, %d", &rt, &imm);
                if (error(rt, rs, rd, current_line) == 2)
                    MOV(rt, imm);
            }
        }
        else if (strcmp(command, "SWP") == 0)
        {
            sscanf(content, "SWP S%d, S%d", &rt, &rs);
            if (error(rt, rs, rd, current_line) == 2)
                SWP(rt, rs);
        }
        else if (strcmp(command, "DUMP_REGS") == 0)
        {
            DUMP_REGS();
        }
        else if (strcmp(command, "DUMP_REGS_F") == 0)
        {
            DUMP_REGS_F();
        }
        else if (strcmp(command, "INPUT") == 0)
        {
            INPUT();
        }
        else if (strcmp(command, "OUTPUT") == 0)
        {
            OUTPUT();
        }
        else if (strcmp(command, "MULL") == 0)
        {
            sscanf(content, "MULL S%d, S%d", &rt, &rd);
            if (error(rt, rs, rd, current_line) == 2)
                MULL(rt, rd);
        }
        else if (strcmp(command, "DIV") == 0)
        {
            sscanf(content, "DIV S%d, S%d", &rt, &rs);
            if (error(rt, rs, rd, current_line) == 2)
                DIV(rt, rs);
        }
        else if (strcmp(command, "PUSH") == 0)
        {
            sscanf(content, "PUSH S%d", &rt);
            if (error(rt, rs, rd, current_line) == 2)
                PUSH(rt);
        }
        else if (strcmp(command, "PUP") == 0)
        {
            sscanf(content, "PUP S%d", &rt);
            if (error(rt, rs, rd, current_line) == 2)
                PUP(rt);
        }
        else if (strcmp(command, "JMP") == 0)
        {
            int lines_jmp = 1;
            sscanf(content, "JMP %d", &imm);
            if (imm > 0 && imm < all_lines)
            {
                if (count_jmp_up > 3)
                {
                    printf("\n\033[31mINFINIT LOOP! SKIPPED AFTER 3 TIMES.(line %d)\n", current_line);
                    continue;
                }
                if (imm < 1)
                {
                    printf("\n\033[31mTHE NUMBER OF LINES HAS TO BE POSITIVE!(line %d)\n", current_line);
                }
                else if (imm > all_lines)
                {
                    printf("\n\033[31mTHERE ARE ONLY '%d' LINES, YOU CAN'T JUMP TO THE LINE '%d'!\n", all_lines, imm);
                }
                else
                {
                    fseek(fptr, lines_jmp, SEEK_SET);
                    while (lines_jmp < imm)
                    {
                        char chars;
                        chars = fgetc(fptr);
                        if (chars == '\n')
                        {
                            lines_jmp++;
                        }
                    }
                }
                count_jmp_up++;
                current_line = lines_jmp - 1;
            }
            else
            {
                if (imm < 0)
                {
                    printf("line%d: negative line number error in jump\n", current_line);
                }
                if (imm > all_lines)
                {
                    printf("line%d: not enough lines to jump\n", current_line);
                }
            }
        }
        else if (strcmp(command, "SKIE") == 0)
        {
            sscanf(content, "SKIE S%d, S%d", &rt, &rs);
            if (error(rt, rs, rd, current_line) == 2)
            {
                if (SKIE(rt, rs) == 0)
                {
                    fgets(content, 1000, fptr);
                }
            }
            current_line++;
        }
        else
        {
            WRONG_COMMAND(current_line);
        }
    }
    fclose(fptr);
    return 0;
}