
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ARRAY = 258,
     BOOL = 259,
     INT = 260,
     CHAR = 261,
     STRING = 262,
     IF = 263,
     ELIF = 264,
     ELSE = 265,
     DO = 266,
     END = 267,
     GETS = 268,
     PUTS = 269,
     CUTS = 270,
     TO_I = 271,
     START = 272,
     STOP = 273,
     WHILE = 274,
     FOR = 275,
     AND = 276,
     OR = 277,
     IN = 278,
     BREAK = 279,
     TRUE = 280,
     FALSE = 281,
     NIL = 282,
     RETURN = 283,
     plus = 284,
     minus = 285,
     mul = 286,
     divs = 287,
     mod = 288,
     less = 289,
     lessOrEqual = 290,
     equal = 291,
     different = 292,
     moreOrEqual = 293,
     more = 294,
     eq = 295,
     leftRoundBracket = 296,
     rightRoundBracket = 297,
     leftSquareBracket = 298,
     rightSquareBracket = 299,
     leftCurlyBracket = 300,
     rightCurlyBracket = 301,
     comma = 302,
     colon = 303,
     semicolon = 304,
     BOOL_CONST = 305,
     INT_CONST = 306,
     CHAR_CONST = 307,
     STRING_CONST = 308,
     IDENTIFIER = 309
   };
#endif
/* Tokens.  */
#define ARRAY 258
#define BOOL 259
#define INT 260
#define CHAR 261
#define STRING 262
#define IF 263
#define ELIF 264
#define ELSE 265
#define DO 266
#define END 267
#define GETS 268
#define PUTS 269
#define CUTS 270
#define TO_I 271
#define START 272
#define STOP 273
#define WHILE 274
#define FOR 275
#define AND 276
#define OR 277
#define IN 278
#define BREAK 279
#define TRUE 280
#define FALSE 281
#define NIL 282
#define RETURN 283
#define plus 284
#define minus 285
#define mul 286
#define divs 287
#define mod 288
#define less 289
#define lessOrEqual 290
#define equal 291
#define different 292
#define moreOrEqual 293
#define more 294
#define eq 295
#define leftRoundBracket 296
#define rightRoundBracket 297
#define leftSquareBracket 298
#define rightSquareBracket 299
#define leftCurlyBracket 300
#define rightCurlyBracket 301
#define comma 302
#define colon 303
#define semicolon 304
#define BOOL_CONST 305
#define INT_CONST 306
#define CHAR_CONST 307
#define STRING_CONST 308
#define IDENTIFIER 309




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 13 "spec.y"

    char *str;



/* Line 1676 of yacc.c  */
#line 166 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


