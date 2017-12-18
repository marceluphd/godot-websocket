/*************************************************************************/
/*  websocket_macros.h                                                   */
/*************************************************************************/
/*                       This file is part of:                           */
/*                      GODOT WEBSOCKET MODULE                           */
/*            https://github.com/LudiDorici/godot-websocket              */
/*************************************************************************/
/* Copyright (c) 2017 Ludi Dorici, di Alessandrelli Fabio                */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
#ifndef WEBSOCKETMACTOS_H
#define WEBSOCKETMACTOS_H

/* clang-format off */
#define GDCICLASS(CNAME) \
public:\
	static CNAME *(*_create)();\
\
	static Ref<CNAME > create_ref() {\
\
		if (!_create)\
			return Ref<CNAME >();\
		return Ref<CNAME >(_create());\
	}\
\
	static CNAME *create() {\
\
		if (!_create)\
			return NULL;\
		return _create();\
	}\
protected:\

#define GDCINULL(CNAME) \
CNAME *(*CNAME::_create)() = NULL;

#define GDCIIMPL(IMPNAME, CNAME) \
public:\
	static CNAME *_create() { return memnew(IMPNAME); }\
	static void make_default() { CNAME::_create = IMPNAME::_create; }\
protected:\
/* clang-format on */

#endif // WEBSOCKETMACTOS_H
