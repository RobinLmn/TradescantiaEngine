#pragma once

namespace TradescantiaEngine
{
	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float: return 4;
		case ShaderDataType::Float2: return 8;
		case ShaderDataType::Float3: return 12;
		case ShaderDataType::Float4: return 16;
		case ShaderDataType::Int: return 4;
		case ShaderDataType::Int2: return 8;
		case ShaderDataType::Int3: return 12;
		case ShaderDataType::Int4: return 16;
		case ShaderDataType::Mat3: return 36;
		case ShaderDataType::Mat4: return 64;
		case ShaderDataType::Bool: return 1;
		}

		TSC_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	struct BufferElement
	{
		uint32_t Offset;
		uint32_t Size;
		std::string Name;
		ShaderDataType Type;
		bool Normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(false)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float: return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Int: return 1;
			case ShaderDataType::Int2: return 2;
			case ShaderDataType::Int3: return 3;
			case ShaderDataType::Int4: return 4;
			case ShaderDataType::Mat3: return 9;
			case ShaderDataType::Mat4: return 16;
			case ShaderDataType::Bool: return 1;
			}

			TSC_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: _Elements(elements)
		{
			CalculateOffsetAndStride();
		};

		BufferLayout() = default;

		std::vector<BufferElement>::iterator begin() { return _Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return _Elements.end(); }

		inline uint32_t GetStride() const { return _Stride; }

	private:
		void CalculateOffsetAndStride()
		{
			_Stride = 0;
			for (auto& element : _Elements)
			{
				element.Offset = _Stride;
				_Stride += element.Size;
			}
		}

		uint32_t _Stride = 0;
		std::vector<BufferElement> _Elements;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		BufferLayout Layout;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		uint32_t Count;

		static IndexBuffer* Create(uint32_t* vertices, uint32_t size);
	};
}