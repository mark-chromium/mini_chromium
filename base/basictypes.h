// Copyright 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MINI_CHROMIUM_BASE_BASICTYPES_H_
#define MINI_CHROMIUM_BASE_BASICTYPES_H_

#include <string.h>
#include <sys/types.h>

#include "base/compiler_specific.h"
#include "base/port.h"

#if __cplusplus >= 201103L

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&) = delete; \
    void operator=(const TypeName&) = delete

#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
    TypeName() = delete; \
    DISALLOW_COPY_AND_ASSIGN(TypeName)

#else

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    void operator=(const TypeName&)

#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
    TypeName(); \
    DISALLOW_COPY_AND_ASSIGN(TypeName)

#endif

template<typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];

template <typename T, size_t N>
char (&ArraySizeHelper(const T (&array)[N]))[N];

#define arraysize(array) (sizeof(ArraySizeHelper(array)))

#define ARRAYSIZE_UNSAFE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
     static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

template<typename To, typename From>
inline To implicit_cast(const From& f) {
  return f;
}

#if __cplusplus >= 201103L

#define COMPILE_ASSERT(expr, msg) static_assert(expr, #msg)

#else

template <bool>
struct CompileAssert {
};

#define COMPILE_ASSERT(expr, msg) \
    typedef CompileAssert<(bool(expr))> msg[bool(expr) ? 1 : -1] ALLOW_UNUSED

template <typename Dest, typename Source>
inline Dest bit_cast(const Source& source) {
  COMPILE_ASSERT(sizeof(Dest) == sizeof(Source), sizes_must_be_equal);

  Dest dest;
  memcpy(&dest, &source, sizeof(dest));
  return dest;
}

#endif

template<typename T>
inline void ignore_result(const T&) {
}

#endif  // MINI_CHROMIUM_BASE_BASICTYPES_H_
