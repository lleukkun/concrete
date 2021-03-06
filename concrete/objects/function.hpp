/*
 * Copyright (c) 2011  Timo Savola
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#ifndef CONCRETE_OBJECTS_FUNCTION_HPP
#define CONCRETE_OBJECTS_FUNCTION_HPP

#include <concrete/block.hpp>
#include <concrete/objects/code.hpp>
#include <concrete/objects/object.hpp>
#include <concrete/util/packed.hpp>

namespace concrete {

struct FunctionBlock: ObjectBlock {
	const PortableCodeObject code;

	FunctionBlock(const TypeObject &type, const CodeObject &code): ObjectBlock(type), code(code)
	{
	}
} CONCRETE_PACKED;

template <typename Ops>
class function_object: public object<Ops> {
	friend class object<ObjectOps>;
	friend class object<PortableObjectOps>;

public:
	static TypeObject Type()
	{
		return Context::Builtins().function_type;
	}

	static function_object New(const CodeObject &code) throw (AllocError)
	{
		auto id = Context::Alloc(sizeof (FunctionBlock));
		new (Context::Pointer(id)) FunctionBlock(Type(), code);
		return id;
	}

	using object<Ops>::operator==;
	using object<Ops>::operator!=;

	template <typename OtherOps>
	function_object(const function_object<OtherOps> &other): object<Ops>(other)
	{
	}

	template <typename OtherOps>
	function_object &operator=(const function_object<OtherOps> &other)
	{
		object<Ops>::operator=(other);
		return *this;
	}

	CodeObject code() const
	{
		return function_block()->code;
	}

protected:
	function_object(BlockId id): object<Ops>(id)
	{
	}

	FunctionBlock *function_block() const
	{
		return static_cast<FunctionBlock *> (object<Ops>::object_block());
	}
} CONCRETE_PACKED;

typedef function_object<ObjectOps>         FunctionObject;
typedef function_object<PortableObjectOps> PortableFunctionObject;

} // namespace

#endif
