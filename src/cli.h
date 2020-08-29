/*
** cli for OCR in src
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#ifndef CLI_H
#define CLI_H

/* --------------------------- */
/* Functions */

void cli_parse_commands(int argc, char **argv);

void cli_run_nn();

void cli_print_logo();

void cli_print_help();

#endif