/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    INT = 261,
    FLOAT = 262,
    CHAR = 263,
    DOUBLE = 264,
    FOR = 265,
    CONST_FLOAT = 266,
    CONST_INT = 267,
    CONST_CHAR = 268,
    ID = 269,
    COMMA = 270,
    SEMICOLON = 271,
    ADDOP = 272,
    ASSIGNOP = 273,
    RELOP = 274,
    LPAREN = 275,
    RPAREN = 276,
    LCURL = 277,
    RCURL = 278,
    LOGICOP = 279,
    DECOP = 280,
    INCOP = 281,
    MULOP = 282,
    BITOP = 283,
    VOID = 284,
    LTHIRD = 285,
    RTHIRD = 286,
    NOT = 287,
    PRINTLN = 288,
    RETURN = 289,
    LTE = 290
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define INT 261
#define FLOAT 262
#define CHAR 263
#define DOUBLE 264
#define FOR 265
#define CONST_FLOAT 266
#define CONST_INT 267
#define CONST_CHAR 268
#define ID 269
#define COMMA 270
#define SEMICOLON 271
#define ADDOP 272
#define ASSIGNOP 273
#define RELOP 274
#define LPAREN 275
#define RPAREN 276
#define LCURL 277
#define RCURL 278
#define LOGICOP 279
#define DECOP 280
#define INCOP 281
#define MULOP 282
#define BITOP 283
#define VOID 284
#define LTHIRD 285
#define RTHIRD 286
#define NOT 287
#define PRINTLN 288
#define RETURN 289
#define LTE 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
