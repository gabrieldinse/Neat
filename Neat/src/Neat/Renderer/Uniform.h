#pragma once

#include <string>

#include "Neat/Core/Core.h"
#include "Neat/Core/Types.h"
#include "Neat/Math/Vector.h"
#include "Neat/Math/Matrix.h"
#include "Neat/Math/MatrixOperations.h"
#include "Neat/Renderer/ShaderDataTypes.h"


namespace Neat
{
   struct UniformData;


	// ---------------------------------------------------------------------- //
	// UniformLibrary-------------------------------------------------------- //
	// ---------------------------------------------------------------------- //
	class UniformLibrary
	{
	public:
		UniformLibrary(UInt shaderProgramID);
		UniformLibrary() = delete;
		~UniformLibrary();

		Bool exists(const std::string& name) const;

		UniformData& operator[](const std::string& name);
		const UniformData& operator[](const std::string& name) const;

	private:
		std::unordered_map<std::string, std::unique_ptr<UniformData>> uniforms;
		UInt shaderProgramID = 0;
	};


	// ---------------------------------------------------------------------- //
	// UniformBase ---------------------------------------------------------- //
	// ---------------------------------------------------------------------- //
   struct UniformBase
   {
		virtual ~UniformBase();

      const std::string& getName() const;
      Int getType() const;
      Int getSize() const;
      Int getLocation() const;

		void checkUniform(ShaderDataType uniformType,
			const std::string& name, const UniformLibrary& uniformLibrary);

   protected:
      std::unique_ptr<UniformData> data;
   };


	// ---------------------------------------------------------------------- //
	// Uniform -------------------------------------------------------------- //
	// ---------------------------------------------------------------------- //
   template <ShaderDataType uniformType>
   struct Uniform : public UniformBase {};

	template<>
	struct Uniform<ShaderDataType::Float> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Float value);
	};

	template<>
	struct Uniform<ShaderDataType::Vec2> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Vec2 values);
	};

	template<>
	struct Uniform<ShaderDataType::Vec3> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Vec3 values);
	};

	template<>
	struct Uniform<ShaderDataType::Vec4> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Vec4 values);
	};

	template<>
	struct Uniform<ShaderDataType::Int> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Int value);
	};

	template<>
	struct Uniform<ShaderDataType::IntArray> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Int* values, Int count);
	};

	template<>
	struct Uniform<ShaderDataType::Mat3> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Mat3 matrix);
	};

	template<>
	struct Uniform<ShaderDataType::Mat4> : public UniformBase
	{
		Uniform(const std::string& name, const UniformLibrary& uniformLibrary);
		void set(Mat4 matrix);
	};
}