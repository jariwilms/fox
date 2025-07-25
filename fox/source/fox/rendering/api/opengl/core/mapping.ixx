export module fox.rendering.api.opengl.mapping;

import std;

import fox.rendering.api.opengl.flags;
import fox.rendering.api.opengl.types;
import fox.rendering.api.opengl.utility;
import fox.rendering.base.buffer;
import fox.rendering.base.cubemap;
import fox.rendering.base.pipeline;
import fox.rendering.base.query;
import fox.rendering.base.render_buffer;
import fox.rendering.base.render_state;
import fox.rendering.base.shader;
import fox.rendering.base.texture;
import fox.rendering.base.vertex_array;
import fox.rendering.base.frame_buffer;

export namespace fox::gfx::api::gl
{
    template<typename T>
    constexpr auto map_type             () -> glf::VertexArray::Attribute::Type
    {
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::int8_t   >) return glf::VertexArray::Attribute::Type::Byte           ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::uint8_t  >) return glf::VertexArray::Attribute::Type::UnsignedByte   ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::int16_t  >) return glf::VertexArray::Attribute::Type::Short          ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::uint16_t >) return glf::VertexArray::Attribute::Type::UnsignedShort  ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::int32_t  >) return glf::VertexArray::Attribute::Type::Integer        ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::uint32_t >) return glf::VertexArray::Attribute::Type::UnsignedInteger;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::float32_t>) return glf::VertexArray::Attribute::Type::Float          ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::float64_t>) return glf::VertexArray::Attribute::Type::Double         ;
    }

    auto map_texture_format_base        (api::Texture::Format format) -> glf::Texture::BaseFormat
    {
        switch (format)
        {
            case api::Texture::Format::R8_UNORM    :
            case api::Texture::Format::R16_UNORM   :
            case api::Texture::Format::R8_SNORM    :
            case api::Texture::Format::R16_SNORM   :
            case api::Texture::Format::R16_FLOAT   :
            case api::Texture::Format::R32_FLOAT   : return glf::Texture::BaseFormat::R;
            
            case api::Texture::Format::RG8_UNORM   :
            case api::Texture::Format::RG16_UNORM  :
            case api::Texture::Format::RG8_SNORM   :
            case api::Texture::Format::RG16_SNORM  :
            case api::Texture::Format::RG16_FLOAT  :
            case api::Texture::Format::RG32_FLOAT  : return glf::Texture::BaseFormat::RG;
            
            case api::Texture::Format::RGB8_UNORM  :
            case api::Texture::Format::RGB16_UNORM :
            case api::Texture::Format::RGB8_SNORM  :
            case api::Texture::Format::RGB16_SNORM :
            case api::Texture::Format::RGB8_SRGB   :
            case api::Texture::Format::RGB16_FLOAT :
            case api::Texture::Format::RGB32_FLOAT : return glf::Texture::BaseFormat::RGB;
            
            case api::Texture::Format::RGBA8_UNORM :
            case api::Texture::Format::RGBA16_UNORM:
            case api::Texture::Format::RGBA8_SNORM :
            case api::Texture::Format::RGBA16_SNORM:
            case api::Texture::Format::RGBA8_SRGB  :
            case api::Texture::Format::RGBA16_FLOAT:
            case api::Texture::Format::RGBA32_FLOAT: return glf::Texture::BaseFormat::RGBA;
            
            case api::Texture::Format::D16_UNORM   :
            case api::Texture::Format::D24_UNORM   :
            case api::Texture::Format::D32_FLOAT   : return glf::Texture::BaseFormat::D;
            
            case api::Texture::Format::S8_UINT     : return glf::Texture::BaseFormat::S;

            default: throw std::invalid_argument{ "Invalid texture format!" };
        }
    }
    auto map_texture_format             (api::Texture::Format format) -> glf::Texture::Format
    {
        switch (format)
        {
            case api::Texture::Format::R8_UNORM         : return glf::Texture::Format::R8_UNORM;
            case api::Texture::Format::RG8_UNORM        : return glf::Texture::Format::RG8_UNORM;
            case api::Texture::Format::RGB8_UNORM       : return glf::Texture::Format::RGB8_UNORM;
            case api::Texture::Format::RGBA8_UNORM      : return glf::Texture::Format::RGBA8_UNORM;
            case api::Texture::Format::R16_UNORM        : return glf::Texture::Format::R16_UNORM;
            case api::Texture::Format::RG16_UNORM       : return glf::Texture::Format::RG16_UNORM;
            case api::Texture::Format::RGB16_UNORM      : return glf::Texture::Format::RGB16_UNORM;
            case api::Texture::Format::RGBA16_UNORM     : return glf::Texture::Format::RGBA16_UNORM;
            case api::Texture::Format::R8_SNORM         : return glf::Texture::Format::R8_SNORM;
            case api::Texture::Format::RG8_SNORM        : return glf::Texture::Format::RG8_SNORM;
            case api::Texture::Format::RGB8_SNORM       : return glf::Texture::Format::RGB8_SNORM;
            case api::Texture::Format::RGBA8_SNORM      : return glf::Texture::Format::RGBA8_SNORM;
            case api::Texture::Format::R16_SNORM        : return glf::Texture::Format::R16_SNORM;
            case api::Texture::Format::RG16_SNORM       : return glf::Texture::Format::RG16_SNORM;
            case api::Texture::Format::RGB16_SNORM      : return glf::Texture::Format::RGB16_SNORM;
            case api::Texture::Format::RGBA16_SNORM     : return glf::Texture::Format::RGBA16_SNORM;
            case api::Texture::Format::RGB8_SRGB        : return glf::Texture::Format::RGB8_SRGB;
            case api::Texture::Format::RGBA8_SRGB       : return glf::Texture::Format::RGBA8_SRGB;
            case api::Texture::Format::R16_FLOAT        : return glf::Texture::Format::R16_FLOAT;
            case api::Texture::Format::RG16_FLOAT       : return glf::Texture::Format::RG16_FLOAT;
            case api::Texture::Format::RGB16_FLOAT      : return glf::Texture::Format::RGB16_FLOAT;
            case api::Texture::Format::RGBA16_FLOAT     : return glf::Texture::Format::RGBA16_FLOAT;
            case api::Texture::Format::R32_FLOAT        : return glf::Texture::Format::R32_FLOAT;
            case api::Texture::Format::RG32_FLOAT       : return glf::Texture::Format::RG32_FLOAT;
            case api::Texture::Format::RGB32_FLOAT      : return glf::Texture::Format::RGB32_FLOAT;
            case api::Texture::Format::RGBA32_FLOAT     : return glf::Texture::Format::RGBA32_FLOAT;
            case api::Texture::Format::D16_UNORM        : return glf::Texture::Format::D16_UNORM;
            case api::Texture::Format::D24_UNORM        : return glf::Texture::Format::D24_UNORM;
            case api::Texture::Format::D32_FLOAT        : return glf::Texture::Format::D32_FLOAT;
            case api::Texture::Format::D24_UNORM_S8_UINT: return glf::Texture::Format::D24_UNORM_S8_UINT;
            case api::Texture::Format::D32_FLOAT_S8_UINT: return glf::Texture::Format::D32_FLOAT_S8_UINT;
            case api::Texture::Format::S8_UINT          : return glf::Texture::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_texture_format_type        (api::Texture::Format format) -> glf::PixelData::Type
    {
        switch (format)
        {
            case api::Texture::Format::R8_UNORM: 
            case api::Texture::Format::RG8_UNORM: 
            case api::Texture::Format::RGB8_UNORM: 
            case api::Texture::Format::RGBA8_UNORM:       return glf::PixelData::Type::UnsignedByte;

            case api::Texture::Format::R16_UNORM: 
            case api::Texture::Format::RG16_UNORM: 
            case api::Texture::Format::RGB16_UNORM: 
            case api::Texture::Format::RGBA16_UNORM:      return glf::PixelData::Type::UnsignedShort;

            case api::Texture::Format::R8_SNORM: 
            case api::Texture::Format::RG8_SNORM: 
            case api::Texture::Format::RGB8_SNORM: 
            case api::Texture::Format::RGBA8_SNORM:       return glf::PixelData::Type::Byte;

            case api::Texture::Format::R16_SNORM: 
            case api::Texture::Format::RG16_SNORM: 
            case api::Texture::Format::RGB16_SNORM: 
            case api::Texture::Format::RGBA16_SNORM:      return glf::PixelData::Type::Short;

            case api::Texture::Format::RGB8_SRGB: 
            case api::Texture::Format::RGBA8_SRGB:        return glf::PixelData::Type::UnsignedByte;
            
            case api::Texture::Format::R16_FLOAT: 
            case api::Texture::Format::RG16_FLOAT: 
            case api::Texture::Format::RGB16_FLOAT: 
            case api::Texture::Format::RGBA16_FLOAT:      return glf::PixelData::Type::HalfFloat;
            
            case api::Texture::Format::R32_FLOAT: 
            case api::Texture::Format::RG32_FLOAT: 
            case api::Texture::Format::RGB32_FLOAT: 
            case api::Texture::Format::RGBA32_FLOAT:      return glf::PixelData::Type::Float;
            
            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_texture_min_filter         (api::Texture::Filter filter) -> glf::Texture::MinificationFilter
    {
        switch (filter)
        {
            case api::Texture::Filter::None:      return glf::Texture::MinificationFilter::Nearest;
            case api::Texture::Filter::Nearest:   return glf::Texture::MinificationFilter::NearestMipmapNearest;
            case api::Texture::Filter::Bilinear:  return glf::Texture::MinificationFilter::LinearMipmapNearest;
            case api::Texture::Filter::Trilinear: return glf::Texture::MinificationFilter::LinearMipmapLinear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    auto map_texture_mag_filter         (api::Texture::Filter filter) -> glf::Texture::MagnificationFilter
    {
        switch (filter)
        {
            case api::Texture::Filter::None:      return glf::Texture::MagnificationFilter::Nearest;
            case api::Texture::Filter::Nearest:   return glf::Texture::MagnificationFilter::Nearest;
            case api::Texture::Filter::Bilinear:  return glf::Texture::MagnificationFilter::Linear;
            case api::Texture::Filter::Trilinear: return glf::Texture::MagnificationFilter::Linear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    auto map_texture_wrapping           (api::Texture::Wrapping wrapping) -> glf::Texture::Wrapping
    {
        switch (wrapping)
        {
            case api::Texture::Wrapping::ClampToEdge:         return glf::Texture::Wrapping::ClampToEdge;
            case api::Texture::Wrapping::ClampToBorder:       return glf::Texture::Wrapping::ClampToBorder;
            case api::Texture::Wrapping::Repeat:              return glf::Texture::Wrapping::Repeat;
            case api::Texture::Wrapping::MirroredRepeat:      return glf::Texture::Wrapping::MirroredRepeat;
            case api::Texture::Wrapping::MirroredClampToEdge: return glf::Texture::Wrapping::MirroredClampToEdge;

            default: throw std::invalid_argument{ "Invalid wrapping!" };
        }
    }
    auto map_render_buffer_format       (api::RenderBuffer::Format format) -> glf::RenderBuffer::Format
    {
        switch (format)
        {
            case api::RenderBuffer::Format::R8_UNORM:          return glf::RenderBuffer::Format::R8;
            case api::RenderBuffer::Format::RG8_UNORM:         return glf::RenderBuffer::Format::RG8;
            case api::RenderBuffer::Format::RGB8_UNORM:        return glf::RenderBuffer::Format::RGB8;
            case api::RenderBuffer::Format::RGBA8_UNORM:       return glf::RenderBuffer::Format::RGBA8;
            case api::RenderBuffer::Format::RGBA8_SRGB:        return glf::RenderBuffer::Format::RGBA8_SRGB;
            case api::RenderBuffer::Format::D16_UNORM:         return glf::RenderBuffer::Format::D16_UNORM;
            case api::RenderBuffer::Format::D24_UNORM:         return glf::RenderBuffer::Format::D24_UNORM;
            case api::RenderBuffer::Format::D32_FLOAT:         return glf::RenderBuffer::Format::D32_FLOAT;
            case api::RenderBuffer::Format::D24_UNORM_S8_UINT: return glf::RenderBuffer::Format::D24_UNORM_S8_UINT;
            case api::RenderBuffer::Format::D32_FLOAT_S8_UINT: return glf::RenderBuffer::Format::D32_FLOAT_S8_UINT;
            case api::RenderBuffer::Format::S8_UINT:           return glf::RenderBuffer::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_cubemap_texture_format_base(api::Cubemap::Format format) -> glf::Texture::BaseFormat
    {
        switch (format)
        {
            case api::Cubemap::Format::R8_UNORM    :
            case api::Cubemap::Format::R16_UNORM   :
            case api::Cubemap::Format::R8_SNORM    :
            case api::Cubemap::Format::R16_SNORM   :
            case api::Cubemap::Format::R16_FLOAT   :
            case api::Cubemap::Format::R32_FLOAT   : return glf::Texture::BaseFormat::R;
            
            case api::Cubemap::Format::RG8_UNORM   :
            case api::Cubemap::Format::RG16_UNORM  :
            case api::Cubemap::Format::RG8_SNORM   :
            case api::Cubemap::Format::RG16_SNORM  :
            case api::Cubemap::Format::RG16_FLOAT  :
            case api::Cubemap::Format::RG32_FLOAT  : return glf::Texture::BaseFormat::RG;
            
            case api::Cubemap::Format::RGB8_UNORM  :
            case api::Cubemap::Format::RGB16_UNORM :
            case api::Cubemap::Format::RGB8_SNORM  :
            case api::Cubemap::Format::RGB16_SNORM :
            case api::Cubemap::Format::RGB8_SRGB   :
            case api::Cubemap::Format::RGB16_FLOAT :
            case api::Cubemap::Format::RGB32_FLOAT : return glf::Texture::BaseFormat::RGB;
            
            case api::Cubemap::Format::RGBA8_UNORM :
            case api::Cubemap::Format::RGBA16_UNORM:
            case api::Cubemap::Format::RGBA8_SNORM :
            case api::Cubemap::Format::RGBA16_SNORM:
            case api::Cubemap::Format::RGBA8_SRGB  :
            case api::Cubemap::Format::RGBA16_FLOAT:
            case api::Cubemap::Format::RGBA32_FLOAT: return glf::Texture::BaseFormat::RGBA;
            
            case api::Cubemap::Format::D16_UNORM   :
            case api::Cubemap::Format::D24_UNORM   :
            case api::Cubemap::Format::D32_FLOAT   : return glf::Texture::BaseFormat::D;
            
            case api::Cubemap::Format::S8_UINT     : return glf::Texture::BaseFormat::S;

            default: throw std::invalid_argument{ "Invalid cubemap format!" };
        }
    }
    auto map_cubemap_texture_format     (api::Cubemap::Format format) -> glf::Texture::Format
    {
        switch (format)
        {
            case api::Cubemap::Format::R8_UNORM:          return glf::Texture::Format::R8_UNORM;
            case api::Cubemap::Format::RG8_UNORM:         return glf::Texture::Format::RG8_UNORM;
            case api::Cubemap::Format::RGB8_UNORM:        return glf::Texture::Format::RGB8_UNORM;
            case api::Cubemap::Format::RGBA8_UNORM:       return glf::Texture::Format::RGBA8_UNORM;
            
            case api::Cubemap::Format::R16_UNORM:         return glf::Texture::Format::R16_UNORM;
            case api::Cubemap::Format::RG16_UNORM:        return glf::Texture::Format::RG16_UNORM;
            case api::Cubemap::Format::RGB16_UNORM:       return glf::Texture::Format::RGB16_UNORM;
            case api::Cubemap::Format::RGBA16_UNORM:      return glf::Texture::Format::RGBA16_UNORM;
            
            case api::Cubemap::Format::R8_SNORM:          return glf::Texture::Format::R8_SNORM;
            case api::Cubemap::Format::RG8_SNORM:         return glf::Texture::Format::RG8_SNORM;
            case api::Cubemap::Format::RGB8_SNORM:        return glf::Texture::Format::RGB8_SNORM;
            case api::Cubemap::Format::RGBA8_SNORM:       return glf::Texture::Format::RGBA8_SNORM;
            
            case api::Cubemap::Format::R16_SNORM:         return glf::Texture::Format::R16_SNORM;
            case api::Cubemap::Format::RG16_SNORM:        return glf::Texture::Format::RG16_SNORM;
            case api::Cubemap::Format::RGB16_SNORM:       return glf::Texture::Format::RGB16_SNORM;
            case api::Cubemap::Format::RGBA16_SNORM:      return glf::Texture::Format::RGBA16_SNORM;
            
            case api::Cubemap::Format::RGB8_SRGB:         return glf::Texture::Format::RGB8_SRGB;
            case api::Cubemap::Format::RGBA8_SRGB:        return glf::Texture::Format::RGBA8_SRGB;
            
            case api::Cubemap::Format::R16_FLOAT:         return glf::Texture::Format::R16_FLOAT;
            case api::Cubemap::Format::RG16_FLOAT:        return glf::Texture::Format::RG16_FLOAT;
            case api::Cubemap::Format::RGB16_FLOAT:       return glf::Texture::Format::RGB16_FLOAT;
            case api::Cubemap::Format::RGBA16_FLOAT:      return glf::Texture::Format::RGBA16_FLOAT;
            
            case api::Cubemap::Format::R32_FLOAT:         return glf::Texture::Format::R32_FLOAT;
            case api::Cubemap::Format::RG32_FLOAT:        return glf::Texture::Format::RG32_FLOAT;
            case api::Cubemap::Format::RGB32_FLOAT:       return glf::Texture::Format::RGB32_FLOAT;
            case api::Cubemap::Format::RGBA32_FLOAT:      return glf::Texture::Format::RGBA32_FLOAT;
            
            case api::Cubemap::Format::D16_UNORM:         return glf::Texture::Format::D16_UNORM;
            case api::Cubemap::Format::D24_UNORM:         return glf::Texture::Format::D24_UNORM;
            case api::Cubemap::Format::D32_FLOAT:         return glf::Texture::Format::D32_FLOAT;
            
            case api::Cubemap::Format::D24_UNORM_S8_UINT: return glf::Texture::Format::D24_UNORM_S8_UINT;
            case api::Cubemap::Format::D32_FLOAT_S8_UINT: return glf::Texture::Format::D32_FLOAT_S8_UINT;
            
            case api::Cubemap::Format::S8_UINT:           return glf::Texture::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_cubemap_texture_format_type(api::Cubemap::Format format) -> glf::PixelData::Type
    {
        switch (format)
        {
            case api::Cubemap::Format::R8_UNORM: 
            case api::Cubemap::Format::RG8_UNORM: 
            case api::Cubemap::Format::RGB8_UNORM: 
            case api::Cubemap::Format::RGBA8_UNORM:       return glf::PixelData::Type::UnsignedByte;

            case api::Cubemap::Format::R16_UNORM:
            case api::Cubemap::Format::RG16_UNORM:
            case api::Cubemap::Format::RGB16_UNORM:
            case api::Cubemap::Format::RGBA16_UNORM:      return glf::PixelData::Type::UnsignedShort;

            case api::Cubemap::Format::R8_SNORM:
            case api::Cubemap::Format::RG8_SNORM:
            case api::Cubemap::Format::RGB8_SNORM:
            case api::Cubemap::Format::RGBA8_SNORM:       return glf::PixelData::Type::Byte;

            case api::Cubemap::Format::R16_SNORM:
            case api::Cubemap::Format::RG16_SNORM:
            case api::Cubemap::Format::RGB16_SNORM:
            case api::Cubemap::Format::RGBA16_SNORM:      return glf::PixelData::Type::Short;

            case api::Cubemap::Format::RGB8_SRGB: 
            case api::Cubemap::Format::RGBA8_SRGB:        return glf::PixelData::Type::UnsignedByte;
            
            case api::Cubemap::Format::R16_FLOAT: 
            case api::Cubemap::Format::RG16_FLOAT: 
            case api::Cubemap::Format::RGB16_FLOAT: 
            case api::Cubemap::Format::RGBA16_FLOAT:      return glf::PixelData::Type::HalfFloat;
            
            case api::Cubemap::Format::R32_FLOAT:
            case api::Cubemap::Format::RG32_FLOAT:
            case api::Cubemap::Format::RGB32_FLOAT:
            case api::Cubemap::Format::RGBA32_FLOAT:      return glf::PixelData::Type::Float;
            
            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_frame_buffer_target        (api::FrameBuffer::Target  target) -> glf::FrameBuffer::Target
    {
        switch (target)
        {
            case api::FrameBuffer::Target::Read:  return glf::FrameBuffer::Target::Read;
            case api::FrameBuffer::Target::Write: return glf::FrameBuffer::Target::Write;

            default: throw std::invalid_argument{ "Invalid framebuffer target!" };
        }
    }
    auto map_frame_buffer_attachment    (api::FrameBuffer::Attachment attachment) -> glf::FrameBuffer::Attachment
    {
        switch (attachment)
        {
            case api::FrameBuffer::Attachment::Color0:       return glf::FrameBuffer::Attachment::Color0; 
            case api::FrameBuffer::Attachment::Color1:       return glf::FrameBuffer::Attachment::Color1; 
            case api::FrameBuffer::Attachment::Color2:       return glf::FrameBuffer::Attachment::Color2; 
            case api::FrameBuffer::Attachment::Color3:       return glf::FrameBuffer::Attachment::Color3; 
            case api::FrameBuffer::Attachment::Color4:       return glf::FrameBuffer::Attachment::Color4; 
            case api::FrameBuffer::Attachment::Color5:       return glf::FrameBuffer::Attachment::Color5; 
            case api::FrameBuffer::Attachment::Color6:       return glf::FrameBuffer::Attachment::Color6; 
            case api::FrameBuffer::Attachment::Color7:       return glf::FrameBuffer::Attachment::Color7; 
            
            case api::FrameBuffer::Attachment::Depth:        return glf::FrameBuffer::Attachment::Depth;
            case api::FrameBuffer::Attachment::Stencil:      return glf::FrameBuffer::Attachment::Stencil;
            case api::FrameBuffer::Attachment::DepthStencil: return glf::FrameBuffer::Attachment::DepthStencil;

            default: throw std::invalid_argument{ "Invalid framebuffer attachment!" };
        }
    }
    auto map_program_stage              (api::Shader::Stage stage) -> glf::Program::Stage
    {
        switch (stage)
        {
            case api::Shader::Stage::Vertex:                 return glf::Program::Stage::Vertex;
            case api::Shader::Stage::TessellationControl:    return glf::Program::Stage::TessellationControl;
            case api::Shader::Stage::TessellationEvaluation: return glf::Program::Stage::TessellationEvaluation;
            case api::Shader::Stage::Geometry:               return glf::Program::Stage::Geometry;
            case api::Shader::Stage::Fragment:               return glf::Program::Stage::Fragment;
            case api::Shader::Stage::Compute:                return glf::Program::Stage::Compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }                                                                      
    auto map_shader_type                (api::Shader::Stage stage) -> glf::Shader::Type
    {
        switch (stage)
        {
            case api::Shader::Stage::Vertex:                 return glf::Shader::Type::Vertex;
            case api::Shader::Stage::TessellationControl:    return glf::Shader::Type::TessellationControl;
            case api::Shader::Stage::TessellationEvaluation: return glf::Shader::Type::TessellationEvaluation;
            case api::Shader::Stage::Geometry:               return glf::Shader::Type::Geometry;
            case api::Shader::Stage::Fragment:               return glf::Shader::Type::Fragment;
            case api::Shader::Stage::Compute:                return glf::Shader::Type::Compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }
    auto map_query_target               (api::Query::Target target) -> glf::Query::Target
    {
        switch (target)
        {
            case api::Query::Target::AnySamplesPassed                        : return glf::Query::Target::AnySamplesPassed;
            case api::Query::Target::AnySamplesPassedConservative            : return glf::Query::Target::AnySamplesPassedConservative;
            case api::Query::Target::ClippingInputPrimitives                 : return glf::Query::Target::ClippingInputPrimitives;
            case api::Query::Target::ClippingOutputPrimitives                : return glf::Query::Target::ClippingOutputPrimitives;
            case api::Query::Target::ComputeShaderInvocations                : return glf::Query::Target::ComputeShaderInvocations;
            case api::Query::Target::FragmentShaderInvocations               : return glf::Query::Target::FragmentShaderInvocations;
            case api::Query::Target::GeometryShaderInvocations               : return glf::Query::Target::GeometryShaderInvocations;
            case api::Query::Target::GeometryShaderPrimitivesEmitted         : return glf::Query::Target::GeometryShaderPrimitivesEmitted;
            case api::Query::Target::PrimitivesGenerated                     : return glf::Query::Target::PrimitivesGenerated;
            case api::Query::Target::PrimitivesSubmitted                     : return glf::Query::Target::PrimitivesSubmitted;
            case api::Query::Target::SamplesPassed                           : return glf::Query::Target::SamplesPassed;
            case api::Query::Target::TessellationControlShaderPatches        : return glf::Query::Target::TessellationControlShaderPatches;
            case api::Query::Target::TessellationEvaluationShaderInvocations : return glf::Query::Target::TessellationEvaluationShaderInvocations;
            case api::Query::Target::TimeElapsed                             : return glf::Query::Target::TimeElapsed;
            case api::Query::Target::Timestamp                               : return glf::Query::Target::Timestamp;
            case api::Query::Target::TransformFeedbackOverflow               : return glf::Query::Target::TransformFeedbackOverflow;
            case api::Query::Target::TransformFeedbackPrimitivesWritten      : return glf::Query::Target::TransformFeedbackPrimitivesWritten;
            case api::Query::Target::TransformFeedbackStreamOverflow         : return glf::Query::Target::TransformFeedbackStreamOverflow;
            case api::Query::Target::VertexShaderInvocations                 : return glf::Query::Target::VertexShaderInvocations;
            case api::Query::Target::VerticesSubmitted                       : return glf::Query::Target::VerticesSubmitted;

            default: throw std::invalid_argument{ "Invalid target!" };
        }
    }
    auto map_depth_function             (api::RenderState::DepthFunction depthFunction) -> glf::DepthFunction
    {
        switch (depthFunction)
        {
            case api::RenderState::DepthFunction::Always:       return glf::DepthFunction::Always;
            case api::RenderState::DepthFunction::Never:        return glf::DepthFunction::Never;
            case api::RenderState::DepthFunction::Equal:        return glf::DepthFunction::Equal;
            case api::RenderState::DepthFunction::NotEqual:     return glf::DepthFunction::NotEqual;
            case api::RenderState::DepthFunction::Less:         return glf::DepthFunction::Less;
            case api::RenderState::DepthFunction::LessEqual:    return glf::DepthFunction::LessEqual;
            case api::RenderState::DepthFunction::Greater:      return glf::DepthFunction::Greater;
            case api::RenderState::DepthFunction::GreaterEqual: return glf::DepthFunction::GreaterEqual;

            default: throw std::invalid_argument{ "Invalid depth function!" };
        }
    }
    auto map_culling_face               (api::RenderState::FaceCulling cullingFace) -> glf::Culling::Facet
    {
        switch (cullingFace)
        {
            case api::RenderState::FaceCulling::Front:     return glf::Culling::Facet::Front;
            case api::RenderState::FaceCulling::Back:      return glf::Culling::Facet::Back;
            case api::RenderState::FaceCulling::FrontBack: return glf::Culling::Facet::FrontBack;

            default: throw std::invalid_argument{ "Invalid culling face!" };
        }
    }
}
