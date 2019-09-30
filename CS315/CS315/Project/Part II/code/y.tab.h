/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ENTRYPOINT = 258,
     IFSTATEMENT = 259,
     ELSEIFSTATEMENT = 260,
     ELSESTATEMENT = 261,
     FORLOOP = 262,
     WHILELOOP = 263,
     BOOLEAN = 264,
     ATTRIBUTE = 265,
     CLASSWITHARG = 266,
     METHODCALL = 267,
     METHOD = 268,
     IN = 269,
     IDENTIFIER = 270,
     PARAMETERIDENTIFIER = 271,
     CONSTANT = 272,
     CLASS = 273,
     INHERITANCE = 274,
     LPARAN = 275,
     RPARAN = 276,
     LBRACKET = 277,
     RBRACKET = 278,
     RANGE = 279,
     GREATER = 280,
     LESS = 281,
     GREATEROREQUAL = 282,
     LESSOREQUAL = 283,
     NOTEQUAL = 284,
     NOT = 285,
     ASSIGNMENT = 286,
     COMPARISON = 287,
     SEMICOLON = 288,
     COMMA = 289,
     OR = 290,
     AND = 291,
     INTEGER = 292,
     DOUBLE = 293,
     MULTIPLICATION = 294,
     DIVISION = 295,
     SUBTRACTION = 296,
     ADDITION = 297,
     REMAINDER = 298,
     STRING = 299
   };
#endif
/* Tokens.  */
#define ENTRYPOINT 258
#define IFSTATEMENT 259
#define ELSEIFSTATEMENT 260
#define ELSESTATEMENT 261
#define FORLOOP 262
#define WHILELOOP 263
#define BOOLEAN 264
#define ATTRIBUTE 265
#define CLASSWITHARG 266
#define METHODCALL 267
#define METHOD 268
#define IN 269
#define IDENTIFIER 270
#define PARAMETERIDENTIFIER 271
#define CONSTANT 272
#define CLASS 273
#define INHERITANCE 274
#define LPARAN 275
#define RPARAN 276
#define LBRACKET 277
#define RBRACKET 278
#define RANGE 279
#define GREATER 280
#define LESS 281
#define GREATEROREQUAL 282
#define LESSOREQUAL 283
#define NOTEQUAL 284
#define NOT 285
#define ASSIGNMENT 286
#define COMPARISON 287
#define SEMICOLON 288
#define COMMA 289
#define OR 290
#define AND 291
#define INTEGER 292
#define DOUBLE 293
#define MULTIPLICATION 294
#define DIVISION 295
#define SUBTRACTION 296
#define ADDITION 297
#define REMAINDER 298
#define STRING 299




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

