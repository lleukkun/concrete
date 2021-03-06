/*
 * Copyright (c) 2011  Timo Savola
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#include "internal.hpp"

namespace concrete {

static InternalFunction functions[internals::count];

void InternalBlock::Register(InternalSerial serial, InternalFunction function)
{
	functions[serial] = function;
}

Object InternalBlock::call(const TupleObject &args, const DictObject &kwargs)
{
	return functions[serial](args, kwargs);
}

} // namespace
