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
    RETURN = 261,
    INT = 262,
    FLOAT = 263,
    CHAR = 264,
    DOUBLE = 265,
    FOR = 266,
    CONST_FLOAT = 267,
    CONST_INT = 268,
    CONST_CHAR = 269,
    ID = 270,
    COMMA = 271,
    SEMICOLON = 272,
    ADDOP = 273,
    ASSIGNOP = 274,
    RELOP = 275,
    LPAREN = 276,
    RPAREN = 277,
    LCURL = 278,
    RCURL = 279,
    LOGICOP = 280,
    DECOP = 281,
    INCOP = 282,
    MULOP = 283,
    BITOP = 284,
    VOID = 285,
    LTHIRD = 286,
    RTHIRD = 287,
    NOT = 288,
    PRINTLN = 289,
    LTE = 290
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define RETURN 261
#define INT 262
#define FLOAT 263
#define CHAR 264
#define DOUBLE 265
#define FOR 266
#define CONST_FLOAT 267
#define CONST_INT 268
#define CONST_CHAR 269
#define ID 270
#define COMMA 271
#define SEMICOLON 272
#define ADDOP 273
#define ASSIGNOP 274
#define RELOP 275
#define LPAREN 276
#define RPAREN 277
#define LCURL 278
#define RCURL 279
#define LOGICOP 280
#define DECOP 281
#define INCOP 282
#define MULOP 283
#define BITOP 284
#define VOID 285
#define LTHIRD 286
#define RTHIRD 287
#define NOT 288
#define PRINTLN 289
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
